#include "Storage.h"
#include <regex>


Storage::Storage(const std::string& path, unsigned int countOfSteps)
:_countOfSteps(countOfSteps),_currGameStep(0){
    std::fstream file;
    file.open(path);
    if(!file)
        _isWritable = false;
    else {
        _isWritable = true;
        _out.open(path,std::ios::app);
    }
    file.close();
    _currGame = new char*[_countOfSteps];
    for (unsigned int i = 0; i < _countOfSteps; ++i) {
        _currGame[i] = new char[COUNT_OF_PLAYERS];
    }

    _in.open(path);
    _winnerOfPrev = 0;
    if(_in.is_open()) // need to get a last game
    {
        std::regex reg(R"(([0-9]+))");
        std::string str;
        std::iostream::pos_type point = 0;
        std::iostream::pos_type temp = 0;
        unsigned int pos = 0;
        _correctInput = true;

        while (true){
            std::getline(_in,str);
            pos++;
            if(std::regex_match(str,reg)){ // end of record of game - number of winner
                temp = _in.tellg() - point;
                point = _in.tellg();
                _countOfStepsPrev = pos;
                pos = 0;
            }
        if(_in.eof())
            break;
        }
        if(point == 0) // no history. File corrupted
            _correctInput = false;
        else { // record history of last game in memory
            _in.clear();
            _countOfStepsPrev -= 2; // last number and empty string
            _in.seekg(point - temp);
            std::getline(_in, str); // we moved to names of strategies and go to next line - choises

            _prevGame = new char *[_countOfStepsPrev];
            for (unsigned int i = 0; i < _countOfStepsPrev; ++i) {
                std::getline(_in, str);
                _prevGame[i] = new char[COUNT_OF_PLAYERS];

                for (unsigned int j = 0; j < COUNT_OF_PLAYERS; ++j) {
                    if (str.length() != COUNT_OF_PLAYERS || (str[j] != 'C' && str[j] != 'D')) {
                        _correctInput = false;
                        break;
                    }
                    _prevGame[i][j] = str[j];
                }
            }
            std::getline(_in, str);
            for (char i: str) {
                _winnerOfPrev = _winnerOfPrev * 10 + (i - '0');
            }
        }
    }else
        _correctInput = false; // file doesn't opened => no data
}

void Storage::recordThePlayers(const std::vector<std::string>& players) {
    if(!_isWritable)
        return;
    for (auto & player : players) {
        _out << player << " ";
    }
    _out << std::endl;
}

void Storage::recordTheStep(const char *code) {
    if(_currGameStep == _countOfSteps)
        _currGameStep = 0;
    for (unsigned int i = 0; i < COUNT_OF_PLAYERS; ++i) {
        _currGame[_currGameStep][i] = code[i];
    }
    _currGameStep++;
}

void Storage::recordTheGame(const unsigned int *points) {
    if(!_isWritable)
        return;

    for (unsigned int i = 0; i < _countOfSteps; ++i) {
        for (unsigned int j = 0; j < COUNT_OF_PLAYERS; ++j) {
            _out << _currGame[i][j];
        }
        _out << std::endl;
    }
    unsigned int maxPoints = 0;
    unsigned int pos = 0;
    for (unsigned int i = 0; i < COUNT_OF_PLAYERS; ++i) {
        if(points[i] > maxPoints){
            maxPoints = points[i];
            pos = i+1;
        }
    }
    _out << pos << std::endl;
}

std::string Storage::getLastStep() {
    if(_currGameStep == 0)
        return NO_DATA;
    std::string res;
    for (unsigned int i = 0; i < COUNT_OF_PLAYERS; ++i) {
        res.push_back(_currGame[_currGameStep-1][i]);
    }
    return res;
}

std::string Storage::getStepFromPrev(unsigned int pos) {
    if(!_correctInput || pos >= _countOfStepsPrev)
        return NO_DATA;
    std::string res;
    for (unsigned int i = 0; i < COUNT_OF_PLAYERS; ++i) {
        res.push_back(_prevGame[pos][i]);
    }
    return res;
}

Storage::~Storage() {
    if(_isWritable)
        _out.close();
    if(_in.is_open()) {
        for (unsigned int i = 0; i < _countOfStepsPrev; ++i) {
            delete[] _prevGame[i];
        }
        delete[] _prevGame;
        _in.close();
    }

    for (unsigned int i = 0; i < _countOfSteps; ++i) {
       delete[] _currGame[i];
    }
    delete[] _currGame;
}
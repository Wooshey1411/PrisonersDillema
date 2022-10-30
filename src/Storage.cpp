#include "Storage.h"
#include <fstream>

Storage::Storage(const std::string& path, unsigned int countOfSteps)
:_path(path),_countOfSteps(countOfSteps),_currGameStep(0){
    if (path == noData)
        _pathExists = false;
    else
        _pathExists = true;
    _currGame = new char*[_countOfSteps];
    for (unsigned int i = 0; i < _countOfSteps; ++i) {
        _currGame[i] = new char[countOfPlayers];
    }

}

void Storage::recordTheStep(char *code) {
    if(_currGameStep == _countOfSteps)
        _currGameStep = 0;
    for (unsigned int i = 0; i < countOfPlayers; ++i) {
        _currGame[_currGameStep][i] = code[i];
    }
    _currGameStep++;
}

std::string Storage::getPrevStep() {
    if (_currGameStep==0)
        return noData;
    std::string str = "";
    for (unsigned int i = 0; i < countOfPlayers; ++i) {
        str.push_back(_currGame[_currGameStep-1][i]);
    }
    return str;
}

void Storage::recordTheGame() {
    if(!_pathExists)
        return;
    std::ofstream out;
    out.open(_path);
    if(!out.is_open()){
        std::cout << "Data file doesn't exist! Game wouldn't be write";
        return;
    }



    for (unsigned int i = 0; i < _countOfSteps; ++i) {
        for (unsigned int j = 0; j < countOfPlayers; ++j) {
            out << _currGame[i][j];
        }
        out << std::endl;
    }
}

Storage::~Storage() {
    for (unsigned int i = 0; i < _countOfSteps; ++i) {
       delete[] _currGame[i];
    }
    delete[] _currGame;
}
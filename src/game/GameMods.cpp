#include "GameMods.h"

void FastGame::organizeTheGame() {
    _storage->recordThePlayers(getNames());

    for (unsigned int i = 0; i < _countOfSteps; ++i) {
        step();
    }
    _storage->recordTheGame(_points);
}

FastGame::~FastGame()  {
    delete[] _points;
    delete[] _code;
}

bool DetailedGame::detailedStep(unsigned int stepNum) {
    std::string in;
    std::cin >> in;
   // std::cin >> in;
   if (in == "quit")
       return true;
    std::cout << "step:" << stepNum << " " << std::endl;
    step();
    std::cout << "selection of strategies: ";
    for (unsigned int i = 0; i < countOfPlayers; ++i) {
        std::cout << _code[i] << " ";
    }
    std::cout << "points earned per step: ";
    for (unsigned int i = 0; i < countOfPlayers; ++i) {
            if (_code[i] == 'C')
                std::cout << _matrix.getValue(_code,'C') << " ";
            else
                std::cout << _matrix.getValue(_code,'D') << " ";
    }
    std::cout << "points in sum: ";
    printPoints();
    return false;
}

void DetailedGame::organizeTheGame() {
    _storage->recordThePlayers(getNames());
    for (unsigned int i = 0; i < _countOfSteps; ++i) {
        bool stopper = detailedStep(i+1);
        if(stopper)
            break;
    }
    _storage->recordTheGame(_points);
}

DetailedGame::~DetailedGame() {
    delete[] _points;
    delete[] _code;
}

void TournamentGame::addPlayers() {
    _factory.getAllStrategies(_allStrategies);
}

void TournamentGame::addPlayers(const std::vector<std::string>& players) {
    for (auto & player : players) {
        _allStrategies.push_back(_factory.createStrategyByName(player));
    }
}

void TournamentGame::organizeTheGame() {
    unsigned int maxPoints = 0;
    std::string nameOfBestPlayer;


    for (unsigned int i = 0; i < _allStrategies.size() - 2; ++i) {
        for (unsigned int j = i+1; j < _allStrategies.size() - 1; ++j) {
            for (unsigned int k = j+1; k < _allStrategies.size(); ++k) {

                addPlayer(_allStrategies[i].name);
                addPlayer(_allStrategies[j].name);
                addPlayer(_allStrategies[k].name);
                _storage->recordThePlayers(getNames());
                for (unsigned int l = 0; l < _countOfSteps; ++l) {
                    step();
                }

                std::cout << "Players: ";
                for (unsigned int l = 0; l < countOfPlayers; ++l) {
                    std::cout << _players[l].name << " ";
                    if(_points[l] > maxPoints){
                        maxPoints = _points[l];
                        nameOfBestPlayer = _players[l].name;
                    }
                }
                _storage->recordTheGame(_points);
                std::cout << "Points: ";
                for (unsigned int l = 0; l < countOfPlayers; ++l) {
                    std:: cout << _points[l] << " ";
                    _points[l] = 0;
                    _players.pop_back();
                }
                std::cout << std::endl;
            }
        }
    }

    std::cout << "Best player:" << nameOfBestPlayer << " his points:" << maxPoints << std::endl;

}

TournamentGame::~TournamentGame() {
    delete[] _points;
    delete[] _code;
}
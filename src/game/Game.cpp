#include "Game.h"

Game::Game(const std::string& pathToMatrix,unsigned int countOfSteps)
:_countOfSteps(countOfSteps){
    _matrix.fillMatrixFromFile(pathToMatrix);
    _points = new unsigned int[countOfPlayers];
    _code = new char[countOfPlayers+1];
    for (unsigned int i = 0; i < countOfPlayers; ++i) {
        _points[i] = 0;
    }
    _code[countOfPlayers] = '\0';
}

void Game::addPlayer(const std::string& name) {
    _players.push_back(_factory.createStrategyByName(name));
}

void Game::step() {
    for (unsigned int i = 0; i < countOfPlayers; ++i) {
        _code[i] = _players[i].strategy->step();
    }

    for (unsigned int i = 0; i < countOfPlayers; ++i) {
        if (_code[i] == 'C')
            _points[i] += _matrix.getValue(_code,'C');
        else
            _points[i] += _matrix.getValue(_code,'D');
    }

}


void Game::printPoints() {
    for (unsigned int i = 0; i < countOfPlayers; ++i) {
        std::cout << _points[i] << " ";
    }
    std::cout << std::endl;
}

Game::~Game() {
    delete[] _points;
    delete[] _code;
}
#include "Game.h"

Game::Game(const std::string& pathToMatrix, const std::string& pathToData, unsigned int countOfSteps)
:_countOfSteps(countOfSteps){
    _matrix.fillMatrixFromFile(pathToMatrix);
    _points = new unsigned int[countOfPlayers];
    _code = new char[countOfPlayers+1];
    for (unsigned int i = 0; i < countOfPlayers; ++i) {
        _points[i] = 0;
    }
    _code[countOfPlayers] = '\0';
    _storage = new Storage(pathToData,countOfSteps);
}

void Game::addPlayer(const std::string& name) {
    _players.push_back(_factory.createStrategyByName(name));
}

std::vector<std::string> Game::getNames() {
    std::vector<std::string> names;
    for (auto & _player : _players) {
        names.push_back(_player.name);
    }
    return names;
}

void Game::step() {
    for (unsigned int i = 0; i < countOfPlayers; ++i) {
            _code[i] = _players[i].strategy->step(_storage);
    }

    for (unsigned int i = 0; i < countOfPlayers; ++i) {
        if (_code[i] == 'C')
            _points[i] += _matrix.getValue(_code,'C');
        else
            _points[i] += _matrix.getValue(_code,'D');
    }
    _storage->recordTheStep(_code);
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
#pragma once
#include "../Storage.h"
#include "../strategy/StrategyFactory.h"
#include "../matrix.h"
#include <vector>

inline const int countOfPlayers = 3;

class Game{
protected:
    std::vector<std::shared_ptr<Strategy>> _players;
    DilemmaMatrix _matrix;
    StrategyFactory _factory;
    unsigned int* _points;
    char* _code;
    Storage* _storage;
    void step();
    unsigned int _countOfSteps;
public:
    Game(const std::string& pathToMatrix,unsigned int countOfSteps);
    virtual void organizeTheGame() = 0;
    void addPlayer(const std::string& name);
    void printPoints();
    virtual ~Game();
};
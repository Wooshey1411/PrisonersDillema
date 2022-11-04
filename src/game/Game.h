#pragma once
#include "../strategy/StrategyFactory.h"
#include "../matrix.h"
#include <vector>
#include "../storage/Storage.h"

class Game{
protected:
    std::vector<struct DataAndPointer> _players;
    DilemmaMatrix _matrix;
    StrategyFactory _factory;
    unsigned int* _points;
    char* _code;
    Storage* _storage;
    void step();
    std::vector<std::string> getNames();
    unsigned int _countOfSteps;
public:
    Game(const std::string& pathToMatrix, const std::string& pathToData, unsigned int countOfSteps);
    virtual void organizeTheGame() = 0;
    void addPlayer(const std::string& name);
    void printPoints();
    virtual ~Game();
};
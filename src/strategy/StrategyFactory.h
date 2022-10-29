#pragma once
#include "Strategies.h"
#include <map>

class StrategyFactory{
private:
    std::map<std::string, Strategy* (*)()> strategies;
public:
    StrategyFactory();
    Strategy* createStrategyByName(const std::string& name);
    ~StrategyFactory();
};


#pragma once
#include "Strategies.h"
#include <map>
#include <memory>

class StrategyFactory{
private:
    std::map<std::string, std::shared_ptr<Strategy> (*)()> strategies;
public:
    StrategyFactory();
    std::shared_ptr<Strategy> createStrategyByName(const std::string& name);
    ~StrategyFactory();
};


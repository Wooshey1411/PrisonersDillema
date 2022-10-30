#pragma once
#include "Strategies.h"
#include <map>
#include <memory>
#include <vector>

struct NameAndPointer{
    std::shared_ptr<Strategy> strategy;
    std::string name;
};

class StrategyFactory{
private:
    std::map<std::string, std::shared_ptr<Strategy> (*)()> strategies;
public:
    StrategyFactory();
    struct NameAndPointer createStrategyByName(const std::string& name);
    void getAllStrategies(std::vector<struct NameAndPointer>& container);
    ~StrategyFactory();
};


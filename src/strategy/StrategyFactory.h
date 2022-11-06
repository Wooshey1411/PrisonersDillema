#pragma once
#include "Strategies.h"
#include <map>
#include <memory>
#include <vector>

struct DataAndPointer{
    std::shared_ptr<Strategy> strategy;
    std::string name;
};

class StrategyFactory{
private:
    std::map<std::string, std::shared_ptr<Strategy> (*)()> _strategies;
public:
    StrategyFactory();
    struct DataAndPointer createStrategyByName(const std::string& name);
    void getAllStrategies(std::vector<struct DataAndPointer>& container);
    ~StrategyFactory();
};


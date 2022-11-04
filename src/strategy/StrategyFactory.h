#pragma once
#include "Strategies.h"
#include <map>
#include <memory>
#include <vector>

struct DataAndPointer{
    std::shared_ptr<Strategy> strategy;
    std::string name;
    bool isUseIO;
};

class StrategyFactory{
private:
    std::map<std::string, std::shared_ptr<Strategy> (*)()> strategies;
    std::map<std::string, std::shared_ptr<Strategy> (*)()> strategiesIO;
public:
    StrategyFactory();
    struct DataAndPointer createStrategyByName(const std::string& name);
    void getAllStrategies(std::vector<struct DataAndPointer>& container);
    ~StrategyFactory();
};


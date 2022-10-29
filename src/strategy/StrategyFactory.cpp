#include "StrategyFactory.h"

template<class type>
Strategy* createStrategy(){
    return new type;
}

StrategyFactory::StrategyFactory() {
    strategies["OnlyBetray"] = createStrategy<OnlyBetray>;
    strategies["Random"] = createStrategy<Random>;
    strategies["Alternation"] = createStrategy<Alternation>;
}

StrategyFactory::~StrategyFactory() {}

Strategy *StrategyFactory::createStrategyByName(const std::string& name){
    std::map<std::string, Strategy* (*)()>::iterator it;
    it = strategies.find(name);
    if(it != strategies.end())
    return it->second();
    throw std::runtime_error("StrategyFabric: Strategy with such name doesn't exist");
}

#include "StrategyFactory.h"
#include <memory>

template<class type>
std::shared_ptr<Strategy> createStrategy(){
    auto a = std::make_shared<type>();
    return a;
}

StrategyFactory::StrategyFactory() {
    strategies["OnlyBetray"] = createStrategy<OnlyBetray>;
    strategies["Random"] = createStrategy<Random>;
    strategies["Alternation"] = createStrategy<Alternation>;
}

StrategyFactory::~StrategyFactory() = default;

std::shared_ptr<Strategy> StrategyFactory::createStrategyByName(const std::string& name){
    std::map<std::string, std::shared_ptr<Strategy> (*)()>::iterator it;
    it = strategies.find(name);
    if(it != strategies.end())
      return it->second();
    throw std::runtime_error("StrategyFabric: Strategy with such name doesn't exist");
}

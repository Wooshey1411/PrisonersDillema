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
    strategies["OnlyCooperate"] = createStrategy<OnlyCooperate>;
    strategies["BetrayEveryThird"] = createStrategy<BetrayEveryThird>;
    strategies["Betrayed"] = createStrategy<Betrayed>;
    strategies["Repeater"] = createStrategy<Repeater>;
    strategies["Popular"] = createStrategy<Popular>;
    strategies["Addition"] = createStrategy<Addition>;
}

StrategyFactory::~StrategyFactory() = default;

struct DataAndPointer StrategyFactory::createStrategyByName(const std::string& name){
    std::map<std::string, std::shared_ptr<Strategy> (*)()>::iterator it;
    it = strategies.find(name);
    if(it != strategies.end()) {
        struct DataAndPointer dap = {it->second(),it->first};
        return dap;
    }
    throw std::runtime_error("StrategyFabric: Strategy with such name doesn't exist");
}

void StrategyFactory::getAllStrategies(std::vector<struct DataAndPointer>& container){
    std::map<std::string, std::shared_ptr<Strategy> (*)()>::iterator it;
    it = strategies.begin();
    for (unsigned int i = 0; i < strategies.size(); ++i) {
        struct DataAndPointer val = {it->second(),it->first};
        container.push_back(val);
        it++;
    }
}
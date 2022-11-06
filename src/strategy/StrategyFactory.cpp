#include "StrategyFactory.h"
#include <memory>

template<class type>
std::shared_ptr<Strategy> createStrategy(){
    auto a = std::make_shared<type>();
    return a;
}


StrategyFactory::StrategyFactory() {
    _strategies["OnlyBetray"] = createStrategy<OnlyBetray>;
    _strategies["Random"] = createStrategy<Random>;
    _strategies["Alternation"] = createStrategy<Alternation>;
    _strategies["OnlyCooperate"] = createStrategy<OnlyCooperate>;
    _strategies["BetrayEveryThird"] = createStrategy<BetrayEveryThird>;
    _strategies["Betrayed"] = createStrategy<Betrayed>;
    _strategies["Repeater"] = createStrategy<Repeater>;
    _strategies["Popular"] = createStrategy<Popular>;
    _strategies["Addition"] = createStrategy<Addition>;
}

StrategyFactory::~StrategyFactory() = default;

struct DataAndPointer StrategyFactory::createStrategyByName(const std::string& name){
    std::map<std::string, std::shared_ptr<Strategy> (*)()>::iterator it;
    it = _strategies.find(name);
    if(it != _strategies.end()) {
        struct DataAndPointer dap = {it->second(),it->first};
        return dap;
    }
    throw std::runtime_error("StrategyFabric: Strategy with such name doesn't exist");
}

void StrategyFactory::getAllStrategies(std::vector<struct DataAndPointer>& container){
    std::map<std::string, std::shared_ptr<Strategy> (*)()>::iterator it;
    it = _strategies.begin();
    for (unsigned int i = 0; i < _strategies.size(); ++i) {
        struct DataAndPointer val = {it->second(),it->first};
        container.push_back(val);
        it++;
    }
}
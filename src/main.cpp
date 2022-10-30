#include <iostream>
#include "matrix.h"
#include "strategy/StrategyFactory.h"

int main() {
    StrategyFactory factory = *new StrategyFactory;

    std::shared_ptr<Strategy> s1 = factory.createStrategyByName("Alternation");
    std::shared_ptr<Strategy> s2 = factory.createStrategyByName("Random");
    std::shared_ptr<Strategy> s3 = factory.createStrategyByName("OnlyBetray");
    for (int i = 0; i < 10; ++i) {
        std::cout << s1->step() << " " << s2->step() << " " << s3->step() << std::endl;
    }
    return 0;
}

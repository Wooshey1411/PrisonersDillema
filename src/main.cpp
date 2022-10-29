#include <iostream>
#include "matrix.h"
#include "strategy/StrategyFactory.h"

int main() {
    StrategyFactory factory = *new StrategyFactory;

    Strategy* s1 = factory.createStrategyByName("Alternation");
    Strategy* s2 = factory.createStrategyByName("Random");
    Strategy* s3 = factory.createStrategyByName("OnlyBetray");
    for (int i = 0; i < 10; ++i) {
        std::cout << s1->step() << " " << s2->step() << " " << s3->step() << std::endl;
    }
    return 0;
}

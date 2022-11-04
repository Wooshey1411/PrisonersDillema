#include "Strategies.h"

char OnlyBetray::step() {
    return 'D';
}
OnlyBetray::~OnlyBetray() = default;

OnlyCooperate::~OnlyCooperate() = default;

char OnlyCooperate::step() {
    return 'C';
}

Random::Random(){
    srand(time(nullptr));
}
char Random::step(){
    int num;
    num=rand();
    num %=2;

    if (num == 0)
        return 'C';
    else
        return 'D';
}
Random::~Random() = default;

Alternation::Alternation(){
    prevStep = 'C';
}
char Alternation::step(){
    if (prevStep == 'C'){
        prevStep = 'D';
        return prevStep;
    }else{
        prevStep = 'C';
        return prevStep;
    }
}
Alternation::~Alternation() = default;

BetrayEveryThird::BetrayEveryThird(){
    counter = 1;
}

char BetrayEveryThird::step() {
    if (counter % 3 == 0)
        return 'D';
    else
        return 'C';
}

BetrayEveryThird::~BetrayEveryThird() = default;


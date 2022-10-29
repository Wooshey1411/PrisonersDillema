#include "Strategies.h"

char OnlyBetray::step() {
    return 'D';
}
OnlyBetray::~OnlyBetray() = default;

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
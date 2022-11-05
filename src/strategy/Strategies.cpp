#include "Strategies.h"

char OnlyBetray::step(Storage*) {
    return 'D';
}
OnlyBetray::~OnlyBetray() = default;

OnlyCooperate::~OnlyCooperate() = default;

char OnlyCooperate::step(Storage*) {
    return 'C';
}

Random::Random(){
    srand(time(nullptr));
}
char Random::step(Storage*){
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
char Alternation::step(Storage*){
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
    counter = 0;
}

char BetrayEveryThird::step(Storage*) {
    counter++;
    if (counter % 3 == 0)
        return 'D';
    else
        return 'C';
}

BetrayEveryThird::~BetrayEveryThird() = default;

Betrayed::Betrayed() {
    _isBetrayed = false;
    _isFirstStep = true;
}

char Betrayed::step(Storage* s) {
    if(_isFirstStep) {
        _isFirstStep = false;
        return 'C';
    }
    if(!_isBetrayed) {
        std::string l = s->getLastStep();
        size_t len = l.size();
        for (size_t i = 0; i < len; ++i) {
            if (l[i] == 'D')
                _isBetrayed = true;
        }
    }
    if(_isBetrayed)
        return 'D';
    return 'C';
}

Betrayed::~Betrayed() = default;

Repeater::Repeater():_pos(0){}

char Repeater::step(Storage* s) {
    std::string st = s->getStepFromPrev(_pos);
    if(st == noData)
        return 'C';
    _pos++;
    return st[s->Winner()-1];
}

Repeater::~Repeater() = default;
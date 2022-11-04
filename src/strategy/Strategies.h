#pragma once
#include "Strategy.h"

class OnlyBetray : public Strategy{
public:
    char step(Storage*) override;
    ~OnlyBetray() override;
};

class OnlyCooperate : public Strategy{
public:
    char step(Storage*) override;
    ~OnlyCooperate() override;
};

class Random : public Strategy{
public:
    Random();
    char step(Storage*) override;
    ~Random() override;
};

class Alternation : public Strategy{
private:
    char prevStep;
public:
    Alternation();
    char step(Storage*) override;
    ~Alternation() override;
};

class BetrayEveryThird : public Strategy{
private:
    unsigned int counter;
public:
    BetrayEveryThird();
    char step(Storage*) override;
    ~BetrayEveryThird() override;
};

class Betrayed : public Strategy{
private:
    bool _isBetrayed;
    bool _isFirstStep;
public:
    Betrayed();
    char step(Storage*) override;
    ~Betrayed() override;
};
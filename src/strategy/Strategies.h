#pragma once
#include "Strategy.h"

class OnlyBetray : public Strategy{
public:
    char step() override;
    ~OnlyBetray() override;
};

class Random : public Strategy{
public:
    Random();
    char step() override;
    ~Random() override;
};

class Alternation : public Strategy{
private:
    char prevStep;
public:
    Alternation();
    char step() override;
    ~Alternation() override;
};

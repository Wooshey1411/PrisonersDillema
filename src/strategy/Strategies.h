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
    char _prevStep;
public:
    Alternation();
    char step(Storage*) override;
    ~Alternation() override;
};

class BetrayEveryThird : public Strategy{
private:
    unsigned int _counter;
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

class Repeater : public Strategy{
private:
    unsigned int _pos;
public:
    Repeater();
    char step(Storage*) override;
    ~Repeater() override;
};

class Popular : public Strategy{
private:
    unsigned int _pos;
public:
    Popular();
    char step(Storage *) override;
    ~Popular() override;
};

class Addition : public Strategy{
private:
    unsigned int _pos;
    unsigned int _counter;
public:
    Addition();
    char step(Storage *) override;
    ~Addition() override;
};
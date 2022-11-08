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
public:
    Alternation();
    char step(Storage*) override;
    ~Alternation() override;
private:
    char _prevStep;
};

class BetrayEveryThird : public Strategy{
public:
    BetrayEveryThird();
    char step(Storage*) override;
    ~BetrayEveryThird() override;
private:
    unsigned int _counter;
};

class Betrayed : public Strategy{
public:
    Betrayed();
    char step(Storage*) override;
    ~Betrayed() override;
private:
    bool _isBetrayed;
    bool _isFirstStep;
};

class Repeater : public Strategy{
public:
    Repeater();
    char step(Storage*) override;
    ~Repeater() override;
private:
    unsigned int _pos;
};

class Popular : public Strategy{
public:
    Popular();
    char step(Storage *) override;
    ~Popular() override;
private:
    unsigned int _pos;
};

class Addition : public Strategy{
public:
    Addition();
    char step(Storage *) override;
    ~Addition() override;
private:
    unsigned int _pos;
    unsigned int _counter;
};
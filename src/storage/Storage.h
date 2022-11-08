#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "../Config.h"

class Storage{
public:
    unsigned int Winner() const {return _winnerOfPrev;};

    Storage(const std::string& path, unsigned int countOfSteps);

    std::string getLastStep() const;
    std::string getStepFromPrev(unsigned int pos) const;

    void recordTheStep(const char* code);
    void recordThePlayers(const std::vector<std::string>& players);
    void recordTheGame(const unsigned int *points);

    ~Storage();
private:
    std::ofstream _out;
    std::ifstream _in;
    unsigned int _countOfSteps;
    unsigned int _winnerOfPrev;
    char ** _currGame;
    unsigned int _currGameStep;
    char** _prevGame;
    unsigned int _countOfStepsPrev;
    bool _correctInput;
    bool _isWritable;
};
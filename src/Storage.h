#pragma once
#include <iostream>
#include <vector>
#include "config.h"

class Storage{
private:
    bool _pathExists;
    std::string _path;
    unsigned int _countOfSteps;
    char ** _currGame;
    unsigned int _currGameStep;

public:
    explicit Storage(const std::string& path, unsigned int countOfSteps);
    void recordTheStep(char* code);
    std::string getPrevStep();
    void recordTheGame();
    ~Storage();
};
#pragma once
#include <vector>
#include <iostream>
struct Params{
    std::vector<std::string> players;
    std::string gameMode;
    unsigned int countOfSteps;
    std::string dataPath;
    std::string matrixPath;
};

struct Params getParams(int argc, char* argv[], int& code);

void printHelp();
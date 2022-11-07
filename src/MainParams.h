#pragma once
#include <vector>
#include <iostream>

enum codes{
    SUCCESS_CODE = 0,
    NO_PLAYERS_CODE,
    NO_MODE_CODE,
    OTHER_CODE
};

struct Params{
    std::vector<std::string> players;
    std::string gameMode;
    unsigned int countOfSteps;
    std::string dataPath;
    std::string matrixPath;
};

int getParams(int argc, char* argv[], Params&);

void printHelp();
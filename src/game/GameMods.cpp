#include "GameMods.h"

void NotDetailedGame::organizeTheGame() {
    for (unsigned int i = 0; i < _countOfSteps; ++i) {
        step();
    }
}

NotDetailedGame::~NotDetailedGame()  {
    delete[] _points;
    delete[] _code;
}

bool DetailedGame::detailedStep(unsigned int stepNum) {
    std::string in;
    std::cin >> in;
   // std::cin >> in;
   if (in == "quit")
       return true;
    std::cout << "step:" << stepNum << " " << std::endl;
    step();
    std::cout << "selection of strategies: ";
    for (unsigned int i = 0; i < countOfPlayers; ++i) {
        std::cout << _code[i] << " ";
    }
    std::cout << "points earned per step: ";
    for (unsigned int i = 0; i < countOfPlayers; ++i) {
            if (_code[i] == 'C')
                std::cout << _matrix.getValue(_code,'C') << " ";
            else
                std::cout << _matrix.getValue(_code,'D') << " ";
    }
    std::cout << "points in sum: ";
    printPoints();
    return false;
}

void DetailedGame::organizeTheGame() {
    for (unsigned int i = 0; i < _countOfSteps; ++i) {
        bool stopper = detailedStep(i+1);
        if(stopper)
            break;
    }

}

DetailedGame::~DetailedGame() {
    delete[] _points;
    delete[] _code;
}
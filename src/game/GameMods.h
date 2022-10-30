#pragma once
#include "Game.h"
class FastGame : public Game{
public:
    void organizeTheGame() override;
    FastGame(const std::string& pathToMatrix,unsigned int countOfSteps)
    : Game(pathToMatrix, countOfSteps){};
    ~FastGame() override;
};

class DetailedGame : public Game{
private:
    bool detailedStep(unsigned int step);
public:
    void organizeTheGame() override;
    DetailedGame(const std::string& pathToMatrix,unsigned int countOfSteps)
            : Game(pathToMatrix, countOfSteps){};
    ~DetailedGame() override;
};

class TournamentGame : public Game{
    std::vector<struct NameAndPointer> _allStrategies;
public:
    void organizeTheGame() override;
    TournamentGame(const std::string& pathToMatrix,unsigned int countOfSteps)
        : Game(pathToMatrix, countOfSteps){};
    void addPlayers();
    void addPlayers(const std::vector<std::string>&);
    ~TournamentGame() override;
};
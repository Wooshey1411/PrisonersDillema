#pragma once
#include "Game.h"
class FastGame : public Game{
public:
    void organizeTheGame() override;
    FastGame(const std::string& pathToMatrix, const std::string& pathToData, unsigned int countOfSteps)
    : Game(pathToMatrix, pathToData , countOfSteps){};
    ~FastGame() override;
};

class DetailedGame : public Game{
private:
    bool detailedStep(unsigned int step);
public:
    void organizeTheGame() override;
    DetailedGame(const std::string& pathToMatrix, const std::string& pathToData, unsigned int countOfSteps)
            : Game(pathToMatrix, pathToData , countOfSteps){};
    ~DetailedGame() override;
};

class TournamentGame : public Game{
    std::vector<struct DataAndPointer> _allStrategies;
public:
    void organizeTheGame() override;
    TournamentGame(const std::string& pathToMatrix, const std::string& pathToData, unsigned int countOfSteps)
            : Game(pathToMatrix, pathToData , countOfSteps){};
    void addPlayers();
    void addPlayers(const std::vector<std::string>&);
    ~TournamentGame() override;
};
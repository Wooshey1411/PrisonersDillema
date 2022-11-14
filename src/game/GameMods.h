#pragma once
#include "Game.h"
class FastGame : public Game{
public:
    void organizeTheGame() override;
    FastGame(const std::string& pathToMatrix, const std::string& pathToData, unsigned int countOfSteps)
    : Game(pathToMatrix, pathToData , countOfSteps){};
    ~FastGame() override = default;
};

class DetailedGame : public Game{
public:
    void organizeTheGame() override;
    DetailedGame(const std::string& pathToMatrix, const std::string& pathToData, unsigned int countOfSteps)
            : Game(pathToMatrix, pathToData , countOfSteps){};
    ~DetailedGame() override = default;
private:
    bool detailedStep(unsigned int step);
};

class TournamentGame : public Game{
public:
    void organizeTheGame() override;
    TournamentGame(const std::string& pathToMatrix, const std::string& pathToData, unsigned int countOfSteps)
            : Game(pathToMatrix, pathToData , countOfSteps){};
    void addPlayers();
    void addPlayers(const std::vector<std::string>&);
    ~TournamentGame() override = default;
private:
    std::vector<struct DataAndPointer> _allStrategies;
};
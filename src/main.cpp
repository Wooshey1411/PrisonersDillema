#include <iostream>
#include "game/GameMods.h"
#include "MainParams.h"

int  main(int argc, char* argv[]) {
    if(argc < 2){
        std::cout << "Wrong number of arguments";
        return 0;
        }
    if(argc == 2 && std::string(argv[1]) == "-help") {
        printHelp();
        return 0;
    }
    int code;
    Params inputParams;
    code = getParams(argc,argv,inputParams);

    if(code == codes::NO_PLAYERS_CODE){
        std::cout << "Wrong players argument!" << std::endl;
        return 0;
    }
    if(inputParams.gameMode == "detailed"){
        if(inputParams.players.size() != COUNT_OF_PLAYERS){
            std::cout << "No enough players" << std::endl;
            return 0;
        }
        DetailedGame game(inputParams.matrixPath,inputParams.dataPath,inputParams.countOfSteps);
        for (unsigned int i = 0; i < COUNT_OF_PLAYERS; ++i) {
            game.addPlayer(inputParams.players[i]);
        }
        game.organizeTheGame();
        return 0;
    }
    if(inputParams.gameMode == "fast"){
        if(inputParams.players.size() != COUNT_OF_PLAYERS){
            std::cout << "No enough players" << std::endl;
            return 0;
        }
        FastGame game(inputParams.matrixPath,inputParams.dataPath,inputParams.countOfSteps);
        for (unsigned int i = 0; i < COUNT_OF_PLAYERS; ++i) {
            game.addPlayer(inputParams.players[i]);
        }
        game.organizeTheGame();
        game.printPoints();
        return 0;
    }
    if(inputParams.gameMode == "tournament"){
        TournamentGame game(inputParams.matrixPath,inputParams.dataPath,inputParams.countOfSteps);
        if (inputParams.players[0] == "all") {
            game.addPlayers();
        }
        else {
            if(inputParams.players.size() != COUNT_OF_PLAYERS){
                std::cout << "No enough players" << std::endl;
                return 0;
            }
            game.addPlayers(inputParams.players);
        }
        game.organizeTheGame();
        return 0;
    }

    std::cout << "This game mode doesn't exist!";
    return 0;
}

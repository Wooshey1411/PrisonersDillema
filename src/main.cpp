#include <iostream>
#include "game/GameMods.h"
#include "MainParams.h"

int  main(int argc, char* argv[]) {
    if(argc < 1){
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
    if(code == codes::NO_MODE_CODE){
        std::cout << "Wrong mode argument!" << std::endl;
        return 0;
    }

    if(inputParams.gameMode == "detailed"){
        DetailedGame game = DetailedGame(inputParams.matrixPath,inputParams.dataPath,inputParams.countOfSteps);
        for (unsigned int i = 0; i < COUNT_OF_PLAYERS; ++i) {
            game.addPlayer(inputParams.players[i]);
        }
        game.organizeTheGame();
        return 0;
    }
    if(inputParams.gameMode == "fast"){
        FastGame game = FastGame(inputParams.matrixPath,inputParams.dataPath,inputParams.countOfSteps);
        for (unsigned int i = 0; i < COUNT_OF_PLAYERS; ++i) {
            game.addPlayer(inputParams.players[i]);
        }
        game.organizeTheGame();
        game.printPoints();
        return 0;
    }
    if(inputParams.gameMode == "tournament"){
        TournamentGame game = TournamentGame(inputParams.matrixPath,inputParams.dataPath,inputParams.countOfSteps);
        if (inputParams.players[0] == "all")
            game.addPlayers();
        else
            game.addPlayers(inputParams.players);
        game.organizeTheGame();
        return 0;
    }

    std::cout << "This game mode doesn't exist!";
    return 0;
}

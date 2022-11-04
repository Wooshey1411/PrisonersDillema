#include <iostream>
#include "game/GameMods.h"
#include <regex>
#include <vector>

struct Params{
    std::vector<std::string> players;
    std::string gameMode;
    unsigned int countOfSteps;
    std::string dataPath;
    std::string matrixPath;
};


int  main(int argc, char* argv[]) {
    if(argc < 1){
        std::cout << "Wrong number of arguments";
        return 0;
        }
    struct Params inputParams;
    int argument = 1;

//region players
    std::cmatch res;
    std::regex regular(R"((-players)=([a-zA-Z]+[+]?)+[a-zA-Z]$)");
    if(!std::regex_match(argv[argument], res, regular)){
        std::cout << "Wrong players argument!";
        return 0;
    }
    regular = R"(([a-zA-Z]+))";
    std::string str = (std::string)argv[argument];
    std::sregex_iterator iterator{str.cbegin(),str.cend(),regular};
    iterator++;
    std::sregex_iterator end{};
    for (auto i = iterator; i != end; i++)
    {
        inputParams.players.push_back(i->str());
    }
    argument++;
//endregion

//region gameMode
    regular = R"((-mode)=([a-zA-Z]+))";
    if(!std::regex_match(argv[argument],res,regular)) {
        std::cout << "Wrong mode argument!";
        return 0;
    }
    str = (std::string)argv[argument];
    regular = R"(([a-zA-Z]+))";
    iterator = {str.cbegin(),str.cend(),regular};
    iterator++;
    inputParams.gameMode = iterator->str();
    argument++;
//endregion

//region steps
    regular = R"((-steps)=([1-9]{1})([0-9]{0,9}))";
    if(argument < argc && std::regex_match(argv[argument],res,regular)) {

        inputParams.countOfSteps = 0;
        unsigned int pos = 7; // position of first digit
        while (true) {
            if (argv[argument][pos] == '\0')
                break;
            inputParams.countOfSteps = inputParams.countOfSteps * 10 + (argv[3][pos] - '0');
            pos++;
        }
        argument++;
    }else {
        std::cout << "No data about count of steps. Uses default value = 10" << std::endl;
        inputParams.countOfSteps = 10;
    }

//endregion

//region dataPath
    regular = R"((-data)=(.+))";
    if(argument < argc && std::regex_match(argv[argument],res,regular)) {
        str = (std::string) argv[argument];
        regular = R"(=(.+))";
        iterator = {str.cbegin(), str.cend(), regular};
        inputParams.dataPath = iterator->str().erase(0, 1);
        argument++;
    }else{
        std::cout << "No data file. The game will not be recorded" << std::endl;
        inputParams.dataPath = noData;
    }
//endregion

//region matrixPath
    regular = R"((-matrix)=(.+))";
    if(argument < argc && std::regex_match(argv[argument],res,regular)) {
        str = (std::string) argv[argument];
        regular = R"(=(.+))";
        iterator = {str.cbegin(), str.cend(), regular};
        inputParams.matrixPath = iterator->str().erase(0, 1);
    }else{
        std::cout << "No matrix file. Uses default matrix" << std::endl;
        inputParams.matrixPath = noData;
    }
//endregion


    if(inputParams.gameMode == "detailed"){
        DetailedGame game = *new DetailedGame(inputParams.matrixPath,inputParams.dataPath,inputParams.countOfSteps);
        for (unsigned int i = 0; i < countOfPlayers; ++i) {
            game.addPlayer(inputParams.players[i]);
        }
        game.organizeTheGame();
        return 0;
    }
    if(inputParams.gameMode == "fast"){
        FastGame game = *new FastGame(inputParams.matrixPath,inputParams.dataPath,inputParams.countOfSteps);
        for (unsigned int i = 0; i < countOfPlayers; ++i) {
            game.addPlayer(inputParams.players[i]);
        }
        game.organizeTheGame();
        game.printPoints();
        return 0;
    }
    if(inputParams.gameMode == "tournament"){
        TournamentGame game = *new TournamentGame(inputParams.matrixPath,inputParams.dataPath,inputParams.countOfSteps);
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

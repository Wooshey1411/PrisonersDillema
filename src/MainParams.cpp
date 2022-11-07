#include "MainParams.h"
#include <regex>
#include <iostream>
#include "Config.h"

int getPlayers(char* argv[], Params& inputParams, int &argument){
    std::regex regular(R"((-players)=([a-zA-Z]+[+]?)+[a-zA-Z]$)");
    if(!std::regex_match(argv[argument], regular)){
        return codes::NO_PLAYERS_CODE;
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

    return codes::SUCCESS_CODE;
}

int getMode(char* argv[], Params& inputParams, int &argument){
    std::regex regular(R"((-mode)=([a-zA-Z]+))");
    if(!std::regex_match(argv[argument],regular)) {
        return codes::NO_MODE_CODE;
    }
    std::string str = (std::string)argv[argument];
    regular = R"(([a-zA-Z]+))";
    std::sregex_iterator iterator{str.cbegin(),str.cend(),regular};
    iterator++;
    inputParams.gameMode = iterator->str();
    argument++;
    return codes::SUCCESS_CODE;
}

int getSteps(char* argv[], int argc, Params& inputParams, int &argument){
    std::regex regular (R"((-steps)=([1-9]{1})([0-9]{0,9}))");
    if(argument < argc && std::regex_match(argv[argument],regular)) {

        inputParams.countOfSteps = 0;
        unsigned int pos = 7; // position of first digit
        while (true) {
            if (argv[argument][pos] == '\0')
                break;
            inputParams.countOfSteps = inputParams.countOfSteps * 10 + (argv[3][pos] - '0');
            pos++;
        }
        argument++;
        return codes::SUCCESS_CODE;
    }else
        return codes::OTHER_CODE;
       // std::cout << "No data about count of steps. Uses default value = 10" << std::endl;
}

int getDataPath(char* argv[], int argc, Params& inputParams, int &argument){
    std::regex regular(R"((-data)=(.+))");
    if(argument < argc && std::regex_match(argv[argument],regular)) {
        std::string str = (std::string) argv[argument];
        regular = R"(=(.+))";
        std::sregex_iterator iterator{str.cbegin(), str.cend(), regular};
        inputParams.dataPath = iterator->str().erase(0, 1);
        argument++;
        return codes::SUCCESS_CODE;
    }else
        return codes::OTHER_CODE;
        //std::cout << "No data file. The game will not be recorded" << std::endl;
}

int getMatrixPath(char* argv[], int argc, Params& inputParams, int &argument){
    std::regex regular(R"((-matrix)=(.+))");
    if(argument < argc && std::regex_match(argv[argument],regular)) {
        std::string str = (std::string) argv[argument];
        regular = R"(=(.+))";
        std::regex_iterator iterator = {str.cbegin(), str.cend(), regular};
        inputParams.matrixPath = iterator->str().erase(0, 1);
        return codes::SUCCESS_CODE;
    }else
        return codes::OTHER_CODE;
        //std::cout << "No matrix file. Uses default matrix" << std::endl;
}

int getParams(int argc, char* argv[], Params& inputParams){
    inputParams.dataPath = NO_DATA;
    inputParams.matrixPath = NO_DATA;
    inputParams.countOfSteps = DEFAULT_COUNT_OF_STEPS;
    int argument = 1;

    if(getPlayers(argv,inputParams,argument) == codes::NO_PLAYERS_CODE)
        return codes::NO_PLAYERS_CODE;
    if(getMode(argv,inputParams,argument) == codes::NO_MODE_CODE)
        return codes::NO_MODE_CODE;

    for (int i = 0; i <= argc-argument; ++i) {
        getSteps(argv,argc,inputParams,argument);
        getDataPath(argv,argc,inputParams,argument);
        getMatrixPath(argv,argc,inputParams,argument);
    }

    return codes::SUCCESS_CODE;
}

void printHelp(){
    std::cout << "This program is simulated dilemma of prisoners where 3 prisoners" << std::endl;
    std::cout << "Input params one after another:" << std::endl;
    std::cout << "-players=player1+player2+player3 - set 3 players by them names" << std::endl;
    std::cout << "-mode=[fast/detailed/tournament] - set game mode. fast - just print result of game, detailed - you can watch every step, tournament - game all vs all" << std::endl;
    std::cout << "-steps=n - set count of steps of game" << std::endl;
    std::cout << "-data=[path] - file for recording history of games. Some players depend on it" << std::endl;
    std::cout << "-matrix=[path] - matrix of points which will get players depending on this choice" << std::endl;
    std::cout << "List of players:" << std::endl;

    std::cout << "Random" << std::endl;
    std::cout << "OnlyBetray" << std::endl;
    std::cout << "OnlyCooperate" << std::endl;
    std::cout << "Alternation" << std::endl;
    std::cout << "BetrayEveryThird" << std::endl;
    std::cout << "Betrayed" << std::endl;
    std::cout << "Popular" << std::endl;
    std::cout << "Repeater" << std::endl;
    std::cout << "Addition" << std::endl;
}
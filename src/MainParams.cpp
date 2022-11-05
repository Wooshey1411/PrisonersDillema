#include "MainParams.h"
#include <regex>
#include <iostream>
#include "Config.h"

struct Params getParams(int argc, char* argv[], int& code){
    struct Params inputParams;
    inputParams.dataPath = noData;
    inputParams.matrixPath = noData;
    inputParams.countOfSteps = defaultCountOfSteps;
    int argument = 1;

//region players
    std::cmatch res;
    std::regex regular(R"((-players)=([a-zA-Z]+[+]?)+[a-zA-Z]$)");
    if(!std::regex_match(argv[argument], res, regular)){
        std::cout << "Wrong players argument!";
        code = 1;
        return inputParams;
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
        code = 1;
        return inputParams;
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
    }else
        std::cout << "No data about count of steps. Uses default value = 10" << std::endl;

//endregion

//region dataPath
    regular = R"((-data)=(.+))";
    if(argument < argc && std::regex_match(argv[argument],res,regular)) {
        str = (std::string) argv[argument];
        regular = R"(=(.+))";
        iterator = {str.cbegin(), str.cend(), regular};
        inputParams.dataPath = iterator->str().erase(0, 1);
        argument++;
    }else
        std::cout << "No data file. The game will not be recorded" << std::endl;
//endregion

//region matrixPath
    regular = R"((-matrix)=(.+))";
    if(argument < argc && std::regex_match(argv[argument],res,regular)) {
        str = (std::string) argv[argument];
        regular = R"(=(.+))";
        iterator = {str.cbegin(), str.cend(), regular};
        inputParams.matrixPath = iterator->str().erase(0, 1);
    }else
        std::cout << "No matrix file. Uses default matrix" << std::endl;
//endregion
    return inputParams;
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
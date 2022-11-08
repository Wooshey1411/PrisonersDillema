#pragma once
#include <map>
#include <memory>
#include "Config.h"

class DilemmaMatrix{
public:
    DilemmaMatrix();
    ~DilemmaMatrix();
    unsigned int getValue(std::string_view code, char type);
    void fillMatrixFromFile(const std::string& path);
private:
    std::map <unsigned int, unsigned int*> _matrix;
};

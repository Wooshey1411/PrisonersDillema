#pragma once
#include <map>
#include <memory>
#include "config.h"

class DilemmaMatrix{
private:
    std::map <unsigned int, unsigned int*> matrix;
public:
    DilemmaMatrix();
    ~DilemmaMatrix();
    unsigned int getValue(std::string_view code, char type);
    void fillMatrixFromFile(const std::string& path);
};
#pragma once
#include <iostream>

class Strategy{
public:
    virtual char step() = 0;
    virtual ~Strategy() = default;
};
#pragma once
#include <iostream>
#include "../storage/Storage.h"

class Strategy{
public:
    virtual char step(Storage*) = 0;
    virtual ~Strategy() = default;
};
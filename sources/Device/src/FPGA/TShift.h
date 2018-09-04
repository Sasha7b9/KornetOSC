#pragma once
#include "defines.h"



class TShift
{
public:
    static int Min();
    static int Zero();
    static int Max();

    TShift(int tshift);

    int InPoints();

    void Set(int tShift);

    operator int() const { return value; };

    char *ToString(char buffer[20]) const;

private:
    int value;
};

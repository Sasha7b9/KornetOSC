#pragma once
#include "Settings/SettingsChannel.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class RShift
{
public:
    static const int MIN = 20;
    static const int MAX = 980;
    static const int ZERO = 500;

    static void Draw();

private:

    static void Draw(Chan ch);
};

#pragma once
#include "Settings/SettingsTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Класс отвечает за вывод информации в нижних двух строках экрана
class BottomPart
{
public:
    static void Draw();

private:
    static int WriteChannel(Channel ch, int x, int y);

    static void WriteTBase(int x, int y);
};


#pragma once
#include "Display/Colors.h"


class Keyboard
{
public:
    static void Init();
    static void Draw();
private:
    static void DrawButton(int x, int y, int width, Color color, const char *title);
};

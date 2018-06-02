#pragma once


class Keyboard
{
public:
    static void Init();
    static void Draw();
private:
    static void DrawButton(int x, int y, int width, const char *title);
};

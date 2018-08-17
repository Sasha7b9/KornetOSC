#pragma once


class  MemoryWindow
{
public:

    static void Draw();

private:

    static void DrawDataInRect(int x, int y, int width, int height, uint8 *data, int length);
};

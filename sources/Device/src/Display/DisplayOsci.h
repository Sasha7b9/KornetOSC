#pragma once


class DisplayOsci
{
public:

    static void Update();

private:

    static void DrawCursorTrigLevel();
   
    static void DrawScaleLine(int x, bool forTrigLev);
};

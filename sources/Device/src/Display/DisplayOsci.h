#pragma once


class DisplayOsci
{
public:

    static void Update();

private:

    static void DrawCursorTrigLevel();

    static void DrawHiPart();
    
    static void DrawScaleLine(int x, bool forTrigLev);

    static void WriteCursors();

    static void DrawHiRightPart();
};

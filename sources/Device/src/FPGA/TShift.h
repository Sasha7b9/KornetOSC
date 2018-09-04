#pragma once

class TShift
{
public:
    static int Min();
    static int Zero();
    static int Max();

    TShift(int tshift);

    int InPoints();

    int Value() { return value; };

    void Set(int tShift);

private:
    int value;
};

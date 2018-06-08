#pragma once
#include "Keyboard/Keyboard.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Handlers
{
public:
    static void Process(KeyEvent);

private:
    static void E();

    static void RShiftLessA();
    static void RShiftMoreA();
    static void RShiftLessB();
    static void RShiftMoreB();
    static void RangeLessA();
    static void RangeMoreA();
    static void RangeLessB();
    static void RangeMoreB();

    static void TShiftLess();
    static void TShiftMore();
    static void TBaseLess();
    static void TBaseMore();

    static void TrigLevLess();
    static void TrigLevMore();

    static void Func();
    static void Arrow();
    static void Enter();
    static void ChannelA();
    static void ChannelB();
    static void Function();
    static void Measures();
    static void Memory();
    static void Service();
    static void Time();
    static void Start();
    static void Trig();
    static void Display();

    static KeyEvent event;
};



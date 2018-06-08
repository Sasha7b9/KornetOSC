#pragma once
#include "Keyboard/Keyboard.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef void(*pFuncVKE)(KeyEvent);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Handlers
{
public:
    static void E(KeyEvent);
    static void RShift(KeyEvent);
    static void Range(KeyEvent);
    static void TShift(KeyEvent);
    static void TBase(KeyEvent);
    static void Func(KeyEvent);
    static void Arrow(KeyEvent);
    static void TrigLev(KeyEvent);
    static void Chan(KeyEvent);
    static void Function(KeyEvent);
    static void Measures(KeyEvent);
    static void Memory(KeyEvent);
    static void Service(KeyEvent);
    static void Time(KeyEvent);
    static void Start(KeyEvent);
    static void Trig(KeyEvent);
    static void Display(KeyEvent);
};



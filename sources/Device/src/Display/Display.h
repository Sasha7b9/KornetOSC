#pragma once
#include "defines.h"
#include "Settings/SettingsTypes.h"
#include "Keyboard/Buttons.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LogEntity
{
    friend class Log;
    static void AddToConsole(char *string);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Display
{
    friend class LogEntity;
public:
    
    static const int HEIGHT = 240;

    static const int WIDTH = 320;

    static void Init();

    static void Update();

    static void SetKey(Key key);

private:

    static void DrawGrid();
    /// Нарисовать информацию в нижней части экрана.
    static void WriteLowPart();

    static int WriteChannel(Channel ch, int x, int y);

    static void WriteTBase(int x, int y);

    static void DrawRShift();

    static void DrawRShift(Channel ch);

    static void DrawConsole();

    static void UpdateOsci();

    static void UpdateTester();

    static void DrawDataTester(int numStep, int x, int y);

    static void UpdateMultimeter();
    /// true означает, что идёт процесс вывода консоли и добавлять в неё новые строки нельзя (это происходит, когда добавление идёт из прерывания)
    static bool inProcessDrawConsole;

    static Key key;
};

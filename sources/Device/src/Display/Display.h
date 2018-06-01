#pragma once
#include "defines.h"
#include "Settings/SettingsTypes.h"
#include "Hardware/Controls.h"


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
    
    static void Init();

    static void Update();

    static void SetKey(Control key);

private:

    static void DrawGrid();
    /// ���������� ���������� � ������ ����� ������.
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
    /// true ��������, ��� ��� ������� ������ ������� � ��������� � �� ����� ������ ������ (��� ����������, ����� ���������� ��� �� ����������)
    static bool inProcessDrawConsole;

    static Control key;
};

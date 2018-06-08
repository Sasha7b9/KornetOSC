#pragma once
#include "defines.h"
#include "Settings/SettingsTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ����� �������� �� ����� ���������� � ������ ���� ������� ������
class BottomPart
{
public:
    static void Draw();

private:
    static int WriteChannel(Channel ch, int x, int y);

    static void WriteTBase(int x, int y);

    static void WriteTextVoltage(Channel ch, int x, int y); ///< �������� � ������ ������ ��������� ������������� ������.

    static void WriteStringAndNumber(const char *text, int16 x, int16 y, int number);

    static void DrawTime(int x, int y);
};


#pragma once
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
};


#pragma once
#include "Hardware/Hardware.h"
#include "Multimeter/Multimeter.h"
#include "Osci/Osci.h"
#include "Tester/Tester.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum DeviceMode
{
    Mode_Osci,
    Mode_Tester,
    Mode_Multimeter,
    NumDeviceModes
};

class Device
{
public:

    static void Init();

    static void Update();

    static DeviceMode CurrentMode();
    /// ������� ���������� ��� ������� �� ������ "�������". ����������� ���������� � ��������� �����
    static void ChangeMode();
private:
    static DeviceMode currentMode;
};

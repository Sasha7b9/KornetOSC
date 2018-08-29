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
    /// Функция вызывается при нажатии на кнопку "Функция". Переключает устройство в следующий режим
    static void ChangeMode();
private:
    static DeviceMode currentMode;
};

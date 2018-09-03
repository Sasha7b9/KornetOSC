#pragma once
#include "Hardware/Hardware.h"
#include "Multimeter/Multimeter.h"
#include "Osci/Osci.h"
#include "Tester/Tester.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Device
{
public:

    struct Mode
    {
        enum E
        {
            Osci,
            Tester,
            Multimeter,
            Number
        } value;

        Mode(E v) : value(v) {};

        operator uint8() const { return (uint8)value; };
    };

    static void Init();

    static void Update();

    static Mode CurrentMode();
    /// Функция вызывается при нажатии на кнопку "Функция". Переключает устройство в следующий режим
    static void ChangeMode();

private:
    static Mode currentMode;
};

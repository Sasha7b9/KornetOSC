#pragma once
#include "Settings/Settings.h"

/*
    Работа с микросхемой EEPROM AT25160N, предназначенной для хранения настроек.
*/
class AT25160N
{
public:
    static void Init();
    static void Test();
    static void Save(Settings &set);
private:
    enum Reg
    {
        WREN,   ///< Set Write Enable Latch
        WRDI,   ///< Reset Write Enable Latch
        RDSR,   ///< Read Status Register
        WRSR,   ///< Write Status Register
        READ,   ///< Read Data from Memory Array
        WRITE   ///< Write Data to Memory Array
    };
    static void WriteReg(Reg reg, uint8 data = 0);
    static uint8 ReadReg(Reg reg);
};

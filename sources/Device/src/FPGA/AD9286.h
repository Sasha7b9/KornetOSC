#pragma once
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class AD9286
{
public:
    static void Init();
    static uint8 ReadByte(uint8 address);
    static void  WriteByte(uint8 address, uint8 byte);

private:
    static void FirstConfig();
    static void ConfigToWrite();
    static void ConfigToRead();
    static void SetPin(uint pin);
    static void ResetPin(uint pin);
    static int ReadPin(uint pin);
};

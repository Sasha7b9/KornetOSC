#pragma once
#include "Settings/Settings.h"

/*
    ������ � ����������� EEPROM AT25160N, ��������������� ��� �������� ��������.
*/
class AT25160N
{
public:
    static void Init();
    static void Save(Settings &set);
    static void Load(Settings &set);
    static void Test();
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

    /// �������� �������� data � ������� reg
    static void WriteToRegister(Reg reg, uint8 data = 0);
    /// ��������� �������� �������� reg
    static uint8 ReadFromRegister(Reg reg);
    /// �������� size ���� � ����������
    static void Write(const uint8 *buffer, int size);
    /// ������ ���� �� ����������
    static uint8 Read();
    /// �������, ���� �� ���������� ��������� ���� ������
    static void WaitFinishWrite();
    /// ������ size ���� �� ������ address
    static void ReadMemory(uint address, uint8 *buffer, int size);
    /// ���������� size ���� �� ������ address
    static void WriteMemory(uint address, uint8 *buffer, int size);
    /// ���������� �������� ����� � 1
    static void SetPin(GPIO_TypeDef *gpio, uint16 pin);
    /// ���������� �������� ����� � 0
    static void ResetPin(GPIO_TypeDef *gpio, uint16 pin);
};

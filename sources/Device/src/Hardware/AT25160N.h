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

    /// ��������� ������
    static void SetWriteLatch();
    /// ��������� ������
    static void ResetWriteLatch();

    /// �������� �������� data � ������� reg
    static void WriteToRegister(Reg reg, uint8 *data = 0, uint size = 0);
    /// ��������� �������� �������� reg
    static uint8 ReadFromRegister(Reg reg);
    /// �������� size ���� � ����������
    static void WriteBuffer(const uint8 *buffer, int size);
    /// ���������� ���� � ����������
    static void WriteByte(uint8 byte);
    /// ������ ���� �� ����������
    static uint8 ReadByte();
    /// �������� size ���� �� ������ address
    static void WriteToAddress(uint address, uint8 *buffer, uint size);
    /// ��������� size ���� � ������ address
    static void ReadFromAddress(uint address, uint8 *buffer, uint size);
    /// �������, ���� �� ���������� ��������� ���� ������
    static void WaitFinishWrite();
    /// ���������� �������� ����� � 1
    static void SetPin(GPIO_TypeDef *gpio, uint16 pin);
    /// ���������� �������� ����� � 0
    static void ResetPin(GPIO_TypeDef *gpio, uint16 pin);
};

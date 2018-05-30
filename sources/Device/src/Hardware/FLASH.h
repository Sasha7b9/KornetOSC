#pragma once
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EPROM
{
public:

    static void SaveSettings();

    static void LoadSettings();
private:
    /// ���������� ����� ������� ���������� ����� � ������� ��������
    static uint FirstFreeAddressForSettings();
    /// \brief ���������� ����� ���������� �������� ��� 0, ���� ��������� �� �����������. fromEnd ���������, ����� ��������� �� �����
    /// ����� ��������� - 0 - ���������, 1 - ������������� � ��� �����
    static uint AddressSavedSettings(int fromEnd);
    /// ���������� ����� ������� ���������� ����� ��� ������
    static uint AddressFirstEmptyByte();

    static uint GetSector(uint address);

    static void EraseSector(uint address);

    static void WriteBytes(uint address, uint8 *data, int size);

    static void ReadBytes(uint address, void *data, uint size);
};


#pragma once
#include "defines.h"

struct DataSettings;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EEPROM
{
public:

    static void SaveSettings();

    static void LoadSettings();

    static void DeleteAllData();

    static bool GetData(int num, DataSettings *ds, uint8 *dataA, uint8 *dataB);
private:
    /// ¬озвращает адрес первого свободного байта в секторе настроек
    static uint FirstFreeAddressForSettings();
    /// \brief ¬озвращает адрес сохранЄнных настроек или 0, если настройки не сохран€лись. fromEnd указывает, какие настройки от конца
    /// нужно загружать - 0 - последние, 1 - предпоследние и так далее
    static uint AddressSavedSettings(int fromEnd);
    /// ¬озвращает адрес первого свободного байта дл€ записи
    static uint AddressFirstEmptyByte();

    static uint GetSector(uint address);

    static void EraseSector(uint address);

    static void WriteBytes(uint address, uint8 *data, int size);

    static void ReadBytes(uint address, void *data, uint size);
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class OTPmem
{
public:
    static bool SaveSerialNumber(char *servialNumber);
    /// ¬озвращает число свободных мест дл€ записи. ≈сли 0, то места в OTP уже не осталось.
    static int GetSerialNumber(char buffer[17]);
};


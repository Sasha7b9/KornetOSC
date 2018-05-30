#pragma once
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EPROM
{
public:

    static void SaveSettings();

    static void LoadSettings();
private:
    /// Возвращает адрес первого свободного байта в секторе настроек
    static uint FirstFreeAddressForSettings();
    /// \brief Возвращает адрес сохранённых настроек или 0, если настройки не сохранялись. fromEnd указывает, какие настройки от конца
    /// нужно загружать - 0 - последние, 1 - предпоследние и так далее
    static uint AddressSavedSettings(int fromEnd);
    /// Возвращает адрес первого свободного байта для записи
    static uint AddressFirstEmptyByte();

    static uint GetSector(uint address);

    static void EraseSector(uint address);

    static void WriteBytes(uint address, uint8 *data, int size);

    static void ReadBytes(uint address, void *data, uint size);
};


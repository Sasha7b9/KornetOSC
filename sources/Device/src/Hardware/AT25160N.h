#pragma once
#include "Settings/Settings.h"

/*
    Работа с микросхемой EEPROM AT25160N, предназначенной для хранения настроек.
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

    /// Разрешить запись
    static void SetWriteLatch();
    /// Запретить запись
    static void ResetWriteLatch();

    /// Записать значение data в регистр reg
    static void WriteToRegister(Reg reg, uint8 *data = 0, uint size = 0);
    /// Прочитать значение регистра reg
    static uint8 ReadFromRegister(Reg reg);
    /// Записыет size байт в микросхему
    static void WriteBuffer(const uint8 *buffer, int size);
    /// Записывает байт в микросхему
    static void WriteByte(uint8 byte);
    /// Читает байт из микросхемы
    static uint8 ReadByte();
    /// Записать size байт по адресу address
    static void WriteToAddress(uint address, uint8 *buffer, uint size);
    /// Прочитать size байт с адреса address
    static void ReadFromAddress(uint address, uint8 *buffer, uint size);
    /// Ожидает, пока не закончится внутреннй цикл записи
    static void WaitFinishWrite();
    /// Установить заданный вывод в 1
    static void SetPin(GPIO_TypeDef *gpio, uint16 pin);
    /// Установить заданный вывод в 0
    static void ResetPin(GPIO_TypeDef *gpio, uint16 pin);
};

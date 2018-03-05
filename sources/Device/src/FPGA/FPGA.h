#pragma once
#include "defines.h"
#include "FPGA_Types.h"
#include "Settings/SettingsTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define RShiftMin       20
#define RShiftZero      500
#define RShiftMax       980
#define TrigLevZero     500
#define TrigLevMax      980
#define TrigLevMin      20
#define TShiftZero      500
#define TShiftMin       0
#define TShiftMax       60000

/// Ќа столько единиц нужно изменить значение смещени€, чтобы маркер смещени€ по напр€жению передвинулс€ на одну точку.
#define STEP_RSHIFT     (((RShiftMax - RShiftMin) / 24) / 20)
#define STEP_TRIGLEV    STEP_RSHIFT

enum Pin
{
    SPI3_SCK,
    SPI3_DAT,
    SPI3_CS1,
    SPI3_CS2,
    A1,
    A2,
    A3,
    A4,
    LF1,
    LF2,
    A1S,
    A0S,
    LFS,
    Num_Pins
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class HardwareFPGA
{
    friend class FPGA;
private:
};

class FPGA
{
public:

    static void Init();

    static void Update();

    static void Start();

    static void OnPressStart();

    static void GiveStart();

    static void LoadSettings();

    static void IncreaseRange(Channel ch);

    static void DecreaseRange(Channel ch);

    static void IncreaseTBase();

    static void DecreaseTBase();

    static void RShiftChange(Channel ch, int delta);

    static void TrigLevChange(int delta);

    static void TShiftChange(int delta);

    static void SetRShift(Channel ch, uint16 rShift);

    static void LoadTrigPolarity();

    static void LoadTrigMode();

    static void LoadTrigSource();

    static void LoadTrigInput();

    static void Stop();

    static void LoadRanges();
    /// «апустить цикл чтени€ дл€ тестер-компонента. ¬ течение time секунд должно быть считано numPoints точек
    static void StartForTester(int numPoints);

    static void ReadForTester(uint8 *dataA, uint8 *dataB);

private:

    static void GPIO_Init();

    static void LoadTBase();

    static void LoadTrigLev();

    static void LoadRShift(Channel ch);

    static void LoadTShift();

    static void WritePin(Pin pin, int enable);

    static void SetPin(Pin pin);

    static void ResetPin(Pin pin);

    static uint GetPin(Pin pin);

    static GPIO_TypeDef *GetPort(Pin pin);

    static void WriteRegisters(Pin cs, uint16 value);

    static void ReadData();

    static uint8 ReadFlag();

    static uint16 ReadLastRecord();

    static void ReadDataChanenl(Channel ch, uint8 data[FPGA_MAX_NUM_POINTS]);
    /// ”становить в соотвествующие положени€ выводы, отвечающие за источник и вход синхронизации
    static void LoadTrigSourceInput();
    /// „итать канал в рандомизаторе с адреса address
    static void ReadDataChanenlRand(Channel ch, uint8 *address, uint8 *data);

    static bool CalculateGate(uint16 rand, uint16 *eMin, uint16 *eMax);

    static int CalculateShift();

    static bool isRunning;
    /// True, если дан запуск
    static bool givingStart;
};

#pragma once
#include "defines.h"
#include "Globals.h"
#include "FPGATypes.h"
#include "Settings/SettingsTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define TrigLevZero     500
#define TrigLevMax      980
#define TrigLevMin      20
#define TShiftZero      500
#define TShiftMin       0
#define TShiftMax       60000


#define STEP_TRIGLEV    STEP_RSHIFT

enum TypeRecord
{
    RecordFPGA,
    RecordAnalog,
    RecordDAC
};

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

extern uint16 gPost;
extern int16 gPred;

extern StateWorkFPGA fpgaStateWork;
#define FPGA_IN_STATE_STOP (fpgaStateWork == StateWorkFPGA_Stop)

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

    static void Stop(bool = true);

    static void LoadRanges();
    /// Запустить цикл чтения для тестер-компонента. В течение time секунд должно быть считано numPoints точек
    static void StartForTester(int numPoints);

    static void ReadForTester(uint8 *dataA, uint8 *dataB);
    /// Установить относительное смещение по времени
    static void SetTShift(int tShift);
    /// Установить относительный уровень синхронизации
    static void SetTrigLev(TrigSource ch, uint16 trigLev);
    /// Запускает цикл сбора информации
    static void OnPressStartStop();
    /// Установить количество измерений, по которым будут рассчитываться ворота в режиме рандомизатора
    static void SetNumberMeasuresForGates(int number);
    /// Установить добавочное смещение по времени для режима рандомизатора. В каждой развёртке это смещение должно быть разное
    static void SetDeltaTShift(int16 shift);

    static void LoadTShift();

    static void SetBandwidth(Channel ch);
    /// Установить режим канала по входу
    static void SetModeCouple(Channel ch, ModeCouple modeCoupe);

    static void SetResistance(Channel ch, Resistance resistance);

    static bool FreqMeter_Init();
    /// Провести процедуру балансировки
    static void BalanceChannel(Channel ch);
    /// Возвращает true, если прибор находится не в процессе сбора информации
    static bool IsRunning();
    /// Установить количество считываемых сигналов в секунду
    static void SetENumSignalsInSec(int numSigInSec);
    /// Можно делать при изменении каких-то настроек. Например, при изменении числа точек (ПАМЯТЬ-Точки) если не вызвать, то будут артефакты изображения
    static void Reset();
    /// Включить/выключить режим пикового детектора
    static void SetPeackDetMode(PeakDetMode peackDetMode);
    /// Установить масштаб по времени
    static void SetTBase(TBase tBase);
    /// Установить источник синхронизации
    static void SetTrigSource(TrigSource trigSource);
    /// Установить полярность синхронизации
    static void SetTrigPolarity(TrigPolarity polarity);
    /// Установить режим входа синхронизации
    static void SetTrigInput(TrigInput trigInput);
    /// Найти и установить уровень синхронизации по последнему считанному сигналу
    static void FindAndSetTrigLevel();
    /// Включить/выключить калибратор.
    static void SetCalibratorMode(CalibratorMode calibratorMode);

    static void EnableRecorderMode(bool enable);

    static int16 CalculateAdditionRShift(Channel ch, Range range, bool wait);

    static float CalculateStretchADC(Channel ch);

    static float CalculateDeltaADC(Channel ch, float *avgADC1, float *avgADC2, float *delta);
    /// Если wait == true, то нужно ожидать после установки режима перед измерением для исключения переходного процесса
    static void CalibrateAddRShift(Channel ch, bool wait);

    static void CalibrateChannel(Channel ch);
    /// Запуск функции калибровки
    static void ProcedureCalibration();
    /// Установить масштаб по напряжению
    static void SetRange(Channel ch, Range range);

    static void FreqMeter_Draw(int x, int y);
    /// Получить значение частоты для вывода в нижней части экрана
    static float FreqMeter_GetFreq();
    /// Функция вызывается из FPGA
    static void FreqMeter_Update(uint16 flag);
    /// Запуск процесса поиска сигнала
    static void  AutoFind();

    static bool FindWave(Channel ch);

    static bool AccurateFindParams(Channel ch);
    /// \brief Функция даёт старт АЦП и ждёт считывания информаии timeWait мс. Если данные получены, то функция возвращает true и их можно получить 
    /// DS_GetData_RAM(ch, 0). Если данные не получены, функция возвращает false.
    static bool ReadingCycle(uint timeWait);

    static void SetTPos(TPos tPos);

private:

    static TBase CalculateTBase(float freq);

    static void CalibrateStretch(Channel ch);

    static bool FindParams(Channel ch, TBase *tBase);
    ///< Возвращает RangeSize, если масштаб не найден.
    static Range FindRange(Channel ch);

    static void GPIO_Init();

    static void LoadTBase();

    static void LoadTrigLev();

    static void LoadRShift(Channel ch);

    static void WritePin(Pin pin, int enable);

    static void SetPin(Pin pin);

    static void ResetPin(Pin pin);

    static uint GetPin(Pin pin);

    static GPIO_TypeDef *GetPort(Pin pin);

    static void WriteRegisters(Pin cs, uint16 value);

    static void ReadData();

    static uint8 ReadFlag();

    static uint16 ReadLastRecord();

    static void ReadDataChanenl(Channel ch, uint8 data[FPGA_MAX_POINTS]);
    /// Установить в соотвествующие положения выводы, отвечающие за источник и вход синхронизации
    static void LoadTrigSourceInput();
    /// Читать канал в рандомизаторе с адреса address
    static void ReadDataChanenlRand(Channel ch, uint8 *address, uint8 *data);

    static bool CalculateGate(uint16 rand, uint16 *eMin, uint16 *eMax);

    static int CalculateShift();
    /// Загрузить регистр WR_UPR (пиковый детектор и калибратор).
    static void LoadRegUPR();

    static void Write(TypeRecord type, uint16 *address, uint data, bool restart);

    static bool isRunning;
    /// True, если дан запуск
    static bool givingStart;
};

#pragma once
#include "defines.h"
#include "Globals.h"
#include "FPGATypes.h"
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

/// �� ������� ������ ����� �������� �������� ��������, ����� ������ �������� �� ���������� ������������ �� ���� �����.
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

    static void Stop(bool);

    static void LoadRanges();
    /// ��������� ���� ������ ��� ������-����������. � ������� time ������ ������ ���� ������� numPoints �����
    static void StartForTester(int numPoints);

    static void ReadForTester(uint8 *dataA, uint8 *dataB);
    /// ���������� ������������� �������� �� �������
    static void SetTShift(int tShift);
    /// ���������� ������������� ������� �������������
    static void SetTrigLev(TrigSource ch, uint16 trigLev);
    /// ��������� ���� ����� ����������
    static void OnPressStartStop();
    /// ���������� ���������� ���������, �� ������� ����� �������������� ������ � ������ �������������
    static void SetNumberMeasuresForGates(int number);
    /// ���������� ���������� �������� �� ������� ��� ������ �������������. � ������ �������� ��� �������� ������ ���� ������
    static void SetDeltaTShift(int16 shift);

    static void LoadTShift();

    static void SetBandwidth(Channel ch);
    /// ���������� ����� ������ �� �����
    static void SetModeCouple(Channel ch, ModeCouple modeCoupe);

    static void SetResistance(Channel ch, Resistance resistance);

    static bool FreqMeter_Init();
    /// �������� ��������� ������������
    static void BalanceChannel(Channel ch);
    /// ���������� true, ���� ������ ��������� �� � �������� ����� ����������
    static bool IsRunning();
    /// ���������� ���������� ����������� �������� � �������
    static void SetENumSignalsInSec(int numSigInSec);
    /// ����� ������ ��� ��������� �����-�� ��������. ��������, ��� ��������� ����� ����� (������-�����) ���� �� �������, �� ����� ��������� �����������
    static void Reset();
    /// ��������/��������� ����� �������� ���������
    static void SetPeackDetMode(PeakDetMode peackDetMode);
    /// ���������� ������� �� �������
    static void SetTBase(TBase tBase);

private:

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
    /// ���������� � �������������� ��������� ������, ���������� �� �������� � ���� �������������
    static void LoadTrigSourceInput();
    /// ������ ����� � ������������� � ������ address
    static void ReadDataChanenlRand(Channel ch, uint8 *address, uint8 *data);

    static bool CalculateGate(uint16 rand, uint16 *eMin, uint16 *eMax);

    static int CalculateShift();

    static bool isRunning;
    /// True, ���� ��� ������
    static bool givingStart;
};

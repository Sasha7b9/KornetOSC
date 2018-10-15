#pragma once
#include "defines.h"
#include "Globals.h"
#include "FPGATypes.h"
#include "Settings/SettingsTime.h"
#include "Settings/SettingsService.h"


/// �� ������� ������ ����� �������� �������� ��������, ����� ������ �������� �� ���������� ������������ �� ���� �����.
#define STEP_RSHIFT     (((RShift::MAX - RShift::MIN) / 24) / 20)
#define STEP_TRIGLEV    STEP_RSHIFT

struct Pin
{
    enum E
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
        Number
    } value;
    Pin(E v) : value(v) {};
    operator uint8() const { return (uint8)value; };
};

#define FPGA_IN_STATE_STOP (FPGA::fpgaStateWork == StateWorkFPGA_Stop)
#define FPGA_IN_STATE_WORK (FPGA::fpgaStateWork == StateWorkFPGA_Work)
#define FPGA_IN_STATE_WAIT (FPGA::fpgaStateWork == StateWorkFPGA_Wait)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class HardwareFPGA
{
    friend class FPGA;
private:
};

class FPGA
{
friend class TrigLev;
public:

    static void Init();

    static void Update();

    static void Start();

    static void OnPressStart();

    static void GiveStart();

    static void LoadSettings();

    static void IncreaseRange(Chan ch);

    static void DecreaseRange(Chan ch);

    static void IncreaseTBase();

    static void DecreaseTBase();

    static void RShiftChange(Chan ch, int delta);

    static void TrigLevChange(int delta);

    static void TShiftChange(int delta);

    static void SetRShift(Chan ch, uint16 rShift);

    static void LoadTrigPolarity();

    static void LoadTrigMode();

    static void LoadTrigSource();

    static void LoadTrigInput();

    static void Stop(bool pause = false);

    static void LoadRanges();
    /// ��������� ���� ������ ��� ������-����������. � ������� time ������ ������ ���� ������� numPoints �����
    static void StartForTester(int numPoints);

    static bool ReadForTester(uint8 *dataA, uint8 *dataB);

    static bool IsRunning()
    {
        return isRunning; 
    }

    static bool InStateStop()
    {
        return false;
    }

    static void LoadTShift();
    
    static StateWorkFPGA GetStateWork();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void SetTShift(int tShift);

    static void Reset();

    static void SetModeCouple(Chan ch, ModeCouple couple);

    class FreqMeter
    {
    public:
        static float GetFreq();

        static bool Init();

        /// ����� ����� �������.
        struct TimeCounting
        {
            enum E
            {
                _100ms,
                _1s,
                _10s
            } value;
            operator uint8() const { return (uint8)value; }
        };

        /// ������� ����������� ��������� ��� ����� �������.
        struct FreqClc
        {
            enum E
            {
                _100kHz,
                _1MHz,
                _10MHz,
                _100MHz
            } value;
            operator uint8() const { return (uint8)value; }
        };

        /// ���������� ��������.
        struct NumberPeriods
        {
            enum E
            {
                _1,
                _10,
                _100
            } value;
            operator uint8() const { return (uint8)value; }
        };

        struct Enabled
        {
            enum E
            {
                On,
                Off
            } value;
            operator uint8() const { return (uint8)value; }
        };
    };

    /// ���������� ������������� ������� �������������
    static void SetTrigLev(Trig::Source ch, uint16 trigLev);
    /// ���������� ���������� ����������� �������� � �������
    static void SetENumSignalsInSec(int numSigInSec);
    /// ���������� ���������� ���������, �� ������� ����� �������������� ������ � ������ �������������
    static void SetNumberMeasuresForGates(int number);
    /// ���������� ������� �� �������
    static void SetTBase(TBase tBase);
    /// ����� � ���������� ������� ������������� �� ���������� ���������� �������
    static void FindAndSetTrigLevel();
    /// ��������/��������� ����������.
    static void SetCalibratorMode(CalibratorMode calibratorMode);

    static void EnableRecorderMode(bool enable);
    /// ���������� ���������� �������� �� ������� ��� ������ �������������. � ������ �������� ��� �������� ������ ���� ������
    static void SetDeltaTShift(int16 shift);

    static void SetBandwidth(Chan ch);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

private:

    static void GPIO_Init();

    static void LoadTBase();

    static void LoadTrigLev();

    static void LoadRShift(Chan ch);

    static void WritePin(Pin pin, int enable);

    static void SetPin(Pin pin);

    static void ResetPin(Pin pin);

    static uint GetPin(Pin pin);

    static GPIO_TypeDef *GetPort(Pin pin);

    static void WriteRegisters(Pin cs, uint16 value);

    static void ReadData();

    static uint8 ReadFlag();

    static uint16 ReadLastRecord();

    static void ReadDataChanenl(Chan ch, uint8 data[FPGA_MAX_NUM_POINTS]);
    /// ���������� � �������������� ��������� ������, ���������� �� �������� � ���� �������������
    static void LoadTrigSourceInput();
    /// ������ ����� � ������������� � ������ address
    static void ReadDataChanenlRand(Chan ch, uint8 *address, uint8 *data);

    static bool CalculateGate(uint16 rand, uint16 *eMin, uint16 *eMax);

    static int CalculateShift(Chan ch);

    static bool isRunning;
    /// True, ���� ��� ������
    static bool givingStart;
    /// ����� ������ ������
    static uint timeStart;
    
public:
    static StateWorkFPGA fpgaStateWork;

    static uint16 post;
    static uint16 pred;
};

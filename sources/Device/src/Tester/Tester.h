#pragma once
#include "defines.h"
#include "Settings/SettingsChannel.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define TESTER_NUM_POINTS               (240)
#define TESTER_CONTROL                  (set.test_control)
#define TESTER_CONTROL_IS_U             (TESTER_CONTROL == Tester::Control::Voltage)
#define TESTER_POLARITY                 (set.test_polarity)
#define TESTER_POLARITY_IS_POSITITVE    (TESTER_POLARITY == Tester::Polarity::Positive)



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Tester
{
public:
    static void Init();

    static void Enable();

    static void Disable();

    static void Update();

    static void ProcessStep();
    /// ��������� ���������� �� Settings
    static void LoadPolarity();
    /// ������������� ��� ��������� ���������� � ����������� � ����������� Settings
    static void LoadStep();

private:
    /// ��������� FPGA � ������������ � �������������� �����������
    static void LoadFPGA();
    /// ������� ������ ��������� ���������
    static void ReadData();
    /// ��������� ������� ������ ��������� ���������
    static void StartFPGA();
    /// ������� ���
    static int step;
    /// ��� ��������� ����������
    static float stepU;

public:
    /// ��� ����� ��������� � ������-���������� - ����������� ��� �����
    struct Control
    {
        enum E
        {
            Voltage,
            Current
        } value;
        operator uint8() const { return (uint8)value; };
    };

    struct Polarity
    {
        enum E
        {
            Positive,
            Negative
        } value;
        operator uint8() const { return (uint8)value; };
    };

    struct StepU
    {
        enum E
        {
            _100mV,
            _500mV
        } value;
        operator uint8() const { return (uint8)value; };
    };

    struct StepI
    {
        enum E
        {
            _4mA,
            _20mA
        } value;
        operator uint8() const { return (uint8)value; };
    };
};

#define NUM_STEPS       5

extern uint8 dataTester[Chan::Number][NUM_STEPS][TESTER_NUM_POINTS];

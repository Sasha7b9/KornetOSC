#pragma once
#include "defines.h"
#include "Settings/Settings.h"
#include "Settings/SettingsTypes.h"


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
};

#define NUM_STEPS       5

extern uint8 dataTester[NumChannels][NUM_STEPS][TESTER_NUM_POINTS];

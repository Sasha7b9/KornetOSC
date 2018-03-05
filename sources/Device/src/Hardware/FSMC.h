#pragma once
#include "defines.h"
#include "Tester/Tester.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef void (*pFuncTester)();

class FSMC
{
public:
    static void Init();

    static void WriteToPanel(uint8 *data, int length);

    static void WriteToFPGA8(uint8 *address, uint8 value);

    static void WriteToFPGA16(uint8 *address, uint16 value);

    static uint8 ReadFromFPGA(uint8 *address);
    /// ���������� true, ���� ��� ����� � �������
    static bool InterchangeWithPanel();
    /// ���������� �������, ������� ����� ��������� ����������� ����� ���������� ������ � �������
    static void RunFunctionAfterInteractionWitchPanel(pFuncTester func);

private:

    enum ModeFSMC
    {
        ModeNone,
        ModePanelWrite,
        ModePanelRead,
        ModeFPGA
    };
   
    static void ReadByte();

    static void ConfigureForFPGA();
    /// ����������� ���� ��������� data �� ������ D0...D7
    static void SetOutData(uint8 data);
    /// ���������� �������� � ����� D0...D7
    static uint8 GetOutData();
    /// ���������� ��������� PAN_0, PAN_1
    static uint8 ReadPAN();

    static ModeFSMC mode;

    static bool interchangeWithPanel;
    /// ���� �� ����� ����, ����� ��������� ��� ������� ����� ���������� ������ � �������
    static pFuncTester funcAfterInteractionWithPanel;
};

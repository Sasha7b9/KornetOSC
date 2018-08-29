#pragma once
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Multimeter
{
public:

    /// ������������ ��� ���������
    class Graphics
    {
    public:
        static void Update();
    private:
        static void PrepareConstantVoltage();
        static void PrepareVariableVoltage();
        static void PrepareConstantCurrent();
        static void PrepareVariableCurrent();
        static void PrepareResistance();
        static void PrepareTestDiode();
        static void PrepareRing();
    };
    /// �������������
    static void Init();

    static void Update();
    /// ������� �������� ��������� - ������������� ������� ����, ��� ��������� ��� �� ������ � ������ �������� �� �����
    static void Clear();
    /// ����� ��� ������� ��������� ��������� �� �������
    static void SetMeasure(uint8 buffer[10]);

    static UART_HandleTypeDef handlerUART;

private:
    /// ���� ������� ������� == 0, �� �������� ������ �� �����
    static char         buffer[11];
};

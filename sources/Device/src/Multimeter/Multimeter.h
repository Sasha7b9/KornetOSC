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
        static void DrawConstantVoltage();
        static void DrawVariableVoltage();
        static void DrawConstantCurrent();
        static void DrawVariableCurrent();
        static void DrawResistance();
        static void DrawTestDiode();
        static void DrawRing();
    };
    /// ������� �������� ��������� - ������������� ������� ����, ��� ��������� ��� �� ������ � ������ �������� �� �����
    static void Clear();
    /// ����� ��� ������� ��������� ��������� �� �������
    static void SetMeasure(uint8 buffer[10]);

private:
    /// ���� ������� ������� == 0, �� �������� ������ �� �����
    static uint8         buffer[10];
};

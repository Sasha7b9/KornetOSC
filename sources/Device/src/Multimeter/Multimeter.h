#pragma once
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MULTI_MEASURE           (set.multi_meas)
#define MULTI_RANGE_VV          (set.multi_rangeVV)
#define MULTI_RANGE_CV          (set.multi_rangeCV)
#define MULTI_RANGE_RESISTANCE  (set.multi_rangeResist)


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

    /// ����� ��������� �����������
    struct Measures
    {
        enum E
        {
            VoltageDC,
            VoltageAC,
            CurrentDC,
            CurrentAC,
            Resistance,
            TestDiode,
            Ring,
            Number
        } value;
        Measures(E v) : value(v) { };
        operator uint8() const { return (uint8)value; };
    };

    /// ��� - ��������� �������
    struct AVP
    {
        enum E
        {
            Off,
            On
        } value;
        AVP(E v) : value(v) { };
    };

    /// ������ ��������� ����������� ����������
    struct RangeCV
    {
        enum E
        {
            _2V,
            _20V,
            _500V
        } value;
        RangeCV(E v) : value(v) { };
        operator uint8() const { return (uint8)value; };
    };

    /// ������ ��������� ����������� ����������
    struct RangeVV
    {
        enum E
        {
            _2V,
            _20V,
            _400V
        } value;
        RangeVV(E v) : value(v) { };
        operator uint8() const { return (uint8)value; };
    };

    /// ������ ��������� ������������ ����������� ����
    struct RangeResistance
    {
        enum E
        {
            _2k,
            _20k,
            _200k,
            _10M
        } value;
        RangeResistance(E v) : value(v) { };
        operator uint8() const  { return (uint8)value; };
    };

private:
    /// ���� ������� ������� == 0, �� �������� ������ �� �����
    static char         buffer[11];
};

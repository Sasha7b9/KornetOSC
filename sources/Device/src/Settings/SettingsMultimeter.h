#pragma once

/// ����� ��������� �����������
struct MultiMeasures
{
    enum E
    {
        ConstantVoltage,
        VariableVoltage,
        ConstantCurrent,
        VariabletCurrent,
        Resistance,
        TestDiode,
        Ring,
        Number
    } value;
    MultiMeasures(E v = ConstantVoltage) : value(v) { };
    operator uint8() const  { return (uint8)value; };
};

/// ��� - ��������� �������
struct MultiAVP
{
    enum E
    {
        Off,
        On
    } value;
    MultiAVP(E v = Off) : value(v) { };
};

/// ������ ��������� ����������� ����������
struct MultiRangeCV
{
    enum E
    {
        _2V,
        _20V,
        _500V
    } value;
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
};

#define MULTI_MEASURE (set.multi_meas)

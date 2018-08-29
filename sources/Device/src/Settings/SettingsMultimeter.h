#pragma once
#include "defines.h"

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
    MultiRangeCV(E v = _500V) : value(v) {};
    operator uint8() const { return (uint8)value; };
};

/// ������ ��������� ����������� ����������
struct MultiRangeVV
{
    enum E
    {
        _2V,
        _20V,
        _400V
    } value;
    MultiRangeVV(E v = _400V) : value(v) {};
    operator uint8() const { return (uint8)value; };
};

/// ������ ��������� ������������ ����������� ����
struct MultiRangeResistance
{
    enum E
    {
        _2k,
        _20k,
        _200k,
        _10M
    } value;
    MultiRangeResistance(E v = _10M) : value(v) {};
    operator uint8() const { return (uint8)value; };
};

#define MULTI_MEASURE           (set.multi_meas)
#define MULTI_RANGE_VV          (set.multi_rangeVV)
#define MULTI_RANGE_CV          (set.multi_rangeCV)
#define MULTI_RANGE_RESISTANCE  (set.multi_rangeResist)

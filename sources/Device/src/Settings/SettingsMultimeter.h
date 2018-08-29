#pragma once

/// Режим измерений мультиметра
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

/// АВП - автовыбор предела
struct MultiAVP
{
    enum E
    {
        Off,
        On
    } value;
    MultiAVP(E v = Off) : value(v) { };
};

/// Предел имзерения постоянного напряжения
struct MultiRangeCV
{
    enum E
    {
        _2V,
        _20V,
        _500V
    } value;
};

/// Предел измерения переменного напряжения
struct RangeVV
{
    enum E
    {
        _2V,
        _20V,
        _400V
    } value;
};

/// Предел измерения сопротивленя постоянному току
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

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

    /// Используется для отрисовки
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
    /// Инициализация
    static void Init();

    static void Update();
    /// Функция обнуляет измерения - устанавливает признак того, что измерения ещё не пришли и ничего выводить не нужно
    static void Clear();
    /// Через эту функцию поступает измерение от прибора
    static void SetMeasure(uint8 buffer[10]);

    static UART_HandleTypeDef handlerUART;

    /// Режим измерений мультиметра
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

    /// АВП - автовыбор предела
    struct AVP
    {
        enum E
        {
            Off,
            On
        } value;
        AVP(E v) : value(v) { };
    };

    /// Предел имзерения постоянного напряжения
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

    /// Предел измерения переменного напряжения
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
        RangeResistance(E v) : value(v) { };
        operator uint8() const  { return (uint8)value; };
    };

private:
    /// Если нулевой элемент == 0, то выводить ничего не нужно
    static char         buffer[11];
};

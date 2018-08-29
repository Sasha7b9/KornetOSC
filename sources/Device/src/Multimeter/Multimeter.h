#pragma once
#include "defines.h"


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
        static void DrawConstantVoltage();
        static void DrawVariableVoltage();
        static void DrawConstantCurrent();
        static void DrawVariableCurrent();
        static void DrawResistance();
        static void DrawTestDiode();
        static void DrawRing();
    };
    /// Функция обнуляет измерения - устанавливает признак того, что измерения ещё не пришли и ничего выводить не нужно
    static void Clear();
    /// Через эту функцию поступает измерение от прибора
    static void SetMeasure(uint8 buffer[10]);

private:
    /// Если нулевой элемент == 0, то выводить ничего не нужно
    static uint8         buffer[10];
};

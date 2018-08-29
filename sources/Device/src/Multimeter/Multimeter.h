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

private:
    /// Если нулевой элемент == 0, то выводить ничего не нужно
    static char         buffer[11];
};

#pragma once
#include "defines.h"
#include "Settings/Settings.h"
#include "Settings/SettingsTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Tester
{
public:
    static void Init();

    static void Enable();

    static void Disable();

    static void Update();

    static void ProcessStep();
    /// Загружает полярность из Settings
    static void LoadPolarity();
    /// Устанавливает шаг изменения напряжения в соотвествии с настройками Settings
    static void LoadStep();

private:
    /// Загрузить FPGA в соответствии с установленными настройками
    static void LoadFPGA();
    /// Считать данные очередной ступеньки
    static void ReadData();
    /// Запустить процесс чтения очередной ступеньки
    static void StartFPGA();
    /// Текущий шаг
    static int step;
    /// Шаг изменения напряжения
    static float stepU;
};

#define NUM_STEPS       5

extern uint8 dataTester[NumChannels][NUM_STEPS][TESTER_NUM_POINTS];

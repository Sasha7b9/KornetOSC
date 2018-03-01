#pragma once
#include "Controls.h"
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Keyboard
{
public:

    static void Init();

    static bool BufferIsEmpty();

    static StructControl GetNextControl();

    static void Update();
    /// Количество выводов RL для опроса клавиатуры
    static const int NUM_RL = 6;
    /// Количество выводов SL для опроса клавиатуры
    static const int NUM_SL = 8;
    /// Возращает имя органа управления
    static const char *ControlName(Control control);

private:

    static void FillCommand(Control control, TypePress typePress);

    static uint TimeBetweenRepeats(uint time);

    static StructControl commands[10];

    static int pointer;
    /// При обнаружении нажатия кнопки сюда записывается время нажатия
    static uint timePress[NUM_RL][NUM_SL];

    static bool init;
};

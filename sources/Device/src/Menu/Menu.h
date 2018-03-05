#pragma once
#include "MenuControls.h"
#include "Keyboard/Buttons.h"
#include "Settings/SettingsTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Menu
{
public:
    static void Init();
    static void Update();
    static void ButtonPress(Key button, TypePress typePress);
    static void Draw();
    static void SaveSettings();

private:
    static void OnPressNone();
    static void OnPressRangeLessA();
    static void OnPressRangeMoreA();
    static void OnPressRangeLessB();
    static void OnPressRangeMoreB();
    static void OnPressTBaseMore();
    static void OnPressTBaseLess();
    static void OnPressRShiftLessA();
    static void OnPressRShiftMoreA();
    static void OnPressRShiftLessB();
    static void OnPressRShiftMoreB();
    static void OnPressTShiftLess();
    static void OnPressTShiftMore();
    static void OnPressTrigLevLess();
    static void OnPressTrigLevMore();
    static void OnPressChannelA();
    static void OnPressChannelB();
    static void OnPressF1();
    static void OnPressF2();
    static void OnPressF3();
    static void OnPressF4();
    static void OnPressF5();
    static void OnPressService();
    static void OnPressStartStop();
    static void OnPressTrig();
    static void OnPressMenu();
    static void OnPressFunction();
    static void OnPressEnter();

    static void VerifyOnDoubleClick(int src, int dir);

    /// \tode Здесь хранится время предыдущего нажатия кнопки для отлова двойного нажатия.
    /// 1 индекс 1канал/2канал/синхронизация/время, 2 индекс - вниз/вверх
    static uint timePrevPress[4][2];
    /// Время двойного нажатия
    static const uint timeDoubleClick = 250;
    /// Здесь хранится тип нажатий нопки для функции ButtonPress
    static TypePress typePress;
    /// Текущая обрабатываемая кнопка
    static Key button;
    /// Если true, то кнопка нажата
    static bool isPressed[NumButtons];
    /// Время последнего нажатия кнопки. Нужно для того, чтобы периодически сохранять настройки
    static uint timeLastPressedButton;
    /// Установить меню в соответствие с текущим режимом
    static void TuneOnDevice();
};

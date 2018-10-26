#include "defines.h"
#include "Display/Painter.h"
#include "Menu/Pages/Include/PageDisplay.h"
#include "FPGA/FPGA.h"
#include "Menu/Menu.h"
#include "Utils/CommonFunctions.h"
#include "Utils/Dictionary.h"
#include "Settings/Settings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase ppDisplaySettings;
extern const PageBase pageDisplay;

const PageBase *PageDisplay::pointer = &pageDisplay;
const PageBase *PageDisplay::PageSettings::pointer = &ppDisplaySettings;


//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2(cThickness,                                                                                            //--- ДИСПЛЕЙ - Толщина ---
             "Толщина", "Thickness",
             "Позволяет изменять толщину выводимых на экран изображений",
             "Allows you to change the thickness of the signals displayed on the screen",
             "x1", "x1",
             "x3", "x3",
             THICKNESS_SIGNAL, pageDisplay, FuncActive, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PageDisplay::Init()
{
    PageSettings::PageColors::OnChanged_Settings_Colors_Background(true);   // Заносим значения в гувернёры цветов
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2(       cViewMode,                                                                                         //--- ДИСПЛЕЙ - Отображение ---
    "Отображ.", "View",
    "Задаёт режим отображения сигнала.",
    "Sets the display mode signal.",
    "Вектор", "Vector",
    "Точки",  "Points",
    MODE_DRAW_SIGNAL, pageDisplay, FuncActive, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static bool IsActive_MinMax()
{
    return !IN_RANDOM_MODE && !IN_P2P_MODE;
}

static void OnChanged_MinMax(bool)
{
    /*
    int maxMeasures = DS_NumberAvailableEntries();  
    int numMinMax = sDisplay_NumberMinMax();

    if (maxMeasures < numMinMax)
    {
    display.ShowWarningWithNumber(ExcessValues, maxMeasures);
    }
    */
}

DEF_CHOICE_8(       cMinMax,                                                                                              //--- ДИСПЛЕЙ - Мин Макс ---
    "Мин Макс", "Min Max",
    "Задаёт количество последних измерений, по которым строятся ограничительные линии, огибающие минимумы и максимумы измерений.",
    "Sets number of the last measurements on which the limiting lines which are bending around minima and maxima of measurements are under "
    "construction."
    ,
    DISABLE_RU,DISABLE_EN,
    "2",   "2",
    "4",   "4",
    "8",   "8",
    "16",  "16",
    "32",  "32",
    "64",  "64",
    "128", "128",
    ENUM_MIN_MAX, pageDisplay, IsActive_MinMax, OnChanged_MinMax, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_REG_10(  cSmoothing,                                                                                        //--- ДИСПЛЕЙ - Сглаживание ---
    "Сглаж.", "Smoothing",
    "Устанавливает количество точек для расчёта сглаженного по соседним точкам сигнала.",
    "Establishes quantity of points for calculation of the signal smoothed on the next points."
    ,
    DISABLE_RU, DISABLE_EN,
    "2 точки",  "2 points",
    "3 точки",  "3 points",
    "4 точки",  "4 points",
    "5 точек",  "5 points",
    "6 точек",  "6 points",
    "7 точек",  "7 points",
    "8 точек",  "8 points",
    "9 точек",  "9 points",
    "10 точек", "10 points",
    ENUM_SMOOTHING, pageDisplay, FuncActive, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PageDisplay::OnChanged_RefreshFPS(bool)
{
    FPGA::SetENumSignalsInSec(ENUM_SIGNALS_IN_SEC.ToFPS());
}

DEF_CHOICE_5(       cRefreshFPS,                                                                                    //--- ДИСПЛЕЙ - Частота обновл ---
    "Частота обновл", "Refresh rate",
    "Задаёт максимальное число выводимых в секунду кадров.",
    "Sets the maximum number of the shots removed in a second.",
    "25", "25",
    "10", "10",
    "5",  "5",
    "2",  "2",
    "1",  "1",
    ENUM_SIGNALS_IN_SEC, pageDisplay, FuncActive, PageDisplay::OnChanged_RefreshFPS, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2(       cScaleYtype,                                                                                          //--- ДИСПЛЕЙ - Смещение ---
    "Смещение", "Оffset",
    "Задаёт режим удержания смещения по вертикали\n1. \"Напряжение\" - сохраняется наряжение смещения.\n2. \"Деления\" - сохраняется положение "
    "смещения на экране.",
    "Sets the mode of retaining the vertical displacement\n1. \"Voltage\" - saved dressing bias.\n2. \"Divisions\" - retained the position of "
    "the offset on the screen.",
    "Напряжение", "Voltage",
    "Деления", "Divisions",
    LINKING_RSHIFT, pageDisplay, FuncActive, FuncChangedChoice, FuncDraw
)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_10( pageDisplay,                                                                                                            //--- ДИСПЛЕЙ ---
    "ДИСПЛЕЙ", "DISPLAY",
    "Содержит настройки отображения дисплея.",
    "Contains settings of display of the display.",
    &cViewMode,                             ///< ДИСПЛЕЙ - Отображение
    PageDisplay::PageAccumulation::pointer, ///< ДИСПЛЕЙ - НАКОПЛЕНИЕ
    PageDisplay::PageAverage::pointer,      ///< ДИСПЛЕЙ - УСРЕДНЕНИЕ
    &cMinMax,                               ///< ДИСПЛЕЙ - Мин Макс
    &cSmoothing,                            ///< ДИСПЛЕЙ - Сглаживание
    &cRefreshFPS,                           ///< ДИСПЛЕЙ - Частота обновл
    PageDisplay::PageGrid::pointer,         ///< ДИСПЛЕЙ - СЕТКА
    &cScaleYtype,                           ///< ДИСПЛЕЙ - Смещение
    &ppDisplaySettings,                     ///< ДИСПЛЕЙ - НАСТРОЙКИ
    &cThickness,                            ///< ДИСПЛЕЙ - Толщина
    Page::Name::Display, Menu::pageMain, FuncActive, EmptyPressPage
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChanged_Settings_Brightness()
{
    Painter::SetBrightnessDisplay(BRIGHTNESS_DISPLAY);
}

DEF_GOVERNOR(       gSettings_Brightness,                                                                      //--- ДИСПЛЕЙ - НАСТРОЙКИ - Яркость ---
    "Яркость", "Brightness",
    "Установка яркости свечения дисплея",
    "Setting the brightness of the display",
    BRIGHTNESS_DISPLAY, 0, 100, ppDisplaySettings, FuncActive, OnChanged_Settings_Brightness, FuncBeforeDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_GOVERNOR(       gSettings_Levels,                                                                           //--- ДИСПЛЕЙ - НАСТРОЙКИ - Уровни ---
    "Уровни", "Levels",
    "Задаёт время, в течение которого после поворота ручки сещения напряжения на экране остаётся вспомогательная метка уровня смещения",
    "Defines the time during which, after turning the handle visits to the voltage on the screen remains auxiliary label offset level",
    TIME_SHOW_LEVELS, 0, 125, ppDisplaySettings, FuncActive, FuncChanged, FuncBeforeDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_GOVERNOR(       gSettings_Time,                                                                              //--- ДИСПЛЕЙ - НАСТРОЙКИ - Время ---
    "Время", "Time",
    "Установка времени, в течение которого сообщения будут находиться на экране",
    "Set the time during which the message will be on the screen",
    TIME_MESSAGES, 1, 99, ppDisplaySettings, FuncActive, FuncChanged, FuncBeforeDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_3(       cSettings_StringNavigation,                                                            //--- ДИСПЛЕЙ - НАСТРОЙКИ - Строка меню ---
    "Строка меню", "Path menu",
    "При выборе \nПоказывать\n слева вверху экрана выводится полный путь до текущей страницы меню", /// \todo Исправить перевод
    "When choosing \nDisplay\n at the top left of the screen displays the full path to the current page menu",
    "Временно", "Temporary",    /// \todo Исправить перевод
    "Всегда", "All",
    "Никогда", "None",
    SHOW_STRING_NAVI, ppDisplaySettings, FuncActive, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChanged_Settings_AltMarkers(bool active)
{
    Display::ChangedRShiftMarkers(active);
}

DEF_CHOICE_3(       cSettings_AltMarkers,                                                                 //--- ДИСПЛЕЙ - НАСТРОЙКИ - Доп. маркеры ---
    "Доп. маркеры", "Alt. markers",
    "Устанавливает режим отображения дополнительных маркеров уровней смещения и синхронизации:\n"
    "\"Скрывать\" - дополнительные маркеры не показываются,\n"
    "\"Показывать\" - дополнительные маркеры показываются всегда,\n"
    "\"Авто\" - дополнительные маркеры показываются в течение 5 сек после поворота ручки смещения канала по напряжению или уровня синхронизации",
    "Sets the display mode of additional markers levels of displacement and synchronization:\n"
    "\"Hide\" - additional markers are not shown,\n"
    "\"Show\" - additional markers are shown always,\n"
    "\"Auto\" - additional markers are displayed for 5 seconds after turning the handle channel offset voltage or trigger level"
    ,
    "Скрывать", "Hide",
    "Показывать", "Show",
    "Авто", "Auto",
    ALT_MARKERS, ppDisplaySettings, FuncActive, OnChanged_Settings_AltMarkers, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChanged_Settings_AutoHide(bool autoHide)
{
    Menu::SetAutoHide(autoHide);
}

DEF_CHOICE_6(cSettings_AutoHide,                                                                       //--- ДИСПЛЕЙ - НАСТРОЙКИ - Скрывать ---
    "Скрывать", "Hide",
    "Установка после последнего нажатия кнопки или поворота ручки, по истечении которого меню автоматически убирается с экрана",
    "Installation after the last keystroke or turning the handle, after which the menu will automatically disappear",
    "Никогда", "Never",
    "Через 5 сек", "Through 5 s",
    "Через 10 сек", "Through 10 s",
    "Через 15 сек", "Through 15 s",
    "Через 30 сек", "Through 30 s",
    "Через 60 сек", "Through 60 s",
    MENU_AUTO_HIDE, ppDisplaySettings, FuncActive, OnChanged_Settings_AutoHide, FuncDraw
)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_7(         ppDisplaySettings,                                                                                      // ДИСПЛЕЙ - НАСТРОЙКИ ///
    "НАСТРОЙКИ", "SETTINGS",
    "Дополнительные настройки дисплея",
    "Additional display settings",
    PageDisplay::PageSettings::PageColors::pointer,     ///< ДИСПЛЕЙ - НАСТРОЙКИ - ЦВЕТА
    &gSettings_Brightness,                              ///< ДИСПЛЕЙ - НАСТРОЙКИ - Яркость
    &gSettings_Levels,                                  ///< ДИСПЛЕЙ - НАСТРОЙКИ - Уровни
    &gSettings_Time,                                    ///< ДИСПЛЕЙ - НАСТРОЙКИ - Время
    &cSettings_StringNavigation,                        ///< ДИСПЛЕЙ - НАСТРОЙКИ - Строка меню
    &cSettings_AltMarkers,                              ///< ДИСПЛЕЙ - НАСТРОЙКИ - Доп. маркеры
    &cSettings_AutoHide,                                ///< ДИСПЛЕЙ - НАСТРОЙКИ - Скрывать
    Page::Name::Display_Settings, &pageDisplay, FuncActive, EmptyPressPage
)

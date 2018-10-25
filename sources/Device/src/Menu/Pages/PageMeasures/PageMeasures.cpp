#include "defines.h"
#include "FPGA/FPGA.h"
#include "Osci/FrequencyCounter.h"
#include "Display/Painter.h"
#include "Hardware/Sound.h"
#include "Menu/Pages/Include/Definition.h"
#include "Menu/Pages/Include/PageMeasures.h"
#include "Utils/Math.h"
#include "Utils/Measure.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pMeasures;
extern const PageBase ppTune;

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2(       cIsShow,                                                                                          //--- ИЗМЕРЕНИЯ - Показывать ---
    "Показывать", "Show",
    "Выводить или не выводить измерения на экран",
    "Output or output measurements on screen",
    "Нет", "No",
    "Да",  "Yes",
    SHOW_MEASURES, pMeasures, FuncActive, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static bool IsActive_Number()
{
    return SHOW_MEASURES;
}

DEF_CHOICE_7(       cNumber,                                                                                          //--- ИЗМЕРЕНИЯ - Количество ---
    "Количество", "Number"
    ,
    "Устанавливает максимальное количество выводимых измерений:\n"
    "\"1\" - одно измерение\n"
    "\"2\" - два измерения\n"
    "\"1х5\" - 1 строка с пятью измерениями\n"
    "\"2х5\" - 2 строки с пятью измерениями в каждой\n"
    "\"3х5\" - 3 строки с пятью измерениями в каждой\n"
    "\"6x1\" - 6 строк по одному измерению в каждой\n"
    "\"6х2\" - 6 строк по два измерения в каждой"
    ,
    "Sets the maximum number of output measurements:\n"
    "\"1\" - one measurement\n"
    "\"2\" - two measurements\n"
    "\"1x5\" - 1 line with the five dimensions\n"
    "\"2x5\" - two rows with five measurements in each\n"
    "\"3x5\" - 3 lines with five measurements in each"
    "\"6x1\" - 6 lines, one in each dimension\n"
    "\"6x2\" - 6 lines of two dimensions in each\n",
    "1", "1",
    "2", "2",
    "1x5", "1x5",
    "2x5", "2x5",
    "3x5", "3x5",
    "6x1", "6x1",
    "6x2", "6x2",
    NUM_MEASURES, pMeasures, IsActive_Number, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static bool IsActive_Channels()
{
    return SHOW_MEASURES;
}

DEF_CHOICE_3(       cChannels,                                                                                            //--- ИЗМЕРЕНИЯ - Каналы ---
    "Каналы", "Channels",
    "По каким каналам выводить измерения",
    "Which channels to output measurement",
    "1",     "1",
    "2",     "2",
    "1 и 2", "1 and 2",
    SOURCE_MEASURES, pMeasures, IsActive_Channels, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static bool IsActive_Mode()
{
    return SHOW_MEASURES;
}

DEF_CHOICE_2(       cMode,                                                                                                   //--- ИЗМЕРЕНИЯ - Вид ---
    "Вид", "View",
    "Уменьшать или нет зону вывода сигнала для исключения перекрытия его результами измерений",
    "Decrease or no zone output signal to avoid overlapping of its measurement results",
    "Как есть",  "As is",
    "Уменьшать", "Reduce",
    MODE_VIEW_SIGNALS, pMeasures, IsActive_Mode, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_SMALL_BUTTON_EXIT(  bTune_Exit,                                                                            //--- ИЗМЕРЕНИЯ - НАСТРОИТЬ - Выход ---
    ppTune, FuncActive, OnPressSB_Exit, DrawSB_Exit
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Tune_Markers()
{
    Measure::ShortPressOnSmallButonMarker();
}

static void Draw_Tune_Markers(int x, int y)
{
    Painter::SetFont(Font::Type::_UGO2);
    Painter::Draw4SymbolsInRect(x + 2, y + 2, '\x60');
    Painter::SetFont(Font::Type::_8);
}

DEF_SMALL_BUTTON(   bTune_Markers,                                                                            //--- ИЗМЕРЕНИЯ - НАСТРОИТЬ - Маркер ---
    "Маркер", "Marker",
    "Позволяет установить маркеры для визуального контроля измерений",
    "Allows to establish markers for visual control of measurements",
    ppTune, FuncActive, OnPress_Tune_Markers, Draw_Tune_Markers
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Tune_Settings()
{
    Measure::pageChoiceIsActive = !Measure::pageChoiceIsActive;
    if (Measure::pageChoiceIsActive)
    {
        Measure::posOnPageChoice = (int8)set.meas_measures[Measure::posActive];
    }
}

static void Draw_Tune_Settings(int x, int y)
{
    Painter::SetFont(Font::Type::_UGO2);
    Painter::Draw4SymbolsInRect(x + 2, y + 1, '\x62');
    Painter::SetFont(Font::Type::_8);
}

DEF_SMALL_BUTTON(   bTune_Settings,                                                                        //--- ИЗМЕРЕНИЯ - НАСТРОИТЬ - Настройка ---
    "Настройка", "Setup",
    "Позволяет выбрать необходимые измерения",
    "Allows to choose necessary measurements",
    ppTune, FuncActive, OnPress_Tune_Settings, Draw_Tune_Settings
)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool IsActive_Tune()
{
    return SHOW_MEASURES;
}

static void OnRegSet_Tune(int angle)
{
    static const int8 step = 3;
    static int8 currentAngle = 0;
    currentAngle += (int8)angle;
    if (currentAngle < step && currentAngle > -step)
    {
        return;
    }
    if (Measure::pageChoiceIsActive)
    {
        Measure::posOnPageChoice += (int8)Math::Sign(currentAngle);
        Sound::RegulatorSwitchRotate();
        if (Measure::posOnPageChoice < 0)
        {
            Measure::posOnPageChoice = Measure::Type::Number - 1;
        }
        else if (Measure::posOnPageChoice == Measure::Type::Number)
        {
            Measure::posOnPageChoice = 0;
        }
        set.meas_measures[Measure::posActive] = (Measure::Type)Measure::posOnPageChoice;
        Painter::ResetFlash();
    }
    else
    {
        Measure::ChangeActive(currentAngle);

        Sound::RegulatorSwitchRotate();
    }
    currentAngle = 0;
}

DEF_PAGE_SB(ppTune,                                                                                               // ИЗМЕРЕНИЯ - НАСТРОИТЬ ///
    "НАСТРОИТЬ", "CONFIGURE",
    "Переход в режми точной настройки количества и видов измерений",
    "Transition to rezhm of exact control of quantity and types of measurements",
    &bTune_Exit,
    0,
    0,
    0,
    &bTune_Markers,
    &bTune_Settings,
    Page::Name::SB_Measures_Tune, &pMeasures, IsActive_Tune, EmptyPressPage, FuncDrawPage, OnRegSet_Tune
)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const PageBase *PageMeasures::pointer = &pMeasures;

DEF_PAGE_5(         pMeasures,                                                                                                        // ИЗМЕРЕНИЯ ///
    "ИЗМЕРЕНИЯ", "MEASURES",
    "Автоматические измерения",
    "Automatic measurements",
    &cIsShow,       // ИЗМЕРЕНИЯ - Показывать
    &cNumber,       // ИЗМЕРЕНИЯ - Количество
    &cChannels,     // ИЗМЕРЕНИЯ - Каналы
    &ppTune,        // ИЗМЕРЕНИЯ - НАСТРОИТЬ
    &cMode,         // ИЗМЕРЕНИЯ - Вид
    Page::Name::Measure, Menu::pageMain, FuncActive, EmptyPressPage
)

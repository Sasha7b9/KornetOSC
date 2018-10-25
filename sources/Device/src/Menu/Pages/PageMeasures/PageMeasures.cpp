#include "defines.h"
#include "Menu/MenuItems.h"
#include "Settings/SettingsTime.h"
#include "Utils/Measure.h"
#include "Settings/Settings.h"
#include "Menu/Pages/Include/PageMeasures.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pMeasures;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_6(         pMeasures,                                                                                                        // ИЗМЕРЕНИЯ ///
    "ИЗМЕРЕНИЯ", "MEASURES",
    "Автоматические измерения",
    "Automatic measurements",
    PageMeasures::PageCursors::pointer, ///< ИЗМЕРЕНИЯ - КУРСОРНЫЕ
    &cIsShow,                           ///< ИЗМЕРЕНИЯ - Показывать
    &cNumber,                           ///< ИЗМЕРЕНИЯ - Количество
    &cChannels,                         ///< ИЗМЕРЕНИЯ - Каналы
    PageMeasures::PageTune::pointer,    ///< ИЗМЕРЕНИЯ - НАСТРОИТЬ
    &cMode,                             ///< ИЗМЕРЕНИЯ - Вид
    Page::Name::Measures, Menu::pageMain, FuncActive, EmptyPressPage
)

const PageBase *PageMeasures::pointer = &pMeasures;

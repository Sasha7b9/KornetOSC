#pragma once
#include "defines.h"
#include "structs.h"
#include "SettingsTypes.h"
#include "SettingsTime.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Settings
 *  @{
 *  @defgroup SettingsDisplay Settings Display
 *  @{
 */


struct ModeDrawSignal
{
    enum E
    {
        Lines,
        Points
    } value;
    operator uint8() const { return (uint8)value; };
};

/// Толщина рисуемого сигнала
struct ThicknessSignal
{
    enum E
    {
        _1,         ///< Сигнал рисуется линией толщиной одна точка
        _3          ///< Сигнал рисуется линией толщиной три точки
    } value;
    operator uint8() const { return (uint8)value; };
};

/// Через какое время после последнего нажатия кнопки скрывать меню.
struct MenuAutoHide
{
    enum E
    {
        None = 0,   ///< Никогда.
        _5   = 5,   ///< Через 5 секунд.
        _10  = 10,  ///< Через 10 секунд.
        _15  = 15,  ///< Через 15 секунд.
        _30  = 30,  ///< Через 30 секунд.
        _60  = 60   ///< Через 60 секунд.
    } value;
    operator uint8() const { return (uint8)value; };
};

/// Режим отображения дополнительных боковых маркеров смещения по напряжению.
struct AltMarkers
{
    enum E
    {
        Hide,        /// Никода не выводить.
        Show,        /// Всегда выводить.
        AutoHide     /// Выводить и прятать через timeShowLevels.
    } value;
    operator uint8() const { return (uint8)value; };
};

/// Тип привязки к смещению по вертикали
struct LinkingRShift
{
    enum E
    {
        Voltage,      ///< Смещение привязано к напряжению
        Position      ///< Смещение привязано к позиции
    } value;
};

/// Тип сетки на экране.
struct TypeGrid
{
    enum E
    {
        _1,
        _2,
        _3,
        _4,
        Size
    } value;
    operator uint8() const { return (uint8)value; };
};

/// Ограничение FPS.
struct ENumSignalsInSec
{
    enum E
    {
        _25,
        _10,
        _5,
        _2,
        _1
    } value;
    ENumSignalsInSec(E v = _25) : value(v) {};
    operator uint8() const { return (uint8)value; };
};

/// Количество точек для расчёта сглаживания.
struct ENumSmoothing
{
    enum E
    {
        Disable,
        _2points,
        _3points,
        _4points,
        _5points,
        _6points,
        _7points,
        _8points,
        _9points,
        _10points
    } value;
    operator uint8() const { return (uint8)value; };
};

struct ModeAccumulation
{
    enum E
    {
        NoReset,   /// В этом режиме показываются строго N последних.
        Reset      /// В этом режиме набираются N последних и потом сбрасываются.
    } value;
    operator uint8() const { return (uint8)value; };
};

/// Количество накоплений.
struct ENumAccum
{
    enum E
    {
        _1,
        _2,
        _4,
        _8,
        _16,
        _32,
        _64,
        _128,
        _Infinity
    } value;
    operator uint8() const { return (uint8)value; };
};

/// Количество измерений для расчёта минимального и максимального значений.
struct ENumMinMax
{
    enum E
    {
        _1,
        _2,
        _4,
        _8,
        _16,
        _32,
        _64,
        _128
    } value;
    operator uint8() const { return (uint8)value; };
};

/// Количество усреднений по измерениям.
struct ENumAverage
{
    enum E
    {
        _1,
        _2,
        _4,
        _8,
        _16,
        _32,
        _64,
        _128,
        _256,
        _512
    } value;
    operator uint8() const { return (uint8)value; };
};

struct ColorScheme
{
    enum E
    {
        WhiteLetters,   ///< В этом случае заголовки элементов меню пишутся белым - не очень хорошо видно снизу
        BlackLetters    ///< В этом случае заголовки элементов меню пишутся чёрным - не очень красиво выглядит
    } value;
};

struct DisplayOrientation
{
    enum E
    {
        Direct,
        Back
    } value;
};

/// Режим показа строки навигации
struct ShowStrNavi
{
    enum E
    {
        Temp,   ///< Показывать на несколько секунд
        All,    ///< Всегда показывать
        None    ///< Никогда не показывать
    } value;
    operator uint8() const { return (uint8)value; };
};


#define THICKNESS_SIGNAL            (set.disp_thickness)
#define THICKNESS_SIGNAL_IS_3       (THICKNESS_SIGNAL == ThicknessSignal::_3)


#define SHIFT_IN_MEMORY             (set.disp_shiftInMemory)
#define TIME_MESSAGES               (set.disp_timeMessages)
#define ENUM_SIGNALS_IN_SEC         (set.disp_ENumSignalsInSec)
#define NUM_SIGNALS_IN_SEC          (sDisplay_NumSignalsInS())
#define LAST_AFFECTED_CH            (set.disp_lastAffectedChannel)
#define LAST_AFFECTED_CH_IS_A       (LAST_AFFECTED_CH.IsA())
#define DISPLAY_ORIENTATION         (set.dbg_Orientation)

#define SHOW_STRING_NAVI            (set.disp_showStringNavigation)
#define SHOW_STRING_NAVI_TEMP       (SHOW_STRING_NAVI == ShowStrNavi::Temp)
#define SHOW_STRING_NAVI_ALL        (SHOW_STRING_NAVI == ShowStrNavi::All)

#define MODE_DRAW_SIGNAL            (set.disp_modeDrawSignal)
#define MODE_DRAW_SIGNAL_IS_LINES   (MODE_DRAW_SIGNAL == ModeDrawSignal::Lines)
#define MODE_DRAW_SIGNAL_IS_POINTS  (MODE_DRAW_SIGNAL == ModeDrawSignal::Points)

#define TYPE_GRID                   (set.disp_typeGrid)
#define TYPE_GRID_1                 (TYPE_GRID == TypeGrid::_1)
#define TYPE_GRID_2                 (TYPE_GRID == TypeGrid::_2)
#define TYPE_GRID_3                 (TYPE_GRID == TypeGrid::_3)
#define TYPE_GRID_4                 (TYPE_GRID == TypeGrid::_4)

#define ENUM_ACCUM                  (set.disp_ENumAccum)
#define ENUM_ACCUM_INF              (ENUM_ACCUM == ENumAccum_Infinity)
#define NUM_ACCUM                   (1 << (int)ENUM_ACCUM)                   /* Возвращает число накоплений */
#define IN_ACCUM_MODE               (ENUM_ACCUM > ENumAccum_1)

#define MODE_ACCUM                  (set.disp_modeAccumulation)
#define MODE_ACCUM_RESET            (MODE_ACCUM == ModeAccumulation::Reset)
#define MODE_ACCUM_NO_RESET         (MODE_ACCUM == ModeAccumulation::NoReset)

#define ENUM_MIN_MAX                (set.disp_ENumMinMax)
#define MIN_MAX_ENABLED             (ENUM_MIN_MAX != ENumMinMax::_1)
#define NUM_MIN_MAX                 (1 << (int)ENUM_MIN_MAX)                /* Возвращает количество измерений сигналов для расчёта минимумов и максимумов. */

#define MODE_AVE                    (set.disp_modeAveraging)
#define ENUM_AVE                    (set.disp_ENumAverage)
#define NUM_AVE                     (1 << (int)ENUM_AVE)
#define IN_AVERAGING_MODE           (ENUM_AVE > ENumAverage::_1 && (!IN_P2P_MODE))

#define ENUM_SMOOTHING              (set.disp_ENumSmoothing)
#define NUM_SMOOTHING               (sDisplay_NumPointSmoothing())
#define SMOOTHING_ENABLED           (ENUM_SMOOTHING != ENumSmoothing::Disable)

#define ALT_MARKERS                 (set.disp_altMarkers)
#define ALT_MARKERS_SHOW            (ALT_MARKERS == AltMarkers::Show)
#define ALT_MARKERS_HIDE            (ALT_MARKERS == AltMarkers::Hide)
#define ALT_MARKERS_AUTO            (ALT_MARKERS == AltMarkers::AutoHide)

#define LINKING_RSHIFT              (set.disp_linkingRShift)

#define BACKGROUND                  (set.disp_background)
#define BACKGROUND_BLACK            (BACKGROUND == Background::Black)

#define MENU_AUTO_HIDE              (set.disp_menuAutoHide)

#define BRIGHTNESS_DISPLAY          (set.disp_brightness)

#define BRIGHTNESS_GRID             (set.disp_brightnessGrid)

#define SET_NUM_BYTES_ON_DISPLAY    (SET_PEAKDET_EN ? 281 * 2 : 281)


/// Возвращает ограничение частоты кадров
int sDisplay_NumSignalsInS();
/// Устанавливает ограничение частоты кадров
void sDisplay_SetNumSignalsInS(int maxFPS);
/// Возвращает число точек сглаживающего фильтра (режим ДИСПЛЕЙ - Сглаживание)
int sDisplay_NumPointSmoothing();
/// Возвращает адрес первой и последней точки на экране в координатах экрана
BitSet64 sDisplay_PointsOnDisplay();
/// \brief Возращает адрес первой и последней точки в координатах экрана
BitSet64 sDisplay_BytesOnDisplay();
/// Возвращает время, через которое меню автоматически скрывается, если не было больше нажатий
int sDisplay_TimeMenuAutoHide();
/// Если экран разделён на две части и основной сигнал выводится сверху - например, в режиме вывода спектра
bool sDisplay_IsSeparate();
/// brightness = 1..100
void sDisplay_SetBrightness(int16 brightness);
/// Возвращает режим усреднения
ModeAveraging sDisplay_GetModeAveraging();

int sDisplay_NumAverage();
/// Это смещение экрана по памяти в режиме пикового детектора оно будет в два раза меньше, чем байт, потому что каждая точка представлена двумя байтами
int sDisplay_ShiftInMemoryInPoints();

#define SHIFT_IN_MEMORY_IN_POINTS sDisplay_ShiftInMemoryInPoints()

/** @}  @}
 */

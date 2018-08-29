#pragma once
#include "defines.h"
#include "SettingsChannel.h"


#define COMMON_ENUM     uint8 value; operator uint8() const { return value; }; operator uint8() { return value; }


/// Чем будем управлять в тестер-компоненте - напряжением или током
struct TesterControl
{
    enum
    {
        Voltage,
        Current
    };
    COMMON_ENUM;
};


struct TesterPolarity
{
    enum
    {
        Positive,
        Negative
    };
    COMMON_ENUM;
};

struct TesterStepU
{
    enum
    {
        _100mV,
        _500mV
    };
    COMMON_ENUM;
};

struct TesterStepI
{
    enum
    {
        _4mA,
        _20mA
    };
    COMMON_ENUM
};

/// Каким курсором управлять
struct CursCntrl
{
    enum
    {
        _1,        ///< первым
        _2,        ///< вторым
        _1_2,      ///< обоими
        Disable    ///< никаким
    };
    COMMON_ENUM;
};

/// Тип усреднений по измерениям
struct ModeAveraging
{
    enum
    {
        Accurately,   ///< Усреднять точно.
        Around        ///< Усреднять приблизительно.
    };
    ModeAveraging(uint8 v = Accurately) : value(v) {};
    COMMON_ENUM;
};

/// Выбор цвета фона.
struct Background
{
    enum
    {
        Black,
        White
    };
    uint8 value;
    operator uint8() const
    {
        return value;
    }
};

/// Положение точки синхронизация на сигнале.
struct TPos
{
    enum
    {
        Left,          ///< Привязка к левому краю.
        Center,        ///< Привязка к центру.
        Right          ///< Привязка к правому краю.
    };
    COMMON_ENUM;
};

/// Что делать при нажатии кнопки ПАМЯТЬ.
struct ModeBtnMemory
{
    enum
    {
        Menu,     ///< Будет открывааться соответствующая страница меню.
        Save      ///< Сохранение содержимого экрана на флешку.
    };
    COMMON_ENUM;
};

/// Режим показа строки навигации
struct ShowStrNavi
{
    enum
    {
        Temp,   ///< Показывать на несколько секунд
        All,    ///< Всегда показывать
        None    ///< Никогда не показывать
    };
    COMMON_ENUM;
};

struct FFTmaxDB
{
    enum
    {
        _40,
        _60,
        _80
    };
    COMMON_ENUM;
};

struct FuncModeDraw
{
    enum
    {
        Disable,
        Separate,
        Together
    };
    COMMON_ENUM;
};

/// \brief Тип балансировки АЦП каналов.
/// Дело в том, что уровни АЦП не совпадают из-за отличия характеристик ( ? ), поэтому мы вводим дополнительное смещение для одного из АЦП канала.
struct BalanceADC
{
    enum
    {
        Disable,     ///< Балансировка выключена.
        Settings,    ///< Используются значения балансировки, которые получены автоматически.
        Hand         ///< Используются значения балансировки, заданные вручную.
    };
    COMMON_ENUM;
};

/// Тип растяжки АЦП
struct StretchADC
{
    enum
    {
        Disable,
        Real,
        Hand
    };
    COMMON_ENUM;
};

struct DisplayOrientation
{
    enum
    {
        Direct,
        Back
    };
    COMMON_ENUM;
};

/// Режим канала по входу.
struct ModeCouple
{
    enum
    {
        DC,      ///< Закрытый вход
        AC,      ///< Открытый вход
        GND,     ///< Вход заземлён.
        Size
    };
    COMMON_ENUM;
    ModeCouple(uint v = 0) : value((uint8)v) {};
};

struct Resistance
{
    enum
    {
        _1Mom,
        _50Om
    };
    COMMON_ENUM;
};

/// Время счёта периода.
struct TimeCounting
{
    enum
    {
        _100ms,
        _1s,
        _10s
    };
    COMMON_ENUM;
};

/// Частота заполняющих импульсов для счёта частоты.
struct FreqClc
{
    enum
    {
        _100kHz,
        _1MHz,
        _10MHz,
        _100MHz
    };
    COMMON_ENUM;
};

/// Количество периодов.
struct NumberPeriods
{
    enum
    {
        _1,
        _10,
        _100
    };
    COMMON_ENUM;
};

/// Количество измерений для расчёта минимального и максимального значений.
struct ENumMinMax
{
    enum
    {
        _1,
        _2,
        _4,
        _8,
        _16,
        _32,
        _64,
        _128
    };
    COMMON_ENUM;
};

struct ColorScheme
{
    enum
    {
        WhiteLetters,   ///< В этом случае заголовки элементов меню пишутся белым - не очень хорошо видно снизу
        BlackLetters    ///< В этом случае заголовки элементов меню пишутся чёрным - не очень красиво выглядит
    };
    COMMON_ENUM;
};

/// Количество усреднений по измерениям.
struct ENumAverage
{
    enum
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
    };
    COMMON_ENUM;
};

/// Режим запуска.
struct StartMode
{
    enum
    {
        Auto,     ///< Автоматический.
        Wait,     ///< Ждущий.
        Single    ///< Однократный.
    };
    COMMON_ENUM;
};

/// Режим слежения курсоров.
struct CursLookMode
{
    enum
    {
        None,      ///< Курсоры не следят.
        Voltage,   ///< Курсоры следят за напряжением автоматически.
        Time,      ///< Курсоры следят за временем автоматически.
        Both       ///< Курсоры следят за временем и напряжением, в зависимости от того, какой курсоры вращали последним.
    };
    COMMON_ENUM;
};

/// Какие курсоры сейчас активны. Какие активны, те и будут перемещаться по вращению ручки УСТАНОВКА.
struct CursActive
{
    enum
    {
        U,
        T,
        None
    };
    COMMON_ENUM;
    CursActive(uint8 v = None) : value(v) {};
};

/// Дискретность перемещения курсоров.
struct CursMovement
{
    enum
    {
        Pixels,    ///< По пикселям экрана
        Percents   ///< По процентам
    };
    COMMON_ENUM;
};

/// Количество накоплений.
struct ENumAccum
{
    enum
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
    };
    COMMON_ENUM;
};

struct ModeAccumulation
{
    enum
    {
        NoReset,   /// В этом режиме показываются строго N последних.
        Reset      /// В этом режиме набираются N последних и потом сбрасываются.
    };
    COMMON_ENUM;
};

/// Количество точек для расчёта сглаживания.
struct ENumSmoothing
{
    enum
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
    };
    COMMON_ENUM;
};

/// Ограничение FPS.
struct ENumSignalsInSec
{
    enum
    {
        _25,
        _10,
        _5,
        _2,
        _1
    };
    ENumSignalsInSec(uint8 v = _25) : value(v) {};
    COMMON_ENUM;
};

/// Тип сетки на экране.
struct TypeGrid
{
    enum
    {
        _1,
        _2,
        _3,
        _4,
        Size
    };
    COMMON_ENUM;
};

/// Тип привязки к смещению по вертикали
struct LinkingRShift
{
    enum
    {
        Voltage,      ///< Смещение привязано к напряжению
        Position      ///< Смещение привязано к позиции
    };
    COMMON_ENUM;
};

/// Режим отображения дополнительных боковых маркеров смещения по напряжению.
struct AltMarkers
{
    enum
    {
        Hide,        /// Никода не выводить.
        Show,        /// Всегда выводить.
        AutoHide     /// Выводить и прятать через timeShowLevels.
    };
    COMMON_ENUM;
};

/// Через какое время после последнего нажатия кнопки скрывать меню.
struct MenuAutoHide
{
    enum
    {
        None = 0,   ///< Никогда.
        _5 = 5,   ///< Через 5 секунд.
        _10 = 10,  ///< Через 10 секунд.
        _15 = 15,  ///< Через 15 секунд.
        _30 = 30,  ///< Через 30 секунд.
        _60 = 60   ///< Через 60 секунд.
    };
    COMMON_ENUM;
};

struct MeasuresNumber
{
    enum
    {
        _1,                       ///< 1 измерение слева внизу.
        _2,                       ///< 2 измерения слева внизу.
        _1_5,                     ///< 1 строка с 5 измерениями.
        _2_5,                     ///< 2 строки по 5 измерений.
        _3_5,                     ///< 3 строки по 5 измерений.
        _6_1,                     ///< 6 строк по 1 измерению.
        _6_2                      ///< 6 строк по 2 измерения.
    };
    COMMON_ENUM;
};

/// Сжимать ли сигналы при выводе измерений.
struct ModeViewSignals
{
    enum
    {
        AsIs,       ///< Показывать сигналы как есть.
        Compress    ///< Сжимать сетку с сигналами.
    };
    COMMON_ENUM;
};

/// Тип выборки для режима рандомизатора.
struct SampleType
{
    enum
    {
        Real,    ///< реальное время - в построении участвуют только реально считанные точки, ничего не рассчитывается.
        Equal    ///< эквивалентная - сигнал строится по последним точкам, полученным от рандомизатора.
    };
    COMMON_ENUM;
    SampleType(uint8 v = Real) : value(v) {};
};

/// Функция ВР/ДЕЛ.
struct FunctionTime
{
    enum
    {
        Time,
        ShiftInMemory
    };
    COMMON_ENUM;
};

/// Тип привязки к смещению по горизонтали
struct LinkingTShift
{
    enum
    {
        Time,     ///< Смещение привязано к времени
        Position  ///< Смещение привязано к позиции
    };
    COMMON_ENUM;
};

struct TrigModeFind
{
    enum
    {
        Hand,      ///< Уровень синхронизации устанавливается вручную или автоматически - однократным нажажтием кнопки.
        Auto       ///< Подстройки уровня синхронизации производится автоматически после каждого нового считанного сигнала.
    };
    COMMON_ENUM;
};

struct CalibratorMode
{
    enum
    {
        Freq,
        DC,
        GND
    };
    COMMON_ENUM;
};

/// Режим калибровки.
struct CalibrationMode
{
    enum
    {
        x1,
        x10,
        Disable
    };
    COMMON_ENUM;
};

struct ScaleFFT
{
    enum
    {
        Log,           ///< Это значение означает логарифмическую шкалу вывода спектра.
        Linear         ///< Это значение означает линейную шкалу вывода спектра.
    };
    COMMON_ENUM;
};

struct SourceFFT
{
    enum
    {
        A,
        B,
        Both
    };
    COMMON_ENUM;
};

struct WindowFFT
{
    enum
    {
        Rectangle,
        Hamming,
        Blackman,
        Hann
    };
    COMMON_ENUM;
};

struct Function
{
    enum
    {
        Sum,
        Mul
    };
    COMMON_ENUM;
};

struct ModeRegSet
{
    enum
    {
        Range,
        RShift
    };
    COMMON_ENUM;
};

/// Режим наименования файлов.
struct FileNamingMode
{
    enum
    {
        Mask,        ///< Именовать по маске.
        Manually     ///< Именовать вручную.
    };
    COMMON_ENUM;
};

/// Как сохранять данные на флешку.
struct ModeSaveSignal
{
    enum
    {
        BMP,
        TXT
    };
    COMMON_ENUM;
};

/// Что показывать в режиме Внутр ЗУ - считанный или записанный сигнал.
struct ModeShowIntMem
{
    enum
    {
        Direct,  ///< Показывать данные реального времени.
        Saved,   ///< Показывать сохранённые данные.
        Both     ///< Показывать оба сигнала.
    };
    COMMON_ENUM;
};

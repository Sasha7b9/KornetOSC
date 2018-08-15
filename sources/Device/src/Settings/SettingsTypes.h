#pragma once
#include "defines.h"

#define COMMON_ENUM     uint8 value; operator uint8() const { return value; }

struct Range
{
    enum
    {
        _2mV,
        _5mV,
        _10mV,
        _20mV,
        _50mV,
        _100mV,
        _200mV,
        _500mV,
        _1V,
        _2V,
        _5V,
        _10V,
        _20V,
        Size
    };
    Range(uint8 v = _2mV) : value(v) {};
    COMMON_ENUM;
    Range& operator++()
    {
        ++value;
        return *this;
    }
};

struct TBase
{
    enum
    {
        _2ns,
        _5ns,
        _10ns,
        _20ns,
        _50ns,
        _100ns,
        _200ns,
        _500ns,
        _1us,
        _2us,
        _5us,
        _10us,
        _20us,
        _50us,
        _100us,
        _200us,
        _500us,
        _1ms,
        _2ms,
        _5ms,
        _10ms,
        _20ms,
        _50ms,
        _100ms,
        _200ms,
        _500ms,
        _1s,
        _2s,
        _5,
        _10s,
        Size
    };
    TBase(uint8 v = _2ns) : value(v) {};
    uint8 value;
    operator uint8() const
    {
        return value;
    }
};

struct TrigInput
{
    enum
    {
        Full,
        HF,
        LF
    };
    TrigInput(uint8 v = Full) : value(v) {};
    uint8 value;
    operator uint8() const
    {
        return value;
    }
};

enum Channel
{
    A,
    B,
    Ext,
    Math,
    NumChannels
};


struct MeasSource
{
    enum
    {
        A,
        B,
        A_B
    };
    uint8 value;
    operator uint8() const
    {
        return value;
    }
};

struct TrigPolarity
{
    enum
    {
        Rising,
        Falling
    };
    uint8 value;
    operator uint8() const
    {
        return value;
    }
};

struct Language
{
    enum
    {
        RU,
        EN,
        Num
    };
    uint8 value;
    operator uint8() const
    {
        return value;
    }
};

struct ModeDrawSignal
{
    enum
    {
        Lines,
        Points
    };
    uint8 value;
    operator uint8() const
    {
        return value;
    }
};


/// Тольщина рисуемого сигнала
struct ThicknessSignal
{
    enum
    {
        _1,         ///< Сигнал рисуется линией толщиной одна точка
        _3          ///< Сигнал рисуется линией толщиной три точки
    };
    uint8 value;
    operator uint8() const
    {
        return value;
    }
};

enum Bandwidth
{
    Bandwidth_Full,     ///< Если это значение выбрано в меню КАНАЛ, то при этом положение устанавливается полоса из ОТЛАДКА-КАНАЛЫ-Полоса.
    Bandwidth_20MHz,
    Bandwidth_100MHz,
    Bandwidth_200MHz,
    Bandwidth_350MHz,
    Bandwidth_650MHz,
    Bandwidth_750MHz
};

struct ModeTrig
{
    enum
    {
        Auto,
        Wait,
        Once
    };
    ModeTrig(uint8 v = Auto) : value(v) {};
    uint8 value;
};

/// Чем будем управлять в тестер-компоненте - напряжением или током
enum TesterControl
{
    Control_Voltage,
    Control_Current
};


enum TesterPolarity
{
    Polarity_Positive,
    Polarity_Negative
};

enum TesterStepU
{
    StepU_100mV,
    StepU_500mV
};

enum TesterStepI
{
    StepI_4mA,
    StepI_20mA
};

/// Каким курсором управлять
enum CursCntrl
{
    CursCntrl_1,        ///< первым
    CursCntrl_2,        ///< вторым
    CursCntrl_1_2,      ///< обоими
    CursCntrl_Disable   ///< никаким
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
enum TPos
{
    TPos_Left,          ///< Привязка к левому краю.
    TPos_Center,        ///< Привязка к центру.
    TPos_Right          ///< Привязка к правому краю.
};

/// Число точек сигнала, с которым идёт работа.
enum ENumPointsFPGA
{
    FNP_512,
    FNP_1k,
    FNP_2k,
    FNP_4k,
    FNP_8k,
    FPGA_ENUM_POINTS_SIZE
};

/// Что делать при нажатии кнопки ПАМЯТЬ.
enum ModeBtnMemory
{
    ModeBtnMemory_Menu,     ///< Будет открывааться соответствующая страница меню.
    ModeBtnMemory_Save      ///< Сохранение содержимого экрана на флешку.
};

/// Делитель.
enum Divider
{
    Divider_1,
    Divider_10
};

/// Источник синхронизации
struct TrigSource
{
    enum
    {
        A,    /// Канал 1
        B,    /// Канал 2
        Ext   /// Внешняя
    };
    TrigSource(uint8 v = A) : value(v) {};
    uint8 value;
    operator uint8() const
    {
        return value;
    }
    operator Channel() const
    {
        return (Channel)value;
    }
};

/// Режим работы.
enum ModeWork
{
    ModeWork_Dir,           ///< Основной режим.
    ModeWork_RAM,           ///< В этом режиме можно просмотреть последние сохранённые измерения.
    ModeWork_ROM,           ///< В этом режиме можно сохранять во flash-памяти измерения просматривать ранее сохранённые.
    ModeWork_None           ///< Используется в модуле Data.c. Нужен, чтобы указать, что мудуль не настроен ни на какой режим.
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

enum FFTmaxDB
{
    FFTmaxDB_40,
    FFTmaxDB_60,
    FFTmaxDB_80
};

enum FuncModeDraw
{
    FuncModeDraw_Disable,
    FuncModeDraw_Separate,
    FuncModeDraw_Together
};

/// \brief Тип балансировки АЦП каналов.
/// Дело в том, что уровни АЦП не совпадают из-за отличия характеристик ( ? ), поэтому мы вводим дополнительное смещение для одного из АЦП канала.
enum BalanceADCtype
{
    BalanceADC_Disable,     ///< Балансировка выключена.
    BalanceADC_Settings,    ///< Используются значения балансировки, которые получены автоматически.
    BalanceADC_Hand         ///< Используются значения балансировки, заданные вручную.
};

/// Тип растяжки АЦП
enum StretchADCtype
{
    StretchADC_Disable,
    StretchADC_Real,
    StretchADC_Hand
};

enum DisplayOrientation
{
    Direct,
    Back
};

/// Режим канала по входу.
enum ModeCouple
{
    ModeCouple_DC,      ///< Закрытый вход
    ModeCouple_AC,      ///< Открытый вход
    ModeCouple_GND,     ///< Вход заземлён.
    CoupleSize
};

enum Resistance
{
    Resistance_1Mom,
    Resistance_50Om
};

/// Время счёта периода.
enum TimeCounting
{
    TimeCounting_100ms,
    TimeCounting_1s,
    TimeCounting_10s
};

/// Частота заполняющих импульсов для счёта частоты.
enum FreqClc
{
    FreqClc_100kHz,
    FreqClc_1MHz,
    FreqClc_10MHz,
    FreqClc_100MHz
};

/// Количество периодов.
enum NumberPeriods
{
    NumberPeriods_1,
    NumberPeriods_10,
    NumberPeriods_100
};

enum PeakDetMode
{
    PeakDet_Disabled,
    PeakDet_Enabled,
    PeakDet_Average
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

enum ColorScheme
{
    ColorScheme_WhiteLetters,   ///< В этом случае заголовки элементов меню пишутся белым - не очень хорошо видно снизу
    ColorScheme_BlackLetters    ///< В этом случае заголовки элементов меню пишутся чёрным - не очень красиво выглядит
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
enum StartMode
{
    StartMode_Auto,     ///< Автоматический.
    StartMode_Wait,     ///< Ждущий.
    StartMode_Single    ///< Однократный.
};

/// Режим слежения курсоров.
enum CursLookMode
{
    CursLookMode_None,      ///< Курсоры не следят.
    CursLookMode_Voltage,   ///< Курсоры следят за напряжением автоматически.
    CursLookMode_Time,      ///< Курсоры следят за временем автоматически.
    CursLookMode_Both       ///< Курсоры следят за временем и напряжением, в зависимости от того, какой курсоры вращали последним.
};

/// Какие курсоры сейчас активны. Какие активны, те и будут перемещаться по вращению ручки УСТАНОВКА.
enum CursActive
{
    CursActive_U,
    CursActive_T,
    CursActive_None
};

/// Дискретность перемещения курсоров.
enum CursMovement
{
    CursMovement_Pixels,    ///< По пикселям экрана
    CursMovement_Percents   ///< По процентам
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
    uint8 value;
    operator uint8() const
    {
        return value;
    }
};

/// Сжимать ли сигналы при выводе измерений.
enum ModeViewSignals
{
    ModeViewSignals_AsIs,       ///< Показывать сигналы как есть.
    ModeViewSignals_Compress    ///< Сжимать сетку с сигналами.
};

/// Тип выборки для режима рандомизатора.
enum SampleType
{
    SampleType_Real,    ///< реальное время - в построении участвуют только реально считанные точки, ничего не рассчитывается.
    SampleType_Equal    ///< эквивалентная - сигнал строится по последним точкам, полученным от рандомизатора.
};

/// Функция ВР/ДЕЛ.
enum FunctionTime
{
    FunctionTime_Time,
    FunctionTime_ShiftInMemory
};

/// Тип привязки к смещению по горизонтали
enum LinkingTShift
{
    LinkingTShift_Time,     ///< Смещение привязано к времени
    LinkingTShift_Position  ///< Смещение привязано к позиции
};

enum TrigModeFind
{
    TrigModeFind_Hand,      ///< Уровень синхронизации устанавливается вручную или автоматически - однократным нажажтием кнопки.
    TrigModeFind_Auto       ///< Подстройки уровня синхронизации производится автоматически после каждого нового считанного сигнала.
};

enum CalibratorMode
{
    Calibrator_Freq,
    Calibrator_DC,
    Calibrator_GND
};

/// Режим калибровки.
enum CalibrationMode
{
    CalibrationMode_x1,
    CalibrationMode_x10,
    CalibrationMode_Disable
};

enum ScaleFFT
{
    ScaleFFT_Log,           ///< Это значение означает логарифмическую шкалу вывода спектра.
    ScaleFFT_Linear         ///< Это значение означает линейную шкалу вывода спектра.
};

struct SourceFFT
{
    enum
    {
        ChannelA,
        ChannelB,
        Both
    };
};

enum WindowFFT
{
    WindowFFT_Rectangle,
    WindowFFT_Hamming,
    WindowFFT_Blackman,
    WindowFFT_Hann
};

enum Function
{
    Function_Sum,
    Function_Mul
};

enum ModeRegSet
{
    ModeRegSet_Range,
    ModeRegSet_RShift
};

/// Режим наименования файлов.
enum FileNamingMode
{
    FileNamingMode_Mask,        ///< Именовать по маске.
    FileNamingMode_Manually     ///< Именовать вручную.
};

/// Как сохранять данные на флешку.
enum ModeSaveSignal
{
    ModeSaveSignal_BMP,
    ModeSaveSignal_TXT
};

/// Что показывать в режиме Внутр ЗУ - считанный или записанный сигнал.
enum ModeShowIntMem
{
    ModeShowIntMem_Direct,  ///< Показывать данные реального времени.
    ModeShowIntMem_Saved,   ///< Показывать сохранённые данные.
    ModeShowIntMem_Both     ///< Показывать оба сигнала.
};

const char *NameRange(Range range);
const char *NameTBase(TBase tBase);

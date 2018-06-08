#pragma once
#include "defines.h"


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
    uint8 value;
    operator uint8() const
    {
        return value;
    }
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
    TrigPolarity(uint8 v = Rising) : value(v) {};
    uint8 value;
    operator uint8() const
    {
        return value;
    }
};

enum Language
{
    RU,
    EN,
    NumLanguages
};

enum ModeDrawSignal
{
    Mode_Lines,
    Mode_Points
};

/// Тольщина рисуемого сигнала
enum ThicknessSignal
{
    Thickness_1,    ///< Сигнал рисуется линией толщиной одна точка
    Thickness_3     ///< Сигнал рисуется линией толщиной три точки
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
enum ModeAveraging
{
    Averaging_Accurately,   ///< Усреднять точно.
    Averaging_Around        ///< Усреднять приблизительно.
};

/// Выбор цвета фона.
enum Background
{
    Background_Black,
    Background_White
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
enum TrigSource
{
    TrigSource_A,    /// Канал 1
    TrigSource_B,    /// Канал 2
    TrigSource_Ext   /// Внешняя
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
enum ShowStrNavi
{
    ShowStrNavi_Temp,   ///< Показывать на несколько секунд
    ShowStrNavi_All,    ///< Всегда показывать
    ShowStrNavi_None    ///< Никогда не показывать
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
    ModeCouple_DC,      ///< Открытый вход.
    ModeCouple_AC,      ///< Закрытый вход.
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
enum ENumMinMax
{
    ENumMinMax_1,
    ENumMinMax_2,
    ENumMinMax_4,
    ENumMinMax_8,
    ENumMinMax_16,
    ENumMinMax_32,
    ENumMinMax_64,
    ENumMinMax_128
};

enum ColorScheme
{
    ColorScheme_WhiteLetters,   ///< В этом случае заголовки элементов меню пишутся белым - не очень хорошо видно снизу
    ColorScheme_BlackLetters    ///< В этом случае заголовки элементов меню пишутся чёрным - не очень красиво выглядит
};

/// Количество усреднений по измерениям.
enum ENumAverage
{
    ENumAverage_1,
    ENumAverage_2,
    ENumAverage_4,
    ENumAverage_8,
    ENumAverage_16,
    ENumAverage_32,
    ENumAverage_64,
    ENumAverage_128,
    ENumAverage_256,
    ENumAverage_512
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
enum ENumAccum
{
    ENumAccum_1,
    ENumAccum_2,
    ENumAccum_4,
    ENumAccum_8,
    ENumAccum_16,
    ENumAccum_32,
    ENumAccum_64,
    ENumAccum_128,
    ENumAccum_Infinity
};

enum ModeAccumulation
{
    ModeAccumulation_NoReset,   /// В этом режиме показываются строго N последних.
    ModeAccumulation_Reset      /// В этом режиме набираются N последних и потом сбрасываются.
};

/// Количество точек для расчёта сглаживания.
enum ENumSmoothing
{
    ENumSmooth_Disable,
    ENumSmooth_2points,
    ENumSmooth_3points,
    ENumSmooth_4points,
    ENumSmooth_5points,
    ENumSmooth_6points,
    ENumSmooth_7points,
    ENumSmooth_8points,
    ENumSmooth_9points,
    ENumSmooth_10points
};

/// Ограничение FPS.
enum ENumSignalsInSec
{
    ENumSignalsInSec_25,
    ENumSignalsInSec_10,
    ENumSignalsInSec_5,
    ENumSignalsInSec_2,
    ENumSignalsInSec_1
};

/// Тип сетки на экране.
enum TypeGrid
{
    TypeGrid_1,
    TypeGrid_2,
    TypeGrid_3,
    TypeGrid_4,
    TG_Size
};

/// Тип привязки к смещению по вертикали
enum LinkingRShift
{
    LinkingRShift_Voltage,      ///< Смещение привязано к напряжению
    LinkingRShift_Position      ///< Смещение привязано к позиции
};

/// Режим отображения дополнительных боковых маркеров смещения по напряжению.
enum AltMarkers
{
    AM_Hide,        /// Никода не выводить.
    AM_Show,        /// Всегда выводить.
    AM_AutoHide     /// Выводить и прятать через timeShowLevels.
};

/// Через какое время после последнего нажатия кнопки скрывать меню.
enum MenuAutoHide
{
    MenuAutoHide_None = 0,   ///< Никогда.
    MenuAutoHide_5 = 5,   ///< Через 5 секунд.
    MenuAutoHide_10 = 10,  ///< Через 10 секунд.
    MenuAutoHide_15 = 15,  ///< Через 15 секунд.
    MenuAutoHide_30 = 30,  ///< Через 30 секунд.
    MenuAutoHide_60 = 60   ///< Через 60 секунд.
};

enum MeasuresNumber
{
    MN_1,                       ///< 1 измерение слева внизу.
    MN_2,                       ///< 2 измерения слева внизу.
    MN_1_5,                     ///< 1 строка с 5 измерениями.
    MN_2_5,                     ///< 2 строки по 5 измерений.
    MN_3_5,                     ///< 3 строки по 5 измерений.
    MN_6_1,                     ///< 6 строк по 1 измерению.
    MN_6_2                      ///< 6 строк по 2 измерения.
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

enum SourceFFT
{
    SourceFFT_ChannelA,
    SourceFFT_ChannelB,
    SourceFFT_Both
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

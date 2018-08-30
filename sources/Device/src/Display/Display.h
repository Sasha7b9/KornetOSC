#pragma once
#include "defines.h"
#include "DisplayTypes.h"
#include "Keyboard/Keyboard.h"
#include "Settings/SettingsDisplay.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BACKGROUND                  (set.disp_background)
#define BACKGROUND_BLACK            (BACKGROUND == Display::Background::Black)

#define SHOW_STRING_NAVI            (set.disp_showStringNavigation)
#define SHOW_STRING_NAVI_TEMP       (SHOW_STRING_NAVI == Display::ShowStrNavi::Temp)
#define SHOW_STRING_NAVI_ALL        (SHOW_STRING_NAVI == Display::ShowStrNavi::All)

#define MODE_DRAW_SIGNAL            (set.disp_modeDrawSignal)
#define MODE_DRAW_SIGNAL_IS_LINES   (MODE_DRAW_SIGNAL == Display::ModeDrawSignal::Lines)
#define MODE_DRAW_SIGNAL_IS_POINTS  (MODE_DRAW_SIGNAL == Display::ModeDrawSignal::Points)

#define THICKNESS_SIGNAL            (set.disp_thickness)
#define THICKNESS_SIGNAL_IS_3       (THICKNESS_SIGNAL == Display::ThicknessSignal::_3)

#define ENUM_MIN_MAX                (set.disp_ENumMinMax)
#define MIN_MAX_ENABLED             (ENUM_MIN_MAX != Display::ENumMinMax::_1)
#define NUM_MIN_MAX                 (1 << (int)ENUM_MIN_MAX)                /* Возвращает количество измерений сигналов для расчёта минимумов и максимумов. */


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class LogEntity
{
    friend class Log;
};

#define DISPLAY_SHOW_WARNING(warn)  Display::ShowWarning(warn)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Cообщения, выводимые на экран
struct Warning
{
    enum E
    {
        LimitChan1_Volts,               ///< Предел масштаба по напряжениию первого канала.
        LimitChan2_Volts,               ///< Предел масштаба по напряжению второго канала.
        LimitSweep_Time,                ///< Предел масштаба по времени.
        EnabledPeakDet,                 ///< Включён пиковый детектор.
        LimitChan1_RShift,              ///< Предел смещения по напряжению первого канала.
        LimitChan2_RShift,              ///< Предел смещения по напряжению второго канала.
        LimitSweep_Level,               ///< Предел уровня синхронизации.
        LimitSweep_TShift,              ///< Предел смещения по времени.
        TooSmallSweepForPeakDet,        ///< Слишком быстрая развёртка для пикового детектора.
        TooFastScanForRecorder,         ///< Слишком быстрая развёртка для поточечного вывода.
        FileIsSaved,                    ///< Файл сохранён на флешку.
        SignalIsSaved,                  ///< Сигнал сохранён в ППЗ.
        SignalIsDeleted,                ///< Из ППЗУ удалён сигнал.
        MenuDebugEnabled,               ///< Включено меню ОТЛАДКА.
        TimeNotSet,                     ///< Время не установлено.
        SignalNotFound,                 ///< Сигнал не найден (автопоиск).
        SetTPosToLeft,                  ///< Рекомендация.
        NeedRebootDevice,               ///< Требуется перезагрузка.
        ImpossibleEnableMathFunction,   ///< Невозможно включить математическую функцию.
        ImpossibleEnableFFT,            ///< Невозможно включить вычисление БПФ.
        WrongFileSystem,                ///< Невозможно подключить флешку.
        WrongModePeackDet,              ///< Невозможно включить пиковый детектор.
        DisableChannelB,                ///< Требуется выключить канал 2.
        TooLongMemory,                  ///< Сообщение о невозможности включения режима 32к.
        NoPeakDet32k,                   ///< Пиковый детектор не работает при длине памяти 32к.
        NoPeakDet16k,                   ///< Пиковый детектор не работает при длине памяти 16к.
        Warn50Ohms,                     ///< Предупреждение об ограничение входного уровня на 50 Омах.
        WarnNeedForFlashDrive,          ///< Требуется подключенная флешка.
        FirmwareSaved,                  ///< Прошивка сохранена на флешку.
        FullyCompletedOTP,              ///< 
        Number
    } value;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Display
{
    friend class LogEntity;
public:
    
    static const int HEIGHT = 240;

    static const int WIDTH = 320;
    /// Эту функцию нужно вызывать при вращении ручки уровня синхронизации для временной отрисовки вспомогательных маркеров
    static void RotateTrigLev();

    static void Init();

    static void Update();

    static void SetKey(Key key);

    static void RemoveAddDrawFunction();

    static void ShowWarning(Warning::E warning);
    /// @brief Установить функцию и режим отрисовки экрана.
    /// @details Возможны три варианта.
    /// 1. DrawMode_Hand - в этом случае будет вызываться функция func(), определяемая пользователем, с частотой 25 раз в секунду.
    /// Используется в случаях, когда не выполняется главный цикл.
    /// 2. DrawMode::Auto и func == 0 - в этом случае будет выполняться функция Update() в главном цикле.
    /// 3. DrawMode::Auto и func != 0 - в этом случае будет выполняться функция func(), определяемая пользователем, но в теле
    /// главного цикла, будучи вызываемой из Update() вместо Update().
    static void SetDrawMode(DrawMode mode, pFuncVV func);

    static void FuncOnWaitStart(const char *text, bool eraseBackground);

    static void FuncOnWaitStop();

    static void SetAddDrawFunction(pFuncVV func);

    static void ChangedRShiftMarkers(bool active);

    static void Clear();

private:

    static void UpdateTester();

    static void DrawDataTester(int numStep, int x, int y);

    static Key key;

public:

    /// Выбор цвета фона.
    struct Background
    {
        enum E
        {
            Black,
            White
        } value;
        operator uint8() const { return (uint8)value; };
    };

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

    /// Тип усреднений по измерениям
    struct ModeAveraging
    {
        enum E
        {
            Accurately,   ///< Усреднять точно.
            Around        ///< Усреднять приблизительно.
        } value;
        ModeAveraging(E v) : value(v) {};
        operator uint8() const  { return (uint8)value; };
    };

    struct Orientation
    {
        enum E
        {
            Direct,
            Back
        } value;
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


    static void SetOrientation(Orientation orientation);
    /// Возвращает режим усреднения
    static ModeAveraging GetModeAveraging();

};

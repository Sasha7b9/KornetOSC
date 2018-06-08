#pragma once
#include "defines.h"
#include "DisplayTypes.h"
#include "Settings/SettingsTypes.h"
#include "Hardware/Keyboard.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class LogEntity
{
    friend class Log;
};

#define DISPLAY_SHOW_WARNING(warn)  Display::ShowWarning(warn)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Cообщения, выводимые на экран
typedef enum
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
    Warning_Count
} Warning;


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

    static void ShowWarning(Warning warning);

    static void SetOrientation(DisplayOrientation orientation);
    /// @brief Установить функцию и режим отрисовки экрана.
    /// @details Возможны три варианта.
    /// 1. DrawMode_Hand - в этом случае будет вызываться функция func(), определяемая пользователем, с частотой 25 раз в секунду.
    /// Используется в случаях, когда не выполняется главный цикл.
    /// 2. DrawMode_Auto и func == 0 - в этом случае будет выполняться функция Update() в главном цикле.
    /// 3. DrawMode_Auto и func != 0 - в этом случае будет выполняться функция func(), определяемая пользователем, но в теле
    /// главного цикла, будучи вызываемой из Update() вместо Update().
    static void SetDrawMode(DrawMode mode, pFuncVV func);

    static void FuncOnWaitStart(const char *text, bool eraseBackground);

    static void FuncOnWaitStop();

    static void SetAddDrawFunction(pFuncVV func);

    static void ChangedRShiftMarkers(bool active);

    static void Clear();

private:
    /// Нарисовать информацию в нижней части экрана.
    static void WriteLowPart();

    static int WriteChannel(Channel ch, int x, int y);

    static void WriteTBase(int x, int y);

    static void DrawRShift();

    static void DrawRShift(Channel ch);

    static void UpdateOsci();

    static void UpdateTester();

    static void DrawDataTester(int numStep, int x, int y);

    static void UpdateMultimeter();

    static Key key;
};

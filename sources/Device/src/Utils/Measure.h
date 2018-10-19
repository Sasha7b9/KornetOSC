#pragma once
#include "Settings/Settings.h"
#include "Settings/SettingsTime.h"
#include "Settings/SettingsChannel.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Utils
 *  @{
 *  @defgroup Measure
 *  @{
 */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Measure
{
public:
    // Виды измерений
    struct Type
    {
        enum E
        {
            None,
            VoltageMax,
            VoltageMin,
            VoltagePic,
            VoltageMaxSteady,
            VoltageMinSteady,
            VoltageAmpl,
            VoltageAverage,
            VoltageRMS,
            VoltageVybrosPlus,
            VoltageVybrosMinus,
            Period,
            Freq,
            TimeNarastaniya,
            TimeSpada,
            DurationPlus,
            DurationMinus,
            SkvaznostPlus,
            SkvaznostMinus,
            DelayPlus,
            DelayMinus,
            PhazaPlus,
            PhazaMinus,
            Number
        } value;
        Type(int8 v = 0) : value((E)v) {};
        operator uint8() const { return (uint8)value; };
    };

    Measure(int r, int c) : row(r), col(c) {};
    /// Возвращает сообщение из ячейки (row, col)
    static Measure Get(int row, int col) { return Measure(row, col); };
    /// Возвращает true, если измерение активное - выбрано ручкой
    bool IsActive();

    Type GetType();

    pString Name();
    /// \brief Установить сигнал для обработки. Данные берутся из DS, inA, inB.
    /// Выходные данные, соответствующие текущим настройками set, рассчитываются сразу и записываются в outA, outB.
    static void SetData(bool needSmoothing);
    /// Рассчитать позицию курсора напряжения, соответствующю заданной позиции курсора posCurT
    static float CalculateCursorU(Chan ch, float posCurT);
    /// Рассчитать позицию курсора времени, соответствующую заданной позиции курсора напряжения posCurU
    static float CalculateCursorT(Chan ch, float posCurU, int numCur);

    static void SetMarkerVoltage(Chan ch, int num, float value);

    static void SetMarkerTime(Chan ch, int num, int value);
   
    static char GetChar(Type measure);

    static void GetActive(int *row, int *col);

    static void SetActive(int row, int col);

    static int NumRows();

    static int NumCols();

    static int GetTopTable();
    /// На сколько сжимать сетку по горизонтали
    static int GetDeltaGridLeft();
    /// На сколько сжимать сетку по вертикали
    static int GetDeltaGridBottom();

    static void ShortPressOnSmallButonMarker();
    /// Нарисовать страницу выбора измерений
    static void DrawPageChoice();
    /// Позиция активного измерения (на котором курсор)
    static int8 posActive;
    /// Если true - раскрыта страница выбора измерения
    static bool pageChoiceIsActive;
    /// Позиция курсора на странице выбора измерения
    static int8 posOnPageChoice;
    /// Строка в таблице, в которой находится данное измерение
    int row;
    /// Колонка в таблице, в которой находится данное измерение
    int col;

    class Graphics
    {
    public:
        /// Отрисовать результаты автоматических измерений
        static void Draw();
        /// Возвращает координату x верхнего левого угла таблицы выводимых измерений
        static int GetTop();

    private:
        /// Верхняя координата y выводимой таблицы автоматических измерений
        static int top;
    };

#define MARKER_VOLTAGE(ch, num)             (Processing::markerVoltage[ch][num] - MIN_VALUE)
#define MARKER_TIME(ch, num)                (Processing::markerTime[ch][num])

private:

    /// Возвращает высоту поля для вывода автоматического измерения
    static int DY();
    /// Возвращает ширину поля для вывода автоматического измерения
    static int DX();

    class Processing
    {
        friend class Measure;

    public:
        /// Аппроксимировать единичное измерение режима рандомизатора функцией sinX/X
        static void InterpolationSinX_X(uint8 *data, int numPoints, TBase tBase);
        /// Возвращает строку автоматического измерения
        static char* GetStringMeasure(Measure::Type measure, Chan ch, char *buffer, int lenBuf);
        /// Расчитать все автоматические измерения
        static void CalculateMeasures();

        static int markerTime[Chan::Number][2];

        static int markerVoltage[Chan::Number][2];

    private:
        /// Приведение сигнала к установленным в приборе настройкам
        static void CountedToCurrentSettings();
        /// Приведение сигнала к текущим Range и rShift
        static void CountedRange(Chan ch);
        /// Приведение сигнала к текущему TBase
        static void CountedTBase();
        /// Приведение сигнала к текущему tShift
        static void CountedTShift();
        /// Приведение количества точек в сигнале к установленным настройкам
        static void CountedEnumPoints();
    };
};


/** @}  @}
 */

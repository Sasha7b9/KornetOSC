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
    // ¬иды измерений
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

    /// \brief ”становить сигнал дл€ обработки. ƒанные берутс€ из DS, inA, inB.
    /// ¬ыходные данные, соответствующие текущим настройками set, рассчитываютс€ сразу и записываютс€ в outA, outB.
    static void SetData(bool needSmoothing);
    /// –ассчитать позицию курсора напр€жени€, соответствующю заданной позиции курсора posCurT
    static float CalculateCursorU(Chan ch, float posCurT);
    /// –ассчитать позицию курсора времени, соответствующую заданной позиции курсора напр€жени€ posCurU
    static float CalculateCursorT(Chan ch, float posCurU, int numCur);

    static void SetMarkerVoltage(Chan ch, int num, float value);

    static void SetMarkerTime(Chan ch, int num, int value);
   
    static char GetChar(Type measure);

    static bool IsActive(int row, int col);

    static void GetActive(int *row, int *col);

    static void SetActive(int row, int col);

    static const char *Name(int row, int col);

    static Type GetType(int row, int col);

    static int NumRows();

    static int NumCols();

    static int GetTopTable();
    /// Ќа сколько сжимать сетку по горизонтали
    static int GetDeltaGridLeft();
    /// Ќа сколько сжимать сетку по вертикали
    static int GetDeltaGridBottom();

    static void ShortPressOnSmallButonMarker();
    /// Ќарисовать страницу выбора измерений
    static void DrawPageChoice();
    /// ѕозици€ активного измерени€ (на котором курсор)
    static int8 posActive;
    /// ≈сли true - раскрыта страница выбора измерени€
    static bool pageChoiceIsActive;
    /// ѕозици€ курсора на странице выбора измерени€
    static int8 posOnPageChoice;

    class Graphics
    {
    public:
        /// ќтрисовать результаты автоматических измерений
        static void Draw();
        /// ¬озвращает координату x верхнего левого угла таблицы выводимых измерений
        static int GetTop();

    private:
        /// ¬ерхн€€ координата y выводимой таблицы автоматических измерений
        static int top;
    };

#define MARKER_VOLTAGE(ch, num)             (Processing::markerVoltage[ch][num] - MIN_VALUE)
#define MARKER_TIME(ch, num)                (Processing::markerTime[ch][num])

private:

    /// ¬озвращает высоту пол€ дл€ вывода автоматического измерени€
    static int DY();
    /// ¬озвращает ширину пол€ дл€ вывода автоматического измерени€
    static int DX();

    class Processing
    {
        friend class Measure;

    public:
        /// јппроксимировать единичное измерение режима рандомизатора функцией sinX/X
        static void InterpolationSinX_X(uint8 *data, int numPoints, TBase tBase);
        /// ¬озвращает строку автоматического измерени€
        static char* GetStringMeasure(Measure::Type measure, Chan ch, char *buffer, int lenBuf);
        /// –асчитать все автоматические измерени€
        static void CalculateMeasures();

        static int markerTime[Chan::Number][2];

        static int markerVoltage[Chan::Number][2];

    private:
        /// ѕриведение сигнала к установленным в приборе настройкам
        static void CountedToCurrentSettings();
        /// ѕриведение сигнала к текущим Range и rShift
        static void CountedRange(Chan ch);
        /// ѕриведение сигнала к текущему TBase
        static void CountedTBase();
        /// ѕриведение сигнала к текущему tShift
        static void CountedTShift();
        /// ѕриведение количества точек в сигнале к установленным настройкам
        static void CountedEnumPoints();
    };
};


/** @}  @}
 */

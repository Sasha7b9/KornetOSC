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
    // ���� ���������
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

    /// \brief ���������� ������ ��� ���������. ������ ������� �� DS, inA, inB.
    /// �������� ������, ��������������� ������� ����������� set, �������������� ����� � ������������ � outA, outB.
    static void SetData(bool needSmoothing);
    /// ���������� ������� ������� ����������, �������������� �������� ������� ������� posCurT
    static float CalculateCursorU(Chan ch, float posCurT);
    /// ���������� ������� ������� �������, ��������������� �������� ������� ������� ���������� posCurU
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
    /// �� ������� ������� ����� �� �����������
    static int GetDeltaGridLeft();
    /// �� ������� ������� ����� �� ���������
    static int GetDeltaGridBottom();

    static void ShortPressOnSmallButonMarker();
    /// ���������� �������� ������ ���������
    static void DrawPageChoice();
    /// ������� ��������� ��������� (�� ������� ������)
    static int8 posActive;
    /// ���� true - �������� �������� ������ ���������
    static bool pageChoiceIsActive;
    /// ������� ������� �� �������� ������ ���������
    static int8 posOnPageChoice;

    class Graphics
    {
    public:
        /// ���������� ���������� �������������� ���������
        static void Draw();
        /// ���������� ���������� x �������� ������ ���� ������� ��������� ���������
        static int GetTop();

    private:
        /// ������� ���������� y ��������� ������� �������������� ���������
        static int top;
    };

#define MARKER_VOLTAGE(ch, num)             (Processing::markerVoltage[ch][num] - MIN_VALUE)
#define MARKER_TIME(ch, num)                (Processing::markerTime[ch][num])

private:

    /// ���������� ������ ���� ��� ������ ��������������� ���������
    static int DY();
    /// ���������� ������ ���� ��� ������ ��������������� ���������
    static int DX();

    class Processing
    {
        friend class Measure;

    public:
        /// ���������������� ��������� ��������� ������ ������������� �������� sinX/X
        static void InterpolationSinX_X(uint8 *data, int numPoints, TBase tBase);
        /// ���������� ������ ��������������� ���������
        static char* GetStringMeasure(Measure::Type measure, Chan ch, char *buffer, int lenBuf);
        /// ��������� ��� �������������� ���������
        static void CalculateMeasures();

        static int markerTime[Chan::Number][2];

        static int markerVoltage[Chan::Number][2];

    private:
        /// ���������� ������� � ������������� � ������� ����������
        static void CountedToCurrentSettings();
        /// ���������� ������� � ������� Range � rShift
        static void CountedRange(Chan ch);
        /// ���������� ������� � �������� TBase
        static void CountedTBase();
        /// ���������� ������� � �������� tShift
        static void CountedTShift();
        /// ���������� ���������� ����� � ������� � ������������� ����������
        static void CountedEnumPoints();
    };
};


/** @}  @}
 */

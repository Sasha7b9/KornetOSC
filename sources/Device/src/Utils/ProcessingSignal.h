#pragma once
#include "Utils/Measure.h"
#include "Data/Storage.h"
#include "FPGA/FPGATypes.h"
#include "Settings/SettingsTime.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Utils
 *  @{
 *  @defgroup ProcessingSignal
 *  @{
 */

#define MARKER_VOLTAGE(ch, num)             (Processing::markerVoltage[ch][num] - MIN_VALUE)
#define MARKER_TIME(ch, num)                (Processing::markerTime[ch][num])

class Processing
{
public:
    /// \brief ���������� ������ ��� ���������. ������ ������� �� DS, inA, inB.
    /// �������� ������, ��������������� ������� ����������� set, �������������� ����� � ������������ � outA, outB.
    static void SetData(bool needSmoothing);
    /// ���������� ������� ������� ����������, �������������� �������� ������� ������� posCurT
    static float CalculateCursorU(Chan ch, float posCurT);
    /// ���������� ������� ������� �������, ��������������� �������� ������� ������� ���������� posCurU
    static float CalculateCursorT(Chan ch, float posCurU, int numCur);
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


/** @}  @}
 */

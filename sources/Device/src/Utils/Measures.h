#pragma once
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Utils
 *  @{
 *  @defgroup Measures
 *  @{
 */

// ���� ���������
struct Meas
{
    enum
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
        Num
    };
    uint8 value;
    operator uint8() const
    {
        return value;
    };
    Meas(const Meas &meas) : value(meas)
    {
    };
    Meas(int8 v = 0) : value((uint8)v)
    {
    };
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Measures
{
public:
    static char GetChar(Meas measure);

    static bool IsActive(int row, int col);

    static void GetActive(int *row, int *col);

    static void SetActive(int row, int col);
    /// ���������� ������ ���� ��� ������ ��������������� ���������
    static int GetDY();
    /// ���������� ������ ���� ��� ������ ��������������� ���������
    static int GetDX();

    static const char *Name(int row, int col);

    static Meas Type(int row, int col);

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
};


/** @}  @}
 */

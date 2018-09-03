#pragma once
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Utils
 *  @{
 *  @defgroup Measures
 *  @{
 */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Measures
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

    static char GetChar(Type measure);

    static bool IsActive(int row, int col);

    static void GetActive(int *row, int *col);

    static void SetActive(int row, int col);
    /// ���������� ������ ���� ��� ������ ��������������� ���������
    static int GetDY();
    /// ���������� ������ ���� ��� ������ ��������������� ���������
    static int GetDX();

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
};


/** @}  @}
 */

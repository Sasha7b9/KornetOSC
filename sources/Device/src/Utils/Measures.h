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

    static char GetChar(Type measure);

    static bool IsActive(int row, int col);

    static void GetActive(int *row, int *col);

    static void SetActive(int row, int col);
    /// Возвращает высоту поля для вывода автоматического измерения
    static int GetDY();
    /// Возвращает ширину поля для вывода автоматического измерения
    static int GetDX();

    static const char *Name(int row, int col);

    static Type GetType(int row, int col);

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
};


/** @}  @}
 */

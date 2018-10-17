#pragma once


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
    /// ¬озвращает координату x верхнего левого угла таблицы выводимых измерений
    static int Top();

    static void Draw();

    static char GetChar(Type measure);

    static bool IsActive(int row, int col);

    static void GetActive(int *row, int *col);

    static void SetActive(int row, int col);
    /// ¬озвращает высоту пол€ дл€ вывода автоматического измерени€
    static int GetDY();
    /// ¬озвращает ширину пол€ дл€ вывода автоматического измерени€
    static int GetDX();

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
};


/** @}  @}
 */

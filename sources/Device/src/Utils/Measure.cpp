#include "defines.h"
#include "Measure.h"
#include "Settings/Settings.h"
#include "Display/Display.h"
#include "Display/Painter.h"
#include "Osci/Grid.h"
#include "Hardware/Sound.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    const char *name;
    const char UGO;
    uint8      notUsed0;
    uint8      notUsed1;
    uint8      notUsed2;
} StructMeasure;

#define DEF_STRUCT_MEASURE(name, ugo) {name, ugo, 0, 0, 0}

static const StructMeasure sMeas[Measure::Type::Number] =
{
    DEF_STRUCT_MEASURE("",            '\x00'),
    DEF_STRUCT_MEASURE("U макс",      '\x20'),
    DEF_STRUCT_MEASURE("U мин",       '\x25'),
    DEF_STRUCT_MEASURE("U пик",       '\x2a'),
    DEF_STRUCT_MEASURE("U макс уст",  '\x40'),
    DEF_STRUCT_MEASURE("U мин уст",   '\x45'),
    DEF_STRUCT_MEASURE("U ампл",      '\x4a'),
    DEF_STRUCT_MEASURE("U ср",        '\x60'),
    DEF_STRUCT_MEASURE("U скз",       '\x65'),
    DEF_STRUCT_MEASURE("Выброс+",     '\x6a'),
    DEF_STRUCT_MEASURE("Выброс-",     '\x80'),
    DEF_STRUCT_MEASURE("Период",      '\x85'),
    DEF_STRUCT_MEASURE("Частота",     '\x8a'),
    DEF_STRUCT_MEASURE("Вр нараст",   '\xa0'),
    DEF_STRUCT_MEASURE("Вр спада",    '\xa5'),
    DEF_STRUCT_MEASURE("Длит+",       '\xaa'),
    DEF_STRUCT_MEASURE("Длит-",       '\xc0'),
    DEF_STRUCT_MEASURE("Скважн+",     '\xc5'),
    DEF_STRUCT_MEASURE("Скважн-",     '\xca'),
    DEF_STRUCT_MEASURE("Задержка\xa7",'\xe0'),
    DEF_STRUCT_MEASURE("Задержка\xa6",'\xe5'),
    DEF_STRUCT_MEASURE("Фаза\xa7",    '\xe0'),
    DEF_STRUCT_MEASURE("Фаза\xa6",    '\xe5')
};

int8 Measure::posActive = 0;
bool Measure::pageChoiceIsActive = false;
int8 Measure::posOnPageChoice = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Measure::IsActive(int row, int col)
{
    if(posActive >= NumCols() * NumRows())
    {
        posActive = 0;
    }
    return (row * NumCols() + col) == posActive;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Measure::GetActive(int *row, int *col)
{
    *row = posActive / NumCols();
    *col = posActive - (*row) * NumCols();
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Measure::SetActive(int row, int col)
{
    posActive = (int8)(row * NumCols() + col);
}

char Measure::GetChar(Measure::Type measure)
{
    return sMeas[measure].UGO;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
int Measure::GetDY()
{
    if(SOURCE_MEASURE_IS_A_B && SET_ENABLED_A && SET_ENABLED_B)
    {
        return 30;
    }
    return 21;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
int Measure::GetDX()
{
    return Grid::Width() / 5; 
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
const char *Measure::Name(int row, int col)
{
    return sMeas[MEASURE(row * NumCols() + col)].name;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
Measure::Type Measure::GetType(int row, int col)
{
    return MEASURE(row * NumCols() + col);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
int Measure::GetTopTable()
{
    if(NUM_MEASURES_IS_6_1 || NUM_MEASURES_IS_6_2)
    {
        return Grid::Bottom() - GetDY() * 6;
    }
    return Grid::Bottom() - NumRows() * GetDY();
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
int Measure::NumCols()
{
    const int cols[] = {1, 2, 5, 5, 5, 1, 2};
    return cols[NUM_MEASURES];
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
int Measure::NumRows()
{
    int rows[] = {1, 1, 1, 2, 3, 6, 6};
    return rows[NUM_MEASURES];
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
int Measure::GetDeltaGridLeft()
{
    if(SHOW_MEASURES && MODE_VIEW_SIGNALS_IS_COMPRESS)
    {
        if(NUM_MEASURES_IS_6_1)
        {
            return GetDX();
        }
        else if(NUM_MEASURES_IS_6_2)
        {
            return GetDX() * 2;
        }
    }
    return 0;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
int Measure::GetDeltaGridBottom()
{
    if(SHOW_MEASURES && MODE_VIEW_SIGNALS_IS_COMPRESS)
    {
        if(NUM_MEASURES_IS_1_5)
        {
            return GetDY();
        }
        else if(NUM_MEASURES_IS_2_5)
        {
            return GetDY() * 2;
        }
        else if(NUM_MEASURES_IS_3_5)
        {
            return GetDY() * 3;
        }
    }
    return 0;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Measure::ShortPressOnSmallButonMarker()
{
    if(MEASURE(posActive) == MEAS_MARKED)
    {
        MEAS_MARKED = Measure::Type::None;
    }
    else
    {
        MEAS_MARKED = MEASURE(posActive);
    }
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Measure::DrawPageChoice()
{
    if(!pageChoiceIsActive)
    {
        return;
    }
    int x = (NUM_MEASURES_IS_6_1 || NUM_MEASURES_IS_6_2) ? (Grid::Right() - 3 * Grid::Width() / 5) : Grid::Left();
    int y = Grid::Top();
    int dX = Grid::Width() / 5;
    int dY = 22;
    int maxRow = (NUM_MEASURES_IS_6_1 || NUM_MEASURES_IS_6_2) ? 8 : 5;
    int maxCol = (NUM_MEASURES_IS_6_1 || NUM_MEASURES_IS_6_2) ? 3 : 5;
    Measure::Type meas = Measure::Type::None;
    Painter::SetFont(Font::Type::_UGO);
    for(int row = 0; row < maxRow; row++)
    {
        for(int col = 0; col < maxCol; col++)
        {
            if(meas >= Measure::Type::Number)
            {
                break;
            }
            int x0 = x + col * dX;
            int y0 = y + row * dY;
            bool active = meas == posOnPageChoice;
            Painter::DrawRectangle(x0, y0, dX, dY, Color::WHITE);
            Painter::FillRegion(x0 + 1, y0 + 1, dX - 2, dY - 2, (active ? Color::FLASH_10 : Color::BACK));
            Painter::SetColor(active ? Color::FLASH_01 : Color::FILL);
            Painter::Draw10SymbolsInRect(x0 + 2, y0 + 1, GetChar(meas));
            if(meas < Measure::Type::Number)
            {
                Painter::SetFont(Font::Type::_5);
                Painter::DrawTextRelativelyRight(x0 + dX, y0 + 12, sMeas[meas].name, active ? Color::FLASH_01 : Color::FILL);
                Painter::SetFont(Font::Type::_UGO);
            }
            meas = (Measure::Type)((int)meas + 1);    // meas++;
        }
    }
    Painter::SetFont(Font::Type::_8);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Measure::Draw()
{
    /*
    TOP_MEASURES = GRID_BOTTOM;

    if (!SHOW_MEASURES)
    {
        return;
    }

    Processing::CalculateMeasures();

    if (MEAS_ZONE_HAND)
    {
        int x0 = POS_MEAS_CUR_T_0 - SHIFT_IN_MEMORY + Grid::Left();
        int y0 = POS_MEAS_CUR_U_0 + GRID_TOP;
        int x1 = POS_MEAS_CUR_T_1 - SHIFT_IN_MEMORY + Grid::Left();
        int y1 = POS_MEAS_CUR_U_1 + GRID_TOP;
        Sort(&x0, &x1);
        Sort(&y0, &y1);
        Painter::DrawRectangle(x0, y0, x1 - x0, y1 - y0, Color::FILL);
    }

    int x0 = Grid::Left() - Measure::GetDeltaGridLeft();
    int dX = Measure::GetDX();
    int dY = Measure::GetDY();
    int y0 = Measure::GetTopTable();

    int numRows = Measure::NumRows();
    int numCols = Measure::NumCols();

    for (int str = 0; str < numRows; str++)
    {
        for (int elem = 0; elem < numCols; elem++)
        {
            int x = x0 + dX * elem;
            int y = y0 + str * dY;
            bool active = Measure::IsActive(str, elem) && Menu::GetNameOpenedPage() == PageSB_Measures_Tune;
            Color color = active ? Color::BACK : Color::FILL;
            Meas measure = Measure::Type(str, elem);
            if (measure != Meas_None)
            {
                Painter::FillRegion(x, y, dX, dY, Color::BACK);
                Painter::DrawRectangle(x, y, dX, dY, Color::FILL);
                TOP_MEASURES = Min(TOP_MEASURES, y);
            }
            if (active)
            {
                Painter::FillRegion(x + 2, y + 2, dX - 4, dY - 4, Color::FILL);
            }
            if (measure != Meas_None)
            {
#define SIZE_BUFFER 20
                char buffer[SIZE_BUFFER];

                Painter::DrawText(x + 4, y + 2, Measure::Name(str, elem), color);
                if (measure == MEAS_MARKED)
                {
                    Painter::FillRegion(x + 1, y + 1, dX - 2, 9, active ? Color::BACK : Color::FILL);
                    Painter::DrawText(x + 4, y + 2, Measure::Name(str, elem), active ? Color::FILL : Color::BACK);
                }
                if (SOURCE_MEASURE_IS_A && SET_ENABLED_A)
                {
                    Painter::DrawText(x + 2, y + 11, Processing::GetStringMeasure(measure, A, buffer, SIZE_BUFFER), Color::CHAN[A]);
                }
                else if (SOURCE_MEASURE_IS_B && SET_ENABLED_B)
                {
                    Painter::DrawText(x + 2, y + 11, Processing::GetStringMeasure(measure, B, buffer, SIZE_BUFFER), Color::CHAN[B]);
                }
                else
                {
                    Painter::DrawText(x + 2, y + 11, Processing::GetStringMeasure(measure, A, buffer, SIZE_BUFFER), Color::CHAN[A]);
                    Painter::DrawText(x + 2, y + (SET_ENABLED_A ? 20 : 11), Processing::GetStringMeasure(measure, B, buffer, SIZE_BUFFER),
                                      Color::CHAN[B]);
                }
            }
        }
    }

    if (Menu::GetNameOpenedPage() == PageSB_Measures_Tune)
    {
        Measure::DrawPageChoice();
    }
    */
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Measure::Top()
{
    return 10;
}

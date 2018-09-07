#include "defines.h"
#include "Measures.h"
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

static const StructMeasure sMeas[Measures::Type::Number] =
{
    DEF_STRUCT_MEASURE("",            '\x00'),
    DEF_STRUCT_MEASURE("U ����",      '\x20'),
    DEF_STRUCT_MEASURE("U ���",       '\x25'),
    DEF_STRUCT_MEASURE("U ���",       '\x2a'),
    DEF_STRUCT_MEASURE("U ���� ���",  '\x40'),
    DEF_STRUCT_MEASURE("U ��� ���",   '\x45'),
    DEF_STRUCT_MEASURE("U ����",      '\x4a'),
    DEF_STRUCT_MEASURE("U ��",        '\x60'),
    DEF_STRUCT_MEASURE("U ���",       '\x65'),
    DEF_STRUCT_MEASURE("������+",     '\x6a'),
    DEF_STRUCT_MEASURE("������-",     '\x80'),
    DEF_STRUCT_MEASURE("������",      '\x85'),
    DEF_STRUCT_MEASURE("�������",     '\x8a'),
    DEF_STRUCT_MEASURE("�� ������",   '\xa0'),
    DEF_STRUCT_MEASURE("�� �����",    '\xa5'),
    DEF_STRUCT_MEASURE("����+",       '\xaa'),
    DEF_STRUCT_MEASURE("����-",       '\xc0'),
    DEF_STRUCT_MEASURE("������+",     '\xc5'),
    DEF_STRUCT_MEASURE("������-",     '\xca'),
    DEF_STRUCT_MEASURE("��������\xa7",'\xe0'),
    DEF_STRUCT_MEASURE("��������\xa6",'\xe5'),
    DEF_STRUCT_MEASURE("����\xa7",    '\xe0'),
    DEF_STRUCT_MEASURE("����\xa6",    '\xe5')
};

int8 Measures::posActive = 0;
bool Measures::pageChoiceIsActive = false;
int8 Measures::posOnPageChoice = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Measures::IsActive(int row, int col)
{
    if(posActive >= NumCols() * NumRows())
    {
        posActive = 0;
    }
    return (row * NumCols() + col) == posActive;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Measures::GetActive(int *row, int *col)
{
    *row = posActive / NumCols();
    *col = posActive - (*row) * NumCols();
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Measures::SetActive(int row, int col)
{
    posActive = (int8)(row * NumCols() + col);
}

char Measures::GetChar(Measures::Type measure)
{
    return sMeas[measure].UGO;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
int Measures::GetDY()
{
    if(SOURCE_MEASURE_IS_A_B && SET_ENABLED_A && SET_ENABLED_B)
    {
        return 30;
    }
    return 21;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
int Measures::GetDX()
{
    return Grid::Width() / 5; 
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
const char *Measures::Name(int row, int col)
{
    return sMeas[MEASURE(row * NumCols() + col)].name;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
Measures::Type Measures::GetType(int row, int col)
{
    return MEASURE(row * NumCols() + col);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
int Measures::GetTopTable()
{
    if(NUM_MEASURES_IS_6_1 || NUM_MEASURES_IS_6_2)
    {
        return Grid::Bottom() - GetDY() * 6;
    }
    return Grid::Bottom() - NumRows() * GetDY();
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
int Measures::NumCols()
{
    const int cols[] = {1, 2, 5, 5, 5, 1, 2};
    return cols[NUM_MEASURES];
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
int Measures::NumRows()
{
    int rows[] = {1, 1, 1, 2, 3, 6, 6};
    return rows[NUM_MEASURES];
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
int Measures::GetDeltaGridLeft()
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
int Measures::GetDeltaGridBottom()
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
void Measures::ShortPressOnSmallButonMarker()
{
    if(MEASURE(posActive) == MEAS_MARKED)
    {
        MEAS_MARKED = Measures::Type::None;
    }
    else
    {
        MEAS_MARKED = MEASURE(posActive);
    }
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Measures::DrawPageChoice()
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
    Measures::Type meas = Measures::Type::None;
    Painter::SetFont(Font::Type::_UGO);
    for(int row = 0; row < maxRow; row++)
    {
        for(int col = 0; col < maxCol; col++)
        {
            if(meas >= Measures::Type::Number)
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
            if(meas < Measures::Type::Number)
            {
                Painter::SetFont(Font::Type::_5);
                Painter::DrawTextRelativelyRight(x0 + dX, y0 + 12, sMeas[meas].name, active ? Color::FLASH_01 : Color::FILL);
                Painter::SetFont(Font::Type::_UGO);
            }
            meas = (Measures::Type)((int)meas + 1);    // meas++;
        }
    }
    Painter::SetFont(Font::Type::_8);
}

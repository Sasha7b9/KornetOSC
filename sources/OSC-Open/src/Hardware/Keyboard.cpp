#include "defines.h"
#include "Keyboard.h"
#include "Hardware/Controls.h"
#include "Display/Painter.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct StructButton
{
    const char *title;
    Control control;
    Color color;
    int x;
    int y;
};

static int x0 = 1;
static int y0 = 242;
static int x1 = 322;
static int y1 = 0;

static int selX = 0; // Если кнопка нажата, то
static int selY = 0; // здесь её координаты

#define WIDTH_BTN1  62
#define HEIGHT_BTN1 27
#define DELTA_BTN   2

#define WIDTH_BTN2  61
#define HEIGHT_BTN2 27

static StructButton strBtn1[2][5] =
{
    {{"F1",      B_1},        {"F2",      B_2},       {"F3",     B_3},       {"F4",        B_4},        {"F5",     B_5}},
    {{"ФУНКЦИЯ", B_Function}, {"ДИСПЛЕЙ", B_Display}, {"СЕРВИС", B_Service}, {"ИЗМЕРЕНИЯ", B_Measures}, {"ПАМЯТЬ", B_Memory}}
};

#define NUM_ROW 10

static const Color green = Color::GREEN_25;
static const Color blue = Color::BLUE_25;
static const Color red = Color::RED_25;

static StructButton bNone       = { "",          B_None };
static StructButton bTBaseMore  = { "нС",        B_TBaseMore,  green };
static StructButton bTBaseLess  = { "С",         B_TBaseLess,  green };
static StructButton bTime       = { "РАЗВЕРТКА", B_Time,       Color::GRAY_25 };
static StructButton bTShiftLess = { "Вр влево",  B_TShiftLess, green };
static StructButton bTShiftMore = { "Вр вправо", B_TShiftMore, green };
static StructButton bStart      = { "ПУСК/СТОП", B_Start,      Color::GRAY_25};
static StructButton bChannelA = { "КАНАЛ 1",  B_ChannelA,    Color::GRAY_25 };
static StructButton bRangeLessA = { "мВ",       B_RangeLessA,  red };
static StructButton bRangeMoreA = { "В",        B_RangeMoreA,  red };
static StructButton bRShiftMoreA = { "Вверх",    B_RShiftMoreA, red };
static StructButton bRShiftLessA = { "Вниз",     B_RShiftLessA, red };
static StructButton bChannelB = { "КАНАЛ 2",  B_ChannelB,    Color::GRAY_25 };
static StructButton bRangeLessB = { "мВ",       B_RangeLessB,  red };
static StructButton bRangeMoreB = { "В",        B_RangeMoreB,  red };
static StructButton bRShiftMoreB = { "Вверх",    B_RShiftMoreB, red };
static StructButton bRShiftLessB = { "Вниз",     B_RShiftLessB, red };
static StructButton bTrig = { "Синхр",     B_Trig,        Color::GRAY_25 };
static StructButton bTrigLevMore = { "С вверх",   B_TrigLevMore, blue };
static StructButton bTrigLevLess = { "С вниз",    B_TrigLevLess, blue };

static StructButton strBtn2[NUM_ROW][3] = 
{
    { bChannelA,   bTrig,        bChannelB},
    { bRangeMoreA, bTrigLevMore, bRangeMoreB},
    { bRangeLessA, bTrigLevLess, bRangeLessB},
    {bRShiftMoreA, bTime,        bRShiftMoreB},
    {bRShiftLessA, bTBaseMore,   bRShiftLessB},
    {bTShiftLess,  bTBaseLess,   bTShiftMore},
    {bNone,        bNone,        bStart},
    {{"",         B_None},              {"Вверх",     B_Up,          blue}, {"",          B_None}},
    {{"Влево",    B_Left,        blue}, {"Ввод",      B_Enter,       blue}, {"Вправо",    B_Right,       blue}},
    {{"",         B_None},              {"Вниз",      B_Down,        blue}, {"",          B_None}}
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Keyboard::Init()
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            StructButton &button = strBtn1[i][j];
            button.x = x0 + j * (WIDTH_BTN1 + DELTA_BTN);
            button.y = y0 + i * (HEIGHT_BTN1 + DELTA_BTN);
            button.color = i == 0 ? Color::GRAY_10 : Color::GRAY_20;
        }
    }

    for (int i = 0; i < NUM_ROW; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            strBtn2[i][j].x = x1 + j * (WIDTH_BTN2 + DELTA_BTN);
            int y = y1 + i * (HEIGHT_BTN2 + DELTA_BTN);
            if (i > 6)
            {
                y += 10;
            }
            else if (i > 5)
            {
                y += 5;
            }
            strBtn2[i][j].y = y;
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Keyboard::Draw()
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            const char *title = strBtn1[i][j].title;
            if (title[0])
            {
                DrawButton(strBtn1[i][j].x, strBtn1[i][j].y, WIDTH_BTN1, strBtn1[i][j].color, title);
            }
        }
    }

    for (int i = 0; i < NUM_ROW; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            const char *title = strBtn2[i][j].title;
            if (title[0])
            {
                DrawButton(strBtn2[i][j].x, strBtn2[i][j].y, WIDTH_BTN2, strBtn2[i][j].color, title);
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Keyboard::DrawButton(int x, int y, int width, Color color, const char *title)
{
    if (selX == x && selY == y)
    {
        Painter::FillRegion(x, y, width, HEIGHT_BTN1, Color::FILL);
        Painter::DrawStringInCenterRect(x, y, width, HEIGHT_BTN1, title, Color::BACK);
    }
    else
    {
        Painter::DrawRectangle(x, y, width, HEIGHT_BTN1, Color::FILL);
        Painter::FillRegion(x + 1, y + 1, width - 2, HEIGHT_BTN1 - 2, color);
        if (title)
        {
            Painter::DrawStringInCenterRect(x, y, width, HEIGHT_BTN1, title, Color::FILL);
        }
    }
}

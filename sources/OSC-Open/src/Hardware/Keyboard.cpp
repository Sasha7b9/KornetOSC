#include "defines.h"
#include "Keyboard.h"
#include "Hardware/Controls.h"
#include "Display/Painter.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct StructButton
{
    const char *title;
    Control control;
    int x;
    int y;
};

static int x0 = 0;
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
    {{"F1", B_1},             {"F2", B_2},            {"F3", B_3},           {"F4", B_4},               {"F5", B_5}},
    {{"ФУНКЦИЯ", B_Function}, {"ДИСПЛЕЙ", B_Display}, {"СЕРВИС", B_Service}, {"ИЗМЕРЕНИЯ", B_Measures}, {"ПАМЯТЬ", B_Memory}}
};

#define NUM_ROW 10

static StructButton strBtn2[NUM_ROW][3] =
{
{{"КАНАЛ 1", B_ChannelA},    {"РАЗВЕРТКА", B_Time},       {"КАНАЛ 2", B_ChannelB}},
{{"мВ",      B_RangeLessA},  {"нС",        B_TBaseLess},  {"мВ",      B_RangeLessB}},
{{"В",       B_RangeMoreA},  {"С",         B_TBaseMore},  {"В",       B_RangeMoreB}},
{{"Вверх",   B_RShiftMoreA}, {"Влево",     B_TShiftLess}, {"Вверх",   B_RShiftMoreB}},
{{"Вниз",    B_RShiftLessA}, {"Вправо",    B_TShiftMore}, {"Вниз",    B_RShiftLessA}},
{{"C лево", B_TrigLevLess}, {"Синхр", B_Trig}, {"С вправо", B_TrigLevMore}},
{{"", }, {"", }, {"ПУСК/СТОП", B_Start}},
{ { "", },{ "Вверх", B_Up},{ "", } },
{ {"Влево", B_Left},{ "Ввод", B_Enter, },{ "Вправо", B_Right}},
{ {"", },{ "Вниз", B_Down},{ "", }}
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Keyboard::Init()
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            strBtn1[i][j].x = x0 + j * (WIDTH_BTN1 + DELTA_BTN);
            strBtn1[i][j].y = y0 + i * (HEIGHT_BTN1 + DELTA_BTN);
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
                DrawButton(strBtn1[i][j].x, strBtn1[i][j].y, WIDTH_BTN1, title);
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
                DrawButton(strBtn2[i][j].x, strBtn2[i][j].y, WIDTH_BTN2, title);
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Keyboard::DrawButton(int x, int y, int width, const char *title)
{
    if (selX == x && selY == y)
    {
        Painter::FillRegion(x, y, width, HEIGHT_BTN1, Color::FILL);
        Painter::DrawStringInCenterRect(x, y, width, HEIGHT_BTN1, title, Color::BACK);
    }
    else
    {
        Painter::DrawRectangle(x, y, width, HEIGHT_BTN1, Color::FILL);
        if (title)
        {
            Painter::DrawStringInCenterRect(x, y, width, HEIGHT_BTN1, title);
        }
    }
}

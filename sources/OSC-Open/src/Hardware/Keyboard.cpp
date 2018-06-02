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

static int selX = 0; // ���� ������ ������, ��
static int selY = 0; // ����� � ����������

#define WIDTH_BTN1  62
#define HEIGHT_BTN1 27
#define DELTA_BTN   2

#define WIDTH_BTN2  61
#define HEIGHT_BTN2 27

static StructButton strBtn1[2][5] =
{
    {{"F1", B_1},             {"F2", B_2},            {"F3", B_3},           {"F4", B_4},               {"F5", B_5}},
    {{"�������", B_Function}, {"�������", B_Display}, {"������", B_Service}, {"���������", B_Measures}, {"������", B_Memory}}
};

#define NUM_ROW 10

static StructButton strBtn2[NUM_ROW][3] =
{
{{"����� 1", B_ChannelA},    {"���������", B_Time},       {"����� 2", B_ChannelB}},
{{"��",      B_RangeLessA},  {"��",        B_TBaseLess},  {"��",      B_RangeLessB}},
{{"�",       B_RangeMoreA},  {"�",         B_TBaseMore},  {"�",       B_RangeMoreB}},
{{"�����",   B_RShiftMoreA}, {"�����",     B_TShiftLess}, {"�����",   B_RShiftMoreB}},
{{"����",    B_RShiftLessA}, {"������",    B_TShiftMore}, {"����",    B_RShiftLessA}},
{{"C ����", B_TrigLevLess}, {"�����", B_Trig}, {"� ������", B_TrigLevMore}},
{{"", }, {"", }, {"����/����", B_Start}},
{ { "", },{ "�����", B_Up},{ "", } },
{ {"�����", B_Left},{ "����", B_Enter, },{ "������", B_Right}},
{ {"", },{ "����", B_Down},{ "", }}
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

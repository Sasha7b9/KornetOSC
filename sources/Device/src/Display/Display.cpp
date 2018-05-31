#include "Device.h"
#include "Display.h"
#include "Grid.h"
#include "Painter.h"
#include "PainterData.h"
#include "Log.h"
#include "Hardware/Timer.h"
#include "Menu/Menu.h"
#include "Settings/Settings.h"
#include "Utils/Debug.h"
#include "Utils/MathOSC.h"
#include <stdlib.h>
#include <string.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define SIZE_CONSOLE    20
static CHAR_BUF2(buffer, SIZE_CONSOLE, 100);
static int stringInConsole = 0;

bool Display::inProcessDrawConsole = false;
Key Display::key = K_None;


const char *ControlName(Key control)
{
    static const char *names[NumButtons] =
    {
        "None",
        "Функция",
        "Измер",
        "Память",
        "Сервис",
        "Канал 1",
        "Канал 2",
        "Развертка",
        "Пуск/стоп",
        "Синхр",
        "Дисплей",
        "Range 1 больше",
        "Range 1 меньше",
        "RShift 1 больше",
        "RShift 1 меньше",
        "Range 2 больше",
        "Range 2 меньше",
        "RShift 2 больше",
        "RShift 2 меньше",
        "TBase больше",
        "TBase меньше",
        "TShift больше",
        "TShift меньше",
        "Синхр больше",
        "Синхр меньше",
        "Влево",
        "Вправо",
        "Вверх",
        "Вниз",
        "Ввод",
        "1",
        "2",
        "3",
        "4",
        "5"
    };

    return names[control];
}

void Display::SetKey(Key key_)
{
    key = key_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Display::Init()
{
    Painter::SetPalette(Color::BACK,        0x00000000);
    Painter::SetPalette(Color::FILL,        0x00ffffff);
    Painter::SetPalette(Color::CHAN_A,      0x000000ff);
    Painter::SetPalette(Color::CHAN_A_HALF, 0x00000080);
    Painter::SetPalette(Color::CHAN_B,      0x0000ff00);
    Painter::SetPalette(Color::CHAN_B_HALF, 0x00008000);
    Painter::SetPalette(Color::GRID,        0x00afafaf);
    Painter::SetPalette(Color::BLUE,        0x000000ff);
    Painter::SetPalette(Color::GREEN,       0x0000ff00);
    Painter::SetPalette(Color::RED,         0x00ff0000);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display::Update()
{
    typedef void (*pFuncDisplayVV)();

    static const pFuncDisplayVV funcs[NumDeviceModes] =
    {
        Display::UpdateOsci,
        Display::UpdateTester,
        Display::UpdateMultimeter
    };

    pFuncDisplayVV func = funcs[Device::CurrentMode()];

    func();

    //LOG_WRITE("время : полное - %d, ожидание - %d", gTimeUS - timeStart, debug.GetTimeCounterUS());
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display::UpdateOsci()
{
    Painter::BeginScene(Color::BACK);

    DrawGrid();

    WriteLowPart();

    DrawRShift();

    PainterData::DrawData();
   
    DrawConsole();

    Menu::Draw();

    //Painter::DrawText(10, 10, ControlName(key), Color::FILL);

    Painter::EndScene();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display::UpdateTester()
{
    Painter::BeginScene(Color::BACK);

    int size = 239;

    Painter::DrawRectangle(0, 0, size, size, Color::FILL);
    Painter::DrawRectangle(0, 0, Display::WIDTH - 1, Display::HEIGHT - 1);

    for (int i = 0; i < NUM_STEPS; i++)
    {
        DrawDataTester(i, 0, 0);
    }

    Menu::Draw();

    DrawConsole();

    Painter::EndScene();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display::DrawDataTester(int numStep, int x0, int y0)
{
    static const uint8 colors[5] = {Color::FILL, Color::GRID, Color::RED, Color::GREEN, Color::BLUE};

    uint8 *dataX = &dataTester[A][numStep][0];
    uint8 *dataY = &dataTester[B][numStep][0];

    Painter::SetColor(colors[numStep]);
    
    MathOSC::Smoothing(dataX, TESTER_NUM_POINTS, TESTER_NUM_SMOOTH + 1);
    MathOSC::Smoothing(dataY, TESTER_NUM_POINTS, TESTER_NUM_SMOOTH + 1);

    if (VIEW_MODE_IS_LINES)
    {
        int x1 = x0 + TESTER_NUM_POINTS - (dataX[1] - MIN_VALUE);
        int y1 = y0 + dataY[1] - MIN_VALUE;
        for (int i = 2; i < TESTER_NUM_POINTS; i++)
        {
            int x2 = x0 + TESTER_NUM_POINTS - (dataX[i] - MIN_VALUE);
            int y2 = y0 + dataY[i] - MIN_VALUE;
            Painter::DrawLine(x1, y1, x2, y2);
            x1 = x2;
            y1 = y2;
        }
    }
    else
    {
        for (int i = 0; i < TESTER_NUM_POINTS; i++)
        {
            int x = x0 + TESTER_NUM_POINTS - (dataX[i] - MIN_VALUE);
            int y = y0 + dataY[i] - MIN_VALUE;

            if (x > x0 && x < x0 + TESTER_NUM_POINTS && y > y0 && y < y0 + TESTER_NUM_POINTS)
            {
                Painter::SetPoint(x, y);
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display::UpdateMultimeter()
{
    Painter::BeginScene(Color::BACK);

    Painter::DrawText(10, 10, "Мультиметр", Color::RED);

    Painter::EndScene();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display::DrawGrid()
{
    int x0 = Grid::Left();
    int y0 = Grid::Top();

    Painter::DrawVLine(x0 + Grid::WIDTH / 2, y0, y0 + Grid::HEIGHT, Color::GRID);

    Painter::DrawHLine(y0 + Grid::HEIGHT / 2, x0, x0 + Grid::WIDTH);

    for (int x = x0; x < x0 + Grid::Width(); x += Grid::SIZE_CELL)
    {
        Painter::DrawVLine(x, y0, y0 + Grid::HEIGHT);
    }

    for (int y = y0; y < y0 + Grid::HEIGHT; y += Grid::SIZE_CELL)
    {
        Painter::DrawHLine(y, x0, x0 + Grid::WIDTH);
    }

    Painter::DrawRectangle(x0, y0, Grid::WIDTH, Grid::HEIGHT, Color::FILL);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display::WriteLowPart()
{
    int x = WriteChannel(A, Grid::LEFT, Grid::Bottom() + 1);
    WriteChannel(B, Grid::LEFT, Grid::Bottom() + 9);
    WriteTBase(x, Grid::Bottom() + 1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Display::WriteChannel(Channel ch, int x, int y)
{
    Painter::DrawText(x, y, ch == A ? "1:" : "2:", Color::Chan(ch));
    
    x += 7;

    static const char symbols[3] = {SYMBOL_COUPLE_AC, SYMBOL_COUPLE_DC, SYMBOL_COUPLE_GND};

    char string[2] = {symbols[SET_COUPLE(ch)], 0};

    Painter::DrawText(x, y, string);

    x += 8;

    Painter::DrawText(x, y, NameRange(SET_RANGE(ch)));

    x += 22;

    CHAR_BUF(buf, 20);

    MathOSC::Voltage2String(RSHIFT_2_ABS(SET_RSHIFT(ch), SET_RANGE(ch)), true, buf);

    Painter::DrawText(x, y, buf);

    return x + 47;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display::WriteTBase(int x, int y)
{
    Painter::DrawText(x, y, NameTBase(SET_TBASE), Color::FILL);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display::DrawRShift()
{
    DrawRShift(A);
    DrawRShift(B);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display::DrawRShift(Channel ch)
{
    Painter::SetColor(Color::Chan(ch));

    int delta = (SET_RSHIFT(ch) - RShiftZero) / STEP_RSHIFT;

    int y = (Grid::Bottom() - Grid::Top()) / 2 + Grid::Top() - delta;

    Painter::DrawChar(Grid::Left() - 8, y - 4, (char)SYMBOL_RSHIFT_MARKER);

    Painter::SetFont(TypeFont_5);

    Painter::DrawChar(Grid::Left() - 7, y - 6, ch == A ? '1' : '2', Color::BACK);

    Painter::SetFont(TypeFont_8);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void LogEntity::AddToConsole(char *string)
{
    /// \todo Мы пропускаем некоторые строки. Сделать отложенное добавление
    if (!Display::inProcessDrawConsole)      // Страхуемся на предмет того, что сейчас не происходит вывод консоли в другом потоке
    {
        static int count = 0;
        if (stringInConsole == SIZE_CONSOLE)
        {
            for (int i = 1; i < SIZE_CONSOLE; i++)
            {
                strcpy(buffer[i - 1], buffer[i]);
            }
            stringInConsole--;
        }
        sprintf(buffer[stringInConsole], "%d %s", count++, string);
        stringInConsole++;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display::DrawConsole()
{
    inProcessDrawConsole = true;

    Painter::SetFont(TypeFont_5);

    int y = 0;

    for (int i = 0; i < stringInConsole; i++)
    {
        Painter::DrawText(1, y, buffer[i], Color::FILL);
        y += 6;
    }

    Painter::SetFont(TypeFont_8);

    inProcessDrawConsole = false;
}

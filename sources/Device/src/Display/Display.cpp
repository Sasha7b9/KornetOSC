#include "Device.h"
#include "Colors.h"
#include "Display.h"
#include "Grid.h"
#include "Painter.h"
#include "PainterData.h"
#include "Log.h"
#include "Hardware/Timer.h"
#include "Hardware/Sound.h"
#include "Menu/Menu.h"
#include "Settings/Settings.h"
#include "Utils/Debug.h"
#include "Utils/MathOSC.h"
#include "FPGA/FPGAMath.h"
#include <stdlib.h>
#include <string.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define NEED_SET_ORIENTATION    (bf.needSetOrientation)

static struct BitFieldDisplay
{
    uint needSetOrientation : 1;
    uint notUsed : 31;
} bf = {};

typedef struct
{
    Warning         warning;
    bool            good;
    uint8           notUsed[2];
    char * const    message[2][3];
} StructWarning;


#define NU {0, 0}

static const StructWarning warns[Warning_Count] =
{
    {LimitChan1_Volts, false, NU,           {{"ПРЕДЕЛ КАНАЛ 1 - ВОЛЬТ/ДЕЛ"},                                            {"LIMIT CHANNEL 1 - VOLTS/DIV"}}},
    {LimitChan2_Volts, false, NU,           {{"ПРЕДЕЛ КАНАЛ 2 - ВОЛЬТ/ДЕЛ"},                                            {"LIMIT CHANNEL 2 - VOLTS/DIV"}}},
    {LimitSweep_Time, false, NU,            {{"ПРЕДЕЛ РАЗВЕРТКА - ВРЕМЯ/ДЕЛ"},                                               {"LIMIT SWEEP - TIME/DIV"}}},
    {EnabledPeakDet, false, NU,             {{"ВКЛЮЧЕН ПИКОВЫЙ ДЕТЕКТОР"},                                                       {"ENABLED PEAK. DET."}}},
    {LimitChan1_RShift, false, NU,          {{"ПРЕДЕЛ КАНАЛ 1 - \x0d"},                                                      {"LIMIT CHANNEL 1 - \x0d"}}},
    {LimitChan2_RShift, false, NU,          {{"ПРЕДЕЛ КАНАЛ 2 - \x0d"},                                                      {"LIMIT CHANNEL 2 - \x0d"}}},
    {LimitSweep_Level, false, NU,           {{"ПРЕДЕЛ РАЗВЕРТКА - УРОВЕНЬ"},                                                    {"LIMIT SWEEP - LEVEL"}}},
    {LimitSweep_TShift, false, NU,          {{"ПРЕДЕЛ РАЗВЕРТКА - \x97"},                                                        {"LIMIT SWEEP - \x97"}}},
    {TooSmallSweepForPeakDet, false, NU,    {{"ПИК. ДЕТ. НЕ РАБОТАЕТ НА РАЗВЕРТКАХ МЕНЕЕ 0.5мкс/дел"},
                                                                                              {"PEAK. DET. NOT WORK ON SWEETS LESS THAN 0.5us/div"}}},
    {TooFastScanForRecorder, false, NU,     {{"САМОПИСЕЦ НЕ МОЖЕТ РАБОТАТЬ НА БЫСТРЫХ РАЗВЁРТКАХ"},          {"SELF-RECORDER DOES NOT WORK FAST SCANS"}}},
    {FileIsSaved, true, NU,                 {{"ФАЙЛ СОХРАНЕН"},                                                                       {"FILE IS SAVED"}}},
    {SignalIsSaved, true, NU,               {{"СИГНАЛ СОХРАНЕН"},                                                                   {"SIGNAL IS SAVED"}}},
    {SignalIsDeleted, true, NU,             {{"СИГНАЛ УДАЛЕН"},                                                                   {"SIGNAL IS DELETED"}}},
    {MenuDebugEnabled, true, NU,            {{"МЕНЮ ОТЛАДКА ВКЛЮЧЕНО"},                                                       {"MENU DEBUG IS ENABLED"}}},
    {TimeNotSet, true, NU,                  {{"ВРЕМЯ НЕ УСТАНОВЛЕНО. МОЖЕТЕ УСТАНОВИТЬ ЕГО СЕЙЧАС"},        {"TIME IS NOT SET. YOU CAN INSTALL IT NOW"}}},
    {SignalNotFound, true, NU,              {{"СИГНАЛ НЕ НАЙДЕН"},                                                              {"SIGNAL IS NOT FOUND"}}},
    {SetTPosToLeft, true, NU,               {{"НА РАЗВЕРТКАХ МЕДЛЕННЕЕ 10мс/дел ЖЕЛАТЕЛЬНО УСТАНАВ-",
                                          "ЛИВАТЬ \"РАЗВЕРТКА - \x7b\" В ПОЛОЖЕНИЕ \"Лево\" ДЛЯ УСКОРЕ-", "НИЯ ВЫВОДА СИГНАЛА"},
                             {"AT SCANNER SLOWLY 10ms/div DESIRABLY SET \"SCAN - \x7b\" IN", "SWITCH \"Left\" FOR TO ACCELERATE THE OUTPUT SIGNAL"}}},
    {NeedRebootDevice, true, NU,            {{"Для вступления изменений в силу", "выключите прибор"},
                                                                              {"FOR THE INTRODUCTION OF CHANGES", "IN FORCE SWITCH OFF THE DEVICE"}}},
    {ImpossibleEnableMathFunction, true, NU, {{"Отключите вычисление БПФ"},                                           {"DISCONNECT CALCULATION OF FFT"}}},
    {ImpossibleEnableFFT, true, NU,         {{"Отключите математическую функцию"},                                 {"DISCONNECT MATHEMATICAL FUNCTION"}}},
    {WrongFileSystem, false, NU,            {{"Не могу прочитать флешку. Убедитесь, что на ней FAT32"},
                                                                                      {"I can not mount a usb flash FDrive:: Make sure to her FAT32"}}},
    {WrongModePeackDet, true, NU,           {{"Чтобы изменить длину памяти, отключите пиковый детектор"},
                                                                                 {"To change the length of the memory, turn off the peak detector"}}},
    {DisableChannelB, true, NU,             {{"Сначала выключите канал 2"},                                           {"First, turn off the channel 2"}}},
    {TooLongMemory, true, NU,               {{"Второй канал рабоатает при длине памяти 16к и менее"},
                                                                                     {"The second channel runs at a length of memory 16k and less"}}},
    {NoPeakDet32k, true, NU,                {{"Пиковый детектор не работает при длине памяти 32к"},
                                                                                  {"The peak detector does not work when the memory length of 32k"}}},
    {NoPeakDet16k, true, NU,                {{"Для работы пикового детектора при длине памяти 16к", "отключите канал 2"},
                                                                         {"For the peak detector with a length of 16k memory", "disable channel 2"}}},
    {Warn50Ohms, false, NU,                 {{"При величине входного сопротивления 50 Ом", "запрещается подавать на вход более 5 В"},
                                                              {"When the input impedance value of 50 ohms", "is prohibited to input more than 5 V"}}},
    {WarnNeedForFlashDrive, true, NU,       {{"Сначала подключите флеш-диск"},                                        {"First connect the flash drive"}}},
    {FirmwareSaved, true, NU,               {{"Прошивка сохранена"},                                                                 {"Firmware saved"}}},
    {FullyCompletedOTP, false, NU,          {{"Память OTP полностью заполнена"},                                         {"OTP memory fully completed"}}}
};

#define NUM_WARNINGS            10
static const char               *warnings[NUM_WARNINGS] = {0};      ///< Здесь предупреждающие сообщения.
static uint                     timeWarnings[NUM_WARNINGS] = {0};   ///< Здесь время, когда предупреждающее сообщение поступило на экран.


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define SIZE_CONSOLE    20
static CHAR_BUF2(buffer, SIZE_CONSOLE, 100);
static int stringInConsole = 0;

bool Display::inProcessDrawConsole = false;
Key Display::key = K_None;
static bool showLevelTrigLev = false;   ///< Нужно ли рисовать горизонтальную линию уровня смещения уровня синхронизации.
static bool drawRShiftMarkers = false;
static pFuncVV funcOnHand       = 0;
static uint timeStart = 0;
static const char *textWait = 0;
static bool clearBackground = false;
static pFuncVV funcAdditionDraw = 0;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display::SetKey(Key key_)
{
    key = key_;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display::Init()
{
    for(uint8 i = 0; i < Color::NUMBER.value; i++)
    {
        Painter::SetColorValue(Color(i), COLOR(i));
    }
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

    //LOG_WRITE("время : полное - %d, ожидание - %d", TIME_US - timeStart, debug.GetTimeCounterUS());
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
    static const Color colors[5] = {Color::FILL, Color::GRID, Color::RED, Color::GREEN, Color::BLUE};

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

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnTimerShowWarning()
{
    uint time = TIME_MS;
    for (int i = 0; i < NUM_WARNINGS; i++)
    {
        if (time - timeWarnings[i] > (uint)TIME_MESSAGES * 1000)
        {
            timeWarnings[i] = 0;
            warnings[i] = 0;
        }
    }

    int pointer = 0;
    for (int i = 0; i < NUM_WARNINGS; i++)
    {
        if (warnings[i] != 0)
        {
            warnings[pointer] = warnings[i];
            timeWarnings[pointer] = timeWarnings[i];
            if (pointer != i)
            {
                timeWarnings[i] = 0;
                warnings[i] = 0;
            }
            pointer++;
        }
    }

    if (pointer == 0)
    {
        Timer::Disable(kShowMessages);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void ShowWarn(const char *message)
{
    if (warnings[0] == 0)
    {
        Timer::SetAndEnable(kShowMessages, OnTimerShowWarning, 100);
    }
    bool alreadyStored = false;
    for (int i = 0; i < NUM_WARNINGS; i++)
    {
        if (warnings[i] == 0 && !alreadyStored)
        {
            warnings[i] = message;
            timeWarnings[i] = TIME_MS;
            alreadyStored = true;
        }
        else if (warnings[i] == message)
        {
            timeWarnings[i] = TIME_MS;
            return;
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display::ShowWarning(Warning warning)
{
    Painter::ResetFlash();
    for (int i = 2; i >= 0; i--)
    {
        char *message = warns[warning].message[LANG][i];
        if (message)
        {
            ShowWarn(message);
        }
    }
    if (warns[warning].good)
    {
        Sound::WarnBeepGood();
    }
    else
    {
        Sound::WarnBeepBad();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DisableShowLevelTrigLev()
{
    showLevelTrigLev = false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display::RotateTrigLev()
{
    if (TIME_SHOW_LEVELS && TRIG_MODE_FIND_HAND)
    {
        showLevelTrigLev = true;
        Timer::SetAndStartOnce(kShowLevelTrigLev, DisableShowLevelTrigLev, (uint)(TIME_SHOW_LEVELS * 1000));
    }
    NEED_FINISH_DRAW = 1;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnRShiftMarkersAutoHide()
{
    drawRShiftMarkers = false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display::ChangedRShiftMarkers(bool active)
{
    drawRShiftMarkers = !ALT_MARKERS_HIDE;
    Timer::SetAndStartOnce(kRShiftMarkersAutoHide, OnRShiftMarkersAutoHide, 5000);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display::SetDrawMode(DrawMode mode, pFuncVV func)
{
    funcOnHand = func;
    if (mode == DrawMode_Hand)
    {
        Timer::SetAndEnable(kTimerDisplay, funcOnHand, 40);
    }
    else
    {
        Timer::Disable(kTimerDisplay);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display::FuncOnWaitStop()
{
    Display::SetDrawMode(DrawMode_Auto, 0);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void FuncOnWait()
{
    if (clearBackground)
    {
        Painter::BeginScene(Color::BACK);
    }

    uint time = ((TIME_MS - timeStart) / 50) % 100;

    if (time > 50)
    {
        time = (100 - time);
    }

    int width = 200;
    int height = 80;
    int x = 160 - width / 2;
    int y = 120 - height / 2;

    Painter::FillRegion(x, y, width, height, Color::BACK);
    Painter::DrawRectangle(x, y, width, height, Color::FILL);
    Painter::DrawStringInCenterRect(x, y, width, height - 20, textWait);
    char buf[100];
    buf[0] = 0;
    for (uint i = 0; i < time; i++)
    {
        strcat(buf, ".");
    }
    Painter::DrawStringInCenterRect(x, y + 20, width, height - 20, buf);
    Painter::EndScene();
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display::FuncOnWaitStart(const char *text, bool eraseBackground)
{
    timeStart = TIME_MS;
    textWait = text;
    clearBackground = eraseBackground;
    Display::SetDrawMode(DrawMode_Hand, FuncOnWait);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display::Clear()
{
    Painter::FillRegion(0, 0, Display::WIDTH - 1, Display::HEIGHT - 2, Color::BACK);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display::RemoveAddDrawFunction()
{
    funcAdditionDraw = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display::SetOrientation(DisplayOrientation orientation)
{
    DISPLAY_ORIENTATION = orientation;
    NEED_SET_ORIENTATION = 1;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display::SetAddDrawFunction(pFuncVV func)
{
    funcAdditionDraw = func;
}

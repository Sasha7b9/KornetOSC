#include "Device.h"
#include "Colors.h"
#include "Globals.h"
#include "Display.h"
#include "DisplayOsci.h"
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
#include "Console.h"
#include "BottomPart.h"
#include "FPGA/RShift.h"
#include <stdlib.h>
#include <string.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define NEED_SET_ORIENTATION    (bf.needSetOrientation)

/*
static struct BitFieldDisplay
{
    uint needSetOrientation : 1;
    uint notUsed : 31;
} bf = {};
*/

typedef struct
{
    Warning         warning;
    bool            good;
    uint8           notUsed[2];
    char * const    message[2][3];
} StructWarning;


#define NU {0, 0}

static const StructWarning warns[Warning::Number] =
{
    {Warning::LimitChan1_Volts, false, NU,           {{"ПРЕДЕЛ КАНАЛ 1 - ВОЛЬТ/ДЕЛ"},                                            {"LIMIT CHANNEL 1 - VOLTS/DIV"}}},
    {Warning::LimitChan2_Volts, false, NU,           {{"ПРЕДЕЛ КАНАЛ 2 - ВОЛЬТ/ДЕЛ"},                                            {"LIMIT CHANNEL 2 - VOLTS/DIV"}}},
    {Warning::LimitSweep_Time, false, NU,            {{"ПРЕДЕЛ РАЗВЕРТКА - ВРЕМЯ/ДЕЛ"},                                               {"LIMIT SWEEP - TIME/DIV"}}},
    {Warning::EnabledPeakDet, false, NU,             {{"ВКЛЮЧЕН ПИКОВЫЙ ДЕТЕКТОР"},                                                       {"ENABLED PEAK. DET."}}},
    {Warning::LimitChan1_RShift, false, NU,          {{"ПРЕДЕЛ КАНАЛ 1 - \x0d"},                                                      {"LIMIT CHANNEL 1 - \x0d"}}},
    {Warning::LimitChan2_RShift, false, NU,          {{"ПРЕДЕЛ КАНАЛ 2 - \x0d"},                                                      {"LIMIT CHANNEL 2 - \x0d"}}},
    {Warning::LimitSweep_Level, false, NU,           {{"ПРЕДЕЛ РАЗВЕРТКА - УРОВЕНЬ"},                                                    {"LIMIT SWEEP - LEVEL"}}},
    {Warning::LimitSweep_TShift, false, NU,          {{"ПРЕДЕЛ РАЗВЕРТКА - \x97"},                                                        {"LIMIT SWEEP - \x97"}}},
    {Warning::TooSmallSweepForPeakDet, false, NU,    {{"ПИК. ДЕТ. НЕ РАБОТАЕТ НА РАЗВЕРТКАХ МЕНЕЕ 0.5мкс/дел"},
                                                                                              {"PEAK. DET. NOT WORK ON SWEETS LESS THAN 0.5us/div"}}},
    {Warning::TooFastScanForRecorder, false, NU,     {{"САМОПИСЕЦ НЕ МОЖЕТ РАБОТАТЬ НА БЫСТРЫХ РАЗВЁРТКАХ"},          {"SELF-RECORDER DOES NOT WORK FAST SCANS"}}},
    {Warning::FileIsSaved, true, NU,                 {{"ФАЙЛ СОХРАНЕН"},                                                                       {"FILE IS SAVED"}}},
    {Warning::SignalIsSaved, true, NU,               {{"СИГНАЛ СОХРАНЕН"},                                                                   {"SIGNAL IS SAVED"}}},
    {Warning::SignalIsDeleted, true, NU,             {{"СИГНАЛ УДАЛЕН"},                                                                   {"SIGNAL IS DELETED"}}},
    {Warning::MenuDebugEnabled, true, NU,            {{"МЕНЮ ОТЛАДКА ВКЛЮЧЕНО"},                                                       {"MENU DEBUG IS ENABLED"}}},
    {Warning::TimeNotSet, true, NU,                  {{"ВРЕМЯ НЕ УСТАНОВЛЕНО. МОЖЕТЕ УСТАНОВИТЬ ЕГО СЕЙЧАС"},        {"TIME IS NOT SET. YOU CAN INSTALL IT NOW"}}},
    {Warning::SignalNotFound, true, NU,              {{"СИГНАЛ НЕ НАЙДЕН"},                                                              {"SIGNAL IS NOT FOUND"}}},
    {Warning::SetTPosToLeft, true, NU,               {{"НА РАЗВЕРТКАХ МЕДЛЕННЕЕ 10мс/дел ЖЕЛАТЕЛЬНО УСТАНАВ-",
                                          "ЛИВАТЬ \"РАЗВЕРТКА - \x7b\" В ПОЛОЖЕНИЕ \"Лево\" ДЛЯ УСКОРЕ-", "НИЯ ВЫВОДА СИГНАЛА"},
                             {"AT SCANNER SLOWLY 10ms/div DESIRABLY SET \"SCAN - \x7b\" IN", "SWITCH \"Left\" FOR TO ACCELERATE THE OUTPUT SIGNAL"}}},
    {Warning::NeedRebootDevice, true, NU,            {{"Для вступления изменений в силу", "выключите прибор"},
                                                                              {"FOR THE INTRODUCTION OF CHANGES", "IN FORCE SWITCH OFF THE DEVICE"}}},
    {Warning::ImpossibleEnableMathFunction, true, NU, {{"Отключите вычисление БПФ"},                                           {"DISCONNECT CALCULATION OF FFT"}}},
    {Warning::ImpossibleEnableFFT, true, NU,         {{"Отключите математическую функцию"},                                 {"DISCONNECT MATHEMATICAL FUNCTION"}}},
    {Warning::WrongFileSystem, false, NU,            {{"Не могу прочитать флешку. Убедитесь, что на ней FAT32"},
                                                                                      {"I can not mount a usb flash FDrive:: Make sure to her FAT32"}}},
    {Warning::WrongModePeackDet, true, NU,           {{"Чтобы изменить длину памяти, отключите пиковый детектор"},
                                                                                 {"To change the length of the memory, turn off the peak detector"}}},
    {Warning::DisableChannelB, true, NU,             {{"Сначала выключите канал 2"},                                           {"First, turn off the channel 2"}}},
    {Warning::TooLongMemory, true, NU,               {{"Второй канал рабоатает при длине памяти 16к и менее"},
                                                                                     {"The second channel runs at a length of memory 16k and less"}}},
    {Warning::NoPeakDet32k, true, NU,                {{"Пиковый детектор не работает при длине памяти 32к"},
                                                                                  {"The peak detector does not work when the memory length of 32k"}}},
    {Warning::NoPeakDet16k, true, NU,                {{"Для работы пикового детектора при длине памяти 16к", "отключите канал 2"},
                                                                         {"For the peak detector with a length of 16k memory", "disable channel 2"}}},
    {Warning::Warn50Ohms, false, NU,                 {{"При величине входного сопротивления 50 Ом", "запрещается подавать на вход более 5 В"},
                                                              {"When the input impedance value of 50 ohms", "is prohibited to input more than 5 V"}}},
    {Warning::WarnNeedForFlashDrive, true, NU,       {{"Сначала подключите флеш-диск"},                                        {"First connect the flash drive"}}},
    {Warning::FirmwareSaved, true, NU,               {{"Прошивка сохранена"},                                                                 {"Firmware saved"}}},
    {Warning::FullyCompletedOTP, false, NU,          {{"Память OTP полностью заполнена"},                                         {"OTP memory fully completed"}}}
};

#define NUM_WARNINGS    10
static const char       *warnings[NUM_WARNINGS] = {0};      ///< Здесь предупреждающие сообщения.
static uint             timeWarnings[NUM_WARNINGS] = {0};   ///< Здесь время, когда предупреждающее сообщение поступило на экран.


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Key Display::key = Key::None;
volatile static bool showLevelTrigLev = false;   ///< Нужно ли рисовать горизонтальную линию уровня смещения уровня синхронизации.
volatile static bool drawRShiftMarkers = false;
static pFuncVV funcOnHand       = 0;
static uint timeStart = 0;
static const char *textWait = 0;
static bool clearBackground = false;
volatile static pFuncVV funcAdditionDraw = 0;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
        DisplayOsci::Update,
        Display::UpdateTester,
        Display::UpdateMultimeter
    };

    pFuncDisplayVV func = funcs[Device::CurrentMode()];

    func();
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

    Console::Draw();

    Painter::EndScene();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display::DrawDataTester(int numStep, int x0, int y0)
{
    static const Color colors[5] = {Color::FILL, Color::GRID, Color::RED, Color::GREEN, Color::BLUE};

    uint8 *dataX = &dataTester[Chan::A][numStep][0];
    uint8 *dataY = &dataTester[Chan::B][numStep][0];

    Painter::SetColor(colors[numStep]);
    
    MathOSC::Smoothing(dataX, TESTER_NUM_POINTS, TESTER_NUM_SMOOTH + 1);
    MathOSC::Smoothing(dataY, TESTER_NUM_POINTS, TESTER_NUM_SMOOTH + 1);

    if (MODE_DRAW_SIGNAL_IS_LINES)
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
void Display::ShowWarning(Warning::E warning)
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
//    NEED_SET_ORIENTATION = 1;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display::SetAddDrawFunction(pFuncVV func)
{
    funcAdditionDraw = func;
}

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
#include "Utils/Math.h"
#include "FPGA/FPGAMath.h"
#include "Console.h"
#include "BottomPart.h"
#include "FPGA/RShift.h"
#include "Multimeter/Multimeter.h"
#include "Tables.h"
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
    {Warning::LimitChan1_Volts, false, NU,           {{"������ ����� 1 - �����/���"},                                            {"LIMIT CHANNEL 1 - VOLTS/DIV"}}},
    {Warning::LimitChan2_Volts, false, NU,           {{"������ ����� 2 - �����/���"},                                            {"LIMIT CHANNEL 2 - VOLTS/DIV"}}},
    {Warning::LimitSweep_Time, false, NU,            {{"������ ��������� - �����/���"},                                               {"LIMIT SWEEP - TIME/DIV"}}},
    {Warning::EnabledPeakDet, false, NU,             {{"������� ������� ��������"},                                                       {"ENABLED PEAK. DET."}}},
    {Warning::LimitChan1_RShift, false, NU,          {{"������ ����� 1 - \x0d"},                                                      {"LIMIT CHANNEL 1 - \x0d"}}},
    {Warning::LimitChan2_RShift, false, NU,          {{"������ ����� 2 - \x0d"},                                                      {"LIMIT CHANNEL 2 - \x0d"}}},
    {Warning::LimitSweep_Level, false, NU,           {{"������ ��������� - �������"},                                                    {"LIMIT SWEEP - LEVEL"}}},
    {Warning::LimitSweep_TShift, false, NU,          {{"������ ��������� - \x97"},                                                        {"LIMIT SWEEP - \x97"}}},
    {Warning::TooSmallSweepForPeakDet, false, NU,    {{"���. ���. �� �������� �� ���������� ����� 0.5���/���"},
                                                                                              {"PEAK. DET. NOT WORK ON SWEETS LESS THAN 0.5us/div"}}},
    {Warning::TooFastScanForRecorder, false, NU,     {{"��������� �� ����� �������� �� ������� ���¨�����"},          {"SELF-RECORDER DOES NOT WORK FAST SCANS"}}},
    {Warning::FileIsSaved, true, NU,                 {{"���� ��������"},                                                                       {"FILE IS SAVED"}}},
    {Warning::SignalIsSaved, true, NU,               {{"������ ��������"},                                                                   {"SIGNAL IS SAVED"}}},
    {Warning::SignalIsDeleted, true, NU,             {{"������ ������"},                                                                   {"SIGNAL IS DELETED"}}},
    {Warning::MenuDebugEnabled, true, NU,            {{"���� ������� ��������"},                                                       {"MENU DEBUG IS ENABLED"}}},
    {Warning::TimeNotSet, true, NU,                  {{"����� �� �����������. ������ ���������� ��� ������"},        {"TIME IS NOT SET. YOU CAN INSTALL IT NOW"}}},
    {Warning::SignalNotFound, true, NU,              {{"������ �� ������"},                                                              {"SIGNAL IS NOT FOUND"}}},
    {Warning::SetTPosToLeft, true, NU,               {{"�� ���������� ��������� 10��/��� ���������� �������-",
                                          "������ \"��������� - \x7b\" � ��������� \"����\" ��� ������-", "��� ������ �������"},
                             {"AT SCANNER SLOWLY 10ms/div DESIRABLY SET \"SCAN - \x7b\" IN", "SWITCH \"Left\" FOR TO ACCELERATE THE OUTPUT SIGNAL"}}},
    {Warning::NeedRebootDevice, true, NU,            {{"��� ���������� ��������� � ����", "��������� ������"},
                                                                              {"FOR THE INTRODUCTION OF CHANGES", "IN FORCE SWITCH OFF THE DEVICE"}}},
    {Warning::ImpossibleEnableMathFunction, true, NU, {{"��������� ���������� ���"},                                           {"DISCONNECT CALCULATION OF FFT"}}},
    {Warning::ImpossibleEnableFFT, true, NU,         {{"��������� �������������� �������"},                                 {"DISCONNECT MATHEMATICAL FUNCTION"}}},
    {Warning::WrongFileSystem, false, NU,            {{"�� ���� ��������� ������. ���������, ��� �� ��� FAT32"},
                                                                                      {"I can not mount a usb flash FDrive:: Make sure to her FAT32"}}},
    {Warning::WrongModePeackDet, true, NU,           {{"����� �������� ����� ������, ��������� ������� ��������"},
                                                                                 {"To change the length of the memory, turn off the peak detector"}}},
    {Warning::DisableChannelB, true, NU,             {{"������� ��������� ����� 2"},                                           {"First, turn off the channel 2"}}},
    {Warning::TooLongMemory, true, NU,               {{"������ ����� ��������� ��� ����� ������ 16� � �����"},
                                                                                     {"The second channel runs at a length of memory 16k and less"}}},
    {Warning::NoPeakDet32k, true, NU,                {{"������� �������� �� �������� ��� ����� ������ 32�"},
                                                                                  {"The peak detector does not work when the memory length of 32k"}}},
    {Warning::NoPeakDet16k, true, NU,                {{"��� ������ �������� ��������� ��� ����� ������ 16�", "��������� ����� 2"},
                                                                         {"For the peak detector with a length of 16k memory", "disable channel 2"}}},
    {Warning::Warn50Ohms, false, NU,                 {{"��� �������� �������� ������������� 50 ��", "����������� �������� �� ���� ����� 5 �"},
                                                              {"When the input impedance value of 50 ohms", "is prohibited to input more than 5 V"}}},
    {Warning::WarnNeedForFlashDrive, true, NU,       {{"������� ���������� ����-����"},                                        {"First connect the flash drive"}}},
    {Warning::FirmwareSaved, true, NU,               {{"�������� ���������"},                                                                 {"Firmware saved"}}},
    {Warning::FullyCompletedOTP, false, NU,          {{"������ OTP ��������� ���������"},                                         {"OTP memory fully completed"}}}
};

#define NUM_WARNINGS    10
static const char       *warnings[NUM_WARNINGS] = {0};      ///< ����� ��������������� ���������.
static uint             timeWarnings[NUM_WARNINGS] = {0};   ///< ����� �����, ����� ��������������� ��������� ��������� �� �����.


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Key Display::key = Key::None;
volatile static bool showLevelTrigLev = false;   ///< ����� �� �������� �������������� ����� ������ �������� ������ �������������.
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

    static const pFuncDisplayVV funcs[Device::Mode::Number] =
    {
        DisplayOsci::Update,
        Display::UpdateTester,
        Multimeter::Graphics::Update
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
    if (mode == DrawMode::Hand)
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
    Display::SetDrawMode(DrawMode::Auto, 0);
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
    Display::SetDrawMode(DrawMode::Hand, FuncOnWait);
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
void Display::SetOrientation(Orientation orientation)
{
    DISPLAY_ORIENTATION = orientation;
//    NEED_SET_ORIENTATION = 1;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display::SetAddDrawFunction(pFuncVV func)
{
    funcAdditionDraw = func;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
Display::ModeAveraging Display::GetModeAveraging()
{
    if (IN_RANDOM_MODE)
    {
        return ModeAveraging::Accurately;
    }
    return MODE_AVE;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Display::NumSignalsInS()
{
    return Tables::ENUMtoENumSignalsInSec(ENUM_SIGNALS_IN_SEC);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display::SetNumSignalsInS(int numSignalsInS)
{
    ENUM_SIGNALS_IN_SEC = Tables::ENumSignalsInSecToENUM(numSignalsInS);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Display::NumPointSmoothing()
{
    /*
    if(MODE_EMS && (ENUM_SMOOTHING < ENumSmooth_4points))
    {
        return 4;
    }
    */

    int retValue = 0;
    if (SMOOTHING_ENABLED)
    {
        retValue = ENUM_SMOOTHING + 1;
    }

    if (IN_RANDOM_MODE)
    {
        int numRand = 0;
        if (NRST_NUM_SMOOTH_FOR_RAND > 1)
        {
            numRand = NRST_NUM_SMOOTH_FOR_RAND;
        }

        LIMIT_BELOW(retValue, numRand);
    }


    return retValue;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
BitSet64 Display::PointsOnDisplay()
{
    BitSet64 retValue;

    retValue.sword0 = (SET_PEAKDET_EN ? (SHIFT_IN_MEMORY / 2) : SHIFT_IN_MEMORY);
    retValue.sword1 = retValue.sword0 + 281;

    return retValue;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
BitSet64 Display::BytesOnDisplay()
{
    BitSet64 retValue;

    retValue.sword0 = SHIFT_IN_MEMORY;
    retValue.sword1 = retValue.sword0 + (SET_PEAKDET_EN ? 281 * 2 : 281);

    return retValue;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Display::TimeMenuAutoHide()
{
    static const int times[] =
    {
        0, 5, 10, 15, 30, 60
    };
    return times[MENU_AUTO_HIDE] * 1000;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Display::IsSeparate()
{
    return FUNC_MODE_DRAW_IS_SEPARATE || FFT_ENABLED;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void SetBrightness(int16 brightness)
{
    BRIGHTNESS_DISPLAY = brightness;
    Painter::SetBrightnessDisplay(brightness);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
int Display::NumAverage()
{
    /*
    if (MODE_EMS && (ENUM_AVE < ENumAverage_8))
    {
        return 8;
    }
    */

    if (!IN_RANDOM_MODE)
    {
        return NUM_AVE;
    }
    else if (NRST_NUM_AVE_FOR_RAND > NUM_AVE)
    {
        return NRST_NUM_AVE_FOR_RAND;
    }

    return NUM_AVE;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Display::ShiftInMemoryInPoints()
{
    if (SET_PEAKDET_DIS)
    {
        return SHIFT_IN_MEMORY;
    }
    return SHIFT_IN_MEMORY / 2;
}

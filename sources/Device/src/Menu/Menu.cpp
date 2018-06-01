#include "Menu.h"
#include "Menu/Pages/PageChannels.h"
#include "Menu/Pages/PageDisplay.h"
#include "Menu/Pages/PageService.h"
#include "Menu/Pages/PageTester.h"
#include "Menu/Pages/PageTrig.h"
#include "Display/Display.h"
#include "FPGA/FPGA.h"
#include "Hardware/Timer.h"
#include "Settings/Settings.h"
#include "Device.h"
#include <string.h>
#include <stdlib.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page pageEmpty;

#define ENABLE_DISABLE_PAGE(page)                                   \
    if (typePress == Press && Device::CurrentMode() == Mode_Osci)   \
    {                                                               \
        if (CURRENT_PAGE == &page)                                  \
        {                                                           \
            CURRENT_PAGE = &pageEmpty;                              \
            MENU_IS_SHOWN = false;                                  \
        }                                                           \
        else                                                        \
        {                                                           \
            CURRENT_PAGE = &page;                                   \
            MENU_IS_SHOWN = true;                                   \
        }                                                           \
    }

uint      Menu::timeLastPressedButton = MAX_UINT;
uint      Menu::timePrevPress[4][2] = {};
Control       Menu::button;
bool      Menu::isPressed[NumButtons] = {};
TypePress Menu::typePress;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Menu::Update()
{

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ButtonPress(Control btn, TypePress tPress)
{
    Display::SetKey(btn);

    typePress = tPress;

    button = btn;

    isPressed[btn] = tPress != Release;

    typedef void(*pFuncMenuVV)();

    static const pFuncMenuVV funcs[NumButtons] =
    {
        &Menu::OnPressNone,
        &Menu::OnPressFunction,
        &Menu::OnPressNone,
        &Menu::OnPressNone,
        &Menu::OnPressService,
        &Menu::OnPressChannelA,
        &Menu::OnPressChannelB,
        &Menu::OnPressNone,
        &Menu::OnPressStartStop,
        &Menu::OnPressTrig,
        &Menu::OnPressMenu,
        &Menu::OnPressRangeMoreA,
        &Menu::OnPressRangeLessA,
        &Menu::OnPressRShiftMoreA,
        &Menu::OnPressRShiftLessA,
        &Menu::OnPressRangeMoreB,
        &Menu::OnPressRangeLessB,
        &Menu::OnPressRShiftMoreB,
        &Menu::OnPressRShiftLessB,
        &Menu::OnPressTBaseMore,
        &Menu::OnPressTBaseLess,
        &Menu::OnPressNone,
        &Menu::OnPressNone,
        &Menu::OnPressTrigLevMore,
        &Menu::OnPressTrigLevLess,
        &Menu::OnPressNone,
        &Menu::OnPressNone,
        &Menu::OnPressNone,
        &Menu::OnPressNone,
        &Menu::OnPressEnter,
        &Menu::OnPressF1,
        &Menu::OnPressF2,
        &Menu::OnPressF3,
        &Menu::OnPressF4,
        &Menu::OnPressF5
    };

    pFuncMenuVV func = funcs[button];

    if (func)
    {
        func();
        timeLastPressedButton = gTimeMS;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressNone()
{
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressF1()
{
    if (typePress == Press)
    {
        CURRENT_PAGE->PressKey(K_1);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressF2()
{
    if (typePress == Press)
    {
        CURRENT_PAGE->PressKey(K_2);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressF3()
{
    if (typePress == Press)
    {
        CURRENT_PAGE->PressKey(K_3);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressF4()
{
    if (typePress == Press)
    {
        CURRENT_PAGE->PressKey(K_4);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressF5()
{
    if (typePress == Press)
    {
        CURRENT_PAGE->PressKey(K_5);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressChannelA()
{
    ENABLE_DISABLE_PAGE(pageChannelA);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressTrig()
{
    ENABLE_DISABLE_PAGE(pageTrig);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressMenu()
{
    ENABLE_DISABLE_PAGE(pageDisplay);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressChannelB()
{
    ENABLE_DISABLE_PAGE(pageChannelB);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressService()
{
    ENABLE_DISABLE_PAGE(pageService);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressRangeLessA()
{
    if (typePress == Press)
    {
        FPGA::DecreaseRange(A);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressRangeMoreA()
{
    if (typePress == Press)
    {
        FPGA::IncreaseRange(A);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressRangeLessB()
{
    if (typePress == Press)
    {
        FPGA::DecreaseRange(B);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressRangeMoreB()
{
    if (typePress == Press)
    {
        FPGA::IncreaseRange(B);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressTBaseLess()
{
    if (typePress == Press)
    {
        FPGA::DecreaseTBase();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressTBaseMore()
{
    if (typePress == Press)
    {
        FPGA::IncreaseTBase();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressRShiftLessA()
{
    if(isPressed[K_RShiftMoreA])
    { 
        FPGA::SetRShift(A, RShiftZero);
    }
    else
    {
        VerifyOnDoubleClick(A, 0);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressRShiftMoreA()
{
    if (isPressed[K_RShiftLessA])
    {
        FPGA::SetRShift(A, RShiftZero);
    }
    else
    {
        VerifyOnDoubleClick(A, 1);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressRShiftLessB()
{
    if (isPressed[K_RShiftMoreB])
    {
        FPGA::SetRShift(B, RShiftZero);
    }
    else
    {
        VerifyOnDoubleClick(B, 0);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressRShiftMoreB()
{
    if (isPressed[K_RShiftLessB])
    {
        FPGA::SetRShift(B, RShiftZero);
    }
    else
    {
        VerifyOnDoubleClick(B, 1);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressTShiftLess()
{
    VerifyOnDoubleClick(3, 0);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressTShiftMore()
{
    VerifyOnDoubleClick(3, 1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressTrigLevMore()
{
    VerifyOnDoubleClick(2, 1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressTrigLevLess()
{
    VerifyOnDoubleClick(2, 0);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::VerifyOnDoubleClick(int src, int dir)
{
    if (typePress == Release)
    {
        return;
    }

    int delta = (dir == 0) ? -1 : 1;

    uint time = gTimeMS;
    int value = delta;
    if (typePress == Press)
    {
        value = time - timePrevPress[src][dir] < timeDoubleClick ? 19 * delta : delta;
    }

    if (src < 2)        { FPGA::RShiftChange((Channel)src, value); }
    else if (src == 2)  { FPGA::TrigLevChange(value); }
    else if(src == 3)   { FPGA::TShiftChange(value); }
    timePrevPress[src][dir] = time;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::Draw()
{
    if (CURRENT_PAGE && MENU_IS_SHOWN)
    {
        if (Device::CurrentMode() == Mode_Osci)
        {
            CURRENT_PAGE->Draw(Grid::Left(), Grid::Bottom() - Control::HEIGHT);
        }
        else if (Device::CurrentMode() == Mode_Tester)
        {
            CURRENT_PAGE->Draw(0, Display::HEIGHT - Control::HEIGHT - 1);
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::Init()
{
    /// \tode ��� �����������, ������� ��� ����� �������������� ������ ������� ����� �� ����� ��������
    //if(CURRENT_PAGE == 0)
    {
        CURRENT_PAGE = &pageEmpty;
    }

    memset(timePrevPress, 0, 4 * 4);

    for (int i = 0; i < NumButtons; i++)
    {
        isPressed[i] = false;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::SaveSettings()
{
    if ((timeLastPressedButton != MAX_UINT) && (gTimeMS - timeLastPressedButton > 5000))
    {
        timeLastPressedButton = MAX_UINT;
        if (Device::CurrentMode() != Mode_Tester)
        {
            set.Save();
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressStartStop()
{
    if (typePress == Press)
    {
        FPGA::OnPressStart();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressFunction()
{
    if (typePress == Press)
    {
        Device::ChangeMode();
        TuneOnDevice();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnPressEnter()
{
    if (typePress == Press)
    {
        MENU_IS_SHOWN = !MENU_IS_SHOWN;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::TuneOnDevice()
{
    static const Page *pageOsci = &pageEmpty;

    DeviceMode mode = Device::CurrentMode();

    if (mode == Mode_Tester)
    {
        pageOsci = CURRENT_PAGE;
        CURRENT_PAGE = &pageTester;
    }
    if (mode == Mode_Osci)
    {
        CURRENT_PAGE = pageOsci;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Page *Menu::CurrentPage(void)
{
    volatile int8 num = CURRENT_PAGE;

    if (num == 1)
    {
        num = num;
    }

    Page *page = (Page *)menu[num];

    return (ADDITION_PAGE_IS_NONE ? page : ADDITION_PAGE);
}

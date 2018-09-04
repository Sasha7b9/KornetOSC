#include "defines.h"
#include "Menu/Menu.h"
#include "Definition.h"
#include "Display/Painter.h"
#include "Display/DisplayTypes.h"
#include "Settings/Settings.h"
#include "Utils/CommonFunctions.h"
#include "Device.h"
#include "PageMultimeter.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pChanA;
extern const PageBase pChanB;
extern const PageBase pTrig;
extern const PageBase pTime;
extern const PageBase pDisplay;
extern const PageBase pCursors;
extern const PageBase pMemory;
extern const PageBase pMeasures;
extern const PageBase pService;
extern const PageBase pHelp;
extern const PageBase pDebug;
extern const PageBase pageOsci;


PageBase *Menu::pageMain = (PageBase *)&pageOsci;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_11_GLOBAL(pageOsci,                                                                                                           // Ã≈Õﬁ ///
    "Ã≈Õﬁ", "MENU",
    "", "",
    pDisplay,   // ƒ»—œÀ≈…
    pChanA,     //  ¿Õ¿À 1
    pChanB,     //  ¿Õ¿À 2
    pTrig,      // —»Õ’–
    pTime,      // –¿«¬≈–“ ¿
    pCursors,   //  ”–—Œ–€
    pMemory,    // œ¿Ãﬂ“‹
    pMeasures,  // »«Ã≈–≈Õ»ﬂ
    pService,   // —≈–¬»—
    pHelp,      // œŒÃŒŸ‹
    pDebug,     // Œ“À¿ƒ ¿
    Page::Name::Main, 0, FuncActive, EmptyPressPage
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
const void *Menu::PageForButton(Key button)
{
    static const void *pages[Key::Number] =
    {  
        0,                  // K_None
        0,                  // K_Function
        (void *)&pMeasures, // K_Measures  2
        (void *)&pMemory,   // K_Memory    3
        (void *)&pService,  // K_Service   4
        (void *)&pChanA,    // K_ChannelA  5
        (void *)&pChanB,    // K_ChannelB  6
        (void *)&pTime,     // K_Time      7
        0,                  // K_Start     
        (void *)&pTrig,     // K_Trig      9
        (void *)&pDisplay   // K_Display  10
    };

    return pages[button];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Menu::IsMainPage(const void *item)
{
    return item == pageMain;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void DrawSB_Exit(int x, int y)
{
    Painter::SetFont(Font::Type::_UGO2);
    Painter::Draw4SymbolsInRect(x + 2, y + 1, '\x2e');
    Painter::SetFont(Font::Type::_8);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void OnPressSB_Exit()
{
    Display::RemoveAddDrawFunction();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
static int CalculateYforCurs(int y, bool top)
{
    return top ? y + Menu::Item::HEIGHT / 2 + 4 : y + Menu::Item::HEIGHT - 2;
}


//---------------------------------------------------------------------------------------------------------------------------------------------------
static int CalculateXforCurs(int x, bool left)
{
    return left ? x + Menu::Item::WIDTH - 20 : x + Menu::Item::WIDTH - 5;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
static void CalculateXY(int *x0, int *x1, int *y0, int *y1)
{
    *x0 = CalculateXforCurs(*x0, true);
    *x1 = CalculateXforCurs(*x1, false);
    *y0 = CalculateYforCurs(*y0, true);
    *y1 = CalculateYforCurs(*y1, false);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void DrawMenuCursVoltage(int x, int y, bool top, bool bottom)
{
    x -= 65;
    y -= 21;
    int x0 = x, x1 = x, y0 = y, y1 = y;
    CalculateXY(&x0, &x1, &y0, &y1);
    for (int i = 0; i < (top ? 3 : 1); i++)
    {
        Painter::DrawHLine(y0 + i, x0, x1);
    }
    for (int i = 0; i < (bottom ? 3 : 1); i++)
    {
        Painter::DrawHLine(y1 - i, x0, x1);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void CalculateConditions(int16 pos0, int16 pos1, Cursors::Control cursCntrl, bool *cond0, bool *cond1)
{
    bool zeroLessFirst = pos0 < pos1;
    *cond0 = cursCntrl == Cursors::Control::_1_2 || (cursCntrl == Cursors::Control::_1 && zeroLessFirst) || (cursCntrl == Cursors::Control::_2 && !zeroLessFirst);
    *cond1 = cursCntrl == Cursors::Control::_1_2 || (cursCntrl == Cursors::Control::_1 && !zeroLessFirst) || (cursCntrl == Cursors::Control::_2 && zeroLessFirst);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void DrawMenuCursTime(int x, int y, bool left, bool right)
{
    x -= 58;
    y -= 16;
    int x0 = x, x1 = x, y0 = y, y1 = y;
    CalculateXY(&x0, &x1, &y0, &y1);
    for (int i = 0; i < (left ? 3 : 1); i++)
    {
        Painter::DrawVLine(x0 + i, y0, y1);
    }
    for (int i = 0; i < (right ? 3 : 1); i++)
    {
        Painter::DrawVLine(x1 - i, y0, y1);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ChangeMode()
{
    if(Device::CurrentMode() == Device::Mode::Multimeter)
    {
        pageMain = (PageBase *)PageMultimeter::pointer;
    }
    else
    {
        pageMain = (PageBase *)&pageOsci;
    }
}

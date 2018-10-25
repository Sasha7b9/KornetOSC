#include "defines.h"
#include "PageFunction.h"
#include "Menu/Menu.h"
#include "Settings/Settings.h"
#include "Hardware/Sound.h"
#include "Definition.h"
#include "Display/Painter.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pageFunction;

const PageBase *PageFunction::pointer = &pageFunction;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_4( pageFunction,                                                                                                            //--- ‘”Õ ÷»ﬂ ---
    "‘”Õ ÷»ﬂ", "FUNCTION",
    "¬˚·Ó ÙÛÌÍˆËË",
    "Function selection",
    *PageFunction::PageFrequencyCounter::pointer,   // ‘”Õ ÷»ﬂ - ◊¿—“Œ“ŒÃ≈–
    *PageFunction::PageFFT::pointer,                // ‘”Õ ÷»ﬂ - —œ≈ “–
    *PageFunction::PageMultimeter::pointer,         // ‘”Õ ÷»ﬂ - Ã”À‹“»Ã≈“–
    *PageFunction::PageTester::pointer,             // ‘”Õ ÷»ﬂ - “≈—“≈–
    Page::Name::Function, Menu::pageMain, FuncActive, FuncPress
)

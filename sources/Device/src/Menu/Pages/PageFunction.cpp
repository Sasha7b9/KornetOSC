#include "defines.h"
#include "PageFunction.h"
#include "Menu/Menu.h"
#include "Settings/Settings.h"
#include "Hardware/Sound.h"
#include "Definition.h"
#include "Display/Painter.h"
#include "PageMultimeter.h"
#include "PageTester.h"
#include "PageFunctionFFT.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pageFunction;

const PageBase *PageFunction::pointer = &pageFunction;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_4( pageFunction,                                                                                                            //--- ‘”Õ ÷»ﬂ ---
    "‘”Õ ÷»ﬂ", "FUNCTION",
    "¬˚·Ó ÙÛÌÍˆËË",
    "Function selection",
    *PageFunction::FrequencyCounter::pointer,   // ‘”Õ ÷»ﬂ - ◊¿—“Œ“ŒÃ≈–
    *PageFunctionFFT::pointer,                  // ‘”Õ ÷»ﬂ - —œ≈ “–
    *PageMultimeter::pointer,                   // ‘”Õ ÷»ﬂ - Ã”À‹“»Ã≈“–
    *PageTester::pointer,                       // ‘”Õ ÷»ﬂ - “≈—“≈–
    Page::Name::Function, Menu::pageMain, FuncActive, FuncPress
)

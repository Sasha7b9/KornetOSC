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
DEF_PAGE_4( pageFunction,                                                                                                            //--- ������� ---
    "�������", "FUNCTION",
    "����� �������",
    "Function selection",
    *PageFunction::FrequencyCounter::pointer,   // ������� - ����������
    *PageFunctionFFT::pointer,                  // ������� - ������
    *PageMultimeter::pointer,                   // ������� - ����������
    *PageTester::pointer,                       // ������� - ������
    Page::Name::Function, Menu::pageMain, FuncActive, FuncPress
)

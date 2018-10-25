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
DEF_PAGE_4( pageFunction,                                                                                                            //--- ������� ---
    "�������", "FUNCTION",
    "����� �������",
    "Function selection",
    *PageFunction::PageFrequencyCounter::pointer,   // ������� - ����������
    *PageFunction::PageFFT::pointer,                // ������� - ������
    *PageFunction::PageMultimeter::pointer,         // ������� - ����������
    *PageFunction::PageTester::pointer,             // ������� - ������
    Page::Name::Function, Menu::pageMain, FuncActive, FuncPress
)

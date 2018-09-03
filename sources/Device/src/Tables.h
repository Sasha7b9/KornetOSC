#pragma once
#include "defines.h"
#include "Settings/Settings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Tables
{
public:
    static Display::ENumSignalsInSec ENumSignalsInSecToENUM(int numSignalsInSec);
    
    static int ENUMtoENumSignalsInSec(Display::ENumSignalsInSec numSignalsInSec);
    
    static pString GetTBaseString(TBase tBase);
    
    static pString GetTBaseStringEN(TBase tBase);
    
    static pString RangeNameFromValue(Range range);
    /// ���������� ����� ������ �� 1 �� 2.
    static int GetNumChannel(Chan ch);
    
    static pString symbolsAlphaBet[0x48];
    /// ������� ������ �� ������� symbolsAlphaBet
    static void DrawStr(int index, int x, int y);
};


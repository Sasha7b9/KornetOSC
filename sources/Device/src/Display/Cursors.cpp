#include "Cursors.h"
#include "Settings/Settings.h"
#include "Display/Grid.h"
#include "Menu/Menu.h"
#include "FPGA/FPGAMath.h"
#include "Utils/StringUtils.h"
#include <string.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Cursors::PosU(Chan ch, int numCur)
{
    return CURsU_POS(ch, numCur) / (Grid::Bottom() == Grid::FullBottom() ? 1.0f : 2.0f);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Cursors::NecessaryDraw()
{
    return (CURsU_ENABLED || CURsT_ENABLED) && (CURS_SHOW || Menu::GetNameOpenedPage() == PageSB_Cursors_Set);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
pString Cursors::Voltage(Chan source, int numCur, char buffer[20])
{
    float voltage = MathFPGA::VoltageCursor(Cursors::PosU(source, numCur), SET_RANGE(source), SET_RSHIFT(source));
    if (SET_DIVIDER_10(source))
    {
        voltage *= 10.0f;
    }
    return Voltage2String(voltage, true, buffer);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
float Cursors::PosT(Chan ch, int num)
{
    float retValue = 0.0f;
    memcpy(&retValue, &set.curs_posCurT[ch][num], sizeof(float));
    return retValue;
}

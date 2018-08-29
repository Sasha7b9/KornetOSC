#include "Settings.h"
#include "Display/Grid.h"
#include "SettingsCursors.h"
#include "Utils/StringUtils.h"
#include "Menu/Menu.h"
#include "FPGA/FPGATypes.h"
#include "FPGA/FPGAMath.h"
#include <math.h>
#include <string.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *sCursors_GetCursorTime(Chan source, int numCur, char buffer[20])
{
//    float pos = 0.0;

    /// \todo Кака я-то дичь с зависанием. Временный костыль.
    //memcpy(&pos, &CURsT_POS(source, numCur), sizeof(float));

    float time = MathFPGA::TimeCursor(CURsT_POS(source, numCur), SET_TBASE);
        
    return Time2String(time, true, buffer);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
const char *sCursors_GetCursorPercentsU(Chan source, char buffer[20])
{
    buffer[0] = 0;
    /** \todo Тут дикая дичь. Эта строчка вызывает HardFault. Возможно, из-за включенного выравнивания Settings.
        Надо подумать */

    // float dPerc = dUperc(source);     
    float dPerc = 100.0f;
    memcpy(&dPerc, &dUperc(source), sizeof(float));

    float dValue = fabsf(Cursors::PosU(source, 0) - Cursors::PosU(source, 1));
    char bufferOut[20];
    char *percents = Float2String(dValue / dPerc * 100.0f, false, 5, bufferOut);
    strcat(buffer, percents);
    strcat(buffer, "%");
    return buffer;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
const char *sCursors_GetCursorPercentsT(Chan source, char buffer[20])
{
    buffer[0] = 0;
    
    float dPerc = 100.0f;
    memcpy(&dPerc, &dTperc(source), sizeof(float));
    
    float dValue = fabsf(CURsT_POS(source, 0) - CURsT_POS(source, 1));
    char bufferOut[20];
    char *percents = Float2String(dValue / dPerc * 100.0f, false, 6, bufferOut);
    strcat(buffer, percents);
    strcat(buffer, "%");
    return buffer;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
float GetCursPosT(Chan ch, int num)
{
    float retValue = 0.0f;
    memcpy(&retValue, &set.curs_posCurT[ch][num], sizeof(float));
    return retValue;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void SetCursPosT_temp(Chan ch, int num, float value)
{
    memcpy(&set.curs_posCurT[ch][num], &value, sizeof(float));
}

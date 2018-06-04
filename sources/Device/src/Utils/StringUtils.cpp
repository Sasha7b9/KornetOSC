#include "StringUtils.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char *SU::Bin2String(uint8 value)
{
    static char buffer[9];
    for (int bit = 0; bit < 8; bit++)
    {
        buffer[7 - bit] = _GET_BIT(value, bit) ? '1' : '0';
    }
    buffer[8] = '\0';
    return buffer;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int SU::NumDigitsInNumber(int value)
{
    value = Abs(value);
    int num = 1;
    while ((value /= 10) > 0)
    {
        num++;
    }
    return num;
}

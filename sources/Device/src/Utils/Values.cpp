#include "defines.h"
#include "Values.h"
#include "Math.h"
#include "StringUtils.h"
#include "Settings/Settings.h"
#include <string.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* Bin::ToString(int depth, char buffer[36]) const
{
    int byte = 3;       /// — этого байта начинаем вывод. “.к. в начале строки - старший байт, в конце - младший

    switch (depth)
    {
        case 8: byte = 0;  break;
        case 16: byte = 1; break;
    }

    char *pointer = buffer;

    while (byte >= 0)
    {
        BinToString8((uint8)(value >> (byte * 8)), pointer);
        if (byte > 0)
        {
            *(pointer + 8) = ' ';
        }
        pointer += 9;
        byte--;
    }

    return buffer;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
char* Bin::BinToString8(uint8 val, char buffer[9]) const
{
    for (int bit = 0; bit < 8; bit++)
    {
        buffer[7 - bit] = _GET_BIT(val, bit) ? '1' : '0';
    }
    buffer[8] = '\0';
    return buffer;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
char* Hex::ToString(int depth, char buffer[9]) const
{
    switch (depth)
    {
        case 8:     sprintf(buffer, "%02X", value); break;
        case 16:    sprintf(buffer, "%04X", value); break;
        case 32:    sprintf(buffer, "%08X", value); break;
        default:                                    break;
    }

    return buffer;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
char *Frequency::ToString(char bufferOut[20]) const
{
    float freq = value;

    bufferOut[0] = 0;
    const char *suffix = 0;
    if (Math::IsEquals(freq, ERROR_VALUE_FLOAT))
    {
        strcat(bufferOut, ERROR_STRING_VALUE);
        return bufferOut;
    }
    if (freq >= 1e6f)
    {
        suffix = LANG_RU ? "ћ√ц" : "MHz";
        freq /= 1e6f;
    }
    else if (freq >= 1e3f)
    {
        suffix = LANG_RU ? "к√ц" : "kHz";
        freq /= 1e3f;
    }
    else
    {
        suffix = LANG_RU ? "√ц" : "Hz";
    }
    char buffer[20];
    strcat(bufferOut, SU::Float2String(freq, false, 4, buffer));
    strcat(bufferOut, suffix);
    return bufferOut;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
char *Frequency::ToStringAccuracy(char bufferOut[20], int numDigits) const
{
    float freq = value;

    bufferOut[0] = 0;
    const char *suffix = LANG_RU ? "√ц" : "Hz";
    if (Math::IsEquals(freq, ERROR_VALUE_FLOAT))
    {
        strcat(bufferOut, ERROR_STRING_VALUE);
        return bufferOut;
    }
    if (freq >= 1e6f)
    {
        suffix = LANG_RU ? "ћ√ц" : "MHz";
        freq /= 1e6f;
    }
    else if (freq >= 1e3f)
    {
        suffix = LANG_RU ? "к√ц" : "kHz";
        freq /= 1e3f;
    }
    char buffer[20];
    strcat(bufferOut, SU::Float2String(freq, false, numDigits, buffer));
    strcat(bufferOut, suffix);
    return bufferOut;
}

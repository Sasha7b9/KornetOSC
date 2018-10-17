#include "defines.h"
#include "Values.h"
#include "Math.h"
#include "StringUtils.h"
#include "Settings/Settings.h"
#include <string.h>
#include <math.h>


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

//----------------------------------------------------------------------------------------------------------------------------------------------------
char *Time::ToString(bool alwaysSign, char buffer[20]) const
{
    float time = value;

    if (Math::IsEquals(time, ERROR_VALUE_FLOAT))
    {
        strcpy(buffer, ERROR_STRING_VALUE);
        return buffer;
    }

    pString suffix[2][4] =
    {
        {"нс", "мкс", "мс", "с"},
        {"ns", "us",  "ms", "s"}
    };

    static const float factor[4] = {1e9f, 1e6f, 1e3f, 1.0f};

    float absTime = fabsf(time);

    int num = 0;

    if (absTime + 0.5e-10f < 1e-6f)
    {
    }
    else if (absTime + 0.5e-7f < 1e-3f)
    {
        num = 1;
    }
    else if (absTime + 0.5e-3f < 1.0f)
    {
        num = 2;
    }
    else
    {
        num = 3;
    }

    char bufferOut[20];
    strcpy(buffer, SU::Float2String(time * factor[num], alwaysSign, 4, bufferOut));
    strcat(buffer, suffix[LANG][num]);
    return buffer;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
char* Time::ToStringAccuracy(bool alwaysSign, char buffer[20], int numDigits) const
{
    float time = value;

    buffer[0] = 0;
    const char *suffix = LANG_RU ? "с" : "s";

    float fabsTime = fabsf(time);

    if (Math::IsEquals(time, ERROR_VALUE_FLOAT))
    {
        strcat(buffer, ERROR_STRING_VALUE);
        return buffer;
    }
    else if (fabsTime + 0.5e-10f < 1e-6f)
    {
        suffix = LANG_RU ? "нс" : "ns";
        time *= 1e9f;
    }
    else if (fabsTime + 0.5e-7f < 1e-3f)
    {
        suffix = LANG_RU ? "мкс" : "us";
        time *= 1e6f;
    }
    else if (fabsTime + 0.5e-3f < 1.0f)
    {
        suffix = LANG_RU ? "мс" : "ms";
        time *= 1e3f;
    }

    char bufferOut[20];
    strcat(buffer, SU::Float2String(time, alwaysSign, numDigits, bufferOut));
    strcat(buffer, suffix);

    return buffer;
}

char* Voltage::ToString(bool alwaysSign, char buffer[20]) const
{
    float voltage = value;

    if (Math::IsEquals(voltage, ERROR_VALUE_FLOAT))
    {
        strcpy(buffer, ERROR_STRING_VALUE);
        return buffer;
    }

    pString suf[2][4] =
    {
        {"\x10мк¬", "\x10м¬", "\x10¬", "\x10к¬"},
        {"\x10uV",  "\x10mV", "\x10V", "\x10kV"}
    };

    static const float factor[4] = {1e6f, 1e3f, 1.0f, 1e-3f};

    int num = 0;
    float absValue = fabsf(voltage) + 0.5e-4f;

    if (absValue < 1e-3f)
    {
        num = 0;
    }
    else if (absValue < 1.0f)
    {
        num = 1;
    }
    else if (absValue < 1e3f)
    {
        num = 2;
    }
    else
    {
        num = 3;
    }

    CHAR_BUF(bufferOut, 20);

    SU::Float2String(voltage * factor[num], alwaysSign, 4, bufferOut);

    strcpy(buffer, bufferOut);
    strcat(buffer, suf[LANG][num]);
    return buffer;
}

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
    int byte = 3;       /// � ����� ����� �������� �����. �.�. � ������ ������ - ������� ����, � ����� - �������

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
        suffix = LANG_RU ? "���" : "MHz";
        freq /= 1e6f;
    }
    else if (freq >= 1e3f)
    {
        suffix = LANG_RU ? "���" : "kHz";
        freq /= 1e3f;
    }
    else
    {
        suffix = LANG_RU ? "��" : "Hz";
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
    const char *suffix = LANG_RU ? "��" : "Hz";
    if (Math::IsEquals(freq, ERROR_VALUE_FLOAT))
    {
        strcat(bufferOut, ERROR_STRING_VALUE);
        return bufferOut;
    }
    if (freq >= 1e6f)
    {
        suffix = LANG_RU ? "���" : "MHz";
        freq /= 1e6f;
    }
    else if (freq >= 1e3f)
    {
        suffix = LANG_RU ? "���" : "kHz";
        freq /= 1e3f;
    }
    char buffer[20];
    strcat(bufferOut, SU::Float2String(freq, false, numDigits, buffer));
    strcat(bufferOut, suffix);
    return bufferOut;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
char *Time::ToString(bool alwaysSign, char buffer[20])
{
    float time = value;

    if (Math::IsEquals(time, ERROR_VALUE_FLOAT))
    {
        strcpy(buffer, ERROR_STRING_VALUE);
        return buffer;
    }

    pString suffix[2][4] =
    {
        {"��", "���", "��", "�"},
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
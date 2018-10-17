#include "defines.h"
#include "Utils/StringUtils.h"
#include "Utils/Dictionary.h"
#include "Utils/Math.h"
#include "Settings/Settings.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#ifndef LANG
#define LANG 0
#define LANG_RU true
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char *SU::Float2String(float value, bool alwaysSign, int numDigits, char bufferOut[20])
{
    if (Math::IsEquals(value, ERROR_VALUE_FLOAT))
    {
        strcpy(bufferOut, ERROR_STRING_VALUE);
        return bufferOut;
    }

    value = Math::RoundFloat(value, numDigits);
    
    char *pBuffer = bufferOut;

    if (value < 0)
    {
        *pBuffer++ = '-';
    }
    else if (alwaysSign)
    {
        *pBuffer++ = '+';
    }

    char format[10] = "%4.2f\0\0";

    format[1] = (char)numDigits + 0x30;

    int numDigitsInInt = Math::DigitsInIntPart(value);

    format[3] = (char)((numDigits - numDigitsInInt) + 0x30);
    if (numDigits == numDigitsInInt)
    {
        format[5] = '.';
    }

    float absValue = fabsf(value);
    sprintf(pBuffer, (char *)format, (double)absValue);

    float val = (float)atof(pBuffer);

    if (Math::DigitsInIntPart(val) != numDigitsInInt)
    {
        numDigitsInInt = Math::DigitsInIntPart(val);
        format[3] = (char)((numDigits - numDigitsInInt) + 0x30);
        if (numDigits == numDigitsInInt)
        {
            format[5] = '.';
        }
        sprintf(pBuffer, format, (double)value);
    }

    bool signExist = alwaysSign || value < 0;
    while (strlen(bufferOut) < (size_t)(numDigits + (signExist ? 2 : 1)))
    {
        strcat(bufferOut, "0");
    }

    return bufferOut;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
char *SU::FloatFract2String(float value, bool alwaysSign, char bufferOut[20])
{
    return Float2String(value, alwaysSign, 4, bufferOut);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
char *SU::Phase2String(float phase, bool, char bufferOut[20])
{
    char buffer[20];
    sprintf(bufferOut, "%s\xa8", Float2String(phase, false, 4, buffer));
    return bufferOut;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
char *SU::Int2String(int value, bool alwaysSign, int numMinFields, char buffer[20])
{
    const int SIZE = 20;
    char format[SIZE] = "%";
    snprintf(&(format[1]), SIZE, "0%d", numMinFields);
    strcat(format, "d");
    if (alwaysSign && value >= 0)
    {
        buffer[0] = '+';
        snprintf(buffer + 1, SIZE - 1, format, value);
    }
    else
    {
        snprintf(buffer, SIZE, format, value);
    }
    return buffer;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool String2Int(char *str, int *value)
{
    int sign = str[0] == '-' ? -1 : 1;
    if (str[0] < '0' || str[0] > '9')
    {
        str++;
    }
    uint length = strlen(str);
    if (length == 0)
    {
        return false;
    }

    *value = 0;
    int pow = 1;
    uint i = length;
    do
    {
        --i;
        int val = str[i] & (~(0x30));
        if (val < 0 || val > 9)
        {
            return false;
        }
        *value += val * pow;
        pow *= 10;
    } while (i > 0);

    if (sign == -1)
    {
        *value *= -1;
    }
    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
char *SU::Db2String(float value, int numDigits, char bufferOut[20])
{
    bufferOut[0] = 0;
    char buffer[20];
    strcat(bufferOut, Float2String(value, false, numDigits, buffer));
    strcat(bufferOut, "дБ");
    return bufferOut;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int BCD2Int(uint bcd)
{
    uint pow = 1;

    int value = 0;

    for (int i = 0; i < 8; i++)
    {
        value += (bcd & 0x0f) * pow;
        pow *= 10;
        bcd = bcd >> 4;
    }

    return value;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int SU::NumWords(const char *string)
{
    ChooseSpaces(&string);

    while (true)
    {
        int numWords = 0;

        if (ChooseSymbols(&string))
        {
            numWords++;
        }
        else
        {
            return numWords;
        }
        ChooseSpaces(&string);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
char *SU::GetWord(char *string, int n, char *out, int size)
{
    if (n >= NumWords(string))
    {
        return 0;
    }

    if (n == 1)
    {
        n = 1;
    }

    // Находим начало искомого слова
    int currentWord = 0;
    do
    {
        if (*string != ' ')                         // Если текущий символ - не пробел, то нашли новое слово
        {
            if (currentWord == n)                   // Если текущее слово - наше
            {
                break;                              // то выходим - string указаывает на искомое слово
            }
            ++currentWord;
            while (*string != ' ' && *string != 0)     // Выбираем буквы этого слова
            {
                ++string;
            }
        }
        while (*string == ' ')
        {
            ++string;                   // Выбираем пробелы
        }
    } while (*string);

    // Находим конец искомого символа
    char *end = string;

    while (*end != ' ' && *end != 0)
    {
        ++end;                          // Ищем конец слова
    }

    int length = end - string;

    if (length + 1 > size)
    {
        return (char *)0xffffffff;              // Не хватит места в выходном буфере - выходим с соответствующим кодом
    }

    for (int i = 0; i < length; i++)
    {
        out[i] = string[i];
    }
    out[length] = 0;

    return out;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int SU::NumDigitsInNumber(int value)
{
    value = Math::Abs(value);
    int num = 1;
    while ((value /= 10) > 0)
    {
        num++;
    }
    return num;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int SU::NumDigitsInNumber(uint value)
{
    int num = 1;
    while ((value /= 10) > 0)
    {
        num++;
    }
    return num;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
char SU::DigitInPosition(uint value, int pos)
{
    while(pos > 0)
    {
        value /= 10;
        pos--;
    }

    return (char)((value % 10) | 0x30);
}


#define  SYMBOL(x) (*(*(x)))

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool SU::ChooseSymbols(const char **string)
{
    if (SYMBOL(string) == 0x0d && SYMBOL(string + 1) == 0x0a)
    {
        return false;
    }

    while (SYMBOL(string) != ' ' && SYMBOL(string) != 0x0d && SYMBOL(string + 1) != 0x0a)
    {
        (*string)++;
    }

    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool SU::ChooseSpaces(const char **string)
{
    if (SYMBOL(string) == 0x0d && SYMBOL(string + 1) == 0x0a)
    {
        return false;
    }

    while (SYMBOL(string) == ' ')
    {
        (*string)++;
    }

    return true;
}

#undef SYMBOL

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool SU::GetWord(const char *string, Word *word, const int numWord)
{
    ChooseSpaces(&string);

    int currentWord = 0;

    while (true)
    {
        if (currentWord == numWord)
        {
            word->address = (char *)string;
            ChooseSymbols(&string);
            word->numSymbols = (int8)(string - word->address);

            char *pointer = word->address;
            int numSymbols = word->numSymbols;
            for (int i = 0; i < numSymbols; i++)
            {
                *pointer = (char)toupper(*pointer);
                pointer++;
            }
            return true;
        }
        if (ChooseSymbols(&string))
        {
            currentWord++;
        }
        else
        {
            return false;
        }
        ChooseSpaces(&string);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool SU::WordEqualZeroString(Word *word, char* string)
{
    char *ch = string;
    char *w = (char*)(word->address);

    while (*ch != 0)
    {
        if (*ch++ != *w++)
        {
            return false;
        }
    }

    return (ch - string) == word->numSymbols;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool SU::EqualsZeroStrings(char *str1, char *str2)
{
    while ((*str1) == (*str2))
    {
        if ((*str1) == '\0')
        {
            return true;
        }
        str1++;
        str2++;
    }
    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool SU::EqualsStrings(char *str1, char *str2, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (str1[i] != str2[i])
        {
            return false;
        }
    }
    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool SU::EqualsStrings(char *str1, char *str2)
{
    uint size = strlen(str1);

    for (uint i = 0; i < size; i++)
    {
        if (str1[i] != str2[i])
        {
            return false;
        }
    }
    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int SU::FindSymbol(const char *string, char symbol)
{
    int pos = 0;
    while(*string)
    {
        if(*string == symbol)
        {
            return pos;
        }
        ++pos;
        ++string;
    }
    return -1;
}

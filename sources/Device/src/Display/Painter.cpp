#include "Painter.h"
#include "Display/Font/Font.h"
#include "Keyboard/Decoder.h"
#include "Utils/Math.h"
#include "Hardware/FSMC.h"
#include "Hardware/Timer.h"
#include <string.h>
#include <stdarg.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool inverseColors = false;
Color    Painter::currentColor = Color::NUMBER;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Painter::BeginScene(Color color)
{
    uint8 buffer[2] = {PAINT_BEGIN_SCENE, color.value};
    FSMC::WriteToPanel(buffer, 2);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::EndScene()
{
    uint8 buffer[1] = {PAINT_END_SCENE};
    FSMC::WriteToPanel(buffer, 1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::SetColor(Color color)
{
    if (color != Color::NUMBER)
    {
        uint8 buffer[2] = {PAINT_SET_COLOR, color.value};
        FSMC::WriteToPanel(buffer, 2);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::FillRegion(int x, int y, int width, int height, Color color)
{
    SetColor(color);
    uint8 buffer[7] = {PAINT_FILL_REGION, (uint8)x, (uint8)(x >> 8), (uint8)y, (uint8)width, (uint8)(width >> 8), (uint8)height};
    FSMC::WriteToPanel(buffer, 7);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Painter::DrawText(int x, int y, const char *text, Color color)
{
    #define MAX_SIZE_BUFFER 100
    
    if(strlen(text) + 1 > MAX_SIZE_BUFFER)
    {
        return x + 10;
    }
       
    SetColor(color);
    size_t size = (size_t)(1 + 2 + 1 + 1 + strlen(text));
    uint8 buffer[MAX_SIZE_BUFFER] = {PAINT_DRAW_TEXT, (uint8)x, (uint8)(x >> 8), (uint8)y, (uint8)(size - 5)};

    uint8 *pointer = &buffer[5];

    for (uint i = 0; i < strlen(text); i++)
    {
        *pointer++ = (uint8)text[i];
    }

    FSMC::WriteToPanel(buffer, (int)size);

    return x + 10;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::SetColorValue(Color color, uint value)
{
    uint8 buffer[6] = {PAINT_SET_PALETTE, color.value, (uint8)value, (uint8)(value >> 8), (uint8)(value >> 16), (uint8)(value >> 24)};

    FSMC::WriteToPanel(buffer, 6);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawRectangle(int x, int y, int width, int height, Color color)
{
    SetColor(color);
    uint8 buffer[7] = {PAINT_DRAW_RECTANGLE, (uint8)x, (uint8)(x >> 8), (uint8)y, (uint8)width, (uint8)(width >> 8), (uint8)height};
    FSMC::WriteToPanel(buffer, 7);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Painter::DrawFormatText(int x, int y, Color color, char *text, ...)
{
    SetColor(color);
#define SIZE_BUFFER_DRAW_FORM_TEXT 200
    CHAR_BUF(buffer, SIZE_BUFFER_DRAW_FORM_TEXT);
    va_list args;
    va_start(args, text);
    vsprintf(buffer, text, args);
    va_end(args);
    return DrawText(x, y, buffer);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Painter::DrawFormatText(int x, int y, char *text, ...)
{
#define SIZE_BUFFER_DRAW_FORM_TEXT 200
    CHAR_BUF(buffer, SIZE_BUFFER_DRAW_FORM_TEXT);
    va_list args;
    va_start(args, text);
    vsprintf(buffer, text, args);
    va_end(args);
    return DrawText(x, y, buffer);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Painter::DrawChar(int x, int y, char symbol, Color color)
{
    DrawFormatText(x, y, color, "%c", symbol);

    return 8;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawHLine(int y, int x0, int x1, Color color)
{
    SetColor(color);
    uint8 buffer[6] = {PAINT_DRAW_HLINE, (uint8)y, (uint8)x0, (uint8)(x0 >> 8), (uint8)x1, (uint8)(x1 >> 8)};
    FSMC::WriteToPanel(buffer, 6);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawHLine(float y, int x0, int x1, Color color)
{
    DrawHLine((int)y, x0, x1, color);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawVLine(int x, int y0, int y1, Color color)
{
    SetColor(color);
    uint8 buffer[5] = {PAINT_DRAW_VLINE, (uint8)x, (uint8)(x >> 8), (uint8)y0, (uint8)y1};
    FSMC::WriteToPanel(buffer, 5);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawVLine(int x, float y0, float y1, Color color)
{
    DrawVLine((int)x, (int)y0, (int)y1, color);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawLine(int x0, int y0, int x1, int y1, Color color)
{
    SetColor(color);
    uint8 buffer[7] = {PAINT_DRAW_LINE, (uint8)x0, (uint8)(x0 >> 8), (uint8)y0, (uint8)x1, (uint8)(x1 >> 8), (uint8)y1};
    FSMC::WriteToPanel(buffer, 7);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::SetPoint(int x, int y, Color color)
{
    SetColor(color);
    uint8 buffer[4] = {PAINT_SET_POINT, (uint8)x, (uint8)(x >> 8), (uint8)y};
    FSMC::WriteToPanel(buffer, 4);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::SetFont(TypeFont typeFont)
{
    uint8 buffer[2] = {PAINT_SET_FONT, (uint8)typeFont};
    FSMC::WriteToPanel(buffer, 2);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawBoundedRegion(int x, int y, int width, int height, Color colorFill, Color colorBound)
{
    DrawRectangle(x, y, width, height, colorBound);
    FillRegion(x + 1, y + 1, width - 2, height - 2, colorFill);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Painter::DrawTextInRectWithTransfersC(int x, int y, int width, int height, const char *text, Color color)
{
    SetColor(color);
    return DrawTextInRectWithTransfers(x, y, width, height, text);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static bool IsLetter(char symbol)
{
    static const bool isLetter[256] =
    {
        false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
        true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true,
        true, true, true, true, true, true, true, true, true, true, true, false, false, false, false, false,
        true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true,
        true, true, true, true, true, true, true, true, true, true, true, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
        true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true,
        true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true,
        true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true,
        true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true
    };

    return isLetter[(uint8)symbol];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static char *GetWord(const char *firstSymbol, int *length, char buffer[20])
{
    int pointer = 0;
    *length = 0;

    while (IsLetter(*firstSymbol))
    {
        buffer[pointer] = *firstSymbol;
        pointer++;
        firstSymbol++;
        (*length)++;
    }
    buffer[pointer] = '\0';

    return buffer;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static bool IsConsonant(char symbol)
{
    static const bool isConsonat[256] =
    {
        false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
        false, true, true, true, true, false, true, true, false, false, true, true, true, true, false, true,
        true, true, true, false, true, true, true, true, true, true, true, false, true, false, false, false,
        false, true, true, true, true, false, true, true, false, false, true, true, true, true, false, true,
        true, true, true, false, true, true, true, true, true, true, true, false, true, false, false, false
    };

    return isConsonat[(uint8)symbol];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static bool CompareArrays(const bool *array1, const bool *array2, int numElems)
{
    for (int i = 0; i < numElems; i++)
    {
        if (array1[i] != array2[i])
        {
            return false;
        }
    }
    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/// \brief ������� ��������� �������. C letters ���������� ����� �����, ��� ����� ����� �������, � lettersInSyllable ����� �������� ����� ���� � 
/// ��������� �����. ���� ����� �����������, ������� ���������� false
static bool FindNextTransfer(const char *letters, int8 *lettersInSyllable)
{

#define VOWEL       0   // �������
#define CONSONANT   1   // ���������

    * lettersInSyllable = (int8)strlen(letters);
    if (strlen(letters) <= 3)
    {
        return false;
    }

    static const bool template1[3] = {false, true, true};               //     011     2   // ����� ������� ������� �������
    static const bool template2[4] = {true, false, true, false};        //     1010    2
    static const bool template3[4] = {false, true, false, true};        //     0101    3
    static const bool template4[4] = {true, false, true, true};         //     1011    3
    static const bool template5[4] = {false, true, false, false};       //     0100    3
    static const bool template6[4] = {true, false, true, true};         //     1011    3
    static const bool template7[5] = {true, true, false, true, false};  //     11010   3
    static const bool template8[6] = {true, true, false, true, true};   //     11011   4

    bool consonant[20];

    int size = (int)strlen(letters);
    for (int i = 0; i < size; i++)
    {
        consonant[i] = IsConsonant(letters[i]);
    }

    if (CompareArrays(template1, consonant, 3))
    {
        *lettersInSyllable = 2;
        return true;
    }
    if (CompareArrays(template2, consonant, 4))
    {
        *lettersInSyllable = 2;
        return true;
    }
    if (strlen(letters) < 5)
    {
        return false;
    }
    if (CompareArrays(template3, consonant, 4) || CompareArrays(template4, consonant, 4) || CompareArrays(template5, consonant, 4) ||
        CompareArrays(template6, consonant, 4))
    {
        *lettersInSyllable = 3;
        return true;
    }
    if (strlen(letters) < 6)
    {
        return false;
    }
    if (CompareArrays(template7, consonant, 5))
    {
        *lettersInSyllable = 3;
        return true;
    }
    if (CompareArrays(template8, consonant, 5))
    {
        *lettersInSyllable = 4;
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static int8 *BreakWord(char *word)
{
    int num = 0;
    static int8 lengthSyllables[10];
    char *position = word;
    while (FindNextTransfer(position, &(lengthSyllables[num])))
    {
        position += lengthSyllables[num];
        num++;
    }
    lengthSyllables[num + 1] = 0;
    if (strcmp(word, "���������") == 0)
    {
        int8 lengths[] = {5, 2, 2, 0};
        memcpy(lengthSyllables, lengths, 4);
    }
    else if (strcmp(word, "���������������") == 0)
    {
        int8 lenghts[] = {4, 3, 4, 5, 3, 0};
        memcpy(lengthSyllables, lenghts, 6);
    }
    return lengthSyllables;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
// ���������� ����� ����� �� ����� numSyllable(�����������) ������ �� ������ ��������
static char *PartWordForTransfer(char *word, int8 *lengthSyllables, int numSyllable, char buffer[30])
{
    size_t length = 0;
    for (int i = 0; i <= numSyllable; i++)
    {
        length += (size_t)lengthSyllables[i];
    }
    memcpy((void *)buffer, (void *)word, length);
    buffer[length] = '-';
    buffer[length + 1] = '\0';
    return buffer;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
// ���� draw == false, �� �������� ������ �� ����, ������ ������������ ������ ��� ����������
static int DrawPartWord(char *word, int x, int y, int xRight, bool draw)
{
    int8 *lengthSyllables = BreakWord(word);
    int numSyllabels = 0;
    char buffer[30];
    for (int i = 0; i < 10; i++)
    {
        if (lengthSyllables[i] == 0)
        {
            numSyllabels = i;
            break;
        }
    }

    for (int i = numSyllabels - 2; i >= 0; i--)
    {
        char *subString = PartWordForTransfer(word, lengthSyllables, i, buffer);
        int length = Font::GetLengthText(subString);
        if (xRight - x > length - 5)
        {
            if (draw)
            {
                Painter::DrawText(x, y, subString);
            }
            return (int)strlen(subString) - 1;
        }
    }

    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Painter::DrawTextInRectWithTransfers(int eX, int eY, int eWidth, int eHeight, const char *text)
{
    int top = eY;
    int left = eX;
    int right = eX + eWidth;
    int bottom = eY + eHeight;

    char buffer[20];
    int numSymbols = (int)strlen(text);

    int y = top - 1;
    int x = left;

    int curSymbol = 0;

    while (y < bottom && curSymbol < numSymbols)
    {
        while (x < right - 1 && curSymbol < numSymbols)
        {
            int length = 0;
            char *word = GetWord(text + curSymbol, &length, buffer);

            if (length <= 1)                            // ��� ��������� �������� ��� ����, �.�. ����� �� �������
            {
                char symbol = text[curSymbol++];
                if (symbol == '\n')
                {
                    x = right;
                    continue;
                }
                if (symbol == ' ' && x == left)
                {
                    continue;
                }
                x = DrawChar(x, y, symbol);
            }
            else                                            // � ����� ������� �� ������� ���� ��� ��������� �������, �.�. ������� �����
            {
                int lengthString = Font::GetLengthText(word);
                if (x + lengthString > right + 5)
                {
                    int numSymb = DrawPartWord(word, x, y, right, true);
                    x = right;
                    curSymbol += numSymb;
                    continue;
                }
                else
                {
                    curSymbol += length;
                    x = DrawText(x, y, word);
                }
            }
        }
        x = left;
        y += 9;
    }

    return y;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Painter::DrawTextWithLimitationC(int x, int y, const char *text, Color color, int limitX, int limitY, int limitWidth, int limitHeight)
{
    SetColor(color);
    int retValue = x;
    while (*text)
    {
        x = DrawCharWithLimitation(x, y, *text, limitX, limitY, limitWidth, limitHeight);
        retValue += Font::GetLengthSymbol(*text);
        text++;
    }
    return retValue + 1;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Painter::DrawCharWithLimitation(int eX, int eY, char symbol, int limitX, int limitY, int limitWidth, int limitHeight)
{
    int8 width = (int8)font->symbol[symbol].width;
    int8 height = (int8)font->height;

    for (int b = 0; b < height; b++)
    {
        if (ByteFontNotEmpty(symbol, b))
        {
            int x = eX;
            int y = eY + b + 9 - height;
            int endBit = 8 - width;
            for (int bit = 7; bit >= endBit; bit--)
            {
                if (BitInFontIsExist(symbol, b, bit))
                {
                    if ((x >= limitX) && (x <= (limitX + limitWidth)) && (y >= limitY) && (y <= limitY + limitHeight))
                    {
                        Painter::SetPoint(x, y);
                    }
                }
                x++;
            }
        }
    }

    return eX + width + 1;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Painter::ByteFontNotEmpty(int eChar, int byte)
{
    static const uint8 *bytes = 0;
    static int prevChar = -1;
    if (eChar != prevChar)
    {
        prevChar = eChar;
        bytes = font->symbol[prevChar].bytes;
    }
    return bytes[byte];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Painter::BitInFontIsExist(int eChar, int numByte, int bit)
{
    static uint8 prevByte = 0;      /// \todo ����� ����� ������� �����?
    static int prevChar = -1;
    static int prevNumByte = -1;
    if (prevNumByte != numByte || prevChar != eChar)
    {
        prevByte = font->symbol[eChar].bytes[numByte];
        prevChar = eChar;
        prevNumByte = numByte;
    }
    return prevByte & (1 << bit);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawTextRelativelyRight(int xRight, int y, const char *text, Color color)
{
    int lenght = Font::GetLengthText(text);
    DrawText(xRight - lenght, y, text, color);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::Draw10SymbolsInRect(int x, int y, char eChar)
{
    for (char i = 0; i < 5; i++)
    {
        DrawChar(x + 8 * i, y, eChar + i);
        DrawChar(x + 8 * i, y + 8, eChar + i + 16);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Painter::DrawStringInCenterRect(int eX, int eY, int width, int eHeight, const char *text, Color color)
{
    SetColor(color);
    int lenght = Font::GetLengthText(text);
    int height = Font::GetHeightSymbol(text[0]);
    int x = eX + (width - lenght) / 2;
    int y = eY + (eHeight - height) / 2;
    return DrawText(x, y, text);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::ResetFlash()
{
    Timer::SetAndEnable(kFlashDisplay, OnTimerFlashDisplay, 400);
    inverseColors = false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::OnTimerFlashDisplay()
{
    inverseColors = !inverseColors;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawBigText(int eX, int eY, int size, const char *text, Color color)
{
    SetColor(color);

    uint numSymbols = strlen(text);

    int x = eX;

    for (uint i = 0; i < numSymbols; i++)
    {
        x = DrawBigChar(x, eY, size, text[i]);
        x += size;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Painter::DrawBigChar(int eX, int eY, int size, char symbol)
{
    int8 width = (int8)font->symbol[symbol].width;
    int8 height = (int8)font->height;

    for (int b = 0; b < height; b++)
    {
        if (ByteFontNotEmpty(symbol, b))
        {
            int x = eX;
            int y = eY + b * size + 9 - height;
            int endBit = 8 - width;
            for (int bit = 7; bit >= endBit; bit--)
            {
                if (BitInFontIsExist(symbol, b, bit))
                {
                    for (int i = 0; i < size; i++)
                    {
                        for (int j = 0; j < size; j++)
                        {
                            SetPoint(x + i, y + j);
                        }
                    }
                }
                x += size;
            }
        }
    }

    return eX + width * size;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Painter::DrawFormText(int x, int y, Color color, pString text, ...)
{
#define SIZE_BUFFER_DRAW_FORM_TEXT 200
    char buffer[SIZE_BUFFER_DRAW_FORM_TEXT];
    va_list args;
    va_start(args, text);
    vsprintf(buffer, text, args);
    va_end(args);
    return DrawText(x, y, buffer, color);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawTextInRect(int x, int y, int width, const char *text)
{
    int xStart = x;
    int xEnd = xStart + width;

    while (*text != 0)
    {
        int length = GetLenghtSubString(text);
        if (length + x > xEnd)
        {
            x = xStart;
            y += Font::GetHeightSymbol(*text);
        }
        int numSymbols = 0;
        numSymbols = DrawSubString(x, y, text);
        text += numSymbols;
        x += length;
        x = DrawSpaces(x, y, text, &numSymbols);
        text += numSymbols;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Painter::GetLenghtSubString(const char *text)
{
    int retValue = 0;
    while (((*text) != ' ') && ((*text) != '\0'))
    {
        retValue += Font::GetLengthSymbol(*text);
        text++;
    }
    return retValue;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Painter::DrawSubString(int x, int y, const char *text)
{
    int numSymbols = 0;
    while (((*text) != ' ') && ((*text) != '\0'))
    {
        x = DrawChar(x, y, *text);
#ifndef OPEN
        ++x;
#endif
        numSymbols++;
        text++;
    }
    return numSymbols;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Painter::DrawSpaces(int x, int y, const char *text, int *numSymbols)
{
    *numSymbols = 0;
    while (*text == ' ')
    {
        x = DrawChar(x, y, *text);
        text++;
        (*numSymbols)++;
    }
    return x;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Painter::DrawStringInCenterRectAndBoundItC(int x, int y, int width, int height, const char *text, Color colorBackground, Color colorFill)
{
    DrawRectangle(x, y, width, height, colorFill);
    FillRegion(x + 1, y + 1, width - 2, height - 2, colorBackground);
    SetColor(colorFill);
    return DrawStringInCenterRect(x, y, width, height, text);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
// ���������� ������ ������, ������� ����� ����� text, ��� ������ �� left �� right � ���������� height. ���� bool == false, �� ����� �� ������ �� ����� 
static bool GetHeightTextWithTransfers(int left, int top, int right, const char *text, int *height)
{
    char buffer[20];
    int numSymbols = (int)strlen(text);

    int y = top - 1;
    int x = left;

    int curSymbol = 0;

    while (y < 231 && curSymbol < numSymbols)
    {
        while (x < right - 1 && curSymbol < numSymbols)
        {
            int length = 0;
            char *word = GetWord(text + curSymbol, &length, buffer);

            if (length <= 1)                            // ��� ��������� �������� ��� ����, �.�. ����� �� �������
            {
                char symbol = text[curSymbol++];
                if (symbol == '\n')
                {
                    x = right;
                    continue;
                }
                if (symbol == ' ' && x == left)
                {
                    continue;
                }
                x += Font::GetLengthSymbol(symbol);
            }
            else                                            // � ����� ������� �� ������� ���� ��� ��������� �������, �.�. ������� �����
            {
                int lengthString = Font::GetLengthText(word);
                if (x + lengthString > right + 5)
                {
                    int numSymb = DrawPartWord(word, x, y, right, false);
                    x = right;
                    curSymbol += numSymb;
                    continue;
                }
                else
                {
                    curSymbol += length;
                    x += Font::GetLengthText(word);
                }
            }
        }
        x = left;
        y += 9;
    }

    *height = y - top + 4;
    LIMITATION(*height, 0, 239);

    return curSymbol == numSymbols;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Painter::DrawTextInBoundedRectWithTransfers(int x, int y, int width, const char *text, Color colorBackground, Color colorFill)
{
    int height = 0;
    GetHeightTextWithTransfers(x + 3, y + 3, x + width - 8, text, &height);

    DrawRectangle(x, y, width, height, colorFill);
    FillRegion(x + 1, y + 1, width - 2, height - 2, colorBackground);
    DrawTextInRectWithTransfersC(x + 3, y + 3, width - 8, height, text, colorFill);
    return y + height;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawVolumeButton(int x, int y, int width, int height, int thickness, Color normal, Color bright, Color dark, bool isPressed, bool isShade)
{
    FillRegion(x + thickness, y + thickness, width - thickness * 2, height - thickness * 2, normal);
    if (isPressed && !isShade)
    {
        for (int i = 0; i < thickness; i++)
        {
            DrawHLine(y + i, x + i, x + width - i, dark);
            DrawVLine(x + i, y + 1 + i, y + height - i);
            DrawVLine(x + width - i, y + 1 + i, y + height - i, bright);
            DrawHLine(y + height - i, x + 1 + i, x + width - i);
        }
    }
    else
    {
        for (int i = 0; i < thickness; i++)
        {
            DrawHLine(y + i, x + i, x + width - i, bright);
            DrawVLine(x + i, y + 1 + i, y + height - i);
            DrawVLine(x + width - i, y + 1 + i, y + height - i, dark);
            DrawHLine(y + height - i, x + 1 + i, x + width - i);
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::Draw4SymbolsInRect(int x, int y, char eChar, Color color /* = Color::NUMBER */)
{
    SetColor(color);
    for (char i = 0; i < 2; i++)
    {
        DrawChar(x + 8 * i, y, eChar + i);
        DrawChar(x + 8 * i, y + 8, eChar + i + 16);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawStringInCenterRectOnBackgroundC(int x, int y, int width, int height, const char *text, Color colorText, int widthBorder, Color colorBackground)
{
    int lenght = Font::GetLengthText(text);
    int eX = DrawStringInCenterRect(x, y, width, height, text, colorBackground);
    int w = lenght + widthBorder * 2 - 2;
    int h = 7 + widthBorder * 2 - 1;
    FillRegion(eX - lenght - widthBorder, y - widthBorder + 1, w, h);
    DrawStringInCenterRect(x, y, width, height, text, colorText);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Painter::DrawTextOnBackground(int x, int y, const char *text, Color colorBackground)
{
    int width = Font::GetLengthText(text);
    int height = Font::GetSize();

    Color colorText(GetColor());
    FillRegion(x - 1, y, width, height, colorBackground);
    SetColor(colorText);

    return DrawText(x, y, text);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Color Painter::GetColor()
{
    return currentColor;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::SetBrightnessDisplay(int16 brightness)
{
    float recValue = 1601.0f;
    if (brightness < 100)
    {
        recValue = 64.0f + (600.0f - 63.0f) / 100.0f / 100.0f * brightness * brightness;
    }
    /*
    uint8 command[4] = {SET_BRIGHTNESS};
    WRITE_SHORT(1, recValue);

    SendToDisplay(command, 4);
    */
}

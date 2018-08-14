#pragma once
#include "defines.h"
#include "Display/Colors.h"
#include "Display/DisplayTypes.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/** @addtogroup Display
 *  @{
 *  @defgroup Painter
 *  @brief ������� ���������
 *  @{
 */

class Painter
{
public:
    /// ���������� � ������ ��������� ������� �����. ��������� ����� ������ color
    static void BeginScene(Color color);
    /// ���������� � ����� ��������� ������� �����. ��������� ���������� ������ �� �����
    static void EndScene();
    static void SetColor(Color color);
    /// ���������� ������� ���� ���������
    static Color GetColor();
    /// ������������� ����� �������� ��������. ����������� � ������� LoadPalette() ��� SetPalette()
    static void SetColorValue(Color color, uint value);
    /// ��������� � ������� ��� �����
    static void LoadPalette();
    /// ���������� ���� ���������
    /// ���������� ����� ������� ������
    static void SetPoint(int x, int y);
    /// ���������� �������������� ����� �� x0 �� x1 ������� ����� ������ delta ��������
    static void DrawHPointLine(int y, int x0, int x1, float delta);
    /// ���������� ������������ ����� �� y0 �� y1 ������� ����� ������ delta ��������
    static void DrawVPointLine(int x, int y0, int y1, float delta);
    /// ���������� �������������� �����
    static void DrawHLine(int y, int x0, int x1, Color color = Color::NUMBER);
    /// ���������� ������������ �����
    static void DrawVLine(int x, int y0, int y1, Color color = Color::NUMBER);
    /// ���������� ������������ �����
    static void DrawLine(int x0, int y0, int x1, int y1, Color color = Color::NUMBER);
    /// \brief ������ ����������� �������������� �����. dFill - ����� ������, dEmpty - �����. ����� ��������. ����� ������ ���������� �� ������. 
    /// dStart ��������� �������� ������ �������� ����� ������������ ������ ������.
    static void DrawDashedHLine(int y, int x0, int x1, int dFill, int dEmpty, int dStart);
    /// ������ ����������� ������������ �����.
    static void DrawDashedVLine(int x, int y0, int y1, int dFill, int dEmpty, int dStart);

    static void DrawRectangle(int x, int y, int width, int height, Color color = Color::NUMBER);

    static void FillRegion(int x, int y, int width, int height, Color color = Color::NUMBER);

    static void DrawVolumeButton(int x, int y, int width, int height, int thickness, Color normal, Color bright, Color dark, bool isPressed, bool isShade);

    static uint ReduceBrightness(uint colorValue, float newBrightness);

    static void SetFont(TypeFont typeFont);

    static int DrawChar(int x, int y, char symbol, Color color = Color::NUMBER);

    static int DrawText(int x, int y, const char *text, Color color = Color::NUMBER);
    /// ������� ����� �� �������������� ����� colorBackgound
    static int DrawTextOnBackground(int x, int y, const char *text, Color colorBackground);

    static int DrawFormatText(int x, int y, char *format, ...);
    /// ����� ������ � ������� x, y
    static int DrawFormText(int x, int y, Color color, pString text, ...);

    static int DrawStringInCenterRect(int x, int y, int width, int height, const char *text, Color color = Color::NUMBER);

    static void DrawTextRelativelyRight(int xRight, int y, const char *text, Color color = Color::NUMBER);

    static void Draw2SymbolsC(int x, int y, char symbol1, char symbol2, Color color1, Color color2);

    static void Draw4SymbolsInRect(int x, int y, char eChar, Color color = Color::NUMBER);

    static void Draw10SymbolsInRect(int x, int y, char eChar);
    /// ����� ����� � ����������
    static int DrawTextInRectWithTransfers(int x, int y, int width, int height, const char *text);

    static void DrawBigText(int x, int y, int size, const char *text, Color color = Color::NUMBER);
    
    static int DrawBigChar(int eX, int eY, int size, char symbol);

private:

    static void CalculateCurrentColor();

    static int GetLenghtSubString(const char *text);

    static int DrawSubString(int x, int y, const char *text);

    static int DrawSpaces(int x, int y, const char *text, int *numSymbols);

    static void CalculateColor(uint8 *color);

    static void OnTimerFlashDisplay();

    static Color currentColor;

    static TypeFont currentTypeFont;

    static void DrawCharHardCol(int x, int y, char symbol);

    static bool ByteFontNotEmpty(int eChar, int byte);

    static void DrawCharInColorDisplay(int eX, int eY, char symbol);

    static int DrawCharWithLimitation(int eX, int eY, char symbol, int limitX, int limitY, int limitWidth, int limitHeight);

    static bool BitInFontIsExist(int eChar, int numByte, int bit);
};


#define WRITE_BYTE(offset, value)   *(command + offset) = (uint8)value
#define WRITE_SHORT(offset, value)  *((uint16 *)(command + offset)) = (uint16)value

/** @} @}
 */

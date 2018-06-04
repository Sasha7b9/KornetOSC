#pragma once
#include "defines.h"
#include "Colors.h"
#include "DisplayTypes.h"
#include "Settings/SettingsTypes.h"
#include "TypeSymbols.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Painter
{
public:
    static void BeginScene(Color color);

    static void EndScene();
    /// Елси не передавать значение цвета, то цвет останется прежним
    static void SetColor(Color color = Color::NUMBER);

    static void FillRegion(int x, int y, int width, int height, Color color = Color::NUMBER);

    static int DrawText(int x, int y, const char *text, Color color = Color::NUMBER);

    static void SetColorValue(Color color, uint value);

    static void DrawRectangle(int x, int y, int width, int height, Color color = Color::NUMBER);

    static void DrawFormatText(int x, int y, Color color, char *format, ...);

    static void DrawChar(int x, int y, char symbol, Color color = Color::NUMBER);

    static void DrawHLine(int y, int x0, int x1, Color color = Color::NUMBER);

    static void DrawHLine(float y, int x0, int x1, Color color = Color::NUMBER);

    static void DrawVLine(int x, int y0, int y1, Color color = Color::NUMBER);

    static void DrawVLine(int x, float y0, float y1, Color color = Color::NUMBER);

    static void DrawLine(int x0, int y0, int x1, int y1, Color color = Color::NUMBER);

    static void SetFont(TypeFont typeFont);

    static void SetPoint(int x, int y, Color color = Color::NUMBER);

    static void DrawBoundedRegion(int x, int y, int width, int height, Color colorFill, Color colorBound);

    static void DrawVolumeButton(int x, int y, int width, int height, int thickness, Color normal, Color bright, Color dark, bool isPressed, bool isShade);

    static void Draw4SymbolsInRect(int x, int y, char eChar, Color color = Color::NUMBER);

    static int DrawStringInCenterRect(int x, int y, int width, int height, const char *text, Color color = Color::NUMBER);

private:
};

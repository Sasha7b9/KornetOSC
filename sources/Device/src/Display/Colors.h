#pragma once
#include "defines.h"
#include "Settings/SettingsTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Color
{
public:
    static Color BLACK;             // Чёрный
    static Color WHITE;             // Белый
    static Color GRAY_10;
    static Color GRAY_25;           // Серый 25%
    static Color GRAY_50;           // Серый 50%
    static Color GRAY_75;           // Серый 75%
    static Color BLUE;
    static Color BLUE_10;
    static Color BLUE_25;
    static Color BLUE_50;
    static Color BLUE_75;
    static Color GREEN;
    static Color GREEN_5;
    static Color GREEN_10;
    static Color GREEN_25;
    static Color GREEN_50;
    static Color GREEN_75;
    static Color RED;
    static Color RED_25;
    static Color RED_50;
    static Color RED_75;
    static Color CHAN_A_HALF;
    static Color CHAN_B_HALF;
    static Color CHAN_A;
    static Color CHAN_B;
    static Color GRID;
    
    static Color NUMBER;

    static Color FLASH_10;
    static Color FLASH_01;

    static Color MENU_ITEM;
    static Color MENU_TITLE;
    static Color MENU_ITEM_DARK;


    static Color FILL;
    static Color BACK;
    
    explicit Color(const uint8 val);
    Color(const Color &color);

    static Color MenuItem(bool shade);      ///< Цвет элемента меню.
    static Color MenuTitle(bool shade);     ///< Цвет заголовка страницы. inShade == true, если страница затенена
    static Color BorderMenu(bool shade);    ///< Цвет окантовки меню
    static Color LightShadingText();        ///< Светлый цвет в тени.
    static Color ChanHalf(Channel ch);
    static Color Chan(Channel ch);
    
    uint8 value;

    static void InitGlobalColors();

    Color& operator=(const Color &color);

private:

    enum
    {
/* 0  */    COLOR_BLACK,
/* 1  */    COLOR_WHITE,
/* 2  */    COLOR_GRAY_10,
/* 3  */    COLOR_GRAY_25,
/* 4  */    COLOR_GRAY_50,
/* 5  */    COLOR_GRAY_75,
/* 6  */    COLOR_BLUE,
/* 7  */    COLOR_BLUE_10,
/* 8  */    COLOR_BLUE_25,
/* 9  */    COLOR_BLUE_50,
/* 10 */    COLOR_BLUE_75,
/* 11 */    COLOR_GREEN,
/* 12 */    COLOR_GREEN_5,
/* 13 */    COLOR_GREEN_10,
/* 14 */    COLOR_GREEN_25,
/* 15 */    COLOR_GREEN_50,
/* 16 */    COLOR_GREEN_75,
/* 17 */    COLOR_RED,
/* 18 */    COLOR_RED_25,
/* 19 */    COLOR_RED_50,
/* 20 */    COLOR_RED_75,
/* 21 */    COLOR_CHAN_A_HALF,
/* 22 */    COLOR_CHAN_B_HALF,
/* 23 */    COLOR_CHAN_A,
/* 24 */    COLOR_CHAN_B,
/* 25 */    COLOR_GRID,

        COLOR_NUMBER,

        COLOR_FLASH_10,
        COLOR_FLASH_01,
        COLOR_MENU_ITEM,
        COLOR_MENU_TITLE,
        COLOR_MENU_ITEM_DARK,
        COLOR_INVERSE
    };
};

bool operator!=(const Color &left, const Color &right);
bool operator==(const Color &left, const Color &right);
bool operator>(const Color &left, const Color &right);

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4623)
#endif

class ColorType
{
public:
    float   red;
    float   green;
    float   blue;
    float   stepRed;
    float   stepGreen;
    float   stepBlue;
    float   brightness;
    Color   color;
    int8    currentField;
    bool    alreadyUsed;
    bool    notUsed;

    /// Если forced == false, то инициализация происходит только при первом вызове функции
    void Init(bool forced);
    void SetBrightness(float brightness = -1.0f);
    void BrightnessChange(int delta);
    void ComponentChange(int delta);
private:
    void CalcSteps();
    void SetColor();
};

#define DEF_COLOR_TYPE(name, r, g, b, sR, sG, sB, bright, col) ColorType name = {r, g, b, sR, sG, sB, bright, col, 0, false, false};
#define COLOR_TYPE(r, g, b, sR, sG, sB, bright, col) {r, g, b, sR, sG, sB, bright, col, 0, false, false};

#ifdef _WIN32
#pragma warning(pop)
#endif

#define MAKE_COLOR(r, g, b) ((col_val)(b + (g << 8) + (r << 16)))
#define R_FROM_COLOR(color) (((col_val)(color) >> 16) & 0xff)
#define G_FROM_COLOR(color) (((col_val)(color) >> 8)  & 0xff)
#define B_FROM_COLOR(color) (((col_val)(color))       & 0xff)

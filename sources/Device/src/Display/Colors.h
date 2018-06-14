#pragma once
#include "defines.h"
#include "Settings/SettingsTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Color
{
public:
    static Color BLACK;
    static Color WHITE;
    static Color GRID;
    static Color DATA_A;
    static Color DATA_B;
    static Color MENU_FIELD;
    static Color MENU_TITLE;
    static Color MENU_TITLE_DARK;
    static Color MENU_TITLE_BRIGHT;
    static Color MENU_ITEM;
    static Color MENU_ITEM_DARK;
    static Color MENU_ITEM_BRIGHT;
    static Color DATA_WHITE_ACCUM_A;
    static Color DATA_WHITE_ACCUM_B;
    static Color RED;
    static Color GREEN;
    static Color BLUE;

    static Color NUMBER;

    static Color FILL;
    static Color BACK;
    static Color FLASH_10;
    static Color FLASH_01;

    explicit Color(uint8 val) : value(val) { }
    Color(const Color &color) : value(color.value) { }

    static Color Chan(Channel ch);
    static Color Cursors(Channel ch);
    static Color Trig();
    static Color ChanAccum(Channel ch);     ///< Цвет канала в режиме накопления
    static Color MenuItem(bool shade);      ///< Цвет элемента меню.
    static Color MenuTitle(bool shade);     ///< Цвет заголовка страницы. inShade == true, если страница затенена
    static Color BorderMenu(bool shade);    ///< Цвет окантовки меню
    static Color LightShadingText();        ///< Светлый цвет в тени.
    static Color Contrast(Color color);     ///< Возвращает цвет, контрастный к color. Может быть белым или чёрным.
    static Color ChanHalf(Channel ch);
    
    uint8 value;

    static void InitGlobalColors();
    static void Log(Color color);

    Color& operator=(const Color &color);

private:

    static Color CHAN[4];
    
    enum
    {
        COLOR_BLACK = 0,
        COLOR_WHITE = 1,
        COLOR_GRID = 2,
        COLOR_DATA_A = 3,
        COLOR_DATA_B = 4,
        COLOR_MENU_FIELD = 5,
        COLOR_MENU_TITLE = 6,
        COLOR_MENU_TITLE_DARK = 7,
        COLOR_MENU_TITLE_BRIGHT = 8,
        COLOR_MENU_ITEM = 9,
        COLOR_MENU_ITEM_DARK = 10,
        COLOR_MENU_ITEM_BRIGHT = 11,
        COLOR_DATA_WHITE_ACCUM_A = 12,   ///< Используется как для отрисовки канала на белом фоне, так и для отрисовки накопленных сигналов
        COLOR_DATA_WHITE_ACCUM_B = 13,
        COLOR_RED = 14,
        COLOR_GREEN = 15,
        COLOR_BLUE = 16,

        COLOR_NUMBER = 32,

        COLOR_FLASH_10 = 33,
        COLOR_FLASH_01 = 34,
        COLOR_INVERSE = 35
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

#define MAKE_COLOR(r, g, b) ((uint)(b + (g << 8) + (r << 16)))
#define R_FROM_COLOR(color) (((uint)(color) >> 16) & 0xff)
#define G_FROM_COLOR(color) (((uint)(color) >> 8)  & 0xff)
#define B_FROM_COLOR(color) (((uint)(color))       & 0xff)

#define COLOR(x) GlobalColors[x]

extern uint GlobalColors[256];

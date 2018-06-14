#include "defines.h"
#include "Log.h"
#include "Display/Colors.h"
#include "Display/Painter.h"
#include "Utils/Math.h"
#include "Settings/Settings.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint colors[256] =
{
    MAKE_COLOR(0x00, 0x00, 0x00),   //COLOR_BLACK = 0,
    MAKE_COLOR(0xff, 0xff, 0xff),   //COLOR_WHITE = 1,
    MAKE_COLOR(0xff, 0xff, 0xff),   //COLOR_GRID = 2,
    MAKE_COLOR(0xff, 0xff, 0xff),   //COLOR_DATA_A = 3,
    MAKE_COLOR(0xff, 0xff, 0xff),   //COLOR_DATA_B = 4,
    MAKE_COLOR(0xff, 0xff, 0xff),   //COLOR_MENU_FIELD = 5,
    MAKE_COLOR(0xff, 0xff, 0xff),   //COLOR_MENU_TITLE = 6,
    MAKE_COLOR(0xff, 0xff, 0xff),   //COLOR_MENU_TITLE_DARK = 7,
    MAKE_COLOR(0xff, 0xff, 0xff),   //COLOR_MENU_TITLE_BRIGHT = 8,
    MAKE_COLOR(0xff, 0xff, 0xff),   //COLOR_MENU_ITEM = 9,
    MAKE_COLOR(0xff, 0xff, 0xff),   //COLOR_MENU_ITEM_DARK = 10,
    MAKE_COLOR(0xff, 0xff, 0xff),   //COLOR_MENU_ITEM_BRIGHT = 11,
    MAKE_COLOR(0xff, 0xff, 0xff),   //COLOR_DATA_WHITE_ACCUM_A = 12,
    MAKE_COLOR(0xff, 0xff, 0xff),   //COLOR_DATA_WHITE_ACCUM_B = 13,
    MAKE_COLOR(0xff, 0xff, 0xff),   //COLOR_GRID_WHITE = 14,
    MAKE_COLOR(0xff, 0xff, 0xff),   //COLOR_EMPTY = 15,
    MAKE_COLOR(0xff, 0xff, 0xff),   //COLOR_FLASH_10 = 16,
    MAKE_COLOR(0xff, 0xff, 0xff),   //COLOR_FLASH_01 = 17,
    MAKE_COLOR(0xff, 0xff, 0xff),   //COLOR_INVERSE = 18,
    MAKE_COLOR(0x00, 25,   0x00),   //COLOR_GREEN_10 = 19,
    MAKE_COLOR(0x00, 0x00, 25),     //COLOR_BLUE_10 = 20,
    MAKE_COLOR(25,   0x00, 0x00),   //COLOR_RED_10 = 21,
    MAKE_COLOR(0x00, 64,   0x00),   //COLOR_GREEN_25 = 22,
    MAKE_COLOR(0x00, 0x00, 64),     //COLOR_BLUE_25 = 23,
    MAKE_COLOR(64,   0x00, 0x00),   //COLOR_RED_25 = 24,
    MAKE_COLOR(0x80, 0x80, 0x80),   //COLOR_GRAY = 25,
    MAKE_COLOR(0x40, 0x40, 0x40),   //COLOR_GRAY_25 = 26,
    MAKE_COLOR(25,   25,   25),     //COLOR_GRAY_10 = 27,
    MAKE_COLOR(51,   51,   51),     //COLOR_GRAY_20 = 28,
    MAKE_COLOR(0x80, 0x00, 0x00),   //COLOR_RED_50 = 29,
    MAKE_COLOR(0x00, 0x00, 0x80),   //COLOR_BLUE_50 = 30,
    MAKE_COLOR(0x00, 0x80, 0x00)    //COLOR_GREEN_50 = 31,
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Color Color::BLACK(COLOR_BLACK);
Color Color::WHITE(COLOR_WHITE);
Color Color::MENU_FIELD(COLOR_MENU_FIELD);
Color Color::MENU_TITLE_DARK(COLOR_MENU_TITLE_DARK);
Color Color::MENU_TITLE_BRIGHT(COLOR_MENU_ITEM_BRIGHT);
Color Color::MENU_ITEM_DARK(COLOR_MENU_ITEM_DARK);
Color Color::MENU_ITEM_BRIGHT(COLOR_MENU_ITEM_BRIGHT);
Color Color::DATA_WHITE_ACCUM_A(COLOR_DATA_WHITE_ACCUM_A);
Color Color::DATA_WHITE_ACCUM_B(COLOR_DATA_WHITE_ACCUM_B);
Color Color::NUMBER(COLOR_NUMBER);
Color Color::FLASH_10(COLOR_FLASH_10);
Color Color::FLASH_01(COLOR_FLASH_01);
Color Color::BLUE_10(COLOR_BLUE_10);
Color Color::GREEN_10(COLOR_GREEN_10);
Color Color::RED_10(COLOR_RED_10);
Color Color::BLUE_25(COLOR_BLUE_25);
Color Color::GREEN_25(COLOR_GREEN_25);
Color Color::RED_25(COLOR_RED_25);
Color Color::GRAY(COLOR_GRAY);
Color Color::GRAY_25(COLOR_GRAY_25);
Color Color::GRAY_10(COLOR_GRAY_10);
Color Color::GRAY_20(COLOR_GRAY_20);
Color Color::RED_50(COLOR_RED_50);
Color Color::BLUE_50(COLOR_BLUE_50);
Color Color::GREEN_50(COLOR_GREEN_50);

Color Color::CHAN[4] = {Color(COLOR_DATA_A), Color(COLOR_DATA_B), Color(COLOR_WHITE), Color(COLOR_WHITE)};
Color Color::FILL(COLOR_WHITE);
Color Color::BACK(COLOR_BLACK);
Color Color::GRID(COLOR_GRID);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Color::Log(Color color)
{
#define colorVal (COLOR(color.value))

    LOG_WRITE("Color %d R=%d, G=%d, B=%d", color.value, R_FROM_COLOR(colorVal), G_FROM_COLOR(colorVal), B_FROM_COLOR(colorVal));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Color Color::Cursors(Channel ch)
{
    return CHAN[ch];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Color Color::BorderMenu(bool shade)
{
    return MenuTitle(shade);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Color Color::MenuTitle(bool shade)
{
    return shade ? Color(COLOR_MENU_ITEM) : Color(COLOR_MENU_TITLE);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Color Color::LightShadingText()
{
    return MenuTitle(false);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Color Color::MenuItem(bool shade)
{
    return shade ? Color(COLOR_MENU_ITEM_DARK) : Color(COLOR_MENU_ITEM);
}

Color Color::Contrast(Color color)
{
    uint colorValue = COLOR(color.value);
    if (R_FROM_COLOR(colorValue) > 16 || G_FROM_COLOR(colorValue) > 32 || B_FROM_COLOR(colorValue) > 16)
    {
        return Color(COLOR_BLACK);
    }
    return Color(COLOR_WHITE);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool operator!=(const Color &left, const Color &right)
{
    return left.value != right.value;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool operator==(const Color &left, const Color &right)
{
    return left.value == right.value;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool operator>(const Color &left, const Color &right)
{
    return left.value > right.value;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ColorType::Init(bool forced)
{
    if (forced)
    {
        alreadyUsed = false;
    }

    if (!alreadyUsed)
    {
        alreadyUsed = true;                  // ѕризнак того, что начальные установки уже произведены

        uint colorValue = COLOR(color.value);

        red = (float)R_FROM_COLOR(colorValue);
        green = (float)G_FROM_COLOR(colorValue);
        blue = (float)B_FROM_COLOR(colorValue);

        SetBrightness();
        
        if (red == 0.0f && green == 0.0f && blue == 0.0f)
        {
            stepRed = 0.31f;
            stepGreen = 0.63f;
            stepBlue = 0.31f;
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ColorType::SetBrightness(float bright)
{
    if (IsEquals(bright, -1.0f))
    {
        brightness = MaxFloat(red / 31.0f, green / 63.0f, blue / 31.0f);

        CalcSteps();
    }
    else
    {
        int delta = (int)((bright + 0.0005f) * 100.0f) - (int)(brightness * 100.0f);

        if (delta > 0)
        {
            for (int i = 0; i < delta; i++)
            {
                BrightnessChange(1);
            }
        }
        else
        {
            for (int i = 0; i < -delta; i++)
            {
                BrightnessChange(-1);
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
јлгоритм изменени€ €ркости.
1. »нициализаци€.
а. –ассчитать €ркость по принципу - €ркость равна относительной интенсивности самого €ркого цветового канала
б. –ассчитать шаг изменени€ цветовой составл€ющей каждого канала на 1% €ркости по формуле:
Ўаг = »нтенсивность канала * яркость, где яркость - относительна€ величина общей €ркости
в. ≈сли интенсивность всех каналов == 0, то дать полный шаг каждому каналу
2. ѕри изменнении €ркости на 1% мен€ть интенсивность каждого канала на Ўаг, расчитанный в предыдущем пункте.
3. ѕри изменени€ интенсивности цветового канала пересчитывать €ркость и шаг изменени€ каждого канала.
*/

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ColorType::BrightnessChange(int delta)
{
    if ((delta > 0 && brightness == 1.0f) || (delta < 0 && brightness == 0.0f))
    {
        return;
    }

    int sign = Sign(delta);

    brightness += sign * 0.01f;
    LIMITATION(brightness, 0.0f, 1.0f);

    red += sign * stepRed;
    green += sign * stepGreen;
    blue += sign * stepBlue;

    SetColor();

    if (stepRed < 0.01f && stepGreen < 0.01f && stepBlue < 0.01f)
    {
        stepRed = 0.31f;
        stepGreen = 0.63f;
        stepBlue = 0.31f;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ColorType::CalcSteps()
{
    stepRed = red / (brightness * 100.0f);
    stepGreen = green / (brightness * 100.0f);
    stepBlue = blue / (brightness * 100.0f);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ColorType::SetColor()
{
    COLOR(color.value) = MAKE_COLOR((int)red, (int)green, (int)blue);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ColorType::ComponentChange(int delta)
{
    static const float maxs[4] = {0.0f, 31.0f, 63.0f, 31.0f};
    float * const pointers[4] = {0, &blue, &green, &red};
    int8 index = currentField;

    if (index >= 1 && index <= 3)
    {
        *(pointers[index]) += (float)Sign(delta);
        Limitation<float>(pointers[index], 0.0f, maxs[index]);
    }

    SetColor();

    SetBrightness();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Color& Color::operator=(const Color &color)
{
    value = color.value;
    return *this;
}

#ifdef OSCI

//----------------------------------------------------------------------------------------------------------------------------------------------------
Color Color::Trig()
{
    if (TRIGSOURCE_IS_EXT)
    {
        return FILL;
    }
    return CHAN[(Channel)TRIGSOURCE];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Color Color::ChanAccum(Channel ch)
{
    return (ch == A) ? Color(COLOR_DATA_WHITE_ACCUM_A) : Color(COLOR_DATA_WHITE_ACCUM_B);
}

#endif

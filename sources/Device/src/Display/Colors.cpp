#include "defines.h"
#include "Colors.h"
#include "Log.h"
#include "Display/Colors.h"
#include "Display/Painter.h"
#include "Settings/Settings.h"
#include "Utils/Math.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Color Color::BLACK(COLOR_BLACK);
Color Color::WHITE(COLOR_WHITE);
Color Color::GRAY_10(COLOR_GRAY_10);
Color Color::GRAY_25(COLOR_GRAY_25);
Color Color::GRAY_50(COLOR_GRAY_50);
Color Color::GRAY_75(COLOR_GRAY_75);
Color Color::BLUE(COLOR_BLUE);
Color Color::BLUE_10(COLOR_BLUE_10);
Color Color::BLUE_25(COLOR_BLUE_25);
Color Color::BLUE_50(COLOR_BLUE_50);
Color Color::BLUE_75(COLOR_BLUE_75);
Color Color::GREEN(COLOR_GREEN);
Color Color::GREEN_5(COLOR_GREEN_5);
Color Color::GREEN_10(COLOR_GREEN_10);
Color Color::GREEN_25(COLOR_GREEN_25);
Color Color::GREEN_50(COLOR_GREEN_50);
Color Color::GREEN_75(COLOR_GREEN_75);
Color Color::RED(COLOR_RED);
Color Color::RED_25(COLOR_RED_25);
Color Color::RED_50(COLOR_RED_50);
Color Color::RED_75(COLOR_RED_75);
Color Color::CHAN_A_HALF(COLOR_CHAN_A_HALF);
Color Color::CHAN_B_HALF(COLOR_CHAN_B_HALF);
Color Color::GRID(COLOR_GRID);
Color Color::CHAN_A(COLOR_CHAN_A);
Color Color::CHAN_B(COLOR_CHAN_B);

Color Color::NUMBER(COLOR_NUMBER);

Color Color::FLASH_10(COLOR_FLASH_10);
Color Color::FLASH_01(COLOR_FLASH_01);

Color Color::MENU_ITEM(COLOR_GRAY_50);
Color Color::MENU_TITLE(COLOR_GRAY_25);
Color Color::MENU_ITEM_DARK(COLOR_GRAY_75);

Color Color::FILL(COLOR_WHITE);
Color Color::BACK(COLOR_BLACK);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Color::Color(const uint8 val) : value(val)
{
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Color::Color(const Color &color) : value(color.value)
{
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Color::InitGlobalColors()
{
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
Color Color::ChanHalf(Channel ch)
{
    return ch == A ? Color::CHAN_A_HALF : Color::CHAN_B_HALF;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Color Color::Chan(Channel ch)
{
    return ch == A ? Color::CHAN_A : Color::CHAN_B;
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
        alreadyUsed = true;                  // ������� ����, ��� ��������� ��������� ��� �����������

        col_val colorValue = COLOR(color.value);

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
�������� ��������� �������.
1. �������������.
�. ���������� ������� �� �������� - ������� ����� ������������� ������������� ������ ������ ��������� ������
�. ���������� ��� ��������� �������� ������������ ������� ������ �� 1% ������� �� �������:
��� = ������������� ������ * �������, ��� ������� - ������������� �������� ����� �������
�. ���� ������������� ���� ������� == 0, �� ���� ������ ��� ������� ������
2. ��� ���������� ������� �� 1% ������ ������������� ������� ������ �� ���, ����������� � ���������� ������.
3. ��� ��������� ������������� ��������� ������ ������������� ������� � ��� ��������� ������� ������.
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

#pragma once
#include "Display/Colors.h"
#include "Menu/MenuItems.h"


//----------------------------------------------------------------------------------------------------------------------------------------------------
class PageDisplay
{
public:

    static void Init();

    static void OnPress_Accumulation_Clear();

    static void OnChanged_RefreshFPS(bool);

    static void OnChanged_Settings_Colors_Background(bool);

    static ColorType colorTypeGrid;

    static ColorType colorTypeA;

    static ColorType colorTypeB;

    static const PageBase *pointer;
};

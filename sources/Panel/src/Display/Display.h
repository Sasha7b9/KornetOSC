#pragma once
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Display
{
public:
    static const int WIDTH = 320;
    static const int HEIGHT = 240;

    static void Init();

    static void Update();

    static uint8 *GetBuffer();

    static void ToggleBuffers();
};


extern LTDC_HandleTypeDef hltdc;

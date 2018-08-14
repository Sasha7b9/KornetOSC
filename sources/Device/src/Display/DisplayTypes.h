#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MI_HEIGHT               23
#define MI_WIDTH                (320 / 5)
#define MP_TITLE_HEIGHT         12
#define MP_TITLE_WIDTH          (MI_WIDTH * 2 - 2)
#define MOSI_HEIGHT             14
#define MI_HEIGHT_VALUE         13
#define MI_WIDTH_VALUE          ((MI_WIDTH) - 4)
#define MOI_HEIGHT_TITLE        19
#define MOI_WIDTH               MP_TITLE_WIDTH
#define MOI_WIDTH_D_IP          34      /* ”величение ширины открытого ip-адреса в случае наличи€ порта */
#define WIDTH_SB                19
#define LEFT_SB                 299
#define GRID_DELTA              20  /*  оличество точек в клетке */


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum TypeFont
{
    TypeFont_5,
    TypeFont_8,
    TypeFont_UGO,
    TypeFont_UGO2,
    TypeFont_Number,
    TypeFont_None
};

enum DrawMode
{
    DrawMode_Auto,
    DrawMode_Hand
};

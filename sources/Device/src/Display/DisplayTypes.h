#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MOSI_HEIGHT             9
#define MOI_HEIGHT_TITLE        19
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

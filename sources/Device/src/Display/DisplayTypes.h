#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MP_TITLE_WIDTH          (Menu::Item::Width() * 2 - 2)
#define MOSI_HEIGHT             14
#define MI_WIDTH_VALUE          ((Menu::Item::Width()) - 4)
#define MOI_HEIGHT_TITLE        19
#define MOI_WIDTH               MP_TITLE_WIDTH
#define MOI_WIDTH_D_IP          34      /* ���������� ������ ��������� ip-������ � ������ ������� ����� */
#define WIDTH_SB                19
#define LEFT_SB                 299
#define GRID_DELTA              20  /* ���������� ����� � ������ */


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

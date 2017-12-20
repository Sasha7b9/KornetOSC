#include "defines.h"
#include "font.h"

#include "font8.inc"
#include "font5.inc"
#include "fontUGO.inc"
#include "fontUGO2.inc"


const Font *fonts[TypeFont_Number] = {&font5, &font8, &fontUGO, &fontUGO2};
const Font *font = &font8;


int Font_GetSize(void)
{
    return font->height;
}

int Font_GetLengthText(const char *text)
{
    int retValue = 0;
    while (*text)
    {
        retValue += Font_GetLengthSymbol((uchar)*text);
        text++;
    }
    return retValue;
}

int Font_GetHeightSymbol(char)
{
    return 9;
}

int Font_GetLengthSymbol(uchar symbol)
{
    return font->symbol[symbol].width + 1;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Font_SetFont(TypeFont typeFont)
{
    switch (typeFont)
    {
        case TypeFont_5:
            font = &font5;
            break;
        case TypeFont_8:
            font = &font8;
            break;
        case TypeFont_UGO:
            font = &fontUGO;
            break;
        case TypeFont_UGO2:
            font = &fontUGO2;
            break;
        case TypeFont_None:
        case TypeFont_Number:
            break;
    }
}
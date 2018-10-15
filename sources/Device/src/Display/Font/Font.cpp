#include "defines.h"

#include "font8.inc"
#include "font5.inc"
#include "fontUGO.inc"
#include "fontUGO2.inc"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Font *fonts[Font::Type::Number] = {&font5, &font8, &fontUGO, &fontUGO2};
const Font *font = &font8;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Font::GetSize(void)
{
    return font->height;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Font::GetLengthText(const char *text)
{
    int retValue = 0;
    while (*text)
    {
        retValue += GetLengthSymbol((char)*text);
        text++;
    }
    return retValue;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Font::GetHeightSymbol(char)
{
    return 9;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Font::GetLengthSymbol(char symbol)
{
    return font->symbol[symbol].width + 1;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Font::SetFont(Font::Type::E typeFont)
{
    switch (typeFont)
    {
        case Type::_5:
            font = &font5;
            break;
        case Type::_8:
            font = &font8;
            break;
        case Type::_UGO:
            font = &fontUGO;
            break;
        case Type::_UGO2:
            font = &fontUGO2;
            break;
        case Type::None:
        case Type::Number:
            break;
    }
}

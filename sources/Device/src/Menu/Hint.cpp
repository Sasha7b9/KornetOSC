#include "Hint.h"
#include "Log.h"
#include "Display/DisplayTypes.h"
#include "Display/Painter.h"
#include "Display/Text.h"
#include "Settings/Settings.h"
#include "Menu/Menu.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool        Hint::show = false;
const Item *Hint::item = 0;
Control     Hint::control = B_None;
int         Hint::numPages = 0;
int         Hint::currentPage = 0;
int         Hint::firstItemOnSecondPage = 0;
bool        Hint::needCalculate = false;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Hint::ProcessControl(StructControl strCtrl)
{
    Control key = strCtrl.key;

    if (key == B_ESC && strCtrl.typePress == Long)
    {
        show = !show;
        item = 0;
        control = B_None;
        numPages = 0;
    }

    if (show)
    {
        if (key >= B_F1 && key <= B_F5)
        {
            item = Menu::CurrentPage()->GetItem(key - B_F1);
            control = B_None;
            needCalculate = true;
        }
        else if (key == REG_LEFT || key == REG_RIGHT)
        {
            if(numPages > 1)
            {
                if(key == REG_LEFT)
                {
                    if(currentPage > 1)
                    {
                        currentPage--;
                    }
                }
                else if(currentPage < numPages)
                {
                    currentPage++;
                }
            }
        }
        else
        {
            item = 0;
        }

        return true;
    }

    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Hint::Draw()
{
    if (show)
    {
        int x0 = 0;
        int y0 = MP_TITLE_HEIGHT;
        int width = 319 - MI_WIDTH;

        y0 = Text::DrawTextInBoundedRectWithTransfers(x0, y0, width,
            LANG_RU ?
            "������� ����� ���������.\n"
            "��� ��������� ���������� �� �������� ���� ��� ���������� ������ ����������� ��������������� ����� ����������.\n"
            "��� ������ �� ������ ��������� ������� � ����������� ������ ESC."
            :
            "Prompt mode is enabled.\n"
            "For information about the menu item or the purpose of the button, use the appropriate control.\n"
            "To exit the prompt mode, press and hold the ESC key."
            ,
            Color::BACK, Color::FILL, Color::GRAY_50);

        Painter::DrawFilledRectangle(x0, y0, width, 239 - y0 - 1, Color::BACK, Color::FILL);

        if (item)
        {
            int yUGO = y0 + 5;

            Painter::SetColor(Color::GREEN_50);
            Text::DrawFormatStringInCenterRect(x0, y0 + 4, width, 10, "*** %s ***", item->Title());
            Painter::SetColor(Color::GREEN);
            y0 = item->DrawHint(x0 + 5, y0 + 17, width - 8) + 5;
            if (item->Type() == Item_Choice)
            {
                Choice *choice = (Choice *)item;
                width -= 10;

                if(needCalculate)
                {
                    Calcualte(choice, x0, y0, width);
                    needCalculate = false;
                }

                DrawPagesUGO(width + 5, yUGO);

                if (numPages == 1)
                {
                    DrawDetailedHint(choice, x0, y0, width, 0, choice->NumSubItems() - 1);
                }
                else
                {
                    if(currentPage == 1)
                    {
                        DrawDetailedHint(choice, x0, y0, width, 0, firstItemOnSecondPage - 1);
                    }
                    else if(currentPage == 2)
                    {
                        DrawDetailedHint(choice, x0, y0, width, firstItemOnSecondPage, choice->NumSubItems() - 1);
                    }
                }
            }
            
        }
        else if (control != B_None)
        {

        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Hint::DrawDetailedHint(Choice *choice, int x0, int y0, int width, int start, int end, bool calculate)
{
    Color colorWhite = Color::WHITE;
    Color colorGreen = Color::GREEN;

    if(calculate)
    {
        colorWhite = colorGreen = Color::BACK;
    }

    Painter::SetColor(colorWhite);

    int number = start + 1;

    for (int i = start; i <= end; i++)
    {
        y0 = Text::DrawFormatTextInColumnWithTransfersDiffColors(x0 + 2, y0, width, colorGreen, "%d. \"%s\" %s", number++,
                                                                 choice->NameSubItem(i), LANG_RU ? choice->hintsRu[i] : choice->hintsEn[i]) + 5;

    }

    return y0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Hint::NumPagesInHint(Choice *choice, int x, int y, int width)
{
    if(DrawDetailedHint(choice, x, y, width, 0, choice->NumSubItems(), true) < SCREEN_HEIGHT)
    {
        return 1;
    }

    return 2;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Hint::Calcualte(Choice *choice, int x, int y, int width)
{
    numPages = NumPagesInHint(choice, x, y, width);
    currentPage = 1;
    firstItemOnSecondPage = 0;

    if(numPages == 2)
    {
        for(int i = 0; i < choice->NumSubItems(); i++)
        {
            if(DrawDetailedHint(choice, x, y, width, 0, i, true) > SCREEN_HEIGHT - 1)
            {
                firstItemOnSecondPage = i;
                break;
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Hint::DrawPagesUGO(const int xRight, const int y0)
{
    if(numPages < 2)
    {
        return;
    }

    int delta = 3;
    int size = 6;

    for(int i = 1; i <= numPages; i++)
    {
        int x = xRight - size - (i - 1) * (delta + size);

        if (numPages + 1 - i == currentPage)
        {
            Painter::FillRegion(x, y0, size, size, Color::FILL);
            Text::SetFont(TypeFont_5);
            Text::DrawChar(x + 2, y0 - 3, (char)(currentPage + 0x30), Color::BACK);
            Text::SetFont(TypeFont_8);
        }
        else
        {
            Painter::DrawRectangle(x, y0, size, size, Color::FILL);
        }
    }
}

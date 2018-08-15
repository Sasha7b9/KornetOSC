#include "Console.h"
#include "Display/Painter.h"

#include <string.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Console::inProcessDrawConsole = false; 
int Console::stringInConsole = 0;
#define SIZE_CONSOLE    20
static CHAR_BUF2(buffer, SIZE_CONSOLE, 100);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Console::Draw()
{
    inProcessDrawConsole = true;

    Painter::SetFont(TypeFont_5);

    int y = 0;

    for (int i = 0; i < stringInConsole; i++)
    {
        Painter::DrawText(1, y, buffer[i], Color::FILL);
        y += 6;
    }

    Painter::SetFont(TypeFont_8);

    inProcessDrawConsole = false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Console::AddString(char *string)
{
    /// \todo Мы пропускаем некоторые строки. Сделать отложенное добавление
    if (!inProcessDrawConsole)      // Страхуемся на предмет того, что сейчас не происходит вывод консоли в другом потоке
    {
        static int count = 0;
        if (stringInConsole == SIZE_CONSOLE)
        {
            for (int i = 1; i < SIZE_CONSOLE; i++)
            {
                strcpy(buffer[i - 1], buffer[i]);
            }
            stringInConsole--;
        }
        sprintf(buffer[stringInConsole], "%d %s", count++, string);
        stringInConsole++;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Console::NumberOfLines()
{
    return stringInConsole;
}

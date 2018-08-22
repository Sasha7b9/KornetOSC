#include "Decoder.h"
#include "Hardware/FSMC.h"
#include "Menu/Menu.h"
#include "Log.h"
#include "Utils/Debug.h"
#include "Hardware/Timer.h"
#include "Display/Console.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Decoder decoder;

#define SIZE_BUFFER 1024
static uint8 buffer[SIZE_BUFFER];
static int pointer = 0;

pFuncBU8 Decoder::curFunc = 0;
int      Decoder::step = 0;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Decoder::AddData(uint8 data)
{
    if (pointer < SIZE_BUFFER)
    {
        buffer[pointer++] = data;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Decoder::Update()
{
    if (pointer)
    {
        if(buffer[0] == 1)
        {
            buffer[0] = 1;
        }
        
        for (int i = 0; i < pointer; i++)
        {
            RunStep(buffer[i]);
        }

        pointer = 0;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Decoder::RunStep(uint8 data)
{
    static const pFuncBU8 commands[NUM_COMMANDS] =
    {
        &Decoder::EmptyFunc,
        &Decoder::ButtonPress,
        &Decoder::EmptyFunc,
        &Decoder::EmptyFunc,
        &Decoder::EmptyFunc,
        &Decoder::EmptyFunc,
        &Decoder::EmptyFunc,
        &Decoder::EmptyFunc,
        &Decoder::EmptyFunc,
        &Decoder::EmptyFunc,
        &Decoder::EmptyFunc,
        &Decoder::EmptyFunc,
        &Decoder::EmptyFunc,
        &Decoder::EmptyFunc
    };

    if (step == 0)
    {

        if (data < NUM_COMMANDS)
        {
            curFunc = commands[data];
        }
        else
        {
            FinishCommand();
            return;
        }
    }

    if (curFunc)
    {
        if (curFunc(data))
        {
            FinishCommand();
        }
        else
        {
            ++step;
        }
    }
    else
    {
        FinishCommand();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Decoder::ButtonPress(uint8 data)
{
    static Key button;
    if (step == 0)
    {
        return false;
    }
    else if (step == 1)
    {
        button = (Key)data;
        return false;
    }
    else
    {
        /*
        if (button.code != 14 && Console::NumberOfLines() < 10)
        {
            LOG_WRITE("code = %d  %d  %d %d %d %d %d %d %d %d %d %d", button.code, pointer,
                      buffer[0], buffer[1], buffer[2], buffer[3], buffer[4],
                      buffer[5], buffer[6], buffer[7], buffer[8], buffer[9]
            );
        }
        */
        Menu::ButtonEvent(KeyEvent(button, (TypePress::E)data));
    }

    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Decoder::FinishCommand()
{
    step = 0;
    curFunc = 0;
}

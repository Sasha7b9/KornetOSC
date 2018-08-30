#include "Multimeter.h"
#include "Display/Painter.h"
#include "Settings/Settings.h"
#include "Hardware/Hardware.h"
#include "Hardware/Timer.h"
#include <string.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char                Multimeter::buffer[11] = {0};
UART_HandleTypeDef  Multimeter::handlerUART;
/// В этот буфер записывается информация в обработчике прерывания приёма
static uint8 bufferUART[10];
/// В этом буфере готовая к выводу информация
#define SIZE_OUT 15
static char out[SIZE_OUT];

static uint numMeasures = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Multimeter::SetMeasure(uint8 buf[10])
{
    memcpy(buffer, buf, 10);
    buffer[2] |= 0x30;
    buffer[3] |= 0x30;
    buffer[4] |= 0x30;
    buffer[5] |= 0x30;
    buffer[6] |= 0x30;

    numMeasures++;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Multimeter::Clear()
{
    buffer[0] = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Multimeter::Init()
{
    handlerUART.Instance = USART3;
    handlerUART.Init.BaudRate = 9600;
    handlerUART.Init.WordLength = UART_WORDLENGTH_8B;
    handlerUART.Init.StopBits = UART_STOPBITS_1;
    handlerUART.Init.Parity = UART_PARITY_NONE;
    handlerUART.Init.Mode = UART_MODE_TX_RX;
    handlerUART.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    handlerUART.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&handlerUART) != HAL_OK)
    {
        ERROR_HANDLER();
    }

    uint8 send[4] = {0x02, 'V', '0', 0x0a};

    HAL_NVIC_SetPriority(USART3_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(USART3_IRQn);

    HAL_UART_Transmit(&handlerUART, send, 4, 10);

    if (HAL_UART_Receive_IT(&handlerUART, bufferUART, 10) != HAL_OK)
    {
        ERROR_HANDLER();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Multimeter::Update()
{
    uint8 send[4] = {0x02, 'V', '0', 0x0a};
    HAL_UART_Transmit(&handlerUART, send, 4, 100);
    HAL_UART_Receive_IT(&handlerUART, bufferUART, 10);

    Graphics::Update();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Multimeter::Graphics::Update()
{
    struct Func
    {
        pFuncVV func;
        Func(pFuncVV f) : func(f) {};
    };

    static const Func funcs[MultiMeasures::Number] =
    {
        PrepareConstantVoltage,
        PrepareVariableVoltage,
        PrepareConstantCurrent,
        PrepareVariableCurrent,
        PrepareResistance,
        PrepareTestDiode,
        PrepareRing
    };

    Painter::BeginScene(Color::BACK);

    if(buffer[0])
    {
        memset(out, 0, SIZE_OUT);

        funcs[MULTI_MEASURE].func();

        Painter::DrawBigText(30, 30, 5, out, Color::FILL);
    }

    Painter::SetColor(Color::FILL);

    Painter::DrawFormatText(10, 200, "%d", numMeasures);

    Painter::EndScene();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Multimeter::Graphics::PrepareConstantVoltage()
{
    out[0] = buffer[1];
    out[1] = buffer[2];
    out[5] = buffer[5];
    out[6] = buffer[6];
    out[7] = ' ';
    out[8] = 'V';
    out[9] = '=';

    switch(MULTI_RANGE_CV)
    {
        case MultiRangeCV::_2V:
            out[2] = '.';
            out[3] = buffer[3];
            out[4] = buffer[4];
            break;
        case MultiRangeCV::_20V:
            out[2] = buffer[3];
            out[3] = '.';
            out[4] = buffer[4];
            break;
        case MultiRangeCV::_500V:
            out[2] = buffer[3];
            out[3] = buffer[4];
            out[4] = '.';
            break;
    };
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Multimeter::Graphics::PrepareVariableVoltage()
{
    out[0] = buffer[2];
    out[4] = buffer[5];
    out[5] = buffer[6];
    out[6] = ' ';
    out[7] = 'V';
    out[8] = '~';

    switch (MULTI_RANGE_VV)
    {
        case MultiRangeVV::_2V:
            out[1] = '.';
            out[2] = buffer[3];
            out[3] = buffer[4];
            break;
        case MultiRangeVV::_20V:
            out[1] = buffer[3];
            out[2] = '.';
            out[3] = buffer[4];
            break;
        case MultiRangeVV::_400V:
            out[1] = buffer[3];
            out[2] = buffer[4];
            out[3] = '.';
            break;
    };
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Multimeter::Graphics::PrepareConstantCurrent()
{
    out[0] = (char)buffer[1];
    out[1] = buffer[2];
    out[2] = '.';
    out[3] = buffer[3];
    out[4] = buffer[4];
    out[5] = buffer[5];
    out[6] = buffer[6];
    out[7] = ' ';
    out[8] = 'A';
    out[9] = '=';
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Multimeter::Graphics::PrepareVariableCurrent()
{
    out[0] = buffer[2];
    out[1] = '.';
    out[2] = buffer[3];
    out[3] = buffer[4];
    out[4] = buffer[5];
    out[5] = buffer[6];
    out[6] = ' ';
    out[7] = 'A';
    out[8] = '~';
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Multimeter::Graphics::PrepareResistance()
{
    out[0] = buffer[2];
    out[4] = buffer[5];
    out[5] = buffer[6];
    out[6] = ' ';
    out[7] = 'к';
    out[8] = 'О';
    out[9] = 'м';

    switch(MULTI_RANGE_RESISTANCE)
    {
        case MultiRangeResistance::_2k:
            out[1] = '.';
            out[2] = buffer[3];
            out[3] = buffer[4];
            break;
        case MultiRangeResistance::_20k:
            out[1] = buffer[3];
            out[2] = '.';
            out[3] = buffer[4];
            break;
        case MultiRangeResistance::_200k:
            out[1] = buffer[3];
            out[2] = buffer[4];
            out[3] = '.';
            break;
        case MultiRangeResistance::_10M:
            out[1] = buffer[3];
            out[2] = '.';
            out[3] = buffer[4];
            out[7] = 'M';
            break;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Multimeter::Graphics::PrepareTestDiode()
{
    out[0] = (char)buffer[1];
    out[1] = buffer[2];
    out[2] = '.';
    out[3] = buffer[3];
    out[4] = buffer[4];
    out[5] = buffer[5];
    out[6] = buffer[6];
    out[7] = ' ';
    out[8] = 'V';
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Multimeter::Graphics::PrepareRing()
{
    out[0] = buffer[2];
    out[1] = '.';
    out[2] = buffer[3];
    out[3] = buffer[4];
    out[4] = buffer[5];
    out[5] = buffer[6];
    out[6] = ' ';
    out[7] = 'к';
    out[8] = 'О';
    out[9] = 'м';
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *)
{
    Multimeter::SetMeasure(bufferUART);

    HAL_UART_Receive_IT(&Multimeter::handlerUART, bufferUART, 10);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    if(huart == &Multimeter::handlerUART)
    {
        huart = &Multimeter::handlerUART;
    }
}

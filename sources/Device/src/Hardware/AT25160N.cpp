#include "AT25160N.h"
#include "Log.h"
#include "Utils/StringUtils.h"
#include <stdlib.h>
#include <string.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static SPI_HandleTypeDef hSPI2 =
{
    SPI2,
    {
        SPI_MODE_MASTER,
        SPI_DIRECTION_2LINES,
        SPI_DATASIZE_8BIT,
        SPI_POLARITY_HIGH,
        SPI_PHASE_1EDGE,
        SPI_NSS_SOFT,
        SPI_BAUDRATEPRESCALER_2,
        SPI_FIRSTBIT_MSB,
        SPI_TIMODE_DISABLE,
        SPI_CRCCALCULATION_DISABLE,
        10
    },
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, HAL_UNLOCKED, HAL_SPI_STATE_RESET, 0
};

static const uint8 addresses[] = 
{
    
    BIN_U8(00000110),   // WREN
    BIN_U8(00000100),   // WRDI
    BIN_U8(00000101),   // RDSR
    BIN_U8(00000001),   // WRSR
    BIN_U8(00000011),   // READ
    BIN_U8(00000010)    // WRITE
};

#define PIN_OUT     GPIOC, GPIO_PIN_3
#define PIN_IN      GPIOC, GPIO_PIN_2
#define PIN_CLK     GPIOB, GPIO_PIN_10
#define PIN_CS      GPIOB, GPIO_PIN_12

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AT25160N::Init()
{
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    /*  Аппаратные ресурсы
    SPI2
    PB12 - NSS
    PB10 - SCK
    PC3  - MOSI
    PC2 -  MISO   */

    //__HAL_RCC_SPI2_CLK_ENABLE();

    GPIO_InitTypeDef isGPIO =
    {//     SCK         NSS
        GPIO_PIN_10 | GPIO_PIN_12,
        GPIO_MODE_OUTPUT_PP,
        GPIO_PULLDOWN
    };
    HAL_GPIO_Init(GPIOB, &isGPIO);

    //             MOSI
    isGPIO.Pin = GPIO_PIN_3;
    HAL_GPIO_Init(GPIOC, &isGPIO);

    //             MISO
    isGPIO.Pin = GPIO_PIN_2;
    isGPIO.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(GPIOC, &isGPIO);

    SetPin(PIN_CS);
    ResetPin(PIN_OUT);
    ResetPin(PIN_CLK);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void AT25160N::Test()
{
    SetWriteLatch();
    uint8 value = 0xaa;
    WriteToRegister(WRSR, &value, 1);
    WaitFinishWrite();
    __IO uint8 state = ReadFromRegister(RDSR);
    LOG_MESSAGE("%s", SU::Bin2String(state));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void AT25160N::SetWriteLatch()
{
    ResetPin(PIN_CS);
    WriteByte(addresses[WREN]);
    SetPin(PIN_CS);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void AT25160N::ResetWriteLatch()
{
    ResetPin(PIN_CS);
    WriteByte(addresses[WRDI]);
    SetPin(PIN_CS);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void AT25160N::WaitFinishWrite()
{
    while(_GET_BIT(ReadFromRegister(RDSR), 0))
    {
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void AT25160N::Save(Settings &)
{
    /*
    Алгоритм сохранения настроек
    1. Настройки могут храниться в первом или втором килобайте памяти.
    2. 
    */
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void AT25160N::Load(Settings &)
{
    /*
    Алгоритм загрузки настроек
    */
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
uint8 AT25160N::ReadFromRegister(Reg reg)
{
    if (reg == RDSR)
    {
        ResetPin(PIN_CS);
        WriteByte(addresses[RDSR]);
        uint8 retValue = ReadByte();
        SetPin(PIN_CS);
        return retValue;
    }

    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void AT25160N::WriteToRegister(Reg reg, uint8 *data, uint size)
{
    ResetPin(PIN_CS);

    if(reg == WRSR || reg == WRITE)
    {
        uint8 *buffer = (uint8 *)malloc(1 + size);
        buffer[0] = addresses[WRSR];
        memcpy(buffer + 1, data, size);
        WriteBuffer(buffer, 2);
        free(buffer);
    }

    SetPin(PIN_CS);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void AT25160N::WriteBuffer(const uint8 *buffer, int size)
{
    for(int byte = 0; byte < size; byte++)
    {
        WriteByte(buffer[byte]);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void AT25160N::WriteByte(uint8 byte)
{
    for(int bit = 7; bit >= 0; bit--)
    {
        if (_GET_BIT(byte, bit))
        {
            SetPin(PIN_OUT);
        }
        SetPin(PIN_CLK);
        ResetPin(PIN_CLK);
        ResetPin(PIN_OUT);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
uint8 AT25160N::ReadByte()
{
    uint8 retValue = 0;

    for(int i = 0; i < 8; i++)
    {
        SetPin(PIN_CLK);
        retValue <<= 1;
        if(HAL_GPIO_ReadPin(PIN_IN) == GPIO_PIN_SET)
        {
            retValue |= 0x01;
        }
        ResetPin(PIN_CLK);
    }

    return retValue;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void AT25160N::SetPin(GPIO_TypeDef *gpio, uint16 pin)
{
    HAL_GPIO_WritePin(gpio, pin, GPIO_PIN_SET);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void AT25160N::ResetPin(GPIO_TypeDef *gpio, uint16 pin)
{
    HAL_GPIO_WritePin(gpio, pin, GPIO_PIN_RESET);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void AT25160N::WriteToAddress(uint address, uint8 *in, uint size)
{
    uint8 *buffer = (uint8 *)malloc(2 + size);
    buffer[0] = (address >> 8) & 0xf;
    buffer[1] = address & 0xf;
    memcpy(buffer + 2, in, size);

    WriteToRegister(WRITE, buffer, size + 2);

    free(buffer);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void AT25160N::ReadFromAddress(uint address, uint8 *in, uint size)
{
    
}

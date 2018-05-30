#include "AT25160N.h"
#include "Log.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static SPI_HandleTypeDef hSPI2 =
{
    SPI2,
    {
        SPI_MODE_MASTER,
        SPI_DIRECTION_2LINES,
        SPI_DATASIZE_8BIT,
        SPI_POLARITY_LOW,
        SPI_PHASE_2EDGE,
        SPI_NSS_HARD_OUTPUT,
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
    BIN_U8(00000110),
    BIN_U8(00000100),
    BIN_U8(00000101),
    BIN_U8(00000001),
    BIN_U8(00000011),
    BIN_U8(00000010)
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AT25160N::Init()
{
    /*  Аппаратные ресурсы
    SPI2
    PB12 - NSS
    PB10 - SCK
    PC3  - MOSI
    PF10 - MISO   */

    __HAL_RCC_SPI2_CLK_ENABLE();

    GPIO_InitTypeDef isGPIO =
    {//     SCK          NSS
        GPIO_PIN_10 | GPIO_PIN_12,
        GPIO_MODE_AF_PP,
        GPIO_NOPULL,
        GPIO_SPEED_FREQ_MEDIUM,
        GPIO_AF5_SPI2
    };
    HAL_GPIO_Init(GPIOB, &isGPIO);

    //              MOSI
    isGPIO.Pin = GPIO_PIN_3;
    HAL_GPIO_Init(GPIOC, &isGPIO);

    //              MISO
    isGPIO.Pin = GPIO_PIN_10;
    HAL_GPIO_Init(GPIOF, &isGPIO);

    HAL_SPI_Init(&hSPI2);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void AT25160N::Test()
{
    WriteReg(WREN);
    __IO uint8 state = ReadReg(RDSR);
    LOG_MESSAGE("d", state);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void AT25160N::Save(Settings &)
{

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void AT25160N::WriteReg(Reg reg, uint8)
{
    if(reg == WREN)
    {
        uint8 buffer = addresses[WREN];
        if (HAL_SPI_Transmit(&hSPI2, &buffer, 1, 100) == HAL_TIMEOUT)
        {
            LOG_MESSAGE("Timeout write");
        };
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
uint8 AT25160N::ReadReg(Reg reg)
{
    if(reg == RDSR)
    {
        uint8 bufferOut[2] = {addresses[RDSR]};
        uint8 bufferIn[2] = {0};
        if (HAL_SPI_TransmitReceive(&hSPI2, bufferOut, bufferIn, 2, 100) == HAL_TIMEOUT)
        {
            LOG_MESSAGE("Timeout read");
        };
        return bufferIn[1];
    }

    return 0;
}

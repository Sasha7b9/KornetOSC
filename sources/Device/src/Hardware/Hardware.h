#pragma once
#include "Hardware/stm32/stm32.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Hardware
{
public:

    static void Init();

private:

    static void SystemClock_Config(void);

    static void MX_GPIO_Init(void);
    static void MX_ADC3_Init(void);
    static void MX_DAC_Init(void);
    static void MX_SPI4_Init(void);
    static void MX_USART3_UART_Init(void);
    static void MX_USB_OTG_FS_PCD_Init(void);
    static void MX_USB_OTG_HS_PCD_Init(void);
};

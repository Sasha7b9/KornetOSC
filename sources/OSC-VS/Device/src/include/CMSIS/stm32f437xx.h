#pragma once
#include "core_cm4.h"             /* Cortex-M4 processor and core peripherals */
#include "system_stm32f4xx.h"
#include <stdint.h>


enum IRQn_Type
{
    NonMaskableInt_IRQn = -14,
    SysTick_IRQn        = -1,
    EXTI9_5_IRQn        = 23,
    USART3_IRQn         = 39
};


typedef struct
{
   int BTCR[8];    /*!< NOR/PSRAM chip-select control register(BCR) and chip-select timing register(BTR), Address offset: 0x00-1C */
} FMC_Bank1_TypeDef;



typedef struct
{
    __IO uint32_t MODER;    /*!< GPIO port mode register,               Address offset: 0x00      */
    __IO uint32_t OTYPER;   /*!< GPIO port output type register,        Address offset: 0x04      */
    __IO uint32_t OSPEEDR;  /*!< GPIO port output speed register,       Address offset: 0x08      */
    __IO uint32_t PUPDR;    /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
    __IO uint32_t IDR;      /*!< GPIO port input data register,         Address offset: 0x10      */
    __IO uint32_t ODR;      /*!< GPIO port output data register,        Address offset: 0x14      */
    __IO uint32_t BSRR;     /*!< GPIO port bit set/reset register,      Address offset: 0x18      */
    __IO uint32_t LCKR;     /*!< GPIO port configuration lock register, Address offset: 0x1C      */
    __IO uint32_t AFR[2];   /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
} GPIO_TypeDef;

typedef struct
{
    __IO uint32_t SR;     /*!< ADC status register,                         Address offset: 0x00 */
    __IO uint32_t CR1;    /*!< ADC control register 1,                      Address offset: 0x04 */
    __IO uint32_t CR2;    /*!< ADC control register 2,                      Address offset: 0x08 */
    __IO uint32_t SMPR1;  /*!< ADC sample time register 1,                  Address offset: 0x0C */
    __IO uint32_t SMPR2;  /*!< ADC sample time register 2,                  Address offset: 0x10 */
    __IO uint32_t JOFR1;  /*!< ADC injected channel data offset register 1, Address offset: 0x14 */
    __IO uint32_t JOFR2;  /*!< ADC injected channel data offset register 2, Address offset: 0x18 */
    __IO uint32_t JOFR3;  /*!< ADC injected channel data offset register 3, Address offset: 0x1C */
    __IO uint32_t JOFR4;  /*!< ADC injected channel data offset register 4, Address offset: 0x20 */
    __IO uint32_t HTR;    /*!< ADC watchdog higher threshold register,      Address offset: 0x24 */
    __IO uint32_t LTR;    /*!< ADC watchdog lower threshold register,       Address offset: 0x28 */
    __IO uint32_t SQR1;   /*!< ADC regular sequence register 1,             Address offset: 0x2C */
    __IO uint32_t SQR2;   /*!< ADC regular sequence register 2,             Address offset: 0x30 */
    __IO uint32_t SQR3;   /*!< ADC regular sequence register 3,             Address offset: 0x34 */
    __IO uint32_t JSQR;   /*!< ADC injected sequence register,              Address offset: 0x38*/
    __IO uint32_t JDR1;   /*!< ADC injected data register 1,                Address offset: 0x3C */
    __IO uint32_t JDR2;   /*!< ADC injected data register 2,                Address offset: 0x40 */
    __IO uint32_t JDR3;   /*!< ADC injected data register 3,                Address offset: 0x44 */
    __IO uint32_t JDR4;   /*!< ADC injected data register 4,                Address offset: 0x48 */
    __IO uint32_t DR;     /*!< ADC regular data register,                   Address offset: 0x4C */
} ADC_TypeDef;


typedef struct
{
    __IO uint32_t CR1;         /*!< TIM control register 1,              Address offset: 0x00 */
    __IO uint32_t CR2;         /*!< TIM control register 2,              Address offset: 0x04 */
    __IO uint32_t SMCR;        /*!< TIM slave mode control register,     Address offset: 0x08 */
    __IO uint32_t DIER;        /*!< TIM DMA/interrupt enable register,   Address offset: 0x0C */
    __IO uint32_t SR;          /*!< TIM status register,                 Address offset: 0x10 */
    __IO uint32_t EGR;         /*!< TIM event generation register,       Address offset: 0x14 */
    __IO uint32_t CCMR1;       /*!< TIM capture/compare mode register 1, Address offset: 0x18 */
    __IO uint32_t CCMR2;       /*!< TIM capture/compare mode register 2, Address offset: 0x1C */
    __IO uint32_t CCER;        /*!< TIM capture/compare enable register, Address offset: 0x20 */
    __IO uint32_t CNT;         /*!< TIM counter register,                Address offset: 0x24 */
    __IO uint32_t PSC;         /*!< TIM prescaler,                       Address offset: 0x28 */
    __IO uint32_t ARR;         /*!< TIM auto-reload register,            Address offset: 0x2C */
    __IO uint32_t RCR;         /*!< TIM repetition counter register,     Address offset: 0x30 */
    __IO uint32_t CCR1;        /*!< TIM capture/compare register 1,      Address offset: 0x34 */
    __IO uint32_t CCR2;        /*!< TIM capture/compare register 2,      Address offset: 0x38 */
    __IO uint32_t CCR3;        /*!< TIM capture/compare register 3,      Address offset: 0x3C */
    __IO uint32_t CCR4;        /*!< TIM capture/compare register 4,      Address offset: 0x40 */
    __IO uint32_t BDTR;        /*!< TIM break and dead-time register,    Address offset: 0x44 */
    __IO uint32_t DCR;         /*!< TIM DMA control register,            Address offset: 0x48 */
    __IO uint32_t DMAR;        /*!< TIM DMA address for full transfer,   Address offset: 0x4C */
    __IO uint32_t OR;          /*!< TIM option register,                 Address offset: 0x50 */
} TIM_TypeDef;

typedef struct
{
    __IO uint32_t CR1;        /*!< SPI control register 1 (not used in I2S mode),      Address offset: 0x00 */
    __IO uint32_t CR2;        /*!< SPI control register 2,                             Address offset: 0x04 */
    __IO uint32_t SR;         /*!< SPI status register,                                Address offset: 0x08 */
    __IO uint32_t DR;         /*!< SPI data register,                                  Address offset: 0x0C */
    __IO uint32_t CRCPR;      /*!< SPI CRC polynomial register (not used in I2S mode), Address offset: 0x10 */
    __IO uint32_t RXCRCR;     /*!< SPI RX CRC register (not used in I2S mode),         Address offset: 0x14 */
    __IO uint32_t TXCRCR;     /*!< SPI TX CRC register (not used in I2S mode),         Address offset: 0x18 */
    __IO uint32_t I2SCFGR;    /*!< SPI_I2S configuration register,                     Address offset: 0x1C */
    __IO uint32_t I2SPR;      /*!< SPI_I2S prescaler register,                         Address offset: 0x20 */
} SPI_TypeDef;

typedef struct
{
    __IO uint32_t DR;         /*!< CRC Data register,             Address offset: 0x00 */
    __IO uint8_t  IDR;        /*!< CRC Independent data register, Address offset: 0x04 */
    uint8_t       RESERVED0;  /*!< Reserved, 0x05                                      */
    uint16_t      RESERVED1;  /*!< Reserved, 0x06                                      */
    __IO uint32_t CR;         /*!< CRC Control register,          Address offset: 0x08 */
} CRC_TypeDef;

typedef struct
{
    __IO uint32_t CR;            /*!< RCC clock control register,                                  Address offset: 0x00 */
    __IO uint32_t PLLCFGR;       /*!< RCC PLL configuration register,                              Address offset: 0x04 */
    __IO uint32_t CFGR;          /*!< RCC clock configuration register,                            Address offset: 0x08 */
    __IO uint32_t CIR;           /*!< RCC clock interrupt register,                                Address offset: 0x0C */
    __IO uint32_t AHB1RSTR;      /*!< RCC AHB1 peripheral reset register,                          Address offset: 0x10 */
    __IO uint32_t AHB2RSTR;      /*!< RCC AHB2 peripheral reset register,                          Address offset: 0x14 */
    __IO uint32_t AHB3RSTR;      /*!< RCC AHB3 peripheral reset register,                          Address offset: 0x18 */
    uint32_t      RESERVED0;     /*!< Reserved, 0x1C                                                                    */
    __IO uint32_t APB1RSTR;      /*!< RCC APB1 peripheral reset register,                          Address offset: 0x20 */
    __IO uint32_t APB2RSTR;      /*!< RCC APB2 peripheral reset register,                          Address offset: 0x24 */
    uint32_t      RESERVED1[2];  /*!< Reserved, 0x28-0x2C                                                               */
    __IO uint32_t AHB1ENR;       /*!< RCC AHB1 peripheral clock register,                          Address offset: 0x30 */
    __IO uint32_t AHB2ENR;       /*!< RCC AHB2 peripheral clock register,                          Address offset: 0x34 */
    __IO uint32_t AHB3ENR;       /*!< RCC AHB3 peripheral clock register,                          Address offset: 0x38 */
    uint32_t      RESERVED2;     /*!< Reserved, 0x3C                                                                    */
    __IO uint32_t APB1ENR;       /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x40 */
    __IO uint32_t APB2ENR;       /*!< RCC APB2 peripheral clock enable register,                   Address offset: 0x44 */
    uint32_t      RESERVED3[2];  /*!< Reserved, 0x48-0x4C                                                               */
    __IO uint32_t AHB1LPENR;     /*!< RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50 */
    __IO uint32_t AHB2LPENR;     /*!< RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54 */
    __IO uint32_t AHB3LPENR;     /*!< RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58 */
    uint32_t      RESERVED4;     /*!< Reserved, 0x5C                                                                    */
    __IO uint32_t APB1LPENR;     /*!< RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60 */
    __IO uint32_t APB2LPENR;     /*!< RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64 */
    uint32_t      RESERVED5[2];  /*!< Reserved, 0x68-0x6C                                                               */
    __IO uint32_t BDCR;          /*!< RCC Backup domain control register,                          Address offset: 0x70 */
    __IO uint32_t CSR;           /*!< RCC clock control & status register,                         Address offset: 0x74 */
    uint32_t      RESERVED6[2];  /*!< Reserved, 0x78-0x7C                                                               */
    __IO uint32_t SSCGR;         /*!< RCC spread spectrum clock generation register,               Address offset: 0x80 */
    __IO uint32_t PLLI2SCFGR;    /*!< RCC PLLI2S configuration register,                           Address offset: 0x84 */
    __IO uint32_t PLLSAICFGR;    /*!< RCC PLLSAI configuration register,                           Address offset: 0x88 */
    __IO uint32_t DCKCFGR;       /*!< RCC Dedicated Clocks configuration register,                 Address offset: 0x8C */
} RCC_TypeDef;


typedef struct
{
    __IO uint32_t CR;       /*!< DAC control register,                                    Address offset: 0x00 */
    __IO uint32_t SWTRIGR;  /*!< DAC software trigger register,                           Address offset: 0x04 */
    __IO uint32_t DHR12R1;  /*!< DAC channel1 12-bit right-aligned data holding register, Address offset: 0x08 */
    __IO uint32_t DHR12L1;  /*!< DAC channel1 12-bit left aligned data holding register,  Address offset: 0x0C */
    __IO uint32_t DHR8R1;   /*!< DAC channel1 8-bit right aligned data holding register,  Address offset: 0x10 */
    __IO uint32_t DHR12R2;  /*!< DAC channel2 12-bit right aligned data holding register, Address offset: 0x14 */
    __IO uint32_t DHR12L2;  /*!< DAC channel2 12-bit left aligned data holding register,  Address offset: 0x18 */
    __IO uint32_t DHR8R2;   /*!< DAC channel2 8-bit right-aligned data holding register,  Address offset: 0x1C */
    __IO uint32_t DHR12RD;  /*!< Dual DAC 12-bit right-aligned data holding register,     Address offset: 0x20 */
    __IO uint32_t DHR12LD;  /*!< DUAL DAC 12-bit left aligned data holding register,      Address offset: 0x24 */
    __IO uint32_t DHR8RD;   /*!< DUAL DAC 8-bit right aligned data holding register,      Address offset: 0x28 */
    __IO uint32_t DOR1;     /*!< DAC channel1 data output register,                       Address offset: 0x2C */
    __IO uint32_t DOR2;     /*!< DAC channel2 data output register,                       Address offset: 0x30 */
    __IO uint32_t SR;       /*!< DAC status register,                                     Address offset: 0x34 */
} DAC_TypeDef;


typedef struct
{
    __IO uint32_t GOTGCTL;              /*!< USB_OTG Control and Status Register          000h */
    __IO uint32_t GOTGINT;              /*!< USB_OTG Interrupt Register                   004h */
    __IO uint32_t GAHBCFG;              /*!< Core AHB Configuration Register              008h */
    __IO uint32_t GUSBCFG;              /*!< Core USB Configuration Register              00Ch */
    __IO uint32_t GRSTCTL;              /*!< Core Reset Register                          010h */
    __IO uint32_t GINTSTS;              /*!< Core Interrupt Register                      014h */
    __IO uint32_t GINTMSK;              /*!< Core Interrupt Mask Register                 018h */
    __IO uint32_t GRXSTSR;              /*!< Receive Sts Q Read Register                  01Ch */
    __IO uint32_t GRXSTSP;              /*!< Receive Sts Q Read & POP Register            020h */
    __IO uint32_t GRXFSIZ;              /*!< Receive FIFO Size Register                   024h */
    __IO uint32_t DIEPTXF0_HNPTXFSIZ;   /*!< EP0 / Non Periodic Tx FIFO Size Register     028h */
    __IO uint32_t HNPTXSTS;             /*!< Non Periodic Tx FIFO/Queue Sts reg           02Ch */
    uint32_t Reserved30[2];             /*!< Reserved                                     030h */
    __IO uint32_t GCCFG;                /*!< General Purpose IO Register                  038h */
    __IO uint32_t CID;                  /*!< User ID Register                             03Ch */
    uint32_t  Reserved40[48];           /*!< Reserved                                0x40-0xFF */
    __IO uint32_t HPTXFSIZ;             /*!< Host Periodic Tx FIFO Size Reg               100h */
    __IO uint32_t DIEPTXF[0x0F];        /*!< dev Periodic Transmit FIFO                        */
} USB_OTG_GlobalTypeDef;


typedef struct
{
    __IO uint32_t SR;         /*!< USART Status register,                   Address offset: 0x00 */
    __IO uint32_t DR;         /*!< USART Data register,                     Address offset: 0x04 */
    __IO uint32_t BRR;        /*!< USART Baud rate register,                Address offset: 0x08 */
    __IO uint32_t CR1;        /*!< USART Control register 1,                Address offset: 0x0C */
    __IO uint32_t CR2;        /*!< USART Control register 2,                Address offset: 0x10 */
    __IO uint32_t CR3;        /*!< USART Control register 3,                Address offset: 0x14 */
    __IO uint32_t GTPR;       /*!< USART Guard time and prescaler register, Address offset: 0x18 */
} USART_TypeDef;


#define RCC_AHB1ENR_GPIOAEN_Pos            (0U)                                
#define RCC_AHB1ENR_GPIOAEN_Msk            (0x1U << RCC_AHB1ENR_GPIOAEN_Pos)   /*!< 0x00000001 */
#define RCC_AHB1ENR_GPIOAEN                RCC_AHB1ENR_GPIOAEN_Msk
#define RCC_AHB1ENR_GPIOBEN_Pos            (1U)                                
#define RCC_AHB1ENR_GPIOBEN_Msk            (0x1U << RCC_AHB1ENR_GPIOBEN_Pos)   /*!< 0x00000002 */
#define RCC_AHB1ENR_GPIOBEN                RCC_AHB1ENR_GPIOBEN_Msk
#define RCC_AHB1ENR_GPIOCEN_Pos            (2U)                                
#define RCC_AHB1ENR_GPIOCEN_Msk            (0x1U << RCC_AHB1ENR_GPIOCEN_Pos)   /*!< 0x00000004 */
#define RCC_AHB1ENR_GPIOCEN                RCC_AHB1ENR_GPIOCEN_Msk             
#define RCC_AHB1ENR_GPIODEN_Pos            (3U)                                
#define RCC_AHB1ENR_GPIODEN_Msk            (0x1U << RCC_AHB1ENR_GPIODEN_Pos)   /*!< 0x00000008 */
#define RCC_AHB1ENR_GPIODEN                RCC_AHB1ENR_GPIODEN_Msk             
#define RCC_AHB1ENR_GPIOEEN_Pos            (4U)                                
#define RCC_AHB1ENR_GPIOEEN_Msk            (0x1U << RCC_AHB1ENR_GPIOEEN_Pos)   /*!< 0x00000010 */
#define RCC_AHB1ENR_GPIOEEN                RCC_AHB1ENR_GPIOEEN_Msk             
#define RCC_AHB1ENR_GPIOFEN_Pos            (5U)                                
#define RCC_AHB1ENR_GPIOFEN_Msk            (0x1U << RCC_AHB1ENR_GPIOFEN_Pos)   /*!< 0x00000020 */
#define RCC_AHB1ENR_GPIOFEN                RCC_AHB1ENR_GPIOFEN_Msk             
#define RCC_AHB1ENR_GPIOGEN_Pos            (6U)                                
#define RCC_AHB1ENR_GPIOGEN_Msk            (0x1U << RCC_AHB1ENR_GPIOGEN_Pos)   /*!< 0x00000040 */
#define RCC_AHB1ENR_GPIOGEN                RCC_AHB1ENR_GPIOGEN_Msk             
#define RCC_AHB1ENR_GPIOHEN_Pos            (7U)                                
#define RCC_AHB1ENR_GPIOHEN_Msk            (0x1U << RCC_AHB1ENR_GPIOHEN_Pos)   /*!< 0x00000080 */
#define RCC_AHB1ENR_GPIOHEN                RCC_AHB1ENR_GPIOHEN_Msk             
#define RCC_AHB1ENR_GPIOIEN_Pos            (8U)                                
#define RCC_AHB1ENR_GPIOIEN_Msk            (0x1U << RCC_AHB1ENR_GPIOIEN_Pos)   /*!< 0x00000100 */
#define RCC_AHB1ENR_GPIOIEN                RCC_AHB1ENR_GPIOIEN_Msk             
#define RCC_AHB1ENR_GPIOJEN_Pos            (9U)                                
#define RCC_AHB1ENR_GPIOJEN_Msk            (0x1U << RCC_AHB1ENR_GPIOJEN_Pos)   /*!< 0x00000200 */
#define RCC_AHB1ENR_GPIOJEN                RCC_AHB1ENR_GPIOJEN_Msk

#define RCC_APB1ENR_DACEN_Pos              (29U)                               
#define RCC_APB1ENR_DACEN_Msk              (0x1U << RCC_APB1ENR_DACEN_Pos)     /*!< 0x20000000 */
#define RCC_APB1ENR_DACEN                  RCC_APB1ENR_DACEN_Msk   

#define PERIPH_BASE                         0x40000000U /*!< Peripheral base address in the alias region                                */


#define USB_OTG_FS_PERIPH_BASE              0x50000000U
#define USB_OTG_HS_PERIPH_BASE              0x40040000U

#define APB1PERIPH_BASE  PERIPH_BASE
#define APB2PERIPH_BASE (PERIPH_BASE + 0x00010000U)
#define AHB1PERIPH_BASE (PERIPH_BASE + 0x00020000U)

#define GPIOA_BASE      (AHB1PERIPH_BASE + 0x0000U)
#define GPIOB_BASE      (AHB1PERIPH_BASE + 0x0400U)
#define GPIOC_BASE      (AHB1PERIPH_BASE + 0x0800U)
#define GPIOD_BASE      (AHB1PERIPH_BASE + 0x0C00U)
#define GPIOE_BASE      (AHB1PERIPH_BASE + 0x1000U)
#define GPIOF_BASE      (AHB1PERIPH_BASE + 0x1400U)
#define GPIOG_BASE      (AHB1PERIPH_BASE + 0x1800U)
#define GPIOH_BASE      (AHB1PERIPH_BASE + 0x1C00U)
#define GPIOI_BASE      (AHB1PERIPH_BASE + 0x2000U)
#define GPIOJ_BASE      (AHB1PERIPH_BASE + 0x2400U)
#define GPIOK_BASE      (AHB1PERIPH_BASE + 0x2800U)

#define CRC_BASE        (AHB1PERIPH_BASE + 0x3000U)
#define RCC_BASE        (AHB1PERIPH_BASE + 0x3800U)
#define ADC3_BASE       (APB2PERIPH_BASE + 0x2200U)
#define DAC_BASE        (APB1PERIPH_BASE + 0x7400U)
#define SPI4_BASE       (APB2PERIPH_BASE + 0x3400U)
#define USART3_BASE     (APB1PERIPH_BASE + 0x4800U)

#define RCC             ((RCC_TypeDef *) RCC_BASE)
#define CRC             ((CRC_TypeDef *) CRC_BASE)
#define ADC3            ((ADC_TypeDef *) ADC3_BASE)
#define DAC             ((DAC_TypeDef *) DAC_BASE) /* Kept for legacy purpose */
#define SPI4            ((SPI_TypeDef *) SPI4_BASE)
#define USART3          ((USART_TypeDef *) USART3_BASE)

#define GPIOA           ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB           ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC           ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD           ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE           ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF           ((GPIO_TypeDef *) GPIOF_BASE)
#define GPIOG           ((GPIO_TypeDef *) GPIOG_BASE)
#define GPIOH           ((GPIO_TypeDef *) GPIOH_BASE)
#define GPIOI           ((GPIO_TypeDef *) GPIOI_BASE)
#define GPIOJ           ((GPIO_TypeDef *) GPIOJ_BASE)
#define GPIOK           ((GPIO_TypeDef *) GPIOK_BASE)

#define USB_OTG_FS      ((USB_OTG_GlobalTypeDef *) USB_OTG_FS_PERIPH_BASE)
#define USB_OTG_HS      ((USB_OTG_GlobalTypeDef *) USB_OTG_HS_PERIPH_BASE)

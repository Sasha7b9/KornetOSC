#include "FPGA.h"
#include "FPGAMath.h"
#include "AD9286.h"
#include "Log.h"
#include "Data/Reader.h"
#include "FPGA/FPGA.h"
#include "Utils/MathOSC.h"
#include "Display/Display.h"
#include "Hardware/FSMC.h"
#include "Hardware/GPIO.h"
#include "Hardware/Hardware.h"
#include "Hardware/Timer.h"
#include "Utils/CommonFunctions.h"
#include "Utils/MathOSC.h"
#include "Utils/Math.h"
#include "Utils/ProcessingSignal.h"
#include "Settings/Settings.h"
#include "Data/Storage.h"
#include "Menu/Pages/PageTime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define NULL_TSHIFT 1000000

#define FPGA_IN_PAUSE                   (bf.pause)
#define FPGA_CAN_READ_DATA              (bf.canRead)
#define FPGA_FIRST_AFTER_WRITE          (bf.firstAfterWrite)
#define NEED_STOP_AFTER_READ_FRAME_2P2  (bf.needStopAfterReadFrame2P2)


static struct BitFieldFPGA
{
    uint pause : 1;
    uint canRead : 1;
    uint firstAfterWrite : 1;     ///< \brief Используется в режиме рандомизатора. После записи любого параметра в альтеру нужно не 
                                            ///<        использовать первое считанное данное с АЦП, потому что оно завышено и портит ворота.
    uint needStopAfterReadFrame2P2 : 1;
    uint notUsed : 28;
} bf = {0, 1, 0, 0, 0};

uint16 gPost = 1024;
int16 gPred = 1024;
int gAddNStop = 0;



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static ADC_HandleTypeDef hADC;

static uint16 adcValueFPGA = 0;

struct PinStruct
{
    GPIO_TypeDef   *gpioTD;
    uint            pin;
};

static PinStruct pins[Num_Pins] =
{
    {GPIOC, GPIO_PIN_10},   // SPI3_SCK
    {GPIOC, GPIO_PIN_12},   // SPI3_DAT
    {GPIOD, GPIO_PIN_3},    // SPI3_CS1
    {GPIOG, GPIO_PIN_13},   // SPI3_CS2
    {GPIOD, GPIO_PIN_10},   // A1
    {GPIOD, GPIO_PIN_11},   // A2
    {GPIOD, GPIO_PIN_12},   // A3
    {GPIOD, GPIO_PIN_13},   // A4
    {GPIOG, GPIO_PIN_2},    // LF1
    {GPIOG, GPIO_PIN_3},    // LF2
    {GPIOG, GPIO_PIN_4},    // A1S
    {GPIOG, GPIO_PIN_5},    // A0S
    {GPIOG, GPIO_PIN_6}     // LFS
};


//static bool isRunning = false;

volatile static int numberMeasuresForGates = 1000;

static uint8 dataRand[NumChannels][FPGA_MAX_POINTS];    ///< Здесь будут данные рандомизатора
              //  2нс 5нс 10нс 20нс 50нс
const int Kr[] = {50, 20, 10,  5,   2};
/// Здесь хранится адрес, начиная с которого будем читать данные по каналам. Если addrRead == 0xffff, то адрес вначале нужно считать
static uint16 addrRead = 0xffff;

static uint8 ValueForRange(Channel ch);

bool FPGA::isRunning = false;
bool FPGA::givingStart = false;
StateWorkFPGA fpgaStateWork = StateWorkFPGA_Stop;
static uint8 *dataRandA = 0;
static uint8 *dataRandB = 0;
static uint timeCompletePredTrig = 0;   ///< Здесь окончание счёта предзапуска. Если == 0, то предзапуск не завершён.
static DataSettings ds;
    static uint timeSwitchingTrig = 0;
int FPGA::addShiftForFPGA = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FPGA::Init()
{
    givingStart = false;

    GPIO_Init();
    
    SetPin(SPI3_CS1);
    SetPin(SPI3_CS2);

    ResetPin(SPI3_SCK);
    ResetPin(SPI3_DAT);

    AD9286::Init();

    // Теперь настроим вход АЦП от рандомизатора
    // PF10 - ADC3 IN8
    // PB11 - EXTI11
    // Режим работы:
    // - измерение по 1 регулярному каналу
    // - одиночное измерение по фронту внешнего запуска (прерывание от PB11)

    __ADC3_CLK_ENABLE();

    static GPIO_InitTypeDef isGPIOadc =
    {
        GPIO_PIN_10,
        GPIO_MODE_ANALOG,
        GPIO_NOPULL
    };
    HAL_GPIO_Init(GPIOF, &isGPIOadc);

    static GPIO_InitTypeDef isGPIOexti =
    {
        GPIO_PIN_11,
        GPIO_MODE_IT_RISING,
        GPIO_NOPULL
    };
    HAL_GPIO_Init(GPIOB, &isGPIOexti);
    
    HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(ADC_IRQn);

    hADC.Instance = ADC3;
    hADC.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
    hADC.Init.Resolution = ADC_RESOLUTION12b;
    hADC.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hADC.Init.ScanConvMode = DISABLE;
    hADC.Init.EOCSelection = ENABLE;
    hADC.Init.ContinuousConvMode = DISABLE;
    hADC.Init.DMAContinuousRequests = DISABLE;
    hADC.Init.NbrOfConversion = 1;
    hADC.Init.DiscontinuousConvMode = DISABLE;
    hADC.Init.NbrOfDiscConversion = 0;
    hADC.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
    hADC.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_Ext_IT11;

    if (HAL_ADC_Init(&hADC) != HAL_OK)
    {
        ERROR_HANDLER();
    }

    ADC_ChannelConfTypeDef sConfig;
    sConfig.Channel = ADC_CHANNEL_8;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
    sConfig.Offset = 0;

    if (HAL_ADC_ConfigChannel(&hADC, &sConfig) != HAL_OK)
    {
        ERROR_HANDLER();
    }

    if (HAL_ADC_Start_IT(&hADC) != HAL_OK)
    {
        ERROR_HANDLER();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::GiveStart()
{
    uint8 value = (uint8)TRIG_POLARITY;
    FSMC::WriteToFPGA8(WR_TRIG, value++);
    FSMC::WriteToFPGA8(WR_TRIG, (uint8)(value % 2));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::Stop(bool)
{
    isRunning = false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::Update()
{
    if (!isRunning)
    {
        return;
    };

    uint8 flag = ReadFlag();

    if (_GET_BIT(flag, BIT_FLAG_PRED) == 1 && !givingStart)
    {
//        GiveStart();
        //LOG_WRITE("предзапуск готов");
        givingStart = true;
    }

    if (_GET_BIT(flag, BIT_FLAG_DATA_READY) == 1)
    {
        //LOG_WRITE("читаю данные");
        ReadData();
        Start();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
uint8 FPGA::ReadFlag()
{
    return FSMC::ReadFromFPGA(RD_FLAG_LO);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
uint16 FPGA::ReadLastRecord()
{
    return (uint16)(FSMC::ReadFromFPGA(RD_LAST_RECORD_LO) + ((FSMC::ReadFromFPGA(RD_LAST_RECORD_HI)) << 8));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::OnPressStart()
{
    isRunning = !isRunning;
    if (isRunning)
    {
        Start();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::Start()
{
    givingStart = false;
    addrRead = 0xffff;

    uint16 post = (uint16)(-FPGA_NUM_POINTS);
    uint16 pred = (uint16)(-3);

    FSMC::WriteToFPGA16(WR_PRED_LO, pred);
    FSMC::WriteToFPGA16(WR_POST_LO, post);
    FSMC::WriteToFPGA8(WR_START, 0xff);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::StartForTester(int)
{
    // У нас двенадцать делений. На двенадцать делений должно приходиться не менее 2.5 мс
    // 2.5мс / 12дел = 0.2 мс/дел = 10мкс/тчк

    SET_TBASE = TBase_500us;

    LoadTBase();

    uint16 post = (uint16)(-TESTER_NUM_POINTS);
    uint16 pred = (uint16)(~3);

    FSMC::WriteToFPGA16(WR_PRED_LO, pred);
    FSMC::WriteToFPGA16(WR_POST_LO, post);
    FSMC::WriteToFPGA8(WR_START, 0xff);

    uint8 flag = 0;
    uint timeStart = TIME_US;
    while (_GET_BIT(flag, BIT_FLAG_PRED) == 0)
    {
        flag = ReadFlag();
        if(TIME_US - timeStart > 1000) /// \todo Временная затычка. Надо сделать так, чтобы такие ситуации были исключены. Сбои происходят, во время
        {                               /// нажатия кнопок
            return;
        }
    }

    GiveStart();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::ReadForTester(uint8 *dataA, uint8 *dataB)
{
    uint8 flag = 0;

    uint timeStart = TIME_US;
    while (_GET_BIT(flag, BIT_FLAG_DATA_READY) == 0)    // Ждём флага готовности данных
    {
        flag = ReadFlag();
        if(TIME_US - timeStart > 10000) /// \todo Временная затычка. Надо сделать так, чтобы такие ситуации были исключены. Сбои происходят, во время
        {                               /// нажатия кнопок
            return;
        }
    }

    uint16 aRead = (uint16)(ReadLastRecord() - TESTER_NUM_POINTS);

    FSMC::WriteToFPGA16(WR_PRED_LO, aRead);           // Указываем адрес, с которого будем читать данные
    FSMC::WriteToFPGA8(WR_START_ADDR, 0xff);             // И даём команду ПЛИС, чтобы чтение начиналось с него

    uint8 *addrA = RD_DATA_A;
    for (int i = 0; i < TESTER_NUM_POINTS; i++)         // Читаем данные первого канала
    {
        *dataA++ = *addrA;
    }

    FSMC::WriteToFPGA16(WR_PRED_LO, aRead);           // Указываем адрес, с котонрого будем читать данные
    FSMC::WriteToFPGA8(WR_START_ADDR, 0xff);             // И даём команду ПЛИС, чтобы чтение начиналось с него

    uint8 *addrB = RD_DATA_B;
    for (int i = 0; i < TESTER_NUM_POINTS; i++)         // Читаем данные второго канала
    {
        *dataB++ = *addrB;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::ReadDataChanenl(Channel ch, uint8 data[FPGA_MAX_POINTS])
{
    if (addrRead == 0xffff)
    {
        addrRead = (uint16)(ReadLastRecord() - FPGA_NUM_POINTS);
    }
    
    FSMC::WriteToFPGA16(WR_PRED_LO, addrRead);
    FSMC::WriteToFPGA8(WR_START_ADDR, 0xff);
    
    uint8 *address = (ch == A) ? RD_DATA_A : RD_DATA_B;

    if (IN_RANDOMIZE_MODE)
    {
        ReadDataChanenlRand(ch, address, data);
    }
    else
    {
        uint8 *p = data;

        for (int i = 0; i < FPGA_NUM_POINTS / 4; ++i)
        {
            *p++ = *address;
            *p++ = *address;
            *p++ = *address;
            *p++ = *address;
        }
    }

    static uint timePrev = 0;

    if (TIME_MS - timePrev > 1000)
    {
        timePrev = TIME_MS;

        uint8 *d = data;

        LOG_WRITE("%d %d %d %d %d %d %d %d %d %d %d %d %d %d", d[0], d[1], d[2], d[3], d[4], d[5], d[6], d[7], d[8], d[9], d[10], d[11], d[12], d[13]);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::ReadDataChanenlRand(Channel ch, uint8 *address, uint8 *data)
{
    int Tsm = CalculateShift();

    if (Tsm == NULL_TSHIFT)
    {
        return;
    }

    int step = Kr[SET_TBASE];

    /*
    if (Tsm < 2)
    {
        Tsm += step;
    }
    */

    int index = Tsm - step;

    while (index < 0)
    {
        index += step;
    }

    uint8 *dataRead = &dataRand[ch][0] + index;

    uint8 *last = &dataRand[ch][0] + FPGA_NUM_POINTS;

    while (dataRead < last)
    {
        *dataRead = *address;
        dataRead += step;
    }

    memcpy(data, &dataRand[ch][0], (uint)FPGA_NUM_POINTS);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int FPGA::CalculateShift()
{
    uint16 min = 0;
    uint16 max = 0;

    if (!CalculateGate(adcValueFPGA, &min, &max))
    {
        return NULL_TSHIFT;
    }

    if (IN_RANDOMIZE_MODE)
    {
        float tin = (float)(adcValueFPGA - min) / (max - min);
        int retValue = (int)(tin * Kr[SET_TBASE] + 0.5f);

//        LOG_WRITE("%d - %d", adcValueFPGA, retValue);

        return retValue;
    }

    return -1;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool FPGA::CalculateGate(uint16 rand, uint16 *eMin, uint16 *eMax)
{
    if (rand < 500 || rand > 4000)
    {
        LOG_WRITE("ОШИБКА!!! считано %d", rand);
        return false;
    }

    static float minGate = 0.0f;
    static float maxGate = 0.0f;
    static int numElements = 0;
    static uint16 min = 0xffff;
    static uint16 max = 0;

    numElements++;
    if (rand < min)
    {
        min = rand;
    }
    if (rand > max)
    {
        max = rand;
    }

    if (minGate == 0.0f)
    {
        *eMin = min;
        *eMax = max;
        if (numElements < numberMeasuresForGates)
        {
            return true;
        }
        minGate = min;
        maxGate = max;
        numElements = 0;
        min = 0xffff;
        max = 0;
    }

    if (numElements >= numberMeasuresForGates)
    {
        //minGate = (9.0f * minGate + min) * 0.1f;
        //maxGate = (9.0f * maxGate + max) * 0.1f;

        minGate = 0.8f * minGate + min * 0.2f;
        maxGate = 0.8f * maxGate + max * 0.2f;

        LOG_WRITE("%.1f %.1f", (double)minGate, (double)maxGate);

        numElements = 0;
        min = 0xffff;
        max = 0;
    }

    *eMin = (uint16)(minGate);
    *eMax = (uint16)(maxGate);

    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::ReadData()
{
    uint8 *dataA = (uint8 *)malloc((uint)FPGA_NUM_POINTS);
    uint8 *dataB = (uint8 *)malloc((uint)FPGA_NUM_POINTS);

    ReadDataChanenl(A, dataA);
    ReadDataChanenl(B, dataB);

    //Storage::AddData(dataA, dataB);
    
    free(dataA);
    free(dataB);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::GPIO_Init()
{
    GPIO_InitTypeDef isGPIO =
    {
        0,
        GPIO_MODE_OUTPUT_PP,
        GPIO_PULLDOWN
    };

    for (int i = 0; i < Num_Pins; i++)
    {
        isGPIO.Pin = GetPin((Pin)i);
        HAL_GPIO_Init(GetPort((Pin)i), &isGPIO);
    }

    for (int i = 0; i < Num_Pins; i++)
    {
        gpio.SetOutputPP_PullDown(GetPort((Pin)i), (uint)MathOSC::LowSignedBit(GetPin((Pin)i)));
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::LoadSettings()
{
    LoadRanges();
    LoadRShift(A);
    LoadRShift(B);
    LoadTrigSourceInput();
    LoadTBase();
    LoadTShift();

    isRunning = false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::IncreaseRange(Channel ch)
{
    LimitationIncrease<uint8>((uint8 *)(&SET_RANGE(ch)), (uint8)(RangeSize - 1));
    LoadRanges();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::DecreaseRange(Channel ch)
{
    LimitationDecrease<uint8>((uint8 *)(&SET_RANGE(ch)), 0);
    LoadRanges();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::IncreaseTBase()
{
    LimitationIncrease<uint8>((uint8 *)(&SET_TBASE), (uint8)(TBaseSize - 1));
    LoadTBase();
    Start();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::DecreaseTBase()
{
    LimitationDecrease<uint8>((uint8 *)(&SET_TBASE), 0);
    LoadTBase();
    Start();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::RShiftChange(Channel ch, int delta)
{
    AddtionThisLimitation<uint16>(&SET_RSHIFT(ch), STEP_RSHIFT * delta, RShiftMin, RShiftMax);

    LoadRShift(ch);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::TrigLevChange(int delta)
{
    AddtionThisLimitation<uint16>(&SET_TRIGLEV_SOURCE, STEP_TRIGLEV * delta, TrigLevMin, TrigLevMax);

    LoadTrigLev();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::TShiftChange(int delta)
{
    AddtionThisLimitation<uint16>(&SET_TSHIFT, delta, TShiftMin, TShiftMax);

    LoadTShift();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
uint FPGA::GetPin(Pin pin)
{
    return pins[pin].pin;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
GPIO_TypeDef *FPGA::GetPort(Pin pin)
{
    return pins[pin].gpioTD;
}

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4310)
#endif

//----------------------------------------------------------------------------------------------------------------------------------------------------
static uint8 ValueForRange(Channel ch)
{
    static const uint8 datas[CoupleSize] =
    {
        BIN_U8(01000001),    // AC
        BIN_U8(10000001),    // DC
        BIN_U8(00000010)     // GND
    };

    if (SET_COUPLE(ch) == ModeCouple_GND)
    {
        return datas[ModeCouple_GND];
    }

    static const uint16 values[RangeSize][NumChannels] =
    {   //             A                    B
        { BIN_U8(00100101), BIN_U8(00010101) },   // 2mV
        { BIN_U8(00100101), BIN_U8(00010101) },   // 5mV
        { BIN_U8(00100101), BIN_U8(00010101) },   // 10mV
        { BIN_U8(00100101), BIN_U8(00010101) },   // 20mV
        { BIN_U8(00010101), BIN_U8(00100101) },   // 50mV
        { BIN_U8(00010101), BIN_U8(00100101) },   // 100mV
        { BIN_U8(00010101), BIN_U8(00100101) },   // 200mV
        { BIN_U8(00101001), BIN_U8(00011001) },   // 500mV
        { BIN_U8(00101001), BIN_U8(00011001) },   // 1V
        { BIN_U8(00101001), BIN_U8(00011001) },   // 2V
        { BIN_U8(00011001), BIN_U8(00101001) },   // 5V
        { BIN_U8(00011001), BIN_U8(00101001) },   // 10V
        { BIN_U8(00011001), BIN_U8(00101001) }    // 20V
    };

    return (uint8)(values[SET_RANGE(ch)][ch] | datas[SET_COUPLE(ch)]);
}

#ifdef _WIN32
#pragma warning(pop)
#endif

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::LoadRanges()
{
    uint16 value = (uint16)(ValueForRange(B) + (ValueForRange(A) << 8));

    WriteRegisters(SPI3_CS2, value);

    PAUSE_ON_MS(10);              // Задержка нужна, чтобы импульсные реле успели отработать

    WriteRegisters(SPI3_CS2, 0);    // Записываем ноль, чтобы реле не потребляли энергии

    static const uint8 vals[RangeSize][NumChannels] =
    {
        { BIN_U8(00000000),  BIN_U8(00000000) },  // 2mV
        { BIN_U8(00000001),  BIN_U8(00000010) },  // 5mV
        { BIN_U8(00000010),  BIN_U8(00000001) },  // 10mV
        { BIN_U8(00000011),  BIN_U8(00000011) },  // 20mV
        { BIN_U8(00000001),  BIN_U8(00000010) },  // 50mV
        { BIN_U8(00000010),  BIN_U8(00000001) },  // 100mV
        { BIN_U8(00000011),  BIN_U8(00000011) },  // 200mV
        { BIN_U8(00000001),  BIN_U8(00000010) },  // 500mV
        { BIN_U8(00000010),  BIN_U8(00000001) },  // 1V
        { BIN_U8(00000011),  BIN_U8(00000011) },  // 2V
        { BIN_U8(00000001),  BIN_U8(00000010) },  // 5V
        { BIN_U8(00000010),  BIN_U8(00000001) },  // 10V
        { BIN_U8(00000011),  BIN_U8(00000011) }   // 20V
    };

    uint8 valueA = vals[SET_RANGE_A][A];

    WritePin(A1, _GET_BIT(valueA, 1));
    WritePin(A2, _GET_BIT(valueA, 0));

    uint8 valueB = vals[SET_RANGE_B][B];

    WritePin(A3, _GET_BIT(valueB, 1));
    WritePin(A4, _GET_BIT(valueB, 0));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::WriteRegisters(Pin cs, uint16 value)
{
    ResetPin(cs);

    if (cs == SPI3_CS1)
    {
        for (int i = 15; i >= 0; --i)
        {
            WritePin(SPI3_DAT, _GET_BIT(value, i));
            PAUSE_ON_TICKS(100);
            SetPin(SPI3_SCK);
            ResetPin(SPI3_SCK);
        }
    }
    else if (cs == SPI3_CS2)
    {
        for (int i = 0; i < 16; ++i)
        {
            WritePin(SPI3_DAT, _GET_BIT(value, i));
            PAUSE_ON_TICKS(100);
            SetPin(SPI3_SCK);
            ResetPin(SPI3_SCK);
        }
    }

    SetPin(cs);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::LoadRShift(Channel ch)
{
    static const uint16 mask[2] = {0xa000, 0x6000};

    WriteRegisters(SPI3_CS1, (uint16)(mask[ch] | (SET_RSHIFT(ch) << 2)));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::LoadTrigLev()
{
    WriteRegisters(SPI3_CS1, (uint16)(0x2000 | (SET_TRIGLEV_SOURCE << 2)));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::WritePin(Pin pin, int enable)
{
    if (enable)
    {
        GetPort(pin)->BSRR = GetPin(pin);
    }
    else
    {
        GetPort(pin)->BSRR = (uint)GetPin(pin) << 16;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetPin(Pin pin)
{
    GetPort(pin)->BSRR = GetPin(pin);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::ResetPin(Pin pin)
{
    GetPort(pin)->BSRR = (uint)GetPin(pin) << 16;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::LoadTShift()
{
    int pred = ~(2);
    int post = ~((1 << 13) - 1);

    FSMC::WriteToFPGA16(WR_PRED_LO, (uint16)pred);
    FSMC::WriteToFPGA16(WR_POST_LO, (uint16)post);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetRShift(Channel ch, uint16 rShift)
{
    Limitation<uint16>(&rShift, RShiftMin, RShiftMax);
    SET_RSHIFT(ch) = rShift;
    LoadRShift(ch);
}

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4310)
#endif

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::LoadTBase()
{
    static const uint8 values[TBaseSize] =
    {
        BIN_U8(00000000),    // 2ns     1       200MHz
        BIN_U8(00000000),    // 5ns     1       200MHz
        BIN_U8(00000000),    // 10ns    1       200MHz
        BIN_U8(00000000),    // 20ns    1       200MHz
        BIN_U8(00000000),    // 50ns    1       200MHz
        BIN_U8(00000000),    // 100ns   1       200MHz
        BIN_U8(00100000),    // 200ns   2       100MHz
        BIN_U8(00100001),    // 500ns   5       40MHz
        BIN_U8(00100010),    // 1us     10      20MHz
        BIN_U8(00100011),    // 2us     20      10MHz
        BIN_U8(01000101),    // 5us     50      4MHz
        BIN_U8(01000110),    // 10us    100     2MHz
        BIN_U8(01000111),    // 20us    200     1MHz
        BIN_U8(01001001),    // 50us    500     400kHz
        BIN_U8(01001010),    // 100us   1k      200kHz
        BIN_U8(01001011),    // 200us   2k      100kHz
        BIN_U8(01001101),    // 500us   5k      40kHz
        BIN_U8(01001110),    // 1ms     10k     20kHz
        BIN_U8(01001111),    // 2ms     20k     10kHz
        BIN_U8(01010001),    // 5ms     50k     4kHz
        BIN_U8(01010010),    // 10ms    100k    2kHz
        BIN_U8(01010011),    // 20ms    200k    1kHz
        BIN_U8(01010101),    // 50ms    500k    400Hz
        BIN_U8(01010110),    // 100ms   1M      200Hz
        BIN_U8(01010111),    // 200ms   2M      100Hz
        BIN_U8(01011001),    // 500ms   5M      40Hz
        BIN_U8(01011010),    // 1s      10M     20Hz
        BIN_U8(01011011),    // 2s      20M     10Hz
        BIN_U8(01011101),    // 5s      50M     4Hz
        BIN_U8(01011110)     // 10s     100M    2Hz
    };

    memset(&dataRand[0][0], 0, FPGA_MAX_POINTS * 2);

    FSMC::WriteToFPGA8(WR_TBASE, values[SET_TBASE]);
}

#ifdef _WIN32
#pragma warning(pop)
#endif

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::LoadTrigMode()
{

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::LoadTrigInput()
{
    LoadTrigSourceInput();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::LoadTrigSource()
{
    LoadTrigSourceInput();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::LoadTrigPolarity()
{

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::LoadTrigSourceInput()
{
    static const uint8 datas[3][2] =
    {//       A                 B
        {BIN_U8(00000010), BIN_U8(00000100)}, // ПС
        {BIN_U8(00000000), BIN_U8(00000110)}, // ВЧ
        {BIN_U8(00000011), BIN_U8(00000101)}  // НЧ
    };
    
    WritePin(A1S, _GET_BIT(datas[TRIG_INPUT][TRIG_SOURCE], 2));
    WritePin(A0S, _GET_BIT(datas[TRIG_INPUT][TRIG_SOURCE], 1));
    WritePin(LFS, _GET_BIT(datas[TRIG_INPUT][TRIG_SOURCE], 0));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::FindAndSetTrigLevel()
{
    if (Storage::NumElementsInStorage() == 0 || TRIGSOURCE_IS_EXT)
    {
        return;
    }

    uint16 *dataA = 0;
    uint16 *dataB = 0;
    DataSettings *ds_ = 0;

    Storage::GetDataFromEnd_RAM(0, &ds_, &dataA, &dataB);

    const uint16 *data = TRIGSOURCE_IS_A ? dataA : dataB;

    int lastPoint = NUM_BYTES(ds_) - 1;

    uint8 min = Math::MinFromArray_RAM(data, 0, lastPoint);
    uint8 max = Math::MaxFromArray_RAM(data, 0, lastPoint);

    uint8 aveValue = (uint8)(((int)min + (int)max) / 2);

    static const float scale = (float)(TrigLevMax - TrigLevZero) / (float)(MAX_VALUE - AVE_VALUE) / 2.4f;

    int trigLev = (int)(TrigLevZero + scale * ((int)aveValue - AVE_VALUE) - (SET_RSHIFT(TRIGSOURCE) - RShiftZero));

    SetTrigLev(TRIGSOURCE, (uint16)trigLev);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetTrigPolarity(TrigPolarity)
{
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetTrigSource(TrigSource)
{
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetTrigInput(TrigInput)
{
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetTBase(TBase tBase)
{
    if (!SET_ENABLED_A && !SET_ENABLED_B)
    {
        return;
    }
    if (tBase < TBaseSize && (int)tBase >= 0)
    {
        float tShiftAbsOld = TSHIFT_2_ABS(SET_TSHIFT, SET_TBASE);
        sTime_SetTBase(tBase);
        LoadTBase();
        if (LINKING_TSHIFT == LinkingTShift_Time)
        {
            SetTShift((int)TSHIFT_2_REL(tShiftAbsOld, SET_TBASE));
        }
        NEED_FINISH_DRAW = 1;
    }
    else
    {
        Display::ShowWarning(LimitSweep_Time);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetPeackDetMode(PeakDetMode peackDetMode)
{
    SET_PEAKDET = peackDetMode;
    LoadRegUPR();
    LoadTBase();
    LoadTShift();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::LoadRegUPR()
{
    uint16 data = 0;
    if (IN_RANDOM_MODE)
    {
        _SET_BIT(data, 0);
    }

    const uint16 mask[3] =
    {
        (1 << UPR_BIT_CALIBRATOR_AC_DC),
        (1 << UPR_BIT_CALIBRATOR_VOLTAGE),
        (0)
    };

    data |= mask[CALIBRATOR_MODE];

    if (RECORDER_MODE)
    {
        data |= (1 << UPR_BIT_RECORDER);
    }

    if (SET_PEAKDET_EN)
    {
        data |= (1 << UPR_BIT_PEAKDET);
    }

    Write(RecordFPGA, (uint16 *)WR_UPR, data, false);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::EnableRecorderMode(bool)
{
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetCalibratorMode(CalibratorMode)
{
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetTrigLev(TrigSource ch, uint16 trigLev)
{
    Display::ChangedRShiftMarkers(true);
    if (trigLev < TrigLevMin || trigLev > TrigLevMax)
    {
        Display::ShowWarning(LimitSweep_Level);
    }
    LIMITATION(trigLev, TrigLevMin, TrigLevMax);

    Display::RotateTrigLev();

    if (SET_TRIGLEV(ch) != trigLev)
    {
        SET_TRIGLEV(ch) = trigLev;
        LoadTrigLev();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool FPGA::IsRunning()
{
    return isRunning;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::Reset()
{
    bool needStart = IsRunning();
    Stop(false);
    if (needStart)
    {
        Start();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetBandwidth(Channel ch)
{
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetModeCouple(Channel ch, ModeCouple modeCoupe)
{
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool FPGA::ProcessingData()
{
    bool retValue = false;                          // Здесь будет true, когда данные считаются

    static const int numRead[] = {100, 50, 20, 10, 5};

    int num = IN_RANDOM_MODE ? numRead[SET_TBASE] / 2 : 1;

    if (IN_RANDOM_MODE)
    {
        dataRandA = (uint8 *)AllocMemForChannelFromHeap(A, 0);
        dataRandB = (uint8 *)AllocMemForChannelFromHeap(B, 0);

        if (SAMPLE_TYPE_IS_REAL)
        {
            num = 1;                                // Для реальной выборки ограничим количество считываний - нам надо только одно измерение.
        }
    }

    for (int i = 0; i < num; i++)
    {
        uint16 flag = ReadFlag();

        if (_GET_BIT(flag, FL_PRED_READY) == 0)       // Если предзапуск не отсчитан - выходим
        {
            break;
        }

        if (timeCompletePredTrig == 0)              // Если окончание предзапуска ранее не было зафиксировано
        {
            timeCompletePredTrig = TIME_MS;         // записываем время, когда оно произошло.
        }

        if (i > 0)
        {
            uint time = TIME_MS;
            // В рандомизаторных развёртках при повторных считываниях нужно подождать флага синхронизации
            while (_GET_BIT(flag, FL_TRIG_READY) == 0 && _GET_BIT(flag, FL_DATA_READY) == 0 && (TIME_MS - time) < 10)
            {                                                       // Это нужно для низких частот импульсов на входе
                flag = ReadFlag();
            }
            if (_GET_BIT(flag, FL_DATA_READY) == 0)
            {
                i = num;
            }
        }

        if (_GET_BIT(flag, FL_TRIG_READY))                            // Если прошёл импульс синхронизации
        {
            if (_GET_BIT(flag, FL_DATA_READY) == 1)                   // Проверяем готовность данных
            {
                fpgaStateWork = StateWorkFPGA_Stop;                 // И считываем, если данные готовы
                HAL_NVIC_DisableIRQ(EXTI2_IRQn);                    // Отключаем чтение точек
                DataReadSave(i == 0, i == num - 1, false);
                ProcessingAfterReadData();
                retValue = true;
            }
        }
        else if (START_MODE_AUTO)  // Если имупльса синхронизации нету, а включён автоматический режим синхронизации
        {
            if (TIME_MS - timeCompletePredTrig > TSHIFT_2_ABS(2, SET_TBASE) * 1000) // Если прошло больше времени, чем помещается в десяти клетках
            {
                if (IN_P2P_MODE)
                {
                }
                else
                {
                    SwitchingTrig();                                           // В непоточечном даём принудительно даём синхронизацю
                }
            }
        }

        if (i == num)
        {
            DataReadSave(false, true, true);
            retValue = true;
            break;
        }

        if (PANEL_CONTROL_RECEIVE && IN_RANDOM_MODE)
        {
            DataReadSave(false, true, true);
            retValue = true;
            break;
        }
    }

    SAFE_FREE(dataRandA);
    SAFE_FREE(dataRandB);

    return retValue;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void InverseDataIsNecessary(Channel ch, uint8 *data)
{
    if (SET_INVERSE(ch))
    {
        for (int i = 0; i < FPGA_MAX_POINTS; i++)
        {
            data[i] = (uint8)((int)(2 * AVE_VALUE) - LimitationRet<uint8>(data[i], MIN_VALUE, MAX_VALUE));
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::DataReadSave(bool first, bool saveToStorage, bool onlySave)
{
    // В этой функции испльзуем память, предназначенную для хранения выходного сигнала, в качестве временного буфера.

    FPGA_IN_PROCESS_OF_READ = 1;
    if (IN_RANDOM_MODE)
    {
        ReadRandomizeModeSave(first, saveToStorage, onlySave);
    }
    else
    {
        ReadRealMode(OUT_A, OUT_B);
    }

    int numBytes = ds.BytesInChannel();

    //CPU::RAM::MemCpy16(RAM8(FPGA_DATA_A), OUT_A, numBytes);
    //CPU::RAM::MemCpy16(RAM8(FPGA_DATA_B), OUT_B, numBytes);

    for (int i = 0; i < numBytes; i++)
    {
        LIMITATION(OUT_A[i], MIN_VALUE, MAX_VALUE);
        LIMITATION(OUT_B[i], MIN_VALUE, MAX_VALUE);
    }

    if (!IN_RANDOM_MODE)
    {
        InverseDataIsNecessary(A, OUT_A);
        InverseDataIsNecessary(B, OUT_B);
    }

    if (saveToStorage)
    {
        Storage::AddData(OUT_A, OUT_B, ds);
    }

    if (TRIG_MODE_FIND_AUTO)
    {
        FindAndSetTrigLevel();
    }

    FPGA_IN_PROCESS_OF_READ = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::ProcessingAfterReadData()
{
    if (!START_MODE_SINGLE)
    {
        if (IN_P2P_MODE && START_MODE_AUTO)                              // Если находимся в режиме поточечного вывода при автоматической синхронизации
        {
            if (!NEED_STOP_AFTER_READ_FRAME_2P2)
            {
                Timer::SetAndStartOnce(kTimerStartP2P, FPGA::Start, 1000);    // то откладываем следующий запуск, чтобы зафиксировать сигнал на экране
            }
        }
        else
        {
            Start();
        }
    }
    else
    {
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SwitchingTrig()
{
    if (TRIG_POLARITY_FRONT)
    {
        *WR_TRIG = 0;
        *WR_TRIG = 1;
    }
    else
    {
        *WR_TRIG = 1;
        *WR_TRIG = 0;
    }
    timeSwitchingTrig = TIME_MS;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static uint16 READ_DATA_ADC_16(const uint16 *address, Channel ch)
{
    float delta = AVE_VALUE - (RShiftZero - SET_RSHIFT(ch)) / (RSHIFT_IN_CELL / 20.0f);
    BitSet16 point;
    BitSet16 retValue;
    point.halfWord = *address;
    int byte0 = (int)(((float)point.byte[0] - delta) * GetStretchADC(ch) + delta + 0.5f);
    LIMITATION(byte0, 0, 255);
    retValue.byte0 = (uint8)byte0;
    int byte1 = (int)(((float)point.byte[1] - delta) * GetStretchADC(ch) + delta + 0.5f);
    LIMITATION(byte1, 0, 255);
    retValue.byte1 = (uint8)byte1;
    return retValue.halfWord;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void ReadRandomizeChannel(Channel ch, uint16 addrFirstRead, uint8 *data, const uint8 *last, int step, int numSkipped)
{
//    *WR_PRED = addrFirstRead;
//    *WR_ADDR_NSTOP = 0xffff;

    uint16 *addr = ADDRESS_READ(ch);

    uint16 newData = 0;

    for (int i = 0; i < numSkipped; i++)
    {
        newData = *addr;
    }

    if (SET_INVERSE(ch))
    {
        while (data <= last)
        {
            newData = READ_DATA_ADC_16(addr, ch);
            *data = (uint8)((int)(2 * AVE_VALUE) - LimitationRet<uint8>((uint8)newData, MIN_VALUE, MAX_VALUE));
            data += step;
        }
    }
    else
    {
        while (data <= last)
        {
            *data = (uint8)READ_DATA_ADC_16(addr, ch);
            data += step;
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool FPGA::ReadRandomizeModeSave(bool first, bool last, bool onlySave)
{
    int bytesInChannel = ds.BytesInChannel();

    if (first)
    {
        memset(dataRandA, 0, (uint)bytesInChannel);
        memset(dataRandB, 0, (uint)bytesInChannel);
    }

    if (!onlySave)
    {
        int Tsm = CalculateShift();

        // Считываем из внешнего ОЗУ ранее записанные туда данные
        // Буфера dataRandA, dataRandB созданы заранее для ускорения, т.к. в режиме рандомизатора в FPGA_Update() выполняется несколько чтений
        if (first)
        {
            if (ENABLED_DS_A)
            {
                memcpy(dataRandA, OUT_A, (uint)bytesInChannel);
            }
            if (ENABLED_DS_B)
            {
                memcpy(dataRandB, OUT_B, (uint)bytesInChannel);
            }
        }

        if (Tsm == NULL_TSHIFT)
        {
            return false;
        };

        if (START_MODE_SINGLE || SAMPLE_TYPE_IS_REAL)
        {
            ClearData();

            // Очищаем массив для данных. После чтения точек несчитанные позиции будут равны нулю, что нужно для экстраполяции
            memset(dataRandA, 0, (uint)bytesInChannel);
            memset(dataRandB, 0, (uint)bytesInChannel);
        }

        // Теперь считаем данные
        TBase tBase = SET_TBASE;
        int step = Kr[tBase];
#define NUM_ADD_STEPS 2
        int index = Tsm - addShiftForFPGA - NUM_ADD_STEPS * step;

        int numSkipped = 0;

        while (index < 0)
        {
            index += step;
            numSkipped++;
        }

        // addrFirstRead - адрес, который мы должны записать в альтеру. Это адрес, с которого альтера начнёт чтение данных
        // Но считывать будем с адреса на 3 меньшего, чем расчётный. Лишние данные нужны, чтобы достроить те точки вначале, 
        // которые выпадают при программном сдвиге.
        // Процедуре чтения мы укажем сколько первых точек выбросить через параметр numSkipped
//        uint16 addrFirstRead = (uint16)(*RD_ADDR_NSTOP + 16384 - (uint16)(bytesInChannel / step) - 1 - NUM_ADD_STEPS);
        uint16 addrFirstRead = 0;

        //uint startRead = gTimerTics;

        ReadRandomizeChannel(B, addrFirstRead, &dataRandB[index], &dataRandB[FPGA_MAX_POINTS - 1], step, numSkipped);
        ReadRandomizeChannel(A, addrFirstRead, &dataRandA[index], &dataRandA[FPGA_MAX_POINTS - 1], step, numSkipped);

        if (START_MODE_SINGLE || SAMPLE_TYPE_IS_REAL)
        {
            Processing::InterpolationSinX_X(dataRandA, bytesInChannel, tBase);
            Processing::InterpolationSinX_X(dataRandB, bytesInChannel, tBase);
        }
    }

    // Теперь сохраняем данные обратно во внешнее ОЗУ
    if (last)
    {
//        CPU::RAM::MemCpy16(dataRandA, RAM8(FPGA_DATA_A), bytesInChannel);
//        CPU::RAM::MemCpy16(dataRandB, RAM8(FPGA_DATA_B), bytesInChannel);
    }

    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void ShiftOnePoint2Right(uint8 *data, int size)
{
    for (int i = size - 1; i >= 1; i--)
    {
        data[i] = data[i - 1];
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
// balance - свдиг точки вверх/вниз для балансировки
static void ReadChannel(uint8 *data, Channel ch, int length, uint16 nStop, bool shift, int balance)
{
    if (length == 0)
    {
        return;
    }
//    *WR_PRED = nStop;
//    *WR_ADDR_NSTOP = 0xffff;

    uint16 *p = (uint16 *)data;
    uint16 *endP = (uint16 *)&data[length];

    uint16 *address = ADDRESS_READ(ch);

    nStop = *address;

    if (shift)
    {
        *((uint8 *)p) = (uint8)(*address);

        p = (uint16 *)(((uint8 *)p) + 1);
        endP -= 8;                          // Это нужно, чтбы не выйти за границу буфера - ведь мы сдвигаем данные на один байт
    }

    while (p < endP && FPGA_IN_PROCESS_OF_READ)
    {
        *p++ = READ_DATA_ADC_16(address, ch);
        *p++ = READ_DATA_ADC_16(address, ch);
        *p++ = READ_DATA_ADC_16(address, ch);
        *p++ = READ_DATA_ADC_16(address, ch);
        *p++ = READ_DATA_ADC_16(address, ch);
        *p++ = READ_DATA_ADC_16(address, ch);
        *p++ = READ_DATA_ADC_16(address, ch);
        *p++ = READ_DATA_ADC_16(address, ch);
    }

    if (shift)                              ///  \todo Во-первых, теряется один байт. Во-вторых, не очень-то красиво выглядит
    {
        while (p < (uint16 *)&data[length - 1])
        {
            *p++ = READ_DATA_ADC_16(address, ch);
        }
    }

    if (balance != 0)
    {
        for (int i = shift ? 1 : 0; i < length; i += 2)
        {
            int newData = (int)data[i] + balance;
            if (newData < 0)
            {
                newData = 0;
            }
            if (newData > 255)
            {
                newData = 255;
            }
            data[i] = (uint8)newData;
        }
    }

    ShiftOnePoint2Right(data, length);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::ReadRealMode(uint8 *dataA, uint8 *dataB)
{
    FPGA_IN_PROCESS_OF_READ = 1;

    uint16 nStop = ReadNStop();

    bool shift = _GET_BIT(ReadFlag(), FL_LAST_RECOR) == 0;    // Если true, будем сдвигать точки на одну

    int balanceA = 0;
    int balanceB = 0;

    if (NRST_BALANCE_ADC_TYPE_IS_HAND &&
        SET_PEAKDET_DIS)               // При включённом пиковом детекторе балансировка не нужна
    {
        balanceA = NRST_BALANCE_ADC_A;
        balanceB = NRST_BALANCE_ADC_B;
    }

    ReadChannel(dataA, A, ds.BytesInChannel(), nStop, shift, balanceA);

    ReadChannel(dataB, B, ds.BytesInChannel(), nStop, shift, balanceB);

//    CPU::RAM::MemCpy16(dataA, RAM8(FPGA_DATA_A), FPGA_MAX_POINTS);
//    CPU::RAM::MemCpy16(dataB, RAM8(FPGA_DATA_B), FPGA_MAX_POINTS);

    FPGA_IN_PROCESS_OF_READ = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::ClearData()
{
//    CPU::RAM::MemClear(RAM8(FPGA_DATA_A), FPGA_MAX_POINTS);
//    CPU::RAM::MemClear(RAM8(FPGA_DATA_B), FPGA_MAX_POINTS);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
uint16 FPGA::ReadNStop()
{
//    return (uint16)(*RD_ADDR_NSTOP + 16384 - (uint16)ds.BytesInChannel() / 2 - 1 - (uint16)gAddNStop);
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::Write(TypeRecord type, uint16 *address, uint data, bool restart)
{
    /*
    // Если необходимо, сохраняем установленный режим на шине, чтобы затем его восстановить
    ModeFSMC modePrev = FSMC::GetMode();
    bool needRestore = modePrev != ModeFSMC_FPGA;
    if (type == RecordFPGA && needRestore)
    {
        FSMC::SetMode(ModeFSMC_FPGA);
    }


    FPGA_FIRST_AFTER_WRITE = 1;
    if (restart)
    {
        if (FPGA_IN_PROCESS_OF_READ)
        {
            Stop(true);
            FPGA_IN_PROCESS_OF_READ = 0;
            Write(type, address, data);
            Start();
        }
        else
        {
            if (!FPGA_IN_STATE_STOP)
            {
                Stop(true);
                Write(type, address, data);
                Start();
            }
            else
            {
                Write(type, address, data);
            }
        }
    }
    else
    {
        Write(type, address, data);
    }


    // Восстанавливаем предыдущий режим на шине, если необходимо.
    if (type == RecordFPGA && needRestore)
    {
        FSMC::SetMode(modePrev);
    }

    Panel::EnableLEDTrig(false); // После каждой засылки выключаем лампочку синхронизации
    */
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetTShift(int tShift)
{
    SetTShift(tShift, true);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetTShift(int tShift, bool needFPGApause)
{
    if (!SET_ENABLED_A && !SET_ENABLED_B)
    {
        return;
    }

    if (tShift < sTime_TShiftMin() || tShift > TShiftMax)
    {
        LIMITATION(tShift, sTime_TShiftMin(), TShiftMax);
        Display::ShowWarning(LimitSweep_TShift);
    }

    int16 oldTShift = (int16)SET_TSHIFT;

    sTime_SetTShift((int16)tShift);
    LoadTShift();       /// \todo temp for s8-54
    NEED_FINISH_DRAW = 1;

    if (needFPGApause && tShift != oldTShift)
    {
        TemporaryPause();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void StopTemporaryPause()
{
    FPGA_IN_PAUSE = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::TemporaryPause()
{
    FPGA_IN_PAUSE = 1;
    Timer::SetAndStartOnce(kTemporaryPauseFPGA, StopTemporaryPause, 100);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::OnPressStartStop()
{
    if (!MODE_WORK_IS_DIR || CONSOLE_IN_PAUSE)           // Если находимся не в режиме непосредственного считывания сигнала
    {
        return;
    }

    if (IN_P2P_MODE)
    {
        OnPressStartStopInP2P();
    }
    else if (FPGA_IN_STATE_STOP)
    {
        Start();
        fpgaStateWork = StateWorkFPGA_Wait;
    }
    else
    {
        Stop(false);
        fpgaStateWork = StateWorkFPGA_Stop;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::OnPressStartStopInP2P()
{
    if (Timer::IsRun(kTimerStartP2P))             // Если находимся в режиме поточечного вывода и в данный момент пауза после считывания очередного 
    {                                           // полного сигнала
        Timer::Disable(kTimerStartP2P);          // то останавливаем таймер, чтобы просмотреть сигнал
    }
    else                                        // Если идёт процесс сбора информации
    {
        if (FPGA_IN_STATE_STOP)
        {
            Start();
        }
        else
        {   // то устанавливаем признак того, что после окончания не надо запускать следующий цикл
            NEED_STOP_AFTER_READ_FRAME_2P2 = NEED_STOP_AFTER_READ_FRAME_2P2 == 0 ? 1u : 0u;
            Stop(false);
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetTPos(TPos tPos)
{
    TPOS = tPos;
    PageTime::OnChanged_TPos(true);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetRange(Channel ch, Range range)
{
    if (!SET_ENABLED(ch))
    {
        return;
    }
    if (range < RangeSize && (int)range >= 0)
    {
        float rShiftAbs = RSHIFT_2_ABS(SET_RSHIFT(ch), SET_RANGE(ch));
        float trigLevAbs = RSHIFT_2_ABS(SET_TRIGLEV(ch), SET_RANGE(ch));
        sChannel_SetRange(ch, range);
        if (LINKING_RSHIFT == LinkingRShift_Voltage)
        {
            SET_RSHIFT(ch) = (uint16)RSHIFT_2_REL(rShiftAbs, range);
            SET_TRIGLEV(ch) = (uint16)RSHIFT_2_REL(trigLevAbs, range);
        }
        LoadRange(ch);
        LoadTrigLev();
    }
    else
    {
        Display::ShowWarning(ch == A ? LimitChan1_Volts : LimitChan2_Volts);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::LoadRange(Channel ch)
{
    /*
    PrepareAndWriteDataToAnalogSPI(ch == A ? CS3 : CS4);
    PrepareAndWriteDataToAnalogSPI(CS2);

    LoadRShift(ch);
    if (ch == (Channel)TRIGSOURCE)
    {
        LoadTrigLev();
    }
    */
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetResistance(Channel ch, Resistance resistance)
{
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetDeltaTShift(int16 shift)
{
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetNumberMeasuresForGates(int number)
{
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
// Функция вызывается, когда можно считывать очередной сигнал.
static void OnTimerCanReadData()
{
    FPGA_CAN_READ_DATA = 1;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetENumSignalsInSec(int numSigInSec)
{
    Timer::SetAndEnable(kENumSignalsInSec, OnTimerCanReadData, (uint)(1000.f / numSigInSec));
}
















#ifdef __cplusplus
extern "C" {
#endif

void ADC_IRQHandler();
    
//----------------------------------------------------------------------------------------------------------------------------------------------------
void ADC_IRQHandler(void)
{
    HAL_ADC_IRQHandler(&hADC);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    adcValueFPGA = (uint16)HAL_ADC_GetValue(hadc);
//    LOG_WRITE("%d", adcValueFPGA);
}

#ifdef __cplusplus
}
#endif


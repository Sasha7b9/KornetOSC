#include "defines.h"
#include "CPU.h"
#include "Hardware/Timer.h"
#include "Multimeter/Multimeter.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define VALUE_FOR_RTC 0x644


#define RTC_CLOCK_SOURCE_LSE
// #define RTC_CLOCK_SOURCE_LSI


#ifdef RTC_CLOCK_SOURCE_LSI
#define RTC_ASYNCH_PREDIV 0x7f
#define RTC_SYNCH_PREDIV 0x0130
#endif

#ifdef RTC_CLOCK_SOURCE_LSE
#define RTC_ASYNCH_PREDIV 0x7f
#define RTC_SYNCH_PREDIV 0x00ff
#endif

static RTC_HandleTypeDef rtcHandle =
{
    RTC,
    {
        RTC_HOURFORMAT_24,          // HourFormat
        RTC_ASYNCH_PREDIV,          // AsynchPrediv
        RTC_SYNCH_PREDIV,           // SynchPrediv
        RTC_OUTPUT_DISABLE,         // OutPut
        RTC_OUTPUT_POLARITY_HIGH,   // OutPutPolarity
        RTC_OUTPUT_TYPE_OPENDRAIN   // OutPutType
    }
};

UART_HandleTypeDef CPU::UART::handler;

static uint8 bufferUART[CPU::UART::SIZE_BUFFER];


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CPU::Init()
{
    UART::Init();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void CPU::RTC_::SetCorrection(int8)
{
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
PackedTime CPU::RTC_::GetPackedTime()
{
    PackedTime time;

    RTC_TimeTypeDef isTime;

    HAL_RTC_GetTime((RTC_HandleTypeDef*)&rtcHandle, &isTime, FORMAT_BIN);

    time.hours = isTime.Hours;
    time.minutes = isTime.Minutes;
    time.seconds = isTime.Seconds;

    RTC_DateTypeDef isDate;
    HAL_RTC_GetDate((RTC_HandleTypeDef*)&rtcHandle, &isDate, FORMAT_BIN);

    time.year = isDate.Year;
    time.month = isDate.Month;
    time.day = isDate.Date;

    time.timeMS = TIME_MS;

    return time;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool CPU::RTC_::SetTimeAndData(int8 day, int8 month, int8 year, int8 hours, int8 minutes, int8 seconds)
{
    RTC_DateTypeDef dateStruct;
    dateStruct.WeekDay = RTC_WEEKDAY_MONDAY;
    dateStruct.Month = (uint8)month;
    dateStruct.Date = (uint8)day;
    dateStruct.Year = (uint8)year;

    if (HAL_RTC_SetDate((RTC_HandleTypeDef*)&rtcHandle, &dateStruct, FORMAT_BIN) != HAL_OK)
    {
        return false;
    };

    RTC_TimeTypeDef timeStruct;
    timeStruct.Hours = (uint8)hours;
    timeStruct.Minutes = (uint8)minutes;
    timeStruct.Seconds = (uint8)seconds;
    timeStruct.TimeFormat = RTC_HOURFORMAT_24;
    timeStruct.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    timeStruct.StoreOperation = RTC_STOREOPERATION_SET;

    if (HAL_RTC_SetTime((RTC_HandleTypeDef*)&rtcHandle, &timeStruct, FORMAT_BIN) != HAL_OK)
    {
        return false;
    };

    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void CPU::UART::Init()
{
    handler.Instance = USART3;
    handler.Init.BaudRate = 9600;
    handler.Init.WordLength = UART_WORDLENGTH_8B;
    handler.Init.StopBits = UART_STOPBITS_1;
    handler.Init.Parity = UART_PARITY_NONE;
    handler.Init.Mode = UART_MODE_TX_RX;
    handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    handler.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&handler) != HAL_OK)
    {
        ERROR_HANDLER();
    }

    uint8 send[4] = {0x02, 'V', '0', 0x0a};

    HAL_UART_Transmit(&handler, send, 4, 10);

    if (HAL_UART_Receive_IT(&handler, bufferUART, SIZE_BUFFER) != HAL_OK)
    {
        ERROR_HANDLER();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *handler)
{
    Multimeter::SetMeasure(bufferUART);

    if(HAL_UART_Receive_IT(handler, bufferUART, CPU::UART::SIZE_BUFFER) != HAL_OK)
    {
        ERROR_HANDLER();
    }
}

#include "Keyboard.h"
#include "Display/Display.h"
#include "Hardware/CPU.h"
#include "Utils/Decoder.h"
#include "Hardware/FSMC.h"
#include "Hardware/Timer.h"
#include "Utils/Math.h"
#include "stm32f4xx_it.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static TIM_HandleTypeDef handleTIM4;

#define SL0 GPIO_PIN_12
#define SL1 GPIO_PIN_13
#define SL2 GPIO_PIN_14
#define SL3 GPIO_PIN_15
#define SL4 GPIO_PIN_8
#define SL5 GPIO_PIN_9
#define SL6 GPIO_PIN_8
#define SL7 GPIO_PIN_9

#define RL0 GPIO_PIN_8
#define RL1 GPIO_PIN_9
#define RL2 GPIO_PIN_10
#define RL3 GPIO_PIN_13
#define RL4 GPIO_PIN_12
#define RL5 GPIO_PIN_11

static const Control controls[Keyboard::NUM_RL][Keyboard::NUM_SL] =
  
{ // SL0         SL1        SL2            SL3            SL4            SL6            SL5           SL7
    {B_1,        B_4,       B_Right,       B_Enter,       B_Start,       B_RangeMoreB,  B_Trig,       B_RShiftLessB},  // RL1
    {B_2,        B_5,       B_Up,          B_Left,        B_None,        B_None,        B_None,       B_ChannelB},     // RL2
    {B_Measures, B_None,    B_ChannelA,    B_None,        B_TBaseMore,   B_None,        B_TShiftMore, B_None},         // RL4
    {B_None,     B_3,       B_Down,        B_None,        B_TrigLevLess, B_RangeLessB,  B_TrigLevMore,B_RShiftMoreB},  // RL0
    {B_Memory,   B_Display, B_RShiftMoreA, B_RShiftLessA, B_Time,        B_None,        B_TBaseLess,  B_None},         // RL5
    {B_Function, B_Service, B_RangeLessA,  B_RangeMoreA,  B_None,        B_None,        B_TShiftLess, B_None}          // RL3
};               



static uint16 sls[Keyboard::NUM_SL]             = {SL2,   SL1,   SL3,   SL0,   SL4,   SL5,   SL6,   SL7};
static GPIO_TypeDef* slsPorts[Keyboard::NUM_SL] = {GPIOB, GPIOB, GPIOB, GPIOB, GPIOD, GPIOD, GPIOC, GPIOC};

static uint16 rls[Keyboard::NUM_RL]             = {RL0,   RL1,   RL2,   RL3,   RL4,   RL5};
static GPIO_TypeDef* rlsPorts[Keyboard::NUM_RL] = {GPIOA, GPIOA, GPIOA, GPIOD, GPIOD, GPIOD};

#define SET_SL(n)   HAL_GPIO_WritePin(slsPorts[n], sls[n], GPIO_PIN_SET);
#define SET_ALL_SL  HAL_GPIO_WritePin(GPIOB, SL0 | SL1 | SL2 | SL3, GPIO_PIN_SET);  \
                    HAL_GPIO_WritePin(GPIOC, SL6 | SL7 , GPIO_PIN_SET);             \
                    HAL_GPIO_WritePin(GPIOD, SL4 | SL5, GPIO_PIN_SET);
#define RESET_SL(n) HAL_GPIO_WritePin(slsPorts[n], sls[n], GPIO_PIN_RESET);
#define READ_RL(n)  HAL_GPIO_ReadPin(rlsPorts[n], rls[n]);

#define BUTTON_IS_PRESS(state) ((state) == 0)

/// Время последнего автонажатия нопки
static uint prevRepeat = 0;
static uint prevPause = 0;

int           Keyboard::pointer = 0;
bool          Keyboard::init = false;
StructControl Keyboard::commands[10];
uint          Keyboard::timePress[NUM_RL][NUM_SL];

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Keyboard::Init()
{
    for (int i = 0; i < NUM_RL; ++i)
    {
        for (int j = 0; j < NUM_SL; ++j)
        {
            timePress[i][j] = 0;
        }
    }

    GPIO_InitTypeDef isGPIO;

    // порты ввода
    isGPIO.Pin = RL0 | RL1 | RL2;
    isGPIO.Mode = GPIO_MODE_INPUT;
    isGPIO.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &isGPIO);

    isGPIO.Pin = RL3 | RL4 | RL5;
    HAL_GPIO_Init(GPIOD, &isGPIO);

    // порты вывода
    isGPIO.Pin = SL0 | SL1 | SL2 | SL3;
    isGPIO.Mode = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(GPIOB, &isGPIO);

    isGPIO.Pin = SL6 | SL7;
    HAL_GPIO_Init(GPIOC, &isGPIO);

    isGPIO.Pin = SL4 | SL5;
    HAL_GPIO_Init(GPIOD, &isGPIO);

    // Инициализируем таймер, по прерываниям которого будем опрашивать клавиатуру
    HAL_NVIC_SetPriority(TIM4_IRQn, 0, 1);

    HAL_NVIC_EnableIRQ(TIM4_IRQn);

    handleTIM4.Instance = TIM4;
    handleTIM4.Init.Period = TIME_UPDATE_KEYBOARD * 10 - 1;
    handleTIM4.Init.Prescaler = (uint)((SystemCoreClock / 2) / 10000) - 1;
    handleTIM4.Init.ClockDivision = 0;
    handleTIM4.Init.CounterMode = TIM_COUNTERMODE_UP;

    if (HAL_TIM_Base_Init(&handleTIM4) != HAL_OK)
    {
        ERROR_HANDLER();
    }

    if (HAL_TIM_Base_Start_IT(&handleTIM4) != HAL_OK)
    {
        ERROR_HANDLER();
    }

    SET_ALL_SL;

    init = true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Keyboard::Update()
{
    if (!init)
    {
        return;
    }
    pointer = 0;

    uint time = HAL_GetTick();

    for (int sl = 0; sl < NUM_SL; ++sl)
    {
        RESET_SL(sl);

        for (int rl = 0; rl < NUM_RL; ++rl)
        {
            uint state = READ_RL(rl);

            volatile Control control = controls[rl][sl];

            if (control != B_None)
            {
                if (timePress[rl][sl])                      // Если клавиша находится в нажатом положении
                {
                    if (time - timePress[rl][sl] > 100)     // Если прошло более 100 мс с момента нажатия
                    {
                        if (!BUTTON_IS_PRESS(state))        // Если сейчас кнопка находится в отжатом состояини
                        {
                            timePress[rl][sl] = 0;
                            FillCommand(controls[rl][sl], Release);
                            prevRepeat = 0;
                        }
                        else if(IsRepeatable(control))      // А здесь она нходится в нажатом положении - отрабатываем автоповтор
                        {
                            if (prevRepeat == 0)
                            {
                                prevRepeat = time;
                                prevPause = 100;
                            }
                            
                            if (prevRepeat + prevPause < time)
                            {
                                prevPause = TimeBetweenRepeats(prevPause);
                                prevRepeat = time;
                                FillCommand(controls[rl][sl], Repeat);
                            }
                        }
                    }
                }
                else if (BUTTON_IS_PRESS(state))
                {
                    timePress[rl][sl] = time;
                    FillCommand(controls[rl][sl], Press);
                    prevRepeat = 0;
                }
            }
        }

        SET_ALL_SL;
    }

    SET_ALL_SL;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Keyboard::FillCommand(Control control, TypePress typePress)
{
    commands[pointer].control = control;
    commands[pointer++].typePress = typePress;
    uint8 data[3] = {IN_BUTTON_PRESS, (uint8)control, (uint8)typePress};
    FSMC::WriteBuffer(data, 3);  // Прерывание от клавиатуры имеет более низкий приоритет, чем чтения по шине, поэтому запись не запустится до тех
                                 // пор, пока не закончится чтение
}   

//----------------------------------------------------------------------------------------------------------------------------------------------------
const char *Keyboard::ControlName(Control control)
{
    static const char *names[NumControls] =
    {
        "None",
        "Функция",
        "Измер",
        "Память",
        "Сервис",
        "Канал 1",
        "Канал 2",
        "Развертка",
        "Пуск/стоп",
        "Синхр",
        "Дисплей",
        "Range 1 больше",
        "Range 1 меньше",
        "RShift 1 больше",
        "RShift 1 меньше",
        "Range 2 больше",
        "Range 2 меньше",
        "RShift 2 больше",
        "RShift 2 меньше",
        "TBase больше",
        "TBase меньше",
        "TShift больше",
        "TShift меньше",
        "Синхр больше",
        "Синхр меньше",
        "Влево",
        "Вправо",
        "Вверх",
        "Вниз",
        "Ввод",
        "1",
        "2",
        "3",
        "4",
        "5"
    };

    return names[control];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool IsRepeatable(Control control)
{
    return control == B_RShiftLessA ||
        control == B_RShiftMoreA ||
        control == B_RShiftLessB ||
        control == B_RShiftMoreB ||
        control == B_TShiftLess ||
        control == B_TShiftMore ||
        control == B_TrigLevLess ||
        control == B_TrigLevMore;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
uint Keyboard::TimeBetweenRepeats(uint prev)
{
    uint retValue = (uint)(prev / 1.1f);

    if (retValue < 10)
    {
        retValue = 10;
    }

    return retValue;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

    void TIM4_IRQHandler();
        
    void TIM4_IRQHandler()
    {
        HAL_TIM_IRQHandler(&handleTIM4);
    }

#ifdef __cplusplus
}
#endif

//----------------------------------------------------------------------------------------------------------------------------------------------------
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &handleTIM4)
    {
        Keyboard::Update();
    }
}

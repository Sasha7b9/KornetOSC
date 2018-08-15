#include "HandlersKeys.h"
#include "Menu.h"
#include "Settings/Settings.h"
#include "FPGA/FPGA.h"
#include "Display/Console.h"
#include "Menu/Pages/Definition.h"
#include "Menu/Pages/PageMeasures.h"
#include "Menu/Pages/PageMemory.h"
#include "Menu/Pages/PageDisplay.h"
#include "Menu/Pages/PageService.h"
#include "Menu/Pages/PageTime.h"
#include "Menu/Pages/PageChannels.h"
#include "Menu/Pages/PageTrig.h"
#include "Log.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
KeyEvent Handlers::event;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Handlers::Process(KeyEvent e)
{
    event = e;

    static const pFuncVV func[Key::NumButtons][4] =
    {
        /* None        */ {E,           E,           E,        E},
        /* Function    */ {Function,    Function,    Function, Function},
        /* Measures    */ {Measures,    Measures,    Measures, Measures},
        /* Memory      */ {Memory,      Memory,      Memory,   Memory},
        /* Service     */ {Service,     Service,     Service,  Service},
        /* ChannelA    */ {ChannelA,    E,           E,        E},
        /* ChannelB    */ {ChannelB,    E,           E,        E},
        /* Time        */ {Time,        Time,        Time,     Time},
        /* Start       */ {Start,       Start,       Start,    Start},
        /* Trig        */ {Trig,        Trig,        Trig,     Trig},
        /* Display     */ {Display,     Display,     Display,  Display},
        /* RangeMoreA  */ {RangeMoreA,  E,           E,        E},
        /* RangeLessA  */ {RangeLessA,  E,           E,        E},
        /* RShiftMoreA */ {RShiftMoreA, RShiftMoreA, E,        E},
        /* RShiftLessA */ {RShiftLessA, RShiftLessA, E,        E},
        /* RangeMoreB  */ {RangeMoreB,  E,           E,        E},
        /* RangeLessB  */ {RangeLessB,  E,           E,        E},
        /* RShiftMoreB */ {RShiftMoreB, RShiftMoreB, E,        E},
        /* RShiftLessB */ {RShiftLessB, RShiftLessB, E,        E},
        /* TBaseMore   */ {TBaseMore,   E,           E,        E},
        /* TBaseLess   */ {TBaseLess,   E,           E,        E},
        /* TShiftMore  */ {TShiftMore,  TShiftMore,  E,        E},
        /* TShiftLess  */ {TShiftLess,  TShiftLess,  E,        E},
        /* TrigLevMore */ {TrigLevMore, TrigLevMore, E,        E},
        /* TrigLevLess */ {TrigLevLess, TrigLevLess, E,        E},
        /* Left        */ {Arrow,       Arrow,       Arrow,    Arrow},
        /* Right       */ {Arrow,       Arrow,       Arrow,    Arrow},
        /* Up          */ {Arrow,       Arrow,       Arrow,    Arrow},
        /* Down        */ {Arrow,       Arrow,       Arrow,    Arrow},
        /* Enter       */ {Enter,       E,           E,        E},
        /* F1          */ {Func,        Func,        Func,     Func},
        /* F2          */ {Func,        Func,        Func,     Func},
        /* F3          */ {Func,        Func,        Func,     Func},
        /* F4          */ {Func,        Func,        Func,     Func},
        /* F5          */ {Func,        Func,        Func,     Func}
    };

    uint8 code = event.key.code;
    uint8 type = event.type.type;

    if (code < Key::NumButtons && type < TypePress::None)
    {
        func[event.key.code][event.type.type]();
    }
    else
    {
        /// \tode Временная затычка. Доделать, чтобы такого не было
        //LOG_WRITE("Ошибка приёма команды кнопки");
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::E()
{
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::RShiftLessA()
{
    FPGA::RShiftChange(A, -1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::RShiftMoreA()
{
    FPGA::RShiftChange(A, 1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::RShiftLessB()
{
    FPGA::RShiftChange(B, -1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::RShiftMoreB()
{
    FPGA::RShiftChange(B, 1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::RangeLessA()
{
    FPGA::DecreaseRange(A);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::RangeMoreA()
{
    FPGA::IncreaseRange(A);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::RangeLessB()
{
    FPGA::DecreaseRange(B);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::RangeMoreB()
{
    FPGA::IncreaseRange(B);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::TShiftLess()
{
    FPGA::TShiftChange(-1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::TShiftMore()
{
    FPGA::TShiftChange(1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::TBaseLess()
{
    FPGA::DecreaseTBase();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::TBaseMore()
{
    FPGA::IncreaseTBase();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::Func()
{
    TypePress press = event.type;

    if(press.Is(TypePress::Press))
    {
        if (MENU_IS_SHOWN)
        {
            Control *control = (Control *)Menu::itemUnderButton[event.key.code];
            if (control)
            {
                control->ShortPress();
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::Arrow()
{
    Control *item = Menu::OpenedItem();

    Page *page = 0;
    TypePress type = event.type;

    if(IS_PAGE(item))
    {
        page = (Page *)item;
    }

    switch(event.key.code)
    {
        case Key::Left:
            if(page && type.Is(TypePress::Press))
            {
                page->ChangeOpened(-1);
            }
            break;
        case Key::Right:
            if(page && type.Is(TypePress::Press))
            {
                page->ChangeOpened(1);
            }
            break;
        case Key::Up:
            break;
        case Key::Down:
            break;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::Enter()
{
    TypePress press = event.type;

    if (press.Is(TypePress::Press))
    {
        if (!MENU_IS_SHOWN)
        {
            Menu::Show(true);
        }
        else
        {
            Menu::CloseOpenedItem();
        }
    }
    else if(press.Is(TypePress::Long))
    {
        Menu::Show(!MENU_IS_SHOWN);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::TrigLevLess()
{
    FPGA::TrigLevChange(-1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::TrigLevMore()
{
    FPGA::TrigLevChange(1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::ChannelA()
{
    //SET_ENABLED_A = !SET_ENABLED_A;

    OpenPage(PageChannelA::pointer);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::ChannelB()
{
    //SET_ENABLED_B = !SET_ENABLED_B;

    OpenPage(PageChannelB::pointer);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::Function()
{
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::Measures()
{
    OpenPage(PageMeasures::pointer);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::Memory()
{
    OpenPage(PageMemory::pointer);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::Service()
{
    OpenPage(PageService::pointer);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::Time()
{
    OpenPage(PageTime::pointer);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::Start()
{
    if (event.type.Is(TypePress::Press))
    {
        FPGA::OnPressStart();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::Trig()
{
    OpenPage(PageTrig::pointer);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::Display()
{
    OpenPage(PageDisplay::pointer);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Handlers::OpenPage(const PageBase *page)
{
    ((Page *)page)->SetCurrentPage();
    ((Page *)page)->Open(true);
    Menu::Show(true);
}

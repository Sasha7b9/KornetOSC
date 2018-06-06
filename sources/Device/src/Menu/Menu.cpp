#include "Menu.h"
#include "Globals.h"
#include "Display/Grid.h"
#include "Display/DisplayTypes.h"
#include "Display/Painter.h"
#include "FlashDrive/FlashDrive.h"
#include "FPGA/FPGA.h"
#include "Hardware/Sound.h"
#include "Hardware/Timer.h"
#include "Pages/Definition.h"
#include "Menu/Pages/PageCursors.h"
#include "Menu/Pages/PageDisplay.h"
#include "Menu/Pages/PageHelp.h"
#include "Menu/Pages/PageMemory.h"
#include "Menu/Pages/PageChannels.h"
#include "Settings/Settings.h"
#include "Utils/Math.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      Key Menu::shortPressureButton = K_None;
      Key Menu::longPressureButton = K_None;
      Key Menu::pressButton = K_None;
      Key Menu::releaseButton = K_None;
         Control *Menu::itemUnderKey = 0;
          pFuncVV Menu::funcAterUpdate = 0;
      Key Menu::bufferForButtons[SIZE_BUFFER_FOR_BUTTONS] = {K_None};
const Key Menu::sampleBufferForButtons[SIZE_BUFFER_FOR_BUTTONS] = {K_5, K_5, K_4, K_4, K_3, K_3, K_2, K_2, K_1, K_1};
         Control *Menu::itemUnderButton[NumButtons] = {0};
      const char *Menu::stringForHint = 0;
         Control *Menu::itemHint = 0;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Menu::Update()
{
    ProcessingShortPressureButton();
    ProcessingLongPressureButton();
    ProcessingPressButton();
    ProcessingReleaseButton();

    if (funcAterUpdate)
    {
        funcAterUpdate();
        funcAterUpdate = 0;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ShortPressureButton(Key button)
{
    if (!HINT_MODE_ENABLED)
    {
        if (button == K_Memory && FDRIVE_IS_CONNECTED && MODE_BTN_MEMORY_IS_SAVE)
        {
            NEED_SAVE_TO_FLASHDRIVE = 1;
        }

        shortPressureButton = button;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::LongPressureButton(Key button)
{
    if (!HINT_MODE_ENABLED)
    {
        longPressureButton = button;
        NEED_FINISH_DRAW = 1;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ProcessButtonForHint(Key button)
{
    if (button == K_Enter)
    {
        Menu::stringForHint = LANG_RU ?
            "������ ���� ��������� ��������� �������:\n"
            "1. ��� �������� ���� ������� ���� ������� � ���������� � ������� 0.5� ��������� ����.\n"
            "2. ��� �������� ���� ��������� ������ � ������� 0.5� ��������� ����.\n"
            "3. ��� ��������� \"������\x99����� �� ����\x99���������\" ������� ���������� �������� ����������� ������ ����. ���� ������� �������� "
            "�������� ��������, ���� �����������.\n"
            "4. ��� ��������� \"������\x99����� �� ����\x99�����������\" ������� ���������� �������� �������� ������ ����. ���� ������� �������� "
            "��������� � ������� ������, ���������� ������� �� ���������� ������� ����.\n"
            "5. ���� ���� ��������� � ������ ����� ������, �� ������� ��������� ��������."
            :
        "���� button performs the following functions:\n"
            "1. At the closed menu pressing or pressing with deduction during 0.5s opens the Menu::\n"
            "2. At the open menu deduction of the button during 0.5s closes the Menu::\n"
            "3. At control \"SERVICE\x99Mode btn MENU\x99\x43lose\" current becomes the page of the previous level of the Menu:: If the root page is "
            "current, the menu is closed.\n"
            "4. At control \"SERVICE\x99Mode btn MENU\x99Toggle\" current becomes the page of the current level of the Menu:: If the current page the "
            "last in the current level, happens transition to the previous level of the Menu::\n"
            "5. If the menu is in the mode of small buttons, pressing closes the page.";

    } 
    else if (button == K_Display)
    {
        Menu::stringForHint = LANG_RU ?
            "������ ������� ��������� ���� �������� �������."
            :
            "������� button opens the display settings Menu::";
    }
    else if (button == K_Memory)
    {
        Menu::stringForHint = LANG_RU ?
            "1. ��� ��������� \"������\x99����� ��\x99��� �� ������\x99����\" ��������� ���� ������ � �������.\n"
            "2. ��� ��������� \"������\x99����� ��\x99��� �� ������\x99����������\" ��������� ������ �� ����-����."
            :
            "1. When setting \"������-EXT\x99STORAGE\x99Mode btn MEMORY\x99Menu\" opens a menu of memory\n"
            "2. When setting \"������-EXT\x99STORAGE\x99Mode btn MEMORY\x99Save\" saves the signal to the flash drive";
    }
    else if (button == K_Measures)
    {
        Menu::stringForHint = LANG_RU ?
            "������ ����� ��������� ���� �������������� ���������."
            :
            "����� button opens a menu of automatic measurements.";
    }
    else if (button == K_Service)
    {
        Menu::stringForHint = LANG_RU ?
            "������ ������ ��������� ���� ��������� ������������."
            :
            "������ button opens a menu of service options.";
    }
    else if (button == K_Start)
    {
        Menu::stringForHint = LANG_RU ?
            "������ ����/�TO� ��������� � ������������� ������� ����� ����������."
            :
            "����/�TO� button starts and stops the process of gathering information.";
    }
    else if (button == K_ChannelA)
    {
        Menu::stringForHint = LANG_RU ?
            "1. ������ �����1 ��������� ���� �������� ������ 1.\n"
            "2. ������� � ��������� ������ �����1 � ������� 0.5� ������������� �������� ������ 1 �� ��������� 0�."
            :
            "1. �����1 button opens the settings menu of the channel 1.\n"
            "2. Pressing and holding the button �����1 for 0.5c for the offset of the vertical channel 1 0V.";
    }
    else if (button == K_ChannelB)
    {
        Menu::stringForHint = LANG_RU ?
            "1. ������ �����2 ��������� ���� �������� ������ 2.\n"
            "2. ������� � ��������� ������ �����2 � ������� 0.5� ������������� �������� ������ 2 �� ��������� 0�."
            :
            "1. �����2 button opens the settings menu of the channel 2.\n"
            "2. Pressing and holding the button �����2 for 0.5c for the offset of the vertical channel 2 0V.";
    }
    else if (button == K_Time)
    {
        Menu::stringForHint = LANG_RU ?
            "1. ������ ���� ��������� ���� �������� ���������.\n"
            "2. ������� � ��������� ������ ���� � ������� 0.5� ������������� �������� �� ����������� 0�."
            :
            "1. ���� button open the settings menu sweep.\n"
            "2. Pressing and holding the button ���� for 0.5s Is the offset horizontal 0s.";
    }
    else if (button == K_Trig)
    {
        Menu::stringForHint = LANG_RU ?
            "1. ������ ����� ��������� ���� �������� �������������.\n"
            "2. ������� � ��������� � ������� 0.5� ������ ����� ��� ��������� \"������\x99��� ���� �����\x99�����������\" ���������� �������������� "
            "��������� ������ �������������.\n"
            "3. ������� � ��������� � ������� 0.5� ������ ����� ��� ��������� \"������\x99��� ���� �����\x99����� ������\" ������������� ������� "
            "������������� 0�."
            :
            "1. ����� button opens a menu settings synchronization.\n"
            "2. Pressing and holding the button ����� for 0.5s when setting \"SERVICE\x99Mode long TRIG\x99\x41utolevel\" automatically adjust the "
            "trigger level.\n"
            "3. Pressing and holding the button ����� for 0.5s when setting \"SERVICE\x99Mode long TRIG\x99SReset trig level\" sets the trigger "
            "level 0V.";
    }
    else
    {
        shortPressureButton = button;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::PressButton(Key button)
{
    Sound::ButtonPress();
    if (HINT_MODE_ENABLED)
    {
        ProcessButtonForHint(button);
        return;
    }

    if (!MENU_IS_SHOWN)
    {
        for (int i = SIZE_BUFFER_FOR_BUTTONS - 1; i > 0; i--)
        {
            bufferForButtons[i] = bufferForButtons[i - 1];
        }
        bufferForButtons[0] = button;
      
        if (memcmp(bufferForButtons, sampleBufferForButtons, SIZE_BUFFER_FOR_BUTTONS) == 0)
        {
            SHOW_DEBUG_MENU = 1;
            Display::ShowWarning(MenuDebugEnabled);
        }
    }
    pressButton = button;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ReleaseButton(Key button)
{
    Sound::ButtonRelease();
    if (!HINT_MODE_ENABLED)
    {
        releaseButton = button;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::SetAutoHide(bool)
{
    if(!MENU_IS_SHOWN)
    {
        return;
    }
    if(sDisplay_TimeMenuAutoHide() == 0)
    {
        Timer::Disable(kMenuAutoHide);
    }
    else
    {
        Timer::SetAndStartOnce(kMenuAutoHide, OnTimerAutoHide, (uint)sDisplay_TimeMenuAutoHide());
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
char *Menu::StringNavigation(char buffer[100])
{
    buffer[0] = 0;
    const char * titles[10] = {0};
    int numTitle = 0;
    Control *item = OpenedItem();
    if(IsMainPage(item))
    {
        return 0;
    }
    while(!IsMainPage(item))
    {
        titles[numTitle++] = item->Title();
        item = (Control *)item->keeper;
    }
    for(int i = 9; i >= 0; i--)
    {
        if(titles[i])
        {
            strcat(buffer, titles[i]);
            if(i != 0)
            {
                strcat(buffer, " - ");
            }
        }
    }
    return buffer;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnTimerAutoHide()
{
    Menu::Show(false);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ProcessingShortPressureButton()
{
    if(shortPressureButton != K_None)
    {
        if (shortPressureButton == K_Memory && MODE_BTN_MEMORY_IS_SAVE && FDRIVE_IS_CONNECTED)
        {
            EXIT_FROM_SETNAME_TO = (uint)(MENU_IS_SHOWN ? RETURN_TO_MAIN_MENU : RETURN_TO_DISABLE_MENU);
            Memory_SaveSignalToFlashDrive();
            shortPressureButton = K_None;
            return;
        }
        NEED_FINISH_DRAW = 1;
        Menu::SetAutoHide(true);

        Key button = shortPressureButton;

        do
        {
            if(button == K_Enter)                                   // ���� ������ ������ ���� � �� �� ��������� � ����� ��������� ���������.
            {
                if(!MENU_IS_SHOWN)
                {
                    Menu::Show(true);
                }
                else
                {
                    if (IS_PAGE(OpenedItem()))
                    {
                        Menu::TemporaryEnableStrNavi();
                    }
                    Menu::CloseOpenedItem();
                }
            }
            else if (MENU_IS_SHOWN && Keyboard::IsFunctionalButton(button))       // ���� ���� �������� � ������ �������������� �������
            {
                void *item = itemUnderButton[button];
                if (HINT_MODE_ENABLED)
                {
                    SetItemForHint(item);
                }
                else
                {
                    if(item)
                    {
                        ((Control *)item)->ShortPress();
                    }
                }
            }
            else                                                        // ���� ���� �� ��������.
            {
                NamePage name = ((const Page *)OpenedItem())->GetNamePage();
                if(button == K_ChannelA && name == Page_ChannelA && MENU_IS_SHOWN)
                {
                    SET_ENABLED_A = !SET_ENABLED_A;
                    PageChannels::OnChanged_InputA(true);
                    break;
                }
                if(button == K_ChannelB && name == Page_ChannelB && MENU_IS_SHOWN)
                {
                    SET_ENABLED_B = !SET_ENABLED_B;
                    PageChannels::OnChanged_InputB(true);
                    break;
                }

                Page *page = (Page *)PageForButton(button);
                if(page && page != (Page *)PageHelp::pointer)
                {
                    page->SetCurrent(true);
                    page->Open(true);
                    Menu::TemporaryEnableStrNavi();
                    Menu::Show(true);
                }
            }
        } while(false);

        shortPressureButton = K_None;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ProcessingLongPressureButton()
{
    Key button = longPressureButton;

    if(button != K_None)
    {
        Control *item = OpenedItem();
        
        Sound::ButtonRelease();
        NEED_FINISH_DRAW = 1;
        SetAutoHide(true);

        if(button == K_Time)
        {
            FPGA::SetTShift(0);
        }
        else if(button == K_Trig)
        {
            FPGA::SetTrigLev(TRIGSOURCE, TrigLevZero);
        }
        else if(button == K_ChannelA)
        {
            FPGA::SetRShift(A, RShiftZero);
        }
        else if(button == K_ChannelB)
        {
            FPGA::SetRShift(B, RShiftZero);
        }
        else if(button == K_Enter)
        {
            if (IS_PAGE_SB(OpenedItem()))
            {
                CloseOpenedItem();
            }
            else
            {
                Show(!MENU_IS_SHOWN);
                if (NOT_PAGE(item))
                {
                    TemporaryEnableStrNavi();
                }
            }
        }
        else if(MENU_IS_SHOWN && Keyboard::IsFunctionalButton(button))
        {
            item = (Control *)itemUnderButton[button];
            if(item)
            {
                item->LongPress();
            }
            if (NOT_PAGE(item))
            {
                TemporaryEnableStrNavi();
            }
        }
        longPressureButton = K_None;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ProcessingPressButton()
{
    if((pressButton >= K_1 && pressButton <= K_5) || pressButton == K_Enter)
    {
        if (pressButton != K_Enter)
        {
            itemUnderKey = itemUnderButton[pressButton];
        }
    }
    if (pressButton == K_Start && !MODE_WORK_IS_RAM)
    {
        FPGA::OnPressStartStop();
    }
    pressButton = K_None;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ProcessingReleaseButton()
{
    if((releaseButton >= K_1 && releaseButton <= K_5) || pressButton == K_Enter)
    {
        itemUnderKey = 0;
        releaseButton = K_None;
    }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::TemporaryEnableStrNavi()
{
    if (SHOW_STRING_NAVI_TEMP)
    {
        SHOW_STRING_NAVIGATION = 1;                                            // ������������� ������� ����, ��� ���� �������� ������ ��������� ����
        Timer::SetAndStartOnce(kStrNaviAutoHide, OnTimerStrNaviAutoHide, 3000); // � ��������� ������, ������� ��� ��������
    }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OnTimerStrNaviAutoHide()
{
    SHOW_STRING_NAVIGATION = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ShortPress_ChoiceReg(void *choice_)
{
    Choice *choice = (Choice*)choice_;

    if(!IS_ACTIVE(choice)) 
    {
        CHOICE_RUN_FUNC_CHANGED(choice, false);
    } 
    else if(OpenedItem() != choice) 
    {
        choice->SetCurrent(CurrentItem() != choice);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ShortPress_IP(void *item)
{
    if (OpenedItem() == item)
    {
        ((IPaddress*)item)->NextPosition();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ShortPress_MAC(void *item)
{
    if (OpenedItem() == item)
    {
        CircleIncrease<int8>(&gCurDigit, 0, 5);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ChangeStateFlashDrive()
{
    if(!FDRIVE_IS_CONNECTED)
    {
        if(GetNameOpenedPage() == PageSB_Memory_Drive_Manager)
        {
            ((Page *)OpenedItem())->ShortPressOnItem(0);
        }
    }
    else if(FLASH_AUTOCONNECT)
    {
        OnPress_Drive_Manager();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::OpenItemTime()
{
    Display::ShowWarning(TimeNotSet);
    ShortPressureButton(K_Service);
    Update();
    Display::Update();
    for (int i = 0; i < 2; i++)
    {
        Update();
        Display::Update();
    }
    ShortPressureButton(K_4);
    Update();
    Display::Update();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Menu::NeedForFireSetLED()
{
    Control *item = OpenedItem();
    
    if (!MENU_IS_SHOWN)
    {
        return IS_CHOICE_REG(item) || IS_CHOICE(item) || IS_GOVERNOR(item);
    }

    NamePage name = GetNameOpenedPage();
    if (
            name == PageSB_Debug_SerialNumber   ||
            name == PageSB_Service_FFT_Cursors  || 
            name == PageSB_Measures_Tune        || 
            name == PageSB_Memory_Last          || 
            name == PageSB_Memory_Internal      ||
            REG_SET_ACTIVE_ON_CURSORS           ||
            (name == PageSB_Service_Function && FUNC_MODE_DRAW_IS_ENABLED)
        )
    {
        return true;
    }
    
    item = CurrentItem();
    
    if (IS_GOVERNOR(item)       ||
        IS_CHOICE_REG(item)     ||
        IS_GOVERNOR_COLOR(item))
    {
        return true;
    }
    
    item = OpenedItem();

    if (IS_CHOICE(item)  ||
        (IS_PAGE(item) && ((const Page *)OpenedItem())->NumSubPages() > 1)
        )
    {
        return true;
    }

    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::Show(bool show)
{
    MENU_IS_SHOWN = show;
    if (show)
    {
        Menu::TemporaryEnableStrNavi();
    }
    Menu::SetAutoHide(true);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::Init()
{
    INIT_PAGE_DISPLAY();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::RunAfterUpdate(pFuncVV func)
{
    funcAterUpdate = func;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Control *Menu::OpenedItem()
{
    TypeItem type = Item_None;
    return (Control *)RetLastOpened((Page *)&mainPage, &type);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
NamePage Menu::GetNameOpenedPage()
{
    return ((const Page *)OpenedItem())->GetNamePage();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void *Menu::RetLastOpened(Page *page, TypeItem *type)
{
    if (page->CurrentItemIsOpened())
    {
        int8 posActItem = page->PosCurrentItem();
        void *item = page->Item(posActItem);
        if (IS_PAGE(page->Item(posActItem)))
        {
            return RetLastOpened((Page *)item, type);
        }
        else
        {
            return item;
        }
    }
    *type = Item_Page;
    return page;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Control *Menu::CurrentItem()
{
    TypeItem type = Item_None;
    void *lastOpened = RetLastOpened((Page *)&mainPage, &type);
    int8 pos = ((const Page *)lastOpened)->PosCurrentItem();
    if (type == Item_Page && pos != 0x7f)
    {
        return ((const Page *)lastOpened)->Item(pos);
    }
    return (Control *)lastOpened;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::CloseOpenedItem()
{
    Control *item = OpenedItem();
    if (IS_PAGE(item))
    {
        if (IS_PAGE_SB(item))
        {
            //((Page *)item)->SmallButonFromPage(0)->funcOnPress();
            SMALL_BUTTON_FROM_PAGE(item, 0)->funcOnPress();
        }
        NamePage name = KEEPER(item)->name;
        ((Page *)KEEPER(item))->SetPosActItem(MENU_POS_ACT_ITEM(name) & 0x7f);
        if (item == (Control *)&mainPage)
        {
            Menu::Show(false);
        }
    }
    else
    {
        item->Open(false);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ChangeItem(Control *item, int delta)
{
    if (IS_CHOICE(item) || IS_CHOICE_REG(item))
    {
        ((Choice *)item)->StartChange(delta);
    }
    else if (IS_GOVERNOR(item))
    {
        Governor *governor = (Governor*)item;
        if (OpenedItem() != governor)
        {
            governor->StartChange(delta);
        }
        else
        {
            governor->ChangeValue(delta);
        }
    }
    else if (IS_GOVERNOR_COLOR(item))
    {
        ((GovernorColor *)item)->ChangeValue(delta);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Page *Menu::PagePointerFromName(NamePage)
{
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawHintItem(int x, int y, int width)
{
    if (!Menu::itemHint)
    {
        return;
    }

    pString names[Item_NumberItems][2] =
    {
        {"",            ""},        // Item_None
        {"",            ""},        // Item_Choice
        {"������",      "Button"},  // Item_Button
        {"��������",    "Page"},    // Item_Page
        {"",            ""},        // Item_Governor
        {"",            ""},        // Item_Time
        {"",            ""},        // Item_IP
        {"",            ""},        // Item_GovernorColor
        {"",            ""},        // Item_Formula
        {"",            ""},        // Item_MAC
        {"",            ""},        // Item_ChoiceReg
        {"������",      "Button"}   // Item_SmallButton
    };
    Language lang = LANG;
    Page *item = (Page *)Menu::itemHint;

    const int SIZE = 100;
    char title[SIZE];
    snprintf(title, SIZE, "%s \"%s\"", names[Menu::itemHint->type][lang], item->titleHint[lang]);

    if (item->type == Item_SmallButton)
    {
        y -= 9;
    }
    Painter::DrawStringInCenterRectAndBoundItC(x, y, width, 15, title, Color::BACK, Color::FILL);
    y = Painter::DrawTextInBoundedRectWithTransfers(x, y + 15, width, item->titleHint[2 + lang], Color::BACK, Color::FILL);
    if (item->type == Item_SmallButton)
    {
        ((SButton*)item)->DrawHints(x, y, width);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Menu::CalculateX(int layer)
{
    return MP_X - layer * Grid::Delta() / 4;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::Draw()
{
    if (MENU_IS_SHOWN || NOT_PAGE(OpenedItem()))
    {
        ResetItemsUnderButton();
        Control *item = OpenedItem();
        if (MENU_IS_SHOWN)
        {
            if (IS_PAGE(item))
            {
                ((Page *)item)->Draw(CalculateX(0), Grid::Top(), true);
            }
            else
            {
                ((Page *)KEEPER(item))->Draw(CalculateX(0), Grid::Top(), true);
            }
        }
        else
        {
            if (IS_CHOICE(item) || IS_CHOICE_REG(item))
            {
                ((Choice *)item)->Draw(CalculateX(0), Grid::Top(), false);
                Painter::DrawVLine(CalculateX(0), Grid::Top() + 1, Grid::Top() + 34, Color::BorderMenu(false));
                Painter::DrawVLine(CalculateX(0) + 1, Grid::Top() + 1, Grid::Top() + 34);
                Painter::DrawVLine(Grid::Right(), Grid::Top() + 30, Grid::Top() + 40, Color::FILL);
                Painter::DrawVLine(CalculateX(0) - 1, Grid::Top() + 1, Grid::Top() + 35, Color::BACK);
                Painter::DrawHLine(Grid::Top() + 35, CalculateX(0) - 1, Grid::Right() - 1);
            }
            else if (IS_GOVERNOR(item))
            {
                ((Governor *)item)->Draw(CalculateX(0), Grid::Top(), true);
                Painter::DrawHLine(Grid::Top(), CalculateX(0) - 2, Grid::Right(), Color::FILL);
                Painter::DrawVLine(Grid::Right(), Grid::Top(), Grid::Top() + 40);
            }
        }
    }

    if (HINT_MODE_ENABLED)
    {
        int x = 1;
        int y = 0;
        int width = 318;
        if (MENU_IS_SHOWN)
        {
            width = Menu::IsMinimize() ? 289 : 220;
        }
        Painter::DrawTextInBoundedRectWithTransfers(x, y, width,
               LANG_RU ? "������� ����� ���������. � ���� ������ ��� ������� �� ������ �� ����� ��������� ���������� � � ����������. "
               "����� ��������� ���� �����, ������� ������ ������ � ����������� � � ������� 0.5�." :
               "Mode is activated hints. In this mode, pressing the button displays the information on its purpose. "
               "To disable this mode, press the button HELP and hold it for 0.5s.",
               Color::BACK, Color::FILL);
        y += LANG_RU ? 49 : 40;
        if (Menu::stringForHint)
        {
            Painter::DrawTextInBoundedRectWithTransfers(x, y, width, Menu::stringForHint, Color::BACK, Color::WHITE);
        }
        else if (Menu::itemHint)
        {
            DrawHintItem(x, y, width);
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ResetItemsUnderButton()
{
    for (int i = 0; i < NumButtons; i++)
    {
        itemUnderButton[i] = 0;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Menu::IsMinimize()
{
    return IS_PAGE_SB(Menu::OpenedItem());
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
const SButton *Menu::GetSmallButton(Key button)
{
    if (Menu::IsMinimize() && button >= K_Enter && button <= K_5)
    {
        Page *page = (Page *)OpenedItem();
        SButton *sb = (SButton *)page->items[button - K_Enter];
        return sb;
    }
    return NULL;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::SetItemForHint(void *item)
{
    Menu::stringForHint = 0;
    Menu::itemHint = (Control *)item;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ButtonPress(Key, TypePress)
{
}

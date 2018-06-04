#pragma once
#include "Hardware/Controls.h"
#include "Menu/MenuItems.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @defgroup Menu
 *  @{
 *  @defgroup Pages
 *  @{
 *  @}
 */

#define PAGE_IS_MAIN                   (name == Page_Main)
#define MENU_TEMP_ENABLE_STRING_NAVI() Menu::TemporaryEnableStrNavi()

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Menu
{
public:
    /// �������������
    static void Init();

    static void ChangeStateFlashDrive();
    /// ������� ������ ���������� � ������� �����.
    static void Update();
    /// ������� ��������� ��������� ������� ������ (����� 0.5 ���.).
    static void ShortPressureButton(Key button);
    /// ������� ��������� �������� ������� ������ (����� 0.5 ���.).
    static void LongPressureButton(Key button);
    /// ������� ����������, ����� ������ ��������� �� �������� � ������� ���������.
    static void PressButton(Key button);
    /// ������� ����������, ����� ������ ��������� �� �������� � ������� ���������.
    static void ReleaseButton(Key button);
    /// ������� ��������� �������� ����� ��������� ������.
    static void RotateRegSetRight();
    /// ������� ��������� �������� ����� ��������� �����.
    static void RotateRegSetLeft();
    /// ���������� ����� ��������������� �������� ���� � ������������ � �����������.
    static void SetAutoHide(bool active);
    /// ���������� ���� � �������� ������ ���� � ��������� ����, ������� � ������ �� �����.
    static char *StringNavigation(char buffer[100]);

    static void Show(bool show);

    static void OpenItemTime();
    /// ������� �������� �������� ����������� ������ ��������� ����, ���� ������ �����������.
    static void TemporaryEnableStrNavi();
    /// ���������� ��� ������� ����� Menu_UpdateInput().
    static void RunAfterUpdate(pFuncVV func);
    /// ���������� ����
    static void Draw();
    /// ���������� ����� ��������� �������� ����
    static Control *OpenedItem();
    /// ���� true - ���� ��������� � �������������� ������.
    static bool IsMinimize();

    static NamePage GetNameOpenedPage();

    static Page *PagePointerFromName(NamePage namePage);
    /// ���������� ����� �������� �������� ���� (�������, ��� �������, �������� �������, ������ �������� ���� ������ ���������
    static Control *CurrentItem();
    /// ������� �������� ������� ����
    static void CloseOpenedItem();
    /// ��������� ��� ����������� �������� Governor, GovernorColor ��� Choice �� ������ item � ����������� �� ����� delta
    static void ChangeItem(Control *item, int delta);

    static int CalculateX(int layer);
    /// ������� ��������� �� ����� ������, ��������������� ������ ������ ������.
    static const SButton*  GetSmallButton(Key button);

    static void SetItemForHint(void *item);
    ///\brief  ����� �������� ����� �������� ����, ���������������� �������������� ������� [1..5], ���� ��� ��������� � ������ ���������, � 0, 
    /// ���� �� ���� ������ �� ������.
    static Control *itemUnderKey;

    static Control *itemUnderButton[NumButtons];
    /// ������ ���������, ������� ���� �������� � ������ ����������� ������ ���������.
    static const char *stringForHint;
    /// Item, ��������� ��� �������� ����� �������� � ������ ����������� ������ ���������.
    static Control *itemHint;

private:
    static void *RetLastOpened(Page *_page, TypeItem *_type);
    /// ��������� ��������� ������� ������
    static void ProcessingShortPressureButton();
    /// ��������� �������� ������� ������
    static void ProcessingLongPressureButton();
    /// ��������� ��������� ������ ����
    static void ProcessingPressButton();
    /// ��������� �������� ������ �����
    static void ProcessingReleaseButton();
    ///< ��������� �������� ����� ���������
    static void ProcessingRegulatorSetRotate();
    /// ��������� ������� �����
    static void ProcessingRegulatorPress();
    /// ��������� ������� ������� ��������������� �������� ����
    static void OnTimerAutoHide();
    /// ��������/��������� ��������� ����� ���������, ���� ����������
    static void SwitchSetLED();
    /// �������, ������� �������� ����� ������ ��������� ����
    static void OnTimerStrNaviAutoHide();
    /// ���������� true, ���� �������� ��������� ������ ������
    static bool NeedForFireSetLED();
    
    static void ProcessButtonForHint(Key button);
    
    static void ShortPress_ChoiceReg(void *choice);
    
    static void ShortPress_IP(void *item);
    
    static void ShortPress_MAC(void *item);
    
    static void ResetItemsUnderButton();
    /// ��������� ����� ��������� �� ������� �������� ����� ������.
    static void RotateRegSetSB(int angle);
          
    /// ���� ��������� �������� ������� ������, �� ����� �������� ��� ���� ������ �� ���������  ����� �������.
    static Key shortPressureButton;
    /// ���� ��������� ������� ������� ������, �� ����� �������� ��� ���� ������ �� ��������� ����� �������.
    static Key longPressureButton;
    /// ��� ������� ������ � ��� ������������ � ��� ���������� � �������� ��� �� �������� ������� ������� ������.
    static Key pressButton;
    /// ��� ���������� ������ � ��� ������������ � ��� ���������� � �������� ��� �� ��������� ������� ���������� ������.
    static Key releaseButton;
    /// ����, �� ������� ����� ��������� ����� ��������� - �������� �������� ���������� �������, ���� - ����������� - "-" - �����, "+" - ������.
    static int angleRegSet;
    /// ��� ������� ����� �������� ���� ��� ����� Menu::Update().
    static pFuncVV funcAterUpdate;
  
    static const int SIZE_BUFFER_FOR_BUTTONS = 10;
    static Key bufferForButtons[SIZE_BUFFER_FOR_BUTTONS];
    
    static const Key sampleBufferForButtons[SIZE_BUFFER_FOR_BUTTONS];
};


/** @}
 */

#pragma once
#include "Display/Colors.h"
#include "Display/Display.h"
#include "MenuItemsDefs.h"
#include "Menu/MenuPagesNames.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Menu
 *  @{
 *  @defgroup MenuItems Menu Items
 *  @{
 */

extern int8 gCurDigit;

#define MENU_ITEMS_ON_DISPLAY       5   ///< ������� ������� ���� ���������� �� ������ �� ���������.


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ������ ���� ������� ����
enum TypeItem
{
    Item_None,           
    Item_Choice,        ///< ����� ������ - ��������� ������� ���� �� ���������� �������� ��������.
    Item_Button,        ///< ������.
    Item_Page,          ///< ��������.
    Item_Governor,      ///< ��������� - ��������� ������� ����� ����� �������� �������� �� ������� ��������� ����������.
    Item_GovernorColor, ///< ��������� ������� ����.
    Item_ChoiceReg,     ///< ������� ������, � ������� ����� �������������� �� �������, � ������
    Item_SmallButton,   ///< ������ ��� ������ ����� ������
    Item_ChoiceParameter,
    Item_NumberItems
};


/// ����� ����� ��� ���� ����� ��������� ����
#define COMMON_PART_MENU_ITEM                                                                                                               \
    TypeItem        type;           /* ��� ����� */                                                                                         \
    int8            num;            /* ����� ��������� ��� Choice ��� ����� ��������� ��� Page*/                                            \
    bool            isPageSB;       /* ���� true, �� ��� �������� ����� ������, ����� type == Item_Page */                                  \
                                    /* ���� type == Item_Choice, �� ������� �������� �������� Choice - ����� ������ �� ���� ��������� */    \
    NamePage        nameOrNumBit;   /* ��� �� ������������ NamePage, ���� type == Item_Page */                                              \
                                    /* � ������, ���� type == Item_Choice,  ���������� ����� ���� */                                        \
    const PageBase  *keeper;        /* ����� ��������, ������� �����������. ��� Page_Main = 0 */                                            \
    pFuncBV         funcOfActive;   /* ������� �� ������ ������� */                                                                         \
    const char      *titleHint[4]   /* �������� �������� �� ������� � ���������� ������. ����� ��������� ��� ������ ������ */

class PageBase;

#define IS_PAGE(control)           (control->type == Item_Page)
#define NOT_PAGE(control)          (control->type != Item_Page)
#define IS_PAGE_SB(control)        (control->isPageSB)
#define IS_CHOICE(control)         (control->type == Item_Choice)
#define IS_CHOICE_REG(control)     (control->type == Item_ChoiceReg)
#define NOT_CHOICE_REG(control)    (control->type != Item_ChoiceReg)
#define IS_GOVERNOR(control)       (control->type == Item_Governor)
#define NOT_GOVERNOR(control)      (control->type != Item_Governor)
#define IS_GOVERNOR_COLOR(control) (control->type == Item_GovernorColor)
#define IS_IP(control)             (control->type == Item_IP)
#define IS_MAC(control)            (control->type == Item_MAC)
#define IS_TIME(control)           (control->type == Item_Time)
    
#define KEEPER(control)            ((PageBase *)control->keeper)
#define IS_ACTIVE(control)         (control->funcOfActive())


class Item
{
public:
    COMMON_PART_MENU_ITEM;
    /// \brief ���������� true, ���� ������� ���� control ������ (��������� �� �� ����� ������� ����. ��� �������, ��� ��������, ��� ������� 
    /// �������������� ������� ���� ����� Choice ��� Governor
    bool IsShade() const;
    /// ���������� true, ���� ������, ��������������� �������� ���� control, ��������� � ������� ���������
    bool IsPressed() const;
    /// �������/��������� �������
    void SetCurrent(bool active);
    /// ���������� true, ���� ������� ���� �� ������ control ������
    bool IsOpened() const;

    void Open(bool open);
    /// ���������� �������� ��������, ��� ��� �������� �� ������� �������
    const char *Title() const;

    bool ChangeOpened(int delta);
    /// ���������� ��� "��������" �������
    void ShortPress();
    /// ���������� ��� "�������" �������
    void LongPress();

    void Draw(bool opened, int x = -1, int y = -1) const;
    /// ������������ ������� ������. ���������� ��������� �� ����, ���� ��������� � �������� ��������� ����� �������, � 0 � ��������� ������
    Item *Press(StructControl strControl);

    TypeItem Type() const;

    /// ���������� ���������� ����� ������ ���� �� ��������
    int PositionOnPage() const;
    /// ���������� �������������� �������, ����������� ������ ����
    Control ButtonForItem() const;
    /// ���������� ������ ���� � �������� ����
    char *FullPath() const;
    /// ������� ��������� � �������� ����� ������. ���������� ������ ���������� ����������� ������
    int DrawHint(int x, int y, int width, Color color = Color::NUMBER) const;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Page ///

/// ��������� �������� ����.
class PageBase
{
public:
    COMMON_PART_MENU_ITEM;
    /// \brief ����� ��������� �� ������ ���� �������� (� ������� ��������) ��� �������� ����� ������  ����� �������� 6 ���������� �� SButton : 
    /// 0 - B_Menu, 1...5 - B_F1...B_F5
    const Item * const *items;
    /// ����� ���������� ��� ������� �� �������� ��������
    pFuncVV  funcOnPress;
    /// ����� ���������� ����� ��������� ������
    pFuncVV  funcOnDraw;
    /// � �������� ����� ������ ���������� ��� �������� ����� ���������
    pFuncVI  funcRegSetSB;
    bool CurrentItemIsOpened() const;
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
#define SMALL_BUTTON_FROM_PAGE(page, numButton)     ((SButton *)((Page *)page)->items[numButton])

class Page : public Item
{
public:
    /// ���������� true, ���� ������� ������� �������� ������
    bool CurrentItemIsOpened() const;
    /// \brief ����� ��������� �� ������ ���� �������� (� ������� ��������) ��� �������� ����� ������  ����� �������� 6 ���������� �� SButton : 
    /// 0 - B_Menu,  1...5 - B_F1...B_F5
    const Item * const *items;   
    /// ����� ���������� ��� ������� �� �������� ��������
    pFuncVV  funcOnPress;
    /// ����� ���������� ����� ��������� ������
    pFuncVV  funcOnDraw;
    /// � �������� ����� ������ ���������� ��� �������� ����� ���������
    pFuncVI  funcRegSetSB;
    /// D��������� ����� ���������� � �������� �� ������ page
    int NumSubPages() const;
    /// ���������� ���������� ��������� � �������� �� ������ page
    int NumItems() const;
    /// ���������� ��� �������� page
    NamePage GetNamePage() const;

    int8 CurrentSubPage() const;

    void SetCurrentSubPage(int8 pos);
    /// ������������� ������� ��������� ������ ����
    void SetPosActItem(int8 pos);
    /// ���������� ����� �������� ���� �������� ��������
    Item *GetItem(int numElement) const;
    /// \brief ���������� ������� ������� �������� �������� �� ������ page �� ������. ���� ������� ����������� 0, ��� ����� 0, ���� ������� 
    /// ����������� 1, ��� ����� 5 � �.�.
    int PosItemOnTop() const;
    /// �������� ������� ��������� ������� ������ ��� ������ numItem �������� page
    void ShortPressOnItem(int numItem);
    /// ���������� ������� �������� �������� ������� page
    int8 PosCurrentItem() const;

    void ChangeSubPage(int delta);
    
    Page() {};
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Button ///

/// ��������� ������.
class ButtonBase
{
public:
    COMMON_PART_MENU_ITEM;
    /// �������, ������� ���������� ��� ������� �� ������.
    pFuncVV     funcOnPress;
    /// ������� ����� ���������� �� ����� ��������� ������.
    pFuncVII    funcForDraw;
};

class Button : public Item
{
public:
    /// �������, ������� ���������� ��� ������� �� ������.
    pFuncVV     funcOnPress;
    /// ������� ����� ���������� �� ����� ��������� ������.
    pFuncVII    funcForDraw;
    /// ������������ ������� ������. ���������� ����, ������ ��� �� ����� ���������� � �������� ���������.
    Item *Press(TypePress press);

    void Draw(int x, int y);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// SButton ///

#ifdef WIN32
#pragma warning(push)
#pragma warning(disable:4623 4626 5027)
#endif
struct StructHelpSmallButton
{
    /// ��������� �� ������� ��������� ����������� �������� ������
    pFuncVII    funcDrawUGO;
    /// ������� � ������� �����������.
    pString     helpUGO[2];
};
#ifdef WIN32
#pragma warning(pop)
#endif


/// ��������� ������ ��� ��������������� ������ ����.
class SButtonBase
{
public:
    COMMON_PART_MENU_ITEM;
    /// ��� ������� ��������� ��� ��������� ������� ������.
    pFuncVV                         funcOnPress;
    /// ��� ������� ���������� ��� ��������� ������ � ����� � ������������ x, y.
    pFuncVII                        funcForDraw;

    const StructHelpSmallButton    *hintUGO;

    int                             numHints;
};


class SButton : public Item
{
public:
    /// ��� ������� ��������� ��� ��������� ������� ������.
    pFuncVV                         funcOnPress;
    /// ��� ������� ���������� ��� ��������� ������ � ����� � ������������ x, y.
    pFuncVII                        funcForDraw;

    const StructHelpSmallButton    *hintUGO; 

    int                             numHints;
    /// ������������ ������� ������. ���������� 0, ������ ��� �� ����� ���������� � �������� ���������
    Item *Press(TypePress press);

    void Draw(int x, int y);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Governor ///

/// ��������� ���������.
class GovernorBase
{
public:
    COMMON_PART_MENU_ITEM;
    /// ���������� ��������, ������� ����� ��������� ���������.
    int16   minValue;
    /// ������������ ��������.
    int16   maxValue;

    int16  *cell;
    /// �������, ������� ����� �������� ����� ����, ��� �������� ���������� ����������.
    pFuncVV funcOfChanged;
    /// �������, ������� ���������� ����� ����������
    pFuncVV funcBeforeDraw;
};

class Governor : public Item
{
public:
    /// ���������� ��������, ������� ����� ��������� ���������.
    int16   minValue;
    /// ������������ ��������.
    int16   maxValue;

    int16  *cell;
    /// �������, ������� ����� �������� ����� ����, ��� �������� ���������� ����������.
    pFuncVV funcOfChanged;
    /// �������, ������� ���������� ����� ����������
    pFuncVV funcBeforeDraw;
    /// ��������� �������� �������� ���������� ��� ���������� �������� ���� ���� Governor (� ����������� �� ����� delta).
    void StartChange(int detla);
    /// ���������� ��������� ������� ��������, ������� ����� ������� governor.
    int16 NextValue() const;
    /// ���������� ��������� ������� ��������, ������� ����� ������� governor.
    int16 PrevValue() const;
    /// ������������ ��������� ���� ��������.
    float Step();
    /// �������� �������� � ������� ������� ��� ��������� ��������.
    void ChangeValue(int delta);
    /// ��� �������� �������� ������������ ������ �� ��������� �������.
    void NextPosition();
    /// ���������� ����� ��������� � ���� ��� ����� �������� governor. ������� �� ������������� ��������, ������� ����� ��������� governor.
    int  NumDigits() const;
    /// ���������� ����������� ����������, ��������������� ��� �������� ���������
    static char GetSymbol(int value);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Choice ///
class ChoiceBase
{
public:
    COMMON_PART_MENU_ITEM;

    int8    *cell;
    /// �������� ������ �� ������� � ���������� ������.
    pString *names;
    /// ��������� ��� ������� �������� �� ������� �����
    pString *hintsRu;
    /// ��������� ��� ������� �������� �� ���������� �����
    pString *hintsEn;
    /// ������� ������ ���������� ����� ��������� �������� ��������.
    pFuncVB	 funcOnChanged;
    /// ������� ���������� ����� ��������� ��������. 
    pFuncVII funcForDraw;
};

class Choice : public Item
{
public:

    int8 * cell;
    /// �������� ������ �� ������� � ���������� ������.
    pString *names;
    /// ��������� ��� ������� �������� �� ������� �����
    pString *hintsRu;
    /// ��������� ��� ������� �������� �� ���������� �����
    pString *hintsEn;
    /// ������� ������ ���������� ����� ��������� �������� ��������.
    pFuncVB	 funcOnChanged;
    /// ������� ���������� ����� ��������� ��������. 
    pFuncVII funcForDraw;

    void StartChange(int delta) const;
    /// ������������ ��������� ���� ��������.
    float Step();
    /// �������� �������� choice � ����������� �� �������� � ����� delta.
    void ChangeIndex(int delta);
    /// ���������� ���������� ��������� ������ � �������� �� ������ choice
    int8 NumSubItems() const;

    void Draw(bool opened, int x = -1, int y = -1);
    /// ���������� ��� �������� �������� ������ �������� choice, ��� ��� �������� � �������� ���� ���������
    const char *NameCurrentSubItem() const;
    /// ���������� ��� ���������� �������� ������ �������� choice, ��� ��� �������� � �������� ���� ���������
    const char *NameNextSubItem() const;
    /// ���������� ������ ����������
    int GetHeightOpened() const;

    const char *NamePrevSubItem() const;
    /// ���������� ��� �������� ������ �������� choice � ������� i ��� ��� �������� � �������� ���� ���������
    const char *NameSubItem(int i) const;
    /// ���������� ��������� �� ����, ���� ��������� � �������� ���������, � 0, ���� � ��������
    Item *Press(StructControl strControl);

    int8 CurrentIndex() const;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Formula ////

/// ��������� ������� ���� ��� ��������� ������������� � ������ �������������� �������
#define FIELD_SIGN_MEMBER_1_ADD 0
#define FIELD_SIGN_MEMBER_1_MUL 1
#define FIELD_SIGN_MEMBER_2_ADD 2
#define FIELD_SIGN_MEMBER_2_MUL 3
#define POS_SIGN_MEMBER_1       0
#define POS_KOEFF_MEMBER_1      1
#define POS_SIGN_MEMBER_2       2
#define POS_KOEFF_MEMBER_2      3

class FormulaBase
{
public:
    COMMON_PART_MENU_ITEM;
    /// ����� ������, ��� �������� Function, �� ������� ������ ���� ��������
    int8 *function;
    /// ����� ������������ ��� ������ ����� ��� ��������
    int8 *koeff1add;
    /// ����� ������������ ��� ������ ����� ��� ��������
    int8 *koeff2add;
    /// ����� ������������ ��� ������ ����� ��� ���������
    int8 *koeff1mul;
    /// ����� ������������ ��� ������ ����� ��� ���������
    int8 *koeff2mul;
    /// ������� ������ : 0 - ���� ������� �����, 1 - ����������� ������� �����, 2 - ���� ������� �����, 3 - ����������� ������� �����
    int8 *curDigit;
    /// ��� ������� ���������� ����� ��������� ��������� �������� ����������.
    pFuncVV funcOfChanged;
};

class Formula : public Item
{
public:
    /// ����� ������, ��� �������� Function, �� ������� ������ ���� ��������
    int8 *function;
    /// ����� ������������ ��� ������ ����� ��� ��������
    int8 *koeff1add;
    /// ����� ������������ ��� ������ ����� ��� ��������
    int8 *koeff2add;
    /// ����� ������������ ��� ������ ����� ��� ���������
    int8 *koeff1mul;
    /// ����� ������������ ��� ������ ����� ��� ���������
    int8 *koeff2mul;
    /// ������� ������ : 0 - ���� ������� �����, 1 - ����������� ������� �����, 2 - ���� ������� �����, 3 - ����������� ������� �����
    int8 *curDigit;
    /// ��� ������� ���������� ����� ��������� ��������� �������� ����������.
    pFuncVV funcOfChanged;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// GovernorColor ///
class ColorType;

class GovernorColorBase
{
public:
    COMMON_PART_MENU_ITEM;
    /// ��������� ��� �������� �����.
    ColorType *ct;
    /// ��� ������� ����� �������� ����� ��������� �������� ��������.
    pFuncVV funcOnChanged;
};

class GovernorColor : public Item
{
public:
    /// ��������� ��� �������� �����.
    ColorType *ct;
    /// ��� ������� ����� �������� ����� ��������� �������� ��������.
    pFuncVV funcOnChanged;
    /// �������� ������� ����� � governor.
    void ChangeValue(int delta);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Time ///

#define iEXIT   0
#define iDAY    1
#define iMONTH  2
#define iYEAR   3
#define iHOURS  4
#define iMIN    5
#define iSEC    6
#define iSET    7

class TimeBase
{
public:
    COMMON_PART_MENU_ITEM;
    /// ������� ���� ���������. 0 - �����, 1 - ���, 2 - ���, 3 - ����, 4 - ����, 5 - �����, 6 - ���, 7 - ����������.
    int8 *curField;

    int8 *hours;

    int8 *minutes;

    int8 *seconds;

    int8 *month;

    int8 *day;

    int8 *year;
};

#define CHOICE_RUN_FUNC_CHANGED(c, val)     \
    if(c->funcOnChanged)                    \
    {                                       \
        c->funcOnChanged(val);              \
    }


typedef void * pVOID;
#define MAX_NUM_ITEMS_IN_PAGE 15
typedef pVOID arrayItems[MAX_NUM_ITEMS_IN_PAGE];

/** @}  @}
 */

#pragma once
#include "Keyboard/Keyboard.h"
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
friend class Handlers;

public:
    /// Инициализация
    static void Init();

    static void ChangeStateFlashDrive();
    /// Функция должна вызываться в главном цикле.
    static void Update();
    /// Функция обработки короткого нажатия кнопки (менее 0.5 сек.).
    static void ShortPressureButton(Key button);
    /// Функция обработки длинного нажатия кнопки (более 0.5 сек.).
    static void LongPressureButton(Key button);
    /// Функция вызывается при нажатии, повторе и отпускании кнопки
    static void ButtonEvent(KeyEvent event);
    /// Установить время автоматического сокрытия меню в соответствии с установками.
    static void SetAutoHide(bool active);
    /// Возвращает путь к текущему пункту меню в текстовом виде, готовом к выводу на экран.
    static char *StringNavigation(char buffer[100]);

    static void Show(bool show);

    static void OpenItemTime();
    /// Функция временно включает отображение строки навигации меню, если задано настройками.
    static void TemporaryEnableStrNavi();
    /// Ввыполнить эту функцию после Menu_UpdateInput().
    static void RunAfterUpdate(pFuncVV func);
    /// Нарисовать меню
    static void Draw();
    /// Возвращает адрес открытого элемента меню
    static Control *OpenedItem();
    /// Если true - меню находится в дополнительном режиме.
    static bool IsMinimize();

    static NamePage GetNameOpenedPage();

    static Page *PagePointerFromName(NamePage namePage);
    /// Возвращает адрес текущего элемента меню (текущим, как правило, является элемент, кнопка которого была нажата последней
    static Control *CurrentItem();
    /// Закрыть открытый элемент меню
    static void CloseOpenedItem();
    /// Уменьшает или увеличивает значение Governor, GovernorColor или Choice по адресу item в зависимости от знака delta
    static void ChangeItem(Control *item, int delta);

    static int CalculateX(int layer);
    /// Вернуть указатель на малую кнопку, соответствующую данной кнопки панели.
    static const SButton* GetSmallButton(Key button);

    static void SetItemForHint(void *item);
    ///\brief  Здесь хранится адрес элемента меню, соответствующего функциональной клавише [1..5], если она находится в нижнем положении, и 0, 
    /// если ни одна кнопка не нажата.
    static Control *itemUnderKey;

    static Control *itemUnderButton[Key::NumButtons];
    /// Строка подсказки, которую надо выводить в случае включённого режима подсказок.
    static const char *stringForHint;
    /// Item, подсказку для которого нужно выводить в случае включённого режима подсказок.
    static Control *itemHint;

private:

    static void *RetLastOpened(Page *_page, TypeItem *_type);
    /// Обработка короткого нажатия кнопки
    static void ProcessingShortPressureButton();
    /// Обработка длинного нажатия кнопки
    static void ProcessingLongPressureButton();
    /// Обработка опускания кнопки вниз
    static void ProcessingPressButton();
    /// Обработка поднятия кнопки вверх
    static void ProcessingReleaseButton();
    /// Обработка события таймера автоматического сокрытия меню
    static void OnTimerAutoHide();
    /// Функция, которая отключит вывод строки навигации меню
    static void OnTimerStrNaviAutoHide();
    /// Возвращает true, если лампочка УСТАНОВКА должна гореть
    static bool NeedForFireSetLED();
    
    static void ProcessButtonForHint(Key button);
    
    static void ShortPress_ChoiceReg(void *choice);
    
    static void ShortPress_IP(void *item);
    
    static void ShortPress_MAC(void *item);
    
    static void ResetItemsUnderButton();
    /// Если произошло короткое нажатие кнопки, то здесь хранится имя этой кнопки до обработки  этого нажатия.
    static Key shortPressureButton;
    /// Если произошло длинное нажатие кнопки, то здесь хранится имя этой кнопки до обработки этого нажатия.
    static Key longPressureButton;
    /// При нажатии кнопки её имя записывается в эту переменную и хранится там до обратоки события нажатия кнопки.
    static Key pressButton;
    /// При отпускании кнопки её имя записывается в эту переменную и хранится там до обработки события отпускания кнопки.
    static Key releaseButton;
    /// Эта функция будет вызывана один раз после Menu::Update().
    static pFuncVV funcAterUpdate;
};


/** @}
 */

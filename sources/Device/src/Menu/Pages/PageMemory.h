#pragma once
#include "defines.h"
#include "Menu/MenuItems.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Menu
 *  @{
 *  @addtogroup Pages
 *  @{
 *  @defgroup PageMemory
 *  @{
 */

class PageMemory
{
public:

    static void OnChanged_Points(bool active);

    static void OnPress_Drive_Manager();

    static void SaveSignalToFlashDrive();

    static const PageBase *pointer;
};



/** @}  @}  @}
 */

#pragma once
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum COMMAND
{           //  смещение               0  |     1    |     2      |      3      |     4        |      5       |   6    |
/* 00 */    COMMAND_NONE,           //    |          |            |             |              |              |        |
/* 01 */    IN_BUTTON_PRESS,        // 01 |  Control | TypePress  |             |              |              |        |
/* 02 */    PAINT_BEGIN_SCENE,      // 02 |   Color  |            |             |              |              |        |
/* 03 */    PAINT_END_SCENE,        // 03 |          |            |             |              |              |        |
/* 04 */    PAINT_SET_COLOR,        // 04 |   Color  |            |             |              |              |        |
/* 05 */    PAINT_FILL_REGION,      // 05 |   x[0:7] |  x[8:15]   |      y      | width[0:7]   | width[8:15]  | height |
/* 06 */    PAINT_DRAW_TEXT,        // 06 |   x[0:7] |  x[8:15]   |      y      | num symbols  |              |        |
/* 07 */    PAINT_SET_PALETTE,      // 07 | numColor | value[0:7] | value[8:15] | value[16:23] | value[24:31] |        |
/* 08 */    PAINT_DRAW_RECTANGLE,   // 08 |   x[0:7] |  x[8:15]   |      y      | width[0:7]   | width[8:15]  | height |
/* 09 */    PAINT_DRAW_VLINE,       // 09 |   x[0:7] |  x[8:15]   |      y0     |      y1      |              |        |
/* 10 */    PAINT_DRAW_HLINE,       // 10 |    y     |  x0[0:7]   |   x0[8:15]  |   x1[0:7]    |  x1[8:15]    |        |
/* 11 */    PAINT_SET_FONT,         // 11 | typeFont |            |             |              |              |        |
/* 12 */    PAINT_SET_POINT,        // 12 |   x[0:7] |  x[8:15]   |      y      |              |              |        |
/* 13 */    PAINT_DRAW_LINE,        // 13 |  x0[0:7] | x0[8:15]   |     y0      |   x1[0:7]    |   x1[8:15]   |   y1   |
/* 14 */    NUM_COMMANDS
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef bool(*pFuncBU8)(uint8);

class Decoder
{
public:

    static void AddData(uint8 data);

    static void Update();
private:

    static void RunStep(uint8 data);

    /// Выполняемая функция
    static pFuncBU8 curFunc;
    /// Текущий байт выполняемой функции
    static int step;

    static bool EmptyFunc(uint8) { return true; }

    static bool ButtonPress(uint8);
    /// Эту функцию надо вызывать после выполнения последнего шага
    static void FinishCommand();
};

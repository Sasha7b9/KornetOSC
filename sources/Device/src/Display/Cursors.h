#pragma once
#include "defines.h"
#include "Settings/SettingsChannel.h"


/// Перемемещение курсоров при вращении ручки УСТАНОВКА - по точкам или процентам
#define CURS_MOVEMENT               (set.curs_movement)
/// Курсоры перемещаются при вращении ручка УСТАНОВКА с дискретностью 1%
#define CURS_MOVEMENT_IN_PERCENTS   (CURS_MOVEMENT == Cursors::Movement::Percents)
/// Курсоры перемещаются при вращении ручка УСТАНОВКА с дискретностью 1 пиксель
#define CURS_MOVEMENT_IN_PIXELS     (CURS_MOVEMENT == Cursors::Movement::Pixels)


/// Позиция курсора напряжения
#define CURsU_POS(ch, num)          (set.curs_posCurU[ch][num])


class Cursors
{
public:
    /// Дискретность перемещения курсоров.
    struct Movement
    {
        enum E
        {
            Pixels,    ///< По пикселям экрана
            Percents   ///< По процентам
        } value;
        operator uint8() const { return (uint8)value; };
    };

    /// Получить позицию курсора напряжения
    static float PosU(Chan ch, int numCur);
};

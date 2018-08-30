#pragma once
#include "defines.h"
#include "Settings/SettingsChannel.h"


/// Перемемещение курсоров при вращении ручки УСТАНОВКА - по точкам или процентам
#define CURS_MOVEMENT               (set.curs_movement)
/// Курсоры перемещаются при вращении ручка УСТАНОВКА с дискретностью 1%
#define CURS_MOVEMENT_IN_PERCENTS   (CURS_MOVEMENT == Cursors::Movement::Percents)
/// Курсоры перемещаются при вращении ручка УСТАНОВКА с дискретностью 1 пиксель
#define CURS_MOVEMENT_IN_PIXELS     (CURS_MOVEMENT == Cursors::Movement::Pixels)

/// Какими курсорами управляет ручка УСТАНОВКА
#define CURS_ACTIVE                 (set.curs_active)
/// Ручка УСТАНОВКА управляет курсорами напряжения
#define CURS_ACTIVE_U               (CURS_ACTIVE == Cursors::Active::U)
/// Ручка УСТАНОВКА управляет курсорами времени
#define CURS_ACTIVE_T               (CURS_ACTIVE == Cursors::Active::T)

/// Позиция курсора напряжения
#define CURsU_POS(ch, num)          (set.curs_posCurU[ch][num])
/// Позиция куросра времени
#define CURsT_POS(ch, num)          Cursors::PosT(ch, num)

/// Режим слежения за курсорами
#define CURS_LOOK_MODE(ch)          (set.curs_lookMode[ch])
/// Включено слежение за курсорами напряжения
#define CURS_LOOK_U(ch)             (CURS_LOOK_MODE(ch) == Cursors::LookMode::Voltage)
/// Включено слежение за курсорами времени
#define CURS_LOOK_T(ch)             (CURS_LOOK_MODE(ch) == Cursors::LookMode::Time)
/// Включено слежение за курсорами времени и напряжения
#define CURS_LOOK_BOTH(ch)          (CURS_LOOK_MODE(ch) == Cursors::LookMode::Both)


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

    /// Какие курсоры сейчас активны. Какие активны, те и будут перемещаться по вращению ручки УСТАНОВКА.
    struct Active
    {
        enum E
        {
            U,
            T,
            None
        } value;
        Active(E v) : value(v) {};
        operator uint8() const { return (uint8)value; };
    };

    /// Режим слежения курсоров.
    struct LookMode
    {
        enum E
        {
            None,      ///< Курсоры не следят.
            Voltage,   ///< Курсоры следят за напряжением автоматически.
            Time,      ///< Курсоры следят за временем автоматически.
            Both       ///< Курсоры следят за временем и напряжением, в зависимости от того, какой курсоры вращали последним.
        } value;
        operator uint8() const { return (uint8)value; };
    };

    /// Получить позицию курсора напряжения
    static float PosU(Chan ch, int numCur);
    /// Возвращает true,если нужно рисовать курсоры
    static bool  NecessaryDraw();
    /// Получить строку курсора напряжения
    static pString Voltage(Chan source, int numCur, char buffer[20]);
    /// Возвращает значение курсора времени
    static float PosT(Chan ch, int num);
};

#pragma once
#include "defines.h"


class SU
{
public:
    /// @brief Преобразует value в текстовую строку. При этом выводятся все 8 разрядов
    /// @attention Строка будет храниться до следующего вызова функции. Если результат нужен большее количество времени, то его нужно скопировать себе
    static char* Bin2String(uint8 value);
};

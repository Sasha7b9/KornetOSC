#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Word
{
    char   *address;
    int8    numSymbols;
    uint8   notUsed0;
    uint8   notUsed1;
    uint8   notUsed2;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SU
{
public:
    /// Ёта команда сразу преобразует к верхенму регистру слово.
    static bool GetWord(const char *string, Word *word, const int numWord);

    static bool WordEqualZeroString(Word *word, char* string);

    static char *Db2String(float value, int numDigits, char bufferOut[20]);
    /// \brief ѕреобразует value в текстовую строку
    /// \attention —трока будет хранитьс€ до следующего вызова функции. ≈сли результат нужен большее количество времени, то его нужно скопировать себе
    static char* Int2String(int value,         ///< значение
                            bool alwaysSign,   ///< если установлен в true, знак будет выводитьс€ всегда
                            int numMinFields,  ///< минимальное число занимаемых знакомест. ≈сли дл€ вывода числа столько не требуетс€, лишние заполн€ютс€ нул€ми
                            char bufferOut[20] ///< сюда записываетс€ возвращаемое значение
    );
    /// —равнивает две строки. „исло символов берЄтс€ из str1
    static bool EqualsStrings(char *str1, char *str2);

    static bool EqualsStrings(char *str1, char *str2, int size);

    static bool EqualsZeroStrings(char *str1, char *str2);

private:
    /// ¬озвращает false, если выбор невозможен - строка кончилась.
    static bool ChooseSymbols(const char **string);
    /// ¬озвращает false, если выбор невозможен - строка кончилась.
    static bool ChooseSpaces(const char **string);
};

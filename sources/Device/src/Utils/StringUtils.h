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
    /// Возвращает число слов в строке string
    static int NumWords(const char *string);
    /// Возвращает указатель на n слово в строке. Если char == 0 - слова нет, если ret value == 0xffffffff - выходной буфер слишком мал
    static char *GetWord(char *string, int n, char *out, int size);
    /// Вычисляет число разрядов в целом типа int.
    static int NumDigitsInNumber(int value);

    static int NumDigitsInNumber(uint value);
    /// Эта команда сразу преобразует к верхенму регистру слово.
    static bool GetWord(const char *string, Word *word, const int numWord);

    static bool WordEqualZeroString(Word *word, char* string);

    static int FindSymbol(const char *string, char symbol);
    /// Возвращает символ в позиции pos от последнего (младшего)
    static char DigitInPosition(uint value, int pos);

    static char* FloatFract2String(float value, bool alwaysSign, char bufferOut[20]);

    static char *Db2String(float value, int numDigits, char bufferOut[20]);
    /// \brief Преобразует value в текстовую строку
    /// \attention Строка будет храниться до следующего вызова функции. Если результат нужен большее количество времени, то его нужно скопировать себе
    static char* Int2String(int value,         ///< значение
                            bool alwaysSign,   ///< если установлен в true, знак будет выводиться всегда
                            int numMinFields,  ///< минимальное число занимаемых знакомест. Если для вывода числа столько не требуется, лишние заполняются нулями
                            char bufferOut[20] ///< сюда записывается возвращаемое значение
    );
    /// Сравнивает две строки. Число символов берётся из str1
    static bool EqualsStrings(char *str1, char *str2);

    static bool EqualsStrings(char *str1, char *str2, int size);

    static bool EqualsZeroStrings(char *str1, char *str2);

private:
    /// Возвращает false, если выбор невозможен - строка кончилась.
    static bool ChooseSymbols(const char **string);
    /// Возвращает false, если выбор невозможен - строка кончилась.
    static bool ChooseSpaces(const char **string);
};

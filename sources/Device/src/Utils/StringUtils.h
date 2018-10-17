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

    /// @brief Преобразует time секунд в текстовую строку
    static char* Time2StringAccuracy(   float time,           ///< время в секундах. Может быть отрицательным
                                        bool alwaysSign,      ///< если true, знак показывается даже если time > 0
                                        char bufferOut[20],   ///< сюда записывается возвращаемое значение
                                        int numDigits         ///< количество цифр в строке
    );
    /// @brief Преобразует voltage вольт в текстовую строку
    /// @attention Страка будет храниться до следующего вызова функции. Если результат нужен большее количество времени, то его нужно скопитровать себе
    static char *Voltage2String(float voltage,     ///< значение напряжения в вольтах
                                bool alwaysSign,   ///< если установлено в true, знак выводится всегда
                                char buffer[20]    ///< сюда записывается возвращаемое значение
    );
    /// \brief Переводит число с плавающей точкой в текстовый вид. numDigits - число цифровых знакомест
    /// \attention Строка будет храниться до следующего вызова функции. Если результат нужен большее количество времени, то его нужно скопироавать себе.
    /// \retval указатель на строку с числом.
    static char *Float2String(float value, bool alwaysSign, int numDigits, char bufferOut[20]);
    /// \brief Преобразует time секунд в текстовую строку
    static char* Time2String(float time,    ///< время в секундах. Может быть отрицательным
                      bool alwaysSign,      ///< если true, знак показывается даже если time > 0
                      char buffer[20]       ///< сюда записывается возвращаемое значение
    );
    /// Преобразует freq герц в текстовую строку.
    static char* Freq2String(float freq, bool, char bufferOut[20]);

    static char* FloatFract2String(float value, bool alwaysSign, char bufferOut[20]);
    /// Преобразует градусы в строку.
    static char* Phase2String(float phase, bool, char bufferOut[20]);
    /// Преобразует freq герц в текстовую строку. При этом число количество цифр в строке равно numDigits
    static char* Freq2StringAccuracy(float freq, char bufferOut[20], int numDigits);

    static char *Db2String(float value, int numDigits, char bufferOut[20]);
    /*
    /// @brief Преобразует value в текстовую строку в шестнадцатиричном виде
    /// @attention Строка будет храниться до следующего вызова функции. Если результат нужен большее количество времени, то его нужно скопировать себе
    char* Hex8toString(uint8 value, char bufferOut[3]);

    char* Hex16toString(uint16 value, char bufferOut[5]);

    char* Hex32toString(uint value, char bufferOut[9], bool upper);
    */
    /// \brief Преобразует value в текстовую строку
    /// \attention Строка будет храниться до следующего вызова функции. Если результат нужен большее количество времени, то его нужно скопировать себе
    static char* Int2String(int value,         ///< значение
                            bool alwaysSign,   ///< если установлен в true, знак будет выводиться всегда
                            int numMinFields,  ///< минимальное число занимаемых знакомест. Если для вывода числа столько не требуется, лишние заполняются нулями
                            char bufferOut[20] ///< сюда записывается возвращаемое значение
    );
    /*
    /// Сравнивает две строки. Число символов берётся из str1
    bool EqualsStrings(char *str1, char *str2);

    bool EqualsStrings(char *str1, char *str2, int size);

    bool EqualsZeroStrings(char *str1, char *str2);
    */

private:
    /// Возвращает false, если выбор невозможен - строка кончилась.
    static bool ChooseSymbols(const char **string);
    /// Возвращает false, если выбор невозможен - строка кончилась.
    static bool ChooseSpaces(const char **string);
};

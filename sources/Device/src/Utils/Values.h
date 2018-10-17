#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Hex
{
public:
    Hex(uint v) : value(v) {};
    /// Преобразует значение в текстовую строку в шестнадцатиричном виде. depth задаёт разрядность числа - 8, 16 или 32 бит.
    char* ToHex(int depth, char bufferOut[9]) const;
    /// Преобразует значение в текстовую строку в двоичном виде. depth задаёт разрядность числа - 8, 16 или 32 бит.
    char* ToBin(int depth, char bufferOut[36]) const;
    /// Возвращает символ в позиции pos от последнего (младшего)
    char DigitInPosition(int pos) const;

    void Set(uint v) { value = v; };
    /// Возвращает число десятичных разрядов.
    int NumDigits() const;

    operator uint() const { return value; };

private:

    char *BinToString8(uint8 value, char buffer[9]) const;

    uint value;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Frequency
{
public:
    Frequency(float v) : value(v) {};

    char* ToString(char bufferOut[20]) const;
    /// Преобразует freq герц в текстовую строку. При этом число количество цифр в строке равно numDigits
    char* ToStringAccuracy(char bufferOut[20], int numDigits) const;

private:
    float value;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Time
{
public:

    Time(float v) : value(v) {};
    /// Преобразует время в текстовую строку
    char* ToString(bool alwaysSign,      ///< если true, знак показывается даже если time > 0
                   char buffer[20]       ///< сюда записывается возвращаемое значение
    ) const;
    /// Преобразует time секунд в текстовую строку
    char* ToStringAccuracy(bool alwaysSign,      ///< если true, знак показывается даже если time > 0
                           char bufferOut[20],   ///< сюда записывается возвращаемое значение
                           int numDigits         ///< количество цифр в строке
    ) const;

private:

    float value;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Voltage
{
public:

    Voltage(float v) : value(v) {};

    char* ToString(bool alwaysSign, char buffer[20]) const;

private:

    float value;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Phase
{
public:

    Phase(float v) : value(v) {};

    char* ToString(char buffer[20]) const;

private:

    float value;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Float
{
public:

    Float(float v) : m_val(v) {};
    /// \brief Переводит число с плавающей точкой в текстовый вид. numDigits - число цифровых знакомест
    /// \attention Строка будет храниться до следующего вызова функции. Если результат нужен большее количество времени, то его нужно скопироавать себе.
    /// \retval указатель на строку с числом.
    char *ToString(bool alwaysSign, int numDigits, char bufferOut[20]) const;

private:
    float m_val;
};

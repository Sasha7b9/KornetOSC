#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class Value
{
public:
    Value(T v) : value(v) {};
    virtual char* ToString(int depth, char *bufferOut) const = 0;
protected:
    T value;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Hex : public Value<uint>
{
public:
    Hex(uint v) : Value(v) {};
    /// ѕреобразует значение в текстовую строку в шестнадцатиричном виде. depth задаЄт разр€дность числа - 8, 16 или 32
    virtual char* ToString(int depth, char bufferOut[9]) const;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Bin : public Value<uint>
{
public:
    Bin(uint v) : Value(v) {};

    virtual char* ToString(int depth, char bufferOut[36]) const;

private:
    char* BinToString8(uint8 value, char buffer[9]) const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Frequency
{
public:
    Frequency(float v) : value(v) {};

    char* ToString(char bufferOut[20]) const;
    /// ѕреобразует freq герц в текстовую строку. ѕри этом число количество цифр в строке равно numDigits
    char* ToStringAccuracy(char bufferOut[20], int numDigits) const;

private:
    float value;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Time
{
public:

    Time(float v) : value(v) {};

    /// ѕреобразует врем€ в текстовую строку
    char* ToString(bool alwaysSign,      ///< если true, знак показываетс€ даже если time > 0
                   char buffer[20]       ///< сюда записываетс€ возвращаемое значение
    );
    /// ѕреобразует time секунд в текстовую строку
    char* ToStringAccuracy(bool alwaysSign,      ///< если true, знак показываетс€ даже если time > 0
                           char bufferOut[20],   ///< сюда записываетс€ возвращаемое значение
                           int numDigits         ///< количество цифр в строке
    );

private:

    float value;
};

//----------------------------------------------------------------------------------------------------------------------------------------------------


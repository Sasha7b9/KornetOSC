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
    /// ����������� �������� � ��������� ������ � ����������������� ����. depth ����� ����������� ����� - 8, 16 ��� 32
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
    /// ����������� freq ���� � ��������� ������. ��� ���� ����� ���������� ���� � ������ ����� numDigits
    char* ToStringAccuracy(char bufferOut[20], int numDigits) const;

private:
    float value;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Time
{
public:

    Time(float v) : value(v) {};

    /// ����������� ����� � ��������� ������
    char* ToString(bool alwaysSign,      ///< ���� true, ���� ������������ ���� ���� time > 0
                   char buffer[20]       ///< ���� ������������ ������������ ��������
    );
    /// ����������� time ������ � ��������� ������
    char* ToStringAccuracy(bool alwaysSign,      ///< ���� true, ���� ������������ ���� ���� time > 0
                           char bufferOut[20],   ///< ���� ������������ ������������ ��������
                           int numDigits         ///< ���������� ���� � ������
    );

private:

    float value;
};

//----------------------------------------------------------------------------------------------------------------------------------------------------


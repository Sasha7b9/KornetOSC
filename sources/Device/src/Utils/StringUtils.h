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
    /// ���������� ����� ���� � ������ string
    static int NumWords(const char *string);
    /// ���������� ��������� �� n ����� � ������. ���� char == 0 - ����� ���, ���� ret value == 0xffffffff - �������� ����� ������� ���
    static char *GetWord(char *string, int n, char *out, int size);
    /// ��������� ����� �������� � ����� ���� int.
    static int NumDigitsInNumber(int value);

    static int NumDigitsInNumber(uint value);
    /// ��� ������� ����� ����������� � �������� �������� �����.
    static bool GetWord(const char *string, Word *word, const int numWord);

    static bool WordEqualZeroString(Word *word, char* string);

    static int FindSymbol(const char *string, char symbol);
    /// ���������� ������ � ������� pos �� ���������� (��������)
    static char DigitInPosition(uint value, int pos);

    static char* FloatFract2String(float value, bool alwaysSign, char bufferOut[20]);

    static char *Db2String(float value, int numDigits, char bufferOut[20]);
    /// \brief ����������� value � ��������� ������
    /// \attention ������ ����� ��������� �� ���������� ������ �������. ���� ��������� ����� ������� ���������� �������, �� ��� ����� ����������� ����
    static char* Int2String(int value,         ///< ��������
                            bool alwaysSign,   ///< ���� ���������� � true, ���� ����� ���������� ������
                            int numMinFields,  ///< ����������� ����� ���������� ���������. ���� ��� ������ ����� ������� �� ���������, ������ ����������� ������
                            char bufferOut[20] ///< ���� ������������ ������������ ��������
    );
    /// ���������� ��� ������. ����� �������� ������ �� str1
    static bool EqualsStrings(char *str1, char *str2);

    static bool EqualsStrings(char *str1, char *str2, int size);

    static bool EqualsZeroStrings(char *str1, char *str2);

private:
    /// ���������� false, ���� ����� ���������� - ������ ���������.
    static bool ChooseSymbols(const char **string);
    /// ���������� false, ���� ����� ���������� - ������ ���������.
    static bool ChooseSpaces(const char **string);
};

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

    /// @brief ����������� time ������ � ��������� ������
    static char* Time2StringAccuracy(   float time,           ///< ����� � ��������. ����� ���� �������������
                                        bool alwaysSign,      ///< ���� true, ���� ������������ ���� ���� time > 0
                                        char bufferOut[20],   ///< ���� ������������ ������������ ��������
                                        int numDigits         ///< ���������� ���� � ������
    );
    /// @brief ����������� voltage ����� � ��������� ������
    /// @attention ������ ����� ��������� �� ���������� ������ �������. ���� ��������� ����� ������� ���������� �������, �� ��� ����� ������������ ����
    static char *Voltage2String(float voltage,     ///< �������� ���������� � �������
                                bool alwaysSign,   ///< ���� ����������� � true, ���� ��������� ������
                                char buffer[20]    ///< ���� ������������ ������������ ��������
    );
    /// \brief ��������� ����� � ��������� ������ � ��������� ���. numDigits - ����� �������� ���������
    /// \attention ������ ����� ��������� �� ���������� ������ �������. ���� ��������� ����� ������� ���������� �������, �� ��� ����� ������������ ����.
    /// \retval ��������� �� ������ � ������.
    static char *Float2String(float value, bool alwaysSign, int numDigits, char bufferOut[20]);
    /// \brief ����������� time ������ � ��������� ������
    static char* Time2String(float time,    ///< ����� � ��������. ����� ���� �������������
                      bool alwaysSign,      ///< ���� true, ���� ������������ ���� ���� time > 0
                      char buffer[20]       ///< ���� ������������ ������������ ��������
    );
    /// ����������� freq ���� � ��������� ������.
    static char* Freq2String(float freq, bool, char bufferOut[20]);

    static char* FloatFract2String(float value, bool alwaysSign, char bufferOut[20]);
    /// ����������� ������� � ������.
    static char* Phase2String(float phase, bool, char bufferOut[20]);
    /// ����������� freq ���� � ��������� ������. ��� ���� ����� ���������� ���� � ������ ����� numDigits
    static char* Freq2StringAccuracy(float freq, char bufferOut[20], int numDigits);

    static char *Db2String(float value, int numDigits, char bufferOut[20]);
    /*
    /// @brief ����������� value � ��������� ������ � ����������������� ����
    /// @attention ������ ����� ��������� �� ���������� ������ �������. ���� ��������� ����� ������� ���������� �������, �� ��� ����� ����������� ����
    char* Hex8toString(uint8 value, char bufferOut[3]);

    char* Hex16toString(uint16 value, char bufferOut[5]);

    char* Hex32toString(uint value, char bufferOut[9], bool upper);
    */
    /// \brief ����������� value � ��������� ������
    /// \attention ������ ����� ��������� �� ���������� ������ �������. ���� ��������� ����� ������� ���������� �������, �� ��� ����� ����������� ����
    static char* Int2String(int value,         ///< ��������
                            bool alwaysSign,   ///< ���� ���������� � true, ���� ����� ���������� ������
                            int numMinFields,  ///< ����������� ����� ���������� ���������. ���� ��� ������ ����� ������� �� ���������, ������ ����������� ������
                            char bufferOut[20] ///< ���� ������������ ������������ ��������
    );
    /*
    /// ���������� ��� ������. ����� �������� ������ �� str1
    bool EqualsStrings(char *str1, char *str2);

    bool EqualsStrings(char *str1, char *str2, int size);

    bool EqualsZeroStrings(char *str1, char *str2);
    */

private:
    /// ���������� false, ���� ����� ���������� - ������ ���������.
    static bool ChooseSymbols(const char **string);
    /// ���������� false, ���� ����� ���������� - ������ ���������.
    static bool ChooseSpaces(const char **string);
};

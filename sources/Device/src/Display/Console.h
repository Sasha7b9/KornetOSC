#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Console
{
public:
    static void Draw();

    static void AddString(char *string);

private:
    /// true ��������, ��� ��� ������� ������ ������� � ��������� � �� ����� ������ ������ (��� ����������, ����� ���������� ��� �� ����������)
    static bool inProcessDrawConsole;
    /// ���������� ����������� ����� � �������
    static int stringInConsole;
};


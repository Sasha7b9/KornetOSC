#pragma once


class HiPart
{
public:
    
    static void Draw();

    static void WriteCursors();

    static void DrawRightPart();

    static void EnableTrigLabel(bool enable);

private:
    /// ������� ����, ����� �� �������� ������ �������������
    static bool trigLabel;
};

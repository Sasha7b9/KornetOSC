#pragma once


class HiPart
{
public:
    
    static void Draw();

    static void WriteCursors();

    static void DrawRightPart();

    static void EnableTrigLabel(bool enable);

private:
    /// Признак того, нужно ли выводить значок синхронизации
    static bool trigLabel;
};

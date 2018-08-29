#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Settings
 *  @{
 *  @defgroup SettingsCursors Settings Cursors
 *  @{
 */

/// ����� ������� ������ �������. ����� �������, �� � ����� ������������ �� �������� ����� ���������.
struct CursActive
{
    enum E
    {
        U,
        T,
        None
    } value;
    CursActive(E v) : value(v) {};
    operator uint8() const { return (uint8)value; };
};

/// ����� �������� ��������.
struct CursLookMode
{
    enum E
    {
        None,      ///< ������� �� ������.
        Voltage,   ///< ������� ������ �� ����������� �������������.
        Time,      ///< ������� ������ �� �������� �������������.
        Both       ///< ������� ������ �� �������� � �����������, � ����������� �� ����, ����� ������� ������� ���������.
    } value;
    operator uint8() const { return (uint8)value; };
};

/// ����� �������� ���������
struct CursCntrl
{
    enum E
    {
        _1,        ///< ������
        _2,        ///< ������
        _1_2,      ///< ������
        Disable    ///< �������
    } value;
    operator uint8() const { return (uint8)value; };
};


#define CURSORS_SHOW_FREQ           (set.curs_showFreq)

/// ������� ������ ������ ������ �������
#define CURS_SOURCE                 (set.curs_source)
/// ������� ������� ������ A
#define CURS_SOURCE_A               (CURS_SOURCE.IsA())
/// ������� ������� ������ B
#define CURS_SOURCE_B               (CURS_SOURCE.IsB())

#define CURsU_CNTRL_CH(ch)          (set.curs_cntrlU[ch])
#define CURsU_CNTRL                 (CURsU_CNTRL_CH(CURS_SOURCE))
#define CURsU_CNTRL_1               (CURsU_CNTRL == CursCntrl::_1)
#define CURsU_CNTRL_2               (CURsU_CNTRL == CursCntrl::_2)
#define CURsU_CNTRL_1_2             (CURsU_CNTRL == CursCntrl::_1_2)
#define CURsU_DISABLED              (CURsU_CNTRL == CursCntrl::Disable)
#define CURsU_ENABLED               (!CURsU_DISABLED)

#define CURsT_CNTRL_CH(ch)          (set.curs_cntrlT[ch])
#define CURsT_CNTRL                 (CURsT_CNTRL_CH(CURS_SOURCE))
#define CURsT_CNTRL_1               (CURsT_CNTRL == CursCntrl::_1)
#define CURsT_CNTRL_2               (CURsT_CNTRL == CursCntrl::_2)
#define CURsT_CNTRL_1_2             (CURsT_CNTRL == CursCntrl::_1_2)
#define CURsT_DISABLED              (CURsT_CNTRL == CursCntrl::Disable)
#define CURsT_ENABLED               (!CURsT_DISABLED)

/// ������� ������� �������
#define CURsT_POS(ch, num)          GetCursPosT(ch, num)

/// ���������� �������� ����������, ��������������� 100%
#define dUperc(ch)                  (set.curs_deltaU100percents[ch])
/// ���������� �������� �������, �������������� 100%
#define dTperc(ch)                  (set.curs_deltaT100percents[ch])

/// ������ ��������� ��������� ����� ���������
#define CURS_ACTIVE                 (set.curs_active)
/// ����� ��������� ��������� ��������� ����������
#define CURS_ACTIVE_U               (CURS_ACTIVE == CursActive::U)
/// ����� ��������� ��������� ��������� �������
#define CURS_ACTIVE_T               (CURS_ACTIVE == CursActive::T)

/// ����� �������� �� ���������
#define CURS_LOOK_MODE(ch)          (set.curs_lookMode[ch])
/// �������� �������� �� ��������� ����������
#define CURS_LOOK_U(ch)             (CURS_LOOK_MODE(ch) == CursLookMode::Voltage)
/// �������� �������� �� ��������� �������
#define CURS_LOOK_T(ch)             (CURS_LOOK_MODE(ch) == CursLookMode::Time)
/// �������� �������� �� ��������� ������� � ����������
#define CURS_LOOK_BOTH(ch)          (CURS_LOOK_MODE(ch) == CursLookMode::Both)

#define CURS_SHOW                   (set.curs_showCursors)


/// ���������� true,���� ����� �������� �������
bool  sCursors_NecessaryDrawCursors();
/// �������� ������ ������� ����������
const char *sCursors_GetCursVoltage(Chan source, int numCur, char buffer[20]);
/// �������� ������ ������� �������
const char *sCursors_GetCursorTime(Chan source, int numCur, char buffer[20]);
/// �������� ������ ��������� �������� ����������
const char *sCursors_GetCursorPercentsU(Chan source, char buffer[20]);
/// �������� ������ ��������� �������� �������
const char *sCursors_GetCursorPercentsT(Chan source, char buffer[20]);
/// ���������� �������� ������� �������
float GetCursPosT(Chan ch, int num);

void SetCursPosT_temp(Chan ch, int num, float value);

/** @}  @}
 */

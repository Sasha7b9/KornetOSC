#pragma once
#include "defines.h"
#include "Settings/SettingsTypes.h"


#define ADDR_ALTERA         ((uint8*)NOR_MEMORY_ADRESS1)


// Адреса альтеры
#define WR_START            (ADDR_ALTERA + 0)           ///< Старт
#define WR_TBASE            (ADDR_ALTERA + 1)           ///< Развёртка
#define WR_PRED_LO          (ADDR_ALTERA + 2)           ///< Предзапуск
#define WR_PRED_HI          (ADDR_ALTERA + 3)
#define WR_POST_LO          (ADDR_ALTERA + 4)           ///< Послезапуск
#define WR_POST_HI          (ADDR_ALTERA + 5)

#define WR_UPR              (ADDR_ALTERA + 6)           ///< Управление
#define BIT_UPR_RAND        0                           ///< Вкл. рандомизатор
#define BIT_UPR_PEAK        1                           ///< Пиковый детектор
#define BIT_UPR_CALIBR      2                           ///< Калибратор

#define WR_FREQMETER        (ADDR_ALTERA + 7)           ///< Управление частотомером
#define WR_TRIG             (ADDR_ALTERA + 9)           ///< Управление синхронизацией/запуском
#define WR_START_ADDR       (ADDR_ALTERA + 11)          ///< \brief Старт адреса. Нужно записываеть по этому адресу, чтобы начать чтение с 
                                                        ///  произвольного адреса (который мы записываем в предзапуск)

#define RD_DATA_A           (ADDR_ALTERA + 0)           ///< Данные первого канала
#define RD_ADC_A            ((uint16 *)(RD_DATA_A))
#define RD_DATA_A_PEAK_MAX  (RD_DATA_A)                 ///< Данные пикового детектора первого канала
#define RD_DATA_A_PEAK_MIN  (RD_DATA_A_PEAK_MAX + 1)
#define RD_DATA_B           (ADDR_ALTERA + 2)           ///< Данные второго канала
#define RD_ADC_B            ((uint16 *)(RD_DATA_B))
#define RD_DATA_B_PEAK_MAX  (RD_DATA_B)                 ///< Данные пиквого детектора второго канала
#define RD_DATA_B_PEAK_MIN  (RD_DATA_B_PEAK_MAX + 1)
#define RD_LAST_RECORD_LO   (ADDR_ALTERA + 4)           ///< Адрес последней записи
#define RD_LAST_RECORD_HI   (ADDR_ALTERA + 5)
#define RD_FREQ_BYTE_0      (ADDR_ALTERA + 8)           ///< Измеренное значение частоты
#define RD_FREQ_BYTE_1      (ADDR_ALTERA + 9)
#define RD_FREQ_BYTE_2      (ADDR_ALTERA + 12)
#define RD_FREQ_BYTE_3      (ADDR_ALTERA + 13)
#define RD_PERIOD_BYTE_0    (ADDR_ALTERA + 16)          ///< Измеренное значение периода
#define RD_PERIOD_BYTE_1    (ADDR_ALTERA + 17)
#define RD_PERIOD_BYTE_2    (ADDR_ALTERA + 20)
#define RD_PERIOD_BYTE_3    (ADDR_ALTERA + 21)
#define RD_FLAG_LO          (ADDR_ALTERA + 24)          ///< Флаг
#define BIT_FLAG_DATA_READY 0                           ///< Данные готовы для считывания
#define BIT_FLAG_PRED       2                           ///< Если 1, то предзапуск отсчитал, можно давать принудительный запуск

#define FL_DATA_READY       0   ///< 0 - данные готовы
#define FL_TRIG_READY       1   ///< 1 - наличие синхроимпульса
#define FL_PRED_READY       2   ///< 2 - окончание счета предзапуска
#define FL_POINT_READY      3   ///< 3 - признак того, что точка готова (в поточечном выводе)
#define FL_FREQ_READY       4   ///< 4 - можно считывать частоту
#define FL_PERIOD_READY     5   ///< 5 - можно считывать период
#define FL_LAST_RECOR       6   ///< 6 - признак последней записи - определяет, какой бит ставить первым
#define FL_OVERFLOW_FREQ    8   ///< 8 - признак переполнения счётчика частоты
#define FL_OVERFLOW_PERIOD  9   ///< 9 - признак переполнения счётчика периода

#define RD_FLAG_HI          (ADDR_ALTERA + 25)

#define UPR_BIT_PEAKDET            1    ///< пиковый детектор - 0/1 выкл/вкл
#define UPR_BIT_CALIBRATOR_AC_DC    2   ///< постоянное/переменное
#define UPR_BIT_CALIBRATOR_VOLTAGE  3   ///< 0/4В
#define UPR_BIT_RECORDER            4   ///< 0 - обычный режим, 1 - регистратор

#define FPGA_MAX_POINTS (8 * 1024)

#define AVE_VALUE           127
#define MIN_VALUE           (AVE_VALUE - 125)
#define MAX_VALUE           (AVE_VALUE + 125)

/// С этого значения tBase должен включаться режим поточечного вывода
#define MIN_TBASE_P2P       TBase_50ms
/// Минимальный масштаб по времени, при котором возможно включение режима пикового детектора
#define MIN_TBASE_PEC_DEAT  TBase_500ns
/// Если значение == 0, значит, его нет. Это нужно для режимов рандомизатора и поточечного вывода p2p, а также для tShift ранее считанного сигнала
#define NONE_VALUE  0


/// Минимальное значение смещения канала по напряжению, засылаемое в аналоговую часть. Соответствует смещению 10 клеток вниз от центральной линии
#define RShiftMin       20
/// Среднее значение смещения канала по напряжению, засылаемое в аналоговую часть. Соответствует расположению марера по центру экрана
#define RShiftZero      500
/// Максимальное значение смещения канала по напряжению, засылаемое в аналоговую часть. Соответствует смещению 10 клеток вверх от центральной лиини
#define RShiftMax       980
/// Сколько точек смещения в одной клетке
#define RSHIFT_IN_CELL (((RShiftMax) - (RShiftMin)) / 24)
/// На столько единиц нужно изменить значение смещения, чтобы маркер смещения по напряжению передвинулся на одну точку.
#define STEP_RSHIFT     (((RShiftMax - RShiftMin) / 24) / 20)


extern uint16 *addressesADC[NumChannels];
#define ADDRESS_READ(ch)    addressesADC[ch];

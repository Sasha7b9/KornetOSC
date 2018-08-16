#pragma once
#include "Settings/Settings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Settings
 *  @{
 *  @defgroup SettingsService Settings Service
 *  @{
 */
 
#define LANG                            (set.serv_lang)
#define LANG_RU                         (LANG == Language::RU)
#define LANG_EN                         (LANG == Language::EN)

#define RECORDER_MODE                   (set.serv_recorder)

#define TIME_SHOW_LEVELS                (set.disp_timeShowLevels)

#define FREQ_METER_ENABLED              (set.freq_Enable)
#define FREQ_METER_TIMECOUNTING         (set.freq_TimeCounting)
#define FREQ_METER_FREQ_CLC             (set.freq_FreqClc)
#define FREQ_METER_NUM_PERIODS          (set.freq_NumberPeriods)

#define CALIBRATOR_MODE                 (set.serv_calibratorMode)

#define SOUND_ENABLED                   (set.serv_soundEnable)
#define SOUND_VOLUME                    (set.serv_soundVolume)

#define COLOR_SCHEME                    (set.serv_colorScheme)
#define COLOR_SCHEME_IS_WHITE_LETTERS   (COLOR_SCHEME == ColorScheme_WhiteLetters)

#define REC_PLACE_OF_SAVING             (set.rec_PlaceOfSaving)
#define REC_NUM_CURSOR                  (set.rec_NumCursor)


/** @}  @}
 */

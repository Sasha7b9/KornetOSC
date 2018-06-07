﻿#pragma once
#include "Settings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Settings
 *  @{
 *  @defgroup SettingsTrig Settings Trig
 *  @{
 */

#define SET_TRIGLEV(ch)         (set.trig_lev[ch])
#define SET_TRIGLEV_SOURCE      SET_TRIGLEV(TRIGSOURCE)
#define SET_TRIGLEV_A           (SET_TRIGLEV(A))
#define SET_TRIGLEV_B           (SET_TRIGLEV(B))

#define TRIG_MODE_FIND          (set.trig_ModeFind)
#define TRIG_MODE_FIND_HAND     (TRIG_MODE_FIND == TrigModeFind_Hand)
#define TRIG_MODE_FIND_AUTO     (TRIG_MODE_FIND == TrigModeFind_Auto)

#define TRIGSOURCE              (set.trig_source)
#define TRIGSOURCE_IS_A         (TRIGSOURCE == TrigSource_A)
#define TRIGSOURCE_IS_B         (TRIGSOURCE == TrigSource_B)
#define TRIGSOURCE_IS_EXT       (TRIGSOURCE == TrigSource_Ext)

#define START_MODE              (set.trig_StartMode)
#define START_MODE_AUTO         (START_MODE == StartMode_Auto)
#define START_MODE_WAIT         (START_MODE == StartMode_Wait)
#define START_MODE_SINGLE       (START_MODE == StartMode_Single)

#define TRIG_POLARITY           (set.trig_polarity)
#define TRIG_POLARITY_FALLING   (TRIG_POLARITY == Polarity_Falling)
#define TRIG_POLARITY_FRONT     (TRIG_POLARITY == Polarity_Rising)

#define TRIG_INPUT              (set.trig_input)
#define TRIG_INPUT_AC           (TRIG_INPUT == TrigInput_AC)
#define TRIG_INPUT_LPF          (TRIG_INPUT == TrigInput_LPF)
#define TRIG_INPUT_FULL         (TRIG_INPUT == TrigInput_Full)

#define TRIG_TIME_DELAY         (set.trig_TimeDelay)

/** @}  @}
 */

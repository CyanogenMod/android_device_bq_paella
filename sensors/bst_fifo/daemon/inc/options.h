/*!
 * @section LICENSE
 *
 * (C) Copyright 2011~2015 Bosch Sensortec GmbH All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *
 * @file         options.h
 * @date         "Thu Jan 8 18:20:01 2015 +0800"
 * @commit       "4b0860f"
 *
 * @brief
 *
 * @detail
 *
 */

#ifndef __OPTIONS_H
#define __OPTIONS_H
#include "sensor_def.h"
#include "configure.h"

//#define CFG_ACC_USE_RAW_DATA
#define CFG_DISCARD_OLD_CMD
#define CFG_SET_AXIS_FROM_FILE

#ifdef __FASTEST_MODE_100HZ__
#define CFG_DELAY_A_MIN 10
#else
#define CFG_DELAY_A_MIN 5
#endif //endif of __FASTEST_MODE_100HZ__
#define CFG_DELAY_A_MAX 200

#define CFG_DELAY_M_MIN 40//50
#define CFG_DELAY_M_MIN_M4G 20
#define CFG_DELAY_M_MAX 200

#define CFG_DELAY_VIRTUAL_G_MIN 20
#define CFG_DELAY_VIRTUAL_G_MAX 200

#ifdef __FASTEST_MODE_100HZ__
#define CFG_DELAY_G_MIN 10
#else
#define CFG_DELAY_G_MIN 5
#endif //endif of __FASTEST_MODE_100HZ__
#define CFG_DELAY_G_MAX 200

#ifdef __FASTEST_MODE_100HZ__
#define CFG_DELAY_O_MIN 10
#else
#define CFG_DELAY_O_MIN 5
#endif //endif of __FASTEST_MODE_100HZ__
#define CFG_DELAY_O_MAX 200

#ifdef __FASTEST_MODE_100HZ__
#define CFG_DELAY_VG_MIN 10
#else
#define CFG_DELAY_VG_MIN 5
#endif //endif of __FASTEST_MODE_100HZ__
#define CFG_DELAY_VG_MAX 200

#ifdef __FASTEST_MODE_100HZ__
#define CFG_DELAY_VLA_MIN 10
#else
#define CFG_DELAY_VLA_MIN 5
#endif //endif of __FASTEST_MODE_100HZ__
#define CFG_DELAY_VLA_MAX 200

#ifdef __FASTEST_MODE_100HZ__
#define CFG_DELAY_VRV_MIN 10
#else
#define CFG_DELAY_VRV_MIN 5
#endif //endif of __FASTEST_MODE_100HZ__
#define CFG_DELAY_VRV_MAX 200

#define CFG_DELAY_GEST_FLIP_MIN   100
#define CFG_DELAY_GEST_FLIP_MAX   100

#define FLIP_FACE_UP              105
#define FLIP_FACE_DOWN            15

#ifdef __UNCALIBRATED_VIRTUAL_SENSOR_SUPPORT__
#define CFG_DELAY_GRV_MIN CFG_DELAY_VRV_MIN
#define CFG_DELAY_GRV_MAX CFG_DELAY_VRV_MAX

#define CFG_DELAY_GU_MIN CFG_DELAY_G_MIN
#define CFG_DELAY_GU_MAX CFG_DELAY_G_MAX

#ifdef __USECASE_TYPE_M4G__
#define CFG_DELAY_MU_MIN CFG_DELAY_M_MIN_M4G
#else
#define CFG_DELAY_MU_MIN CFG_DELAY_M_MIN
#endif
#define CFG_DELAY_MU_MAX CFG_DELAY_M_MAX

#endif

#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
#define CFG_DELAY_GEOM_RV_MIN CFG_DELAY_VRV_MIN
#define CFG_DELAY_GEOM_RV_MAX CFG_DELAY_VRV_MAX
#endif

#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_0__
#define CFG_DELAY_STC_MIN CFG_DELAY_A_MIN
#define CFG_DELAY_STC_MAX CFG_DELAY_A_MAX

#define CFG_DELAY_STD_MIN CFG_DELAY_A_MIN
#define CFG_DELAY_STD_MAX CFG_DELAY_A_MAX

#endif


#endif

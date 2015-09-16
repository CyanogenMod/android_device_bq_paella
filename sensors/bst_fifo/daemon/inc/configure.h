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
 * @file       configure.h
 * @date       "Thu Jan 8 18:20:01 2015 +0800"
 * @commit     "4b0860f"
 *
 * @brief
 *
 * @detail
 *
 */


#ifndef __CONFIGURE_H
#define __CONFIGURE_H
#define CFG_CHANNEL_A        AVAILABLE
#define CFG_CHANNEL_G        AVAILABLE
#define CFG_CHANNEL_M        AVAILABLE
#define CFG_CHANNEL_O        VIRTUAL
#define CFG_CHANNEL_VG       VIRTUAL
#define CFG_CHANNEL_VLA      VIRTUAL
#define CFG_CHANNEL_VRV      VIRTUAL

#ifdef __UNCALIBRATED_VIRTUAL_SENSOR_SUPPORT__
#define CFG_CHANNEL_GRV      VIRTUAL
#define CFG_CHANNEL_GYU      VIRTUAL
#define CFG_CHANNEL_MU       VIRTUAL
#endif

#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
#define CFG_CHANNEL_GEOM_RV  VIRTUAL
#endif

#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_0__
#define CFG_CHANNEL_STC      VIRTUAL
#define CFG_CHANNEL_STD      VIRTUAL
#endif


#endif


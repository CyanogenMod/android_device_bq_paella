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
 * @file         BstSensorPriv.h
 * @date         "Fri Jan 9 17:45:01 2015 +0800"
 * @commit       "7c424a4"
 *
 * @brief
 *
 * @detail
 *
 */


#ifndef __SENSOR_PRIV_H
#define __SENSOR_PRIV_H
#include "BstSensorDataType.h"

#define PATH_DIR_SENSOR_STORAGE "/data/misc/sensor"
#define FIFO_CMD (PATH_DIR_SENSOR_STORAGE "/fifo_cmd")
#define FIFO_DAT (PATH_DIR_SENSOR_STORAGE "/fifo_dat")
#define FIFO_LIST (PATH_DIR_SENSOR_STORAGE "/fifo_list")


#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) ((int)(sizeof(arr) / sizeof((arr)[0])))
#endif

#define SCALE_TIME_S2NS 1000000000LL
#define SCALE_TIME_MS2NS 1000000LL
#define SCALE_TIME_US2NS 1000LL


#define SET_SENSOR_ACTIVE	0x01
#define SET_SENSOR_DELAY	0x02
#define SET_SENSOR_FLUSH	0x03

#define CHANNEL_PKT_MAGIC_CMD   (int)'C'
#define CHANNEL_PKT_MAGIC_DAT   (int)'D'
#define CHANNEL_PKT_MAGIC_LIST  (int)'L'

#ifdef __HYBRID_HAL__
struct bst_axis_remap {
	int src_x:3;
	int src_y:3;
	int src_z:3;

	int sign_x:2;
	int sign_y:2;
	int sign_z:2;
};

#define BST_DFT_AXIS_REMAP_TAB_SZ 8
#endif

#endif

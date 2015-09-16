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
 * @file         channels.c
 * @date         "Thu Jan 8 18:20:01 2015 +0800"
 * @commit       "4b0860f"
 *
 * @brief
 *
 * @detail
 *
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <linux/ioctl.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define LOG_TAG_MODULE "<channels.c>"
#include "sensord.h"
#include "sensor_def.h"
#include "configure.h"


struct channel g_list_ch[] = {
	{
		name: "ACCELERATION",
		type: SENSOR_TYPE_A,
		handle: SENSOR_HANDLE_ACCELERATION,

		cfg:
			{
				availability: CFG_CHANNEL_A,
				calib_bg: 0,
				sp_name: "SP_FUSION",
#ifdef CFG_BYPASS_PROC_CHANNEL_A
				bypass_proc:1
#endif
			},

		init: channel_init_a,
		get_data: get_data_a,
	},

	{
		name: "GYROSCOPE",
		type: SENSOR_TYPE_G,
		handle: SENSOR_HANDLE_GYROSCOPE,

		cfg:
			{
				availability: CFG_CHANNEL_G,
				calib_bg: 0,
				sp_name: "SP_FUSION"
			},

		init: channel_init_g,
		get_data: get_data_g,
	},

	{
		name: "MAGNETIC",
		type: SENSOR_TYPE_M,
		handle: SENSOR_HANDLE_MAGNETIC_FIELD,

		cfg:
			{
				availability: CFG_CHANNEL_M,
				calib_bg: 0,
				sp_name: "SP_FUSION"
			},

		init: channel_init_m,
		get_data: get_data_m,
	},

	{
		name: "ORIENTATION",
		type: SENSOR_TYPE_O,
		handle: SENSOR_HANDLE_ORIENTATION,

		cfg:
			{
				availability: CFG_CHANNEL_O,
				calib_bg: 0,
				sp_name: "SP_FUSION"
			},

		init: channel_init_o,
		get_data: get_data_o,
	},

	{
		name: "GRAVITY",
		type: SENSOR_TYPE_VG,
		handle: SENSOR_HANDLE_GRAVITY,

		cfg:
			{
				availability: CFG_CHANNEL_VG,
				calib_bg: 0,
				sp_name: "SP_FUSION"
			},

		init: channel_init_vg,
		get_data: get_data_vg,
	},

	{
		name: "LINEAR_ACCELERATION",
		type: SENSOR_TYPE_VLA,
		handle: SENSOR_HANDLE_LINEAR_ACCELERATION,

		cfg:
			{
				availability: CFG_CHANNEL_VLA,
				calib_bg: 0,
				sp_name: "SP_FUSION"
			},

		init: channel_init_vla,
		get_data: get_data_vla,
	},

	{
		name: "ROTATION_VECOTR",
		type: SENSOR_TYPE_VRV,
		handle: SENSOR_HANDLE_ROTATION_VECTOR,

		cfg:
			{
				availability: CFG_CHANNEL_VRV,
				calib_bg: 0,
				sp_name: "SP_FUSION"
			},

		init: channel_init_vrv,
		get_data: get_data_vrv,
	},

#ifdef __FLIP_GESTURE__
	{
		name: "GEST_FLIP",
		type: SENSOR_TYPE_GEST_FLIP,
		handle: SENSOR_HANDLE_GEST_FLIP,

		cfg:
			{
				availability: VIRTUAL,
				calib_bg: 0,
				sp_name: "SP_FUSION"
			},

		init: channel_gest_flip_init,
		get_data: channel_gest_flip_get_data,
		enable: channel_gest_flip_enable,
	},
#endif
	{
		name: "SW SIGNIFICANT SENSOR",
		type: SENSOR_TYPE_SW_SIGNIFICANT_MOTION,
		handle: SENSOR_HANDLE_SW_SIGNIFCANT_MOITON,

		cfg:
			{
				availability: VIRTUAL,
				calib_bg: 0,
				sp_name: "SP_FUSION"
			},

		init: channel_sgm_init,
		get_data: channel_sgm_get_data,
		enable: channel_sgm_enable,
	},

#ifdef __UNCALIBRATED_VIRTUAL_SENSOR_SUPPORT__
	{
		name: "GAME_ROTATION_VECOTR",
		type: SENSOR_TYPE_GRV,
		handle: SENSOR_HANDLE_GAME_ROTATION_VECTOR,

		cfg:
			{
				availability: CFG_CHANNEL_GRV,
				calib_bg: 0,
				sp_name: "SP_FUSION"
			},

		init: channel_init_grv,
		get_data: get_data_grv,
	},

	{
		name: "GYROSCOPE_UNCALIBRATED",
		type: SENSOR_TYPE_GYU,
		handle: SENSOR_HANDLE_GYROSCOPE_UNCALIBRATED,

		cfg:
			{
				availability: CFG_CHANNEL_GYU,
				calib_bg: 0,
				sp_name: "SP_FUSION"
			},

		init: channel_init_gu,
		get_data: get_data_gu,
	},

	{
		name: "MAGNETIC_UNCALIBRATED",
		type: SENSOR_TYPE_MU,
		handle: SENSOR_HANDLE_MAGNETIC_FIELD_UNCALIBRATED,

		cfg:
			{
				availability: CFG_CHANNEL_MU,
				calib_bg: 0,
				sp_name: "SP_FUSION"
			},

		init: channel_init_mu,
		get_data: get_data_mu,
	},
#endif

#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
	{
		name: "GEOMAGNETIC_ROTATION_VECTOR",
		type: SENSOR_TYPE_GEOM_RV,
		handle: SENSOR_HANDLE_GEOMAGNETIC_ROTATION_VECTOR,

		cfg:
			{
				availability: CFG_CHANNEL_GEOM_RV,
				calib_bg: 0,
				sp_name: "SP_FUSION"
			},

		init: channel_init_geom_rv,
		get_data: get_data_geom_rv,
	},
#endif

#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_0__
	{
		name: "STEP_COUNTER",
		type: SENSOR_TYPE_STC,
		handle: SENSOR_HANDLE_STEP_COUNTER,

		cfg:
			{
				availability: CFG_CHANNEL_STC,
				calib_bg: 0,
				sp_name: "SP_FUSION"
			},

		init: channel_init_stc,
		get_data: get_data_stc,
		enable: channel_stc_enable,
	},
	{
		name: "STEP_DETECTOR",
		type: SENSOR_TYPE_STD,
		handle: SENSOR_HANDLE_STEP_DETECTOR,

		cfg:
			{
				availability: CFG_CHANNEL_STD,
				calib_bg: 0,
				sp_name: "SP_FUSION"
			},

		init: channel_init_std,
		get_data: get_data_std,
		enable: channel_std_enable,
	},
#endif


};

int channel_get_num()
{
	return ARRAY_SIZE(g_list_ch);
}

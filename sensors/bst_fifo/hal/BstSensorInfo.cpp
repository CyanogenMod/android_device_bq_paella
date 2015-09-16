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
 * @file         BstSensorInfo.cpp
 * @date         "Thu Jan 8 18:20:01 2015 +0800"
 * @commit       "4b0860f"
 *
 * @brief
 *
 * @detail
 *
 */

#include "sensors.h"

#include "BstSensor.h"
#include "BstSensorInfo.h"

#define VENDOR_NAME_BST_SHORT "BOSCH "
#define VENDOR_NAME_BST "Bosch Sensortec GmbH"
#define SENSOR_STR " Sensor"

#define SENSOR_VER_BST 3060105

#if defined(L8910_COMMON) || defined(L9100_COMMON)
#define SENSOR_REMOVE_UNSUPPORT
#endif

const struct sensor_t BstSensorInfo::g_bst_sensor_list[] = {
	{
		name: VENDOR_NAME_BST_SHORT BST_SENSOR_NAME_A SENSOR_STR,
		vendor: VENDOR_NAME_BST,
		version: SENSOR_VER_BST,
		handle: SENSORS_ACCELERATION_HANDLE,
		type: SENSOR_TYPE_ACCELEROMETER,
		maxRange: 16.0f * 9.805,
		resolution: 4.0f * 9.805 / (1 << HW_INFO_BITWIDTH_A),
		power: 0.13f,
#ifdef __FASTEST_MODE_100HZ__
		minDelay: 10000,
#else
		minDelay: 5000,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
		fifoReservedEventCount: 0,
		fifoMaxEventCount: 0,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_3__
		stringType: SENSOR_STRING_TYPE_ACCELEROMETER,
		requiredPermission: "",
		maxDelay: 200000,
		flags: SENSOR_FLAG_CONTINUOUS_MODE,
#endif
		reserved: {}
	},

	{
	#ifdef __AMM202__
		name: "AKM09911 " BST_SENSOR_NAME_M SENSOR_STR,
	#elif defined __AMM203__
		name: "AKM09912 " BST_SENSOR_NAME_M SENSOR_STR,
	#elif defined __AMM204__
		name: "YAS532 " BST_SENSOR_NAME_M SENSOR_STR,
	#elif defined __AMM205__
		name: "YAS537 " BST_SENSOR_NAME_M SENSOR_STR,
	#elif defined __AMM206__
		name: "AKM09913 " BST_SENSOR_NAME_M SENSOR_STR,
	#else
		name: VENDOR_NAME_BST_SHORT BST_SENSOR_NAME_M SENSOR_STR,
	#endif
		vendor: VENDOR_NAME_BST,
		version: SENSOR_VER_BST,
		handle: SENSORS_MAGNETIC_FIELD_HANDLE,
		type: SENSOR_TYPE_MAGNETIC_FIELD,
		maxRange: 1600.0f,
		resolution: 0.3f,
		power: 0.5f,
#ifdef __USECASE_TYPE_M4G__
		minDelay: 20000,
#else
		minDelay: 40000,
#endif

#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
                fifoReservedEventCount: 0,
                fifoMaxEventCount: 0,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_3__
                stringType: SENSOR_STRING_TYPE_MAGNETIC_FIELD,
                requiredPermission: "",
                maxDelay: 200000,
                flags: SENSOR_FLAG_CONTINUOUS_MODE,
#endif
		reserved: {}
	},

	{
		name: VENDOR_NAME_BST_SHORT BST_SENSOR_NAME_G SENSOR_STR,
		vendor: VENDOR_NAME_BST,
		version: SENSOR_VER_BST,
		handle: SENSORS_GYROSCOPE_HANDLE,
		type: SENSOR_TYPE_GYROSCOPE,
		maxRange: 2500.0f,
		resolution: 250.0f / (1 << 16),
		power: 5.0f,
#ifdef __FASTEST_MODE_100HZ__
		minDelay: 10000,
#else
		minDelay: 5000,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
                fifoReservedEventCount: 0,
                fifoMaxEventCount: 0,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_3__
                stringType: SENSOR_STRING_TYPE_GYROSCOPE,
                requiredPermission: "",
                maxDelay: 200000,
                flags: SENSOR_FLAG_CONTINUOUS_MODE,
#endif
		reserved: {}
	},

	{
		name: VENDOR_NAME_BST_SHORT BST_SENSOR_NAME_O SENSOR_STR,
		vendor: VENDOR_NAME_BST,
		version: SENSOR_VER_BST,
		handle: SENSORS_ORIENTATION_HANDLE,
		type: SENSOR_TYPE_ORIENTATION,
		maxRange: 360.0f,
		resolution: 1.0f,
		power: 0.63f,
#ifdef __FASTEST_MODE_100HZ__
		minDelay: 10000,
#else
		minDelay: 5000,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
                fifoReservedEventCount: 0,
                fifoMaxEventCount: 0,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_3__
                stringType: SENSOR_STRING_TYPE_ORIENTATION,
                requiredPermission: "",
                maxDelay: 200000,
                flags: SENSOR_FLAG_CONTINUOUS_MODE,
#endif
		reserved: {}
	},

	{
		name: VENDOR_NAME_BST_SHORT BST_SENSOR_NAME_VG SENSOR_STR,
		vendor: VENDOR_NAME_BST,
		version: SENSOR_VER_BST,
		handle: SENSORS_GRAVITY_HANDLE,
		type: SENSOR_TYPE_GRAVITY,
		maxRange: 9.805f * 2,
		resolution: 4.0f * 9.805 / (1 << HW_INFO_BITWIDTH_A),
		power: 5.63f,
#ifdef __FASTEST_MODE_100HZ__
		minDelay: 10000,
#else
		minDelay: 5000,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
                fifoReservedEventCount: 0,
                fifoMaxEventCount: 0,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_3__
                stringType: SENSOR_STRING_TYPE_GRAVITY,
                requiredPermission: "",
                maxDelay: 200000,
                flags: SENSOR_FLAG_CONTINUOUS_MODE,
#endif
		reserved: {}
	},

	{
		name: VENDOR_NAME_BST_SHORT BST_SENSOR_NAME_VLA SENSOR_STR,
		vendor: VENDOR_NAME_BST,
		version: SENSOR_VER_BST,
		handle: SENSORS_LINEAR_ACCEL_HANDLE,
		type: SENSOR_TYPE_LINEAR_ACCELERATION,
		maxRange: 9.805f * 2,
		resolution: 4.0f * 9.805 / (1 << HW_INFO_BITWIDTH_A),
		power: 5.63f,
#ifdef __FASTEST_MODE_100HZ__
		minDelay: 10000,
#else
		minDelay: 5000,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
                fifoReservedEventCount: 0,
                fifoMaxEventCount: 0,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_3__
                stringType: SENSOR_STRING_TYPE_LINEAR_ACCELERATION,
                requiredPermission: "",
                maxDelay: 200000,
                flags: SENSOR_FLAG_CONTINUOUS_MODE,
#endif
		reserved: {}
	},

	{
		name: VENDOR_NAME_BST_SHORT BST_SENSOR_NAME_VRV SENSOR_STR,
		vendor: VENDOR_NAME_BST,
		version: SENSOR_VER_BST,
		handle: SENSORS_ROTATION_VECTOR_HANDLE,
		type: SENSOR_TYPE_ROTATION_VECTOR,
		maxRange: 1.0f,
		resolution: 1.0f / (1 << 24),
		power: 5.63f,
#ifdef __FASTEST_MODE_100HZ__
		minDelay: 10000,
#else
		minDelay: 5000,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
                fifoReservedEventCount: 0,
                fifoMaxEventCount: 0,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_3__
                stringType: SENSOR_STRING_TYPE_ROTATION_VECTOR,
                requiredPermission: "",
                maxDelay: 200000,
                flags: SENSOR_FLAG_CONTINUOUS_MODE,
#endif
		reserved: {}
	},


#ifndef SENSOR_REMOVE_UNSUPPORT
	{
		name: VENDOR_NAME_BST_SHORT
			BST_SENSOR_NAME_GEST_FLIP SENSOR_STR,
		vendor: VENDOR_NAME_BST,
		version: SENSOR_VER_BST,
		handle: SENSORS_GEST_FLIP_HANDLE,
		type: BST_SENSOR_TYPE_GEST_FLIP,
		maxRange: 1.0f,
		resolution: 1.0f,
		power: 0.13f,
		minDelay: 0,
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
                fifoReservedEventCount: 0,
                fifoMaxEventCount: 0,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_3__
                stringType: "bosch.gest.flip.sensor",
                requiredPermission: "",
                maxDelay: 200000,
                flags: SENSOR_FLAG_ONE_SHOT_MODE | SENSOR_FLAG_WAKE_UP,
#endif
		reserved: {}
	},
#endif //SENSOR_REMOVE_UNSUPPORT

#ifndef SENSOR_REMOVE_UNSUPPORT
	{
		name: VENDOR_NAME_BST_SHORT BST_SENSOR_NAME_SGM SENSOR_STR,
		vendor: VENDOR_NAME_BST,
		version: SENSOR_VER_BST,
		handle: SENSORS_SW_SIGNIFICANT_MOTION_HANDLE,
		type: BSTEXT_SENSOR_TYPE_SW_SGM,
		maxRange: 1.0f,
		resolution: 1.0f,
		power: 0.13f,
#ifdef __FASTEST_MODE_100HZ__
		minDelay: 10000,
#else
		minDelay: 5000,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
                fifoReservedEventCount: 0,
                fifoMaxEventCount: 0,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_3__
                stringType: "bosch.software.signficant.motion.sensor",
                requiredPermission: "",
                maxDelay: 200000,
                flags: SENSOR_FLAG_ONE_SHOT_MODE | SENSOR_FLAG_WAKE_UP,
#endif
		reserved: {}
	},
#endif //SENSOR_REMOVE_UNSUPPORT

#ifdef __UNCALIBRATED_VIRTUAL_SENSOR_SUPPORT__
	{
		name: VENDOR_NAME_BST_SHORT BST_SENSOR_NAME_GRV SENSOR_STR,
		vendor: VENDOR_NAME_BST,
		version: SENSOR_VER_BST,
		handle: SENSORS_GAME_ROTATION_VECTOR_HANDLE,
		type: SENSOR_TYPE_GAME_ROTATION_VECTOR,
		maxRange: 1.0f,
		resolution: 1.0f / (1 << 24),
		power: 5.63f,
#ifdef __FASTEST_MODE_100HZ__
		minDelay: 10000,
#else
		minDelay: 5000,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
                fifoReservedEventCount: 0,
                fifoMaxEventCount: 0,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_3__
                stringType: SENSOR_STRING_TYPE_GAME_ROTATION_VECTOR,
                requiredPermission: "",
                maxDelay: 200000,
                flags: SENSOR_FLAG_CONTINUOUS_MODE,
#endif
		reserved: {}
	},

	{
		name: VENDOR_NAME_BST_SHORT BST_SENSOR_NAME_GYU SENSOR_STR,
		vendor: VENDOR_NAME_BST,
		version: SENSOR_VER_BST,
		handle: SENSORS_GYROSCOPE_UNCALIBRATED_HANDLE,
		type: SENSOR_TYPE_GYROSCOPE_UNCALIBRATED,
		maxRange: 2500.0f,
		resolution: 250.0f / (1 << 16),
		power: 5.0f,
#ifdef __FASTEST_MODE_100HZ__
		minDelay: 10000,
#else
		minDelay: 5000,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
                fifoReservedEventCount: 0,
                fifoMaxEventCount: 0,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_3__
                stringType: SENSOR_STRING_TYPE_GYROSCOPE_UNCALIBRATED,
                requiredPermission: "",
                maxDelay: 200000,
                flags: SENSOR_FLAG_CONTINUOUS_MODE,
#endif
		reserved: {}
	},

	{
		name: VENDOR_NAME_BST_SHORT BST_SENSOR_NAME_MU SENSOR_STR,
		vendor: VENDOR_NAME_BST,
		version: SENSOR_VER_BST,
		handle: SENSORS_MAGNETIC_UNCALIBRATED_HANDLE,
		type: SENSOR_TYPE_MAGNETIC_FIELD_UNCALIBRATED,
		maxRange: 1600.0f,
		resolution: 0.3f,
		power: 0.5f,
#ifdef __USECASE_TYPE_M4G__
		minDelay: 20000,
#else
		minDelay: 40000,
#endif

#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
                fifoReservedEventCount: 0,
                fifoMaxEventCount: 0,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_3__
                stringType: SENSOR_STRING_TYPE_MAGNETIC_FIELD_UNCALIBRATED,
                requiredPermission: "",
                maxDelay: 200000,
                flags: SENSOR_FLAG_CONTINUOUS_MODE,
#endif
		reserved: {}
	},
#endif

#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
	{
		name: VENDOR_NAME_BST_SHORT BST_SENSOR_NAME_GEOM_RY SENSOR_STR,
		vendor: VENDOR_NAME_BST,
		version: SENSOR_VER_BST,
		handle: SENSORS_GEOMAGNETIC_ROTATION_VECTOR_HANDLE,
		type: SENSOR_TYPE_GEOMAGNETIC_ROTATION_VECTOR,
		maxRange: 1.0f,
		resolution: 1.0f / (1 << 24),
		power: 5.63f,
#ifdef __FASTEST_MODE_100HZ__
		minDelay: 10000,
#else
		minDelay: 5000,
#endif
		fifoReservedEventCount: 0,
		fifoMaxEventCount: 0,
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_3__
                stringType: SENSOR_STRING_TYPE_GEOMAGNETIC_ROTATION_VECTOR,
                requiredPermission: "",
                maxDelay: 200000,
                flags: SENSOR_FLAG_CONTINUOUS_MODE,
#endif
		reserved: {}
	},
#endif

#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_0__
#ifndef SENSOR_REMOVE_UNSUPPORT
	{
		name: VENDOR_NAME_BST_SHORT BST_SENSOR_NAME_STC SENSOR_STR,
		vendor: VENDOR_NAME_BST,
		version: SENSOR_VER_BST,
		handle: SENSORS_STEP_COUNTER_HANDLE,
		type: SENSOR_TYPE_STEP_COUNTER,
		maxRange: 10000.0f,
		resolution: 1.0f,
		power: 5.63f,
		minDelay: 0,
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
                fifoReservedEventCount: 0,
                fifoMaxEventCount: 0,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_3__
                stringType: SENSOR_STRING_TYPE_STEP_COUNTER,
                requiredPermission: "",
                maxDelay: 1000000,
                flags: SENSOR_FLAG_ON_CHANGE_MODE,
#endif
		reserved: {}
	},
	{
		name: VENDOR_NAME_BST_SHORT BST_SENSOR_NAME_STD SENSOR_STR,
		vendor: VENDOR_NAME_BST,
		version: SENSOR_VER_BST,
		handle: SENSORS_STEP_DETECTOR_HANDLE,
		type: SENSOR_TYPE_STEP_DETECTOR,
		maxRange: 1.0f,
		resolution: 1.0f,
		power: 5.63f,
		minDelay: 0,
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
                fifoReservedEventCount: 0,
                fifoMaxEventCount: 0,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_3__
                stringType: SENSOR_STRING_TYPE_STEP_DETECTOR,
                requiredPermission: "",
                maxDelay: 1000000,
                flags: SENSOR_FLAG_SPECIAL_REPORTING_MODE,
#endif
		reserved: {}
	},
#endif //SENSOR_REMOVE_UNSUPPORT

#endif

};


const struct sensor_t * BstSensorInfo::getSensor(int handle)
{
	const struct sensor_t *s = NULL;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(g_bst_sensor_list); i++) {
		if (g_bst_sensor_list[i].handle == handle) {
			break;
		}
	}

	if (i < ARRAY_SIZE(g_bst_sensor_list)) {
		s = (const struct sensor_t *) g_bst_sensor_list + i;
	}

	return s;
}

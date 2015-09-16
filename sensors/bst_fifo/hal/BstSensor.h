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
 * @file         BstSensor.h
 * @date         "Fri Jan 9 17:45:01 2015 +0800"
 * @commit       "7c424a4"
 *
 * @brief
 *
 * @detail
 *
 */


#ifndef ANDROID_BST_SENSOR_H
#define ANDROID_BST_SENSOR_H

#include <stdint.h>
#include <errno.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#include "version.h"
#include "sensors.h"
#include "SensorBase.h"
#include "BstSensorPriv.h"
#include "BstSensorInfo.h"
#include "BstSensorType.h"

#define BST_DATA_POLL_TIMEOUT 500000

enum BST_SENSOR_HANDLE {
	BST_SENSOR_HANDLE_START = 0,
	BST_SENSOR_HANDLE_ACCELERATION,         /* 1 */
	BST_SENSOR_HANDLE_MAGNETIC_FIELD,       /* 2 */
	BST_SENSOR_HANDLE_ORIENTATION,          /* 3 */
	BST_SENSOR_HANDLE_GYROSCOPE,            /* 4 */
	BST_SENSOR_HANDLE_LIGHT,                /* 5 */
	BST_SENSOR_HANDLE_PRESSURE,             /* 6 */
	BST_SENSOR_HANDLE_TEMPERATURE,          /* 7 */
	BST_SENSOR_HANDLE_PROXIMITY,            /* 8 */
	BST_SENSOR_HANDLE_GRAVITY,              /* 9 */
	BST_SENSOR_HANDLE_LINEAR_ACCELERATION,  /* 10 */
	BST_SENSOR_HANDLE_ROTATION_VECTOR,      /* 11 */
	BST_SENSOR_HANDLE_ORIENTATION_RAW,      /* 12 */

	BST_SENSOR_HANDLE_GEST_FLIP,            /* 13 */
	BST_SENSOR_HANDLE_SW_SIGNIFICANT_MOTION,
#ifdef __UNCALIBRATED_VIRTUAL_SENSOR_SUPPORT__
	BST_SENSOR_HANDLE_GAME_ROTATION_VECTOR,
	BST_SENSOR_HANDLE_GYROSCOPE_UNCALIBRATED,
	BST_SENSOR_HANDLE_MAGNETIC_FIELD_UNCALIBRATED,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
	BST_SENSOR_HANDLE_GEOMAGNETIC_ROTATION_VECTOR,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_0__
	BST_SENSOR_HANDLE_STEP_COUNTER,
	BST_SENSOR_HANDLE_STEP_DETECTOR,
#endif

	BST_SENSOR_HANDLE_END
};

#define BST_SENSOR_NUM_MAX		 (BST_SENSOR_HANDLE_END-1)

#ifdef __BMI_FAST_CALIB_FEATURE__
#define BMI_FAST_CALIB_ACC_DONE 6
#define BMI_FAST_CALIB_GYRO_DONE 4
#endif


class BstSensor : public SensorBase {
	public:
		BstSensor();
		virtual ~BstSensor();

		enum
		{
			BST_SID_START = -1,
			BST_SID_GYRO,
			BST_SID_ACC,
			BST_SID_MAG,
			BST_SID_ORI,
			BST_SID_ROV,
			BST_SID_LA,
			BST_SID_GRV,
			BST_SID_PRS,
			BST_SID_GEST_FLIP,
			BST_SID_SGM,
#ifdef __UNCALIBRATED_VIRTUAL_SENSOR_SUPPORT__
			BST_SID_GROV,
			BST_SID_GRU,
			BST_SID_MU,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
			BST_SID_GEOM_RV,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_0__
			BST_SID_STC,
			BST_SID_STD,
#endif
			NUM_SENSORS
		};

		virtual int setDelay(int32_t id, int64_t ns);
		virtual int enable(int32_t id, int enable);
		virtual int readEvents(sensors_event_t *pdata, int count);
		static int64_t getTimestamp();
		static int getSensorList(struct sensor_t *list, int len);
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
		virtual int batch(int id, int flags, int64_t period_ns, int64_t timeout);
		virtual int flush(int id);
#endif

	protected:
		uint32_t mEnabled;
		uint64_t mDelays[BST_SENSOR_NUM_MAX];
		int mCmdFd;
		int mListFd;

		void processEvent(int code, int value);

		const static int s_tab_id2handle[BST_SENSOR_NUM_MAX];
		const static int s_tab_handle2id[BST_SENSOR_NUM_MAX];
		static int id2handle(int id);
		static int handle2id(int handle);
	private:
		int initIPC();
		static int initStorage();
};

#endif  // ANDROID_BST_SENSOR_H

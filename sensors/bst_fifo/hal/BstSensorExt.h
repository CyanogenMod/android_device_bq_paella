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
 * @file         BstSensorAccel.h
 * @date         "Fri Jan 30 18:07:49 2015 +0800"
 * @commit       "6732061"
 *
 * @brief
 *
 * @detail
 *
 */

#ifndef __BST_SENSOR_EXT_H
#define __BST_SENSOR_EXT_H

#include <stdint.h>
#include <errno.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#include "sensors.h"
#include "SensorBase.h"
#include "InputEventReader.h"
#include "BstSensorType.h"

/*****************************************************************************/

/* interruption enum, should same as defined in sensor linux driver */
#ifdef __SIGNIFICANT_MOTION_SENSOR_SUPPORT__
	#define SIGNIFICANT_MOTION_INTERRUPT    REL_DIAL
#else
	#define SLOP_INTERRUPT    REL_DIAL
#endif

#ifdef __BMI_FAST_CALIB_FEATURE__
#define BMI_FAST_CALIB_ACC_DONE 6
#define BMI_FAST_CALIB_GYRO_DONE 4
#endif

#define ORIENT_INTERRUPT    ABS_PRESSURE
#define FLAT_INTERRUPT    ABS_DISTANCE
#define HIGH_G_INTERRUPT_X_HAPPENED    1
#define HIGH_G_INTERRUPT_Y_HAPPENED    2
#define HIGH_G_INTERRUPT_Z_HAPPENED    3
#define HIGH_G_INTERRUPT_X_NEGATIVE_HAPPENED    4
#define HIGH_G_INTERRUPT_Y_NEGATIVE_HAPPENED    5
#define HIGH_G_INTERRUPT_Z_NEGATIVE_HAPPENED    6
#define SLOPE_INTERRUPT_X_HAPPENED    7
#define SLOPE_INTERRUPT_Y_HAPPENED    8
#define SLOPE_INTERRUPT_Z_HAPPENED    9
#define SLOPE_INTERRUPT_X_NEGATIVE_HAPPENED    10
#define SLOPE_INTERRUPT_Y_NEGATIVE_HAPPENED    11
#define SLOPE_INTERRUPT_Z_NEGATIVE_HAPPENED    12
#define DOUBLE_TAP_INTERRUPT_HAPPENED    13
#define SINGLE_TAP_INTERRUPT_HAPPENED    14
#define UPWARD_PORTRAIT_UP_INTERRUPT_HAPPENED    15
#define UPWARD_PORTRAIT_DOWN_INTERRUPT_HAPPENED    16
#define UPWARD_LANDSCAPE_LEFT_INTERRUPT_HAPPENED    17
#define UPWARD_LANDSCAPE_RIGHT_INTERRUPT_HAPPENED    18
#define DOWNWARD_PORTRAIT_UP_INTERRUPT_HAPPENED    19
#define DOWNWARD_PORTRAIT_DOWN_INTERRUPT_HAPPENED    20
#define DOWNWARD_LANDSCAPE_LEFT_INTERRUPT_HAPPENED    21
#define DOWNWARD_LANDSCAPE_RIGHT_INTERRUPT_HAPPENED    22
#define FLAT_INTERRUPT_TURE_HAPPENED    23
#define FLAT_INTERRUPT_FALSE_HAPPENED    24
#define LOW_G_INTERRUPT_HAPPENED    25
#define SLOW_NO_MOTION_INTERRUPT_HAPPENED    26


enum BSTEXT_SENSOR_HANDLE {
	BSTEXT_SENSOR_HANDLE_START = 0,
#ifdef __SIGNIFICANT_MOTION_SENSOR_SUPPORT__
	BSTEXT_SENSOR_HANDLE_SIGNIFICANT_MOTION,
#endif
	BSTEXT_SENSOR_HANDLE_END
};
#define BSTEXT_SENSOR_NUM_MAX    (BSTEXT_SENSOR_HANDLE_END-1)

#define BST_SENSOR_EXT_INPUT_DEV "bmi160"

#ifdef __SIGNIFICANT_MOTION_SENSOR_SUPPORT__
#define BMI160_SIGNIFICANT_MOTION_SENSOR_ENABLE_NODE "enable_int"
#endif


struct input_event;

class BstSensorExt : public SensorBase {
	InputEventCircularReader mInputReader;
	sensors_event_t mPendingEvent;

	char input_sysfs_path[PATH_MAX];
	int input_sysfs_path_len;
	static const struct sensor_t g_bstext_sensor_list[];

public:
	BstSensorExt();
	virtual ~BstSensorExt();
	virtual int readEvents(sensors_event_t* data, int count);
	virtual int enable(int32_t handle, int enabled);
	static int getSensorList(struct sensor_t *list, int len);
	static const struct sensor_t * getSensor(int handle);
	int enableSensor(int en, char* sensor, char* enable_mode);
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
	virtual int batch(int handle, int flags, int64_t period_ns, int64_t timeout);
	virtual int flush(int handle);
#endif

	enum
	{
		BSTEXT_SID_START = -1,
	#ifdef __SIGNIFICANT_MOTION_SENSOR_SUPPORT__
		BSTEXT_SID_SMT,
	#endif
		NUM_BSTEXT_SENSORS
	};

protected:
	char mInputSysfsPath[PATH_MAX];
	int getInputSysfsNodeInt(const char *name, int *val);
	int mInputSysfsPathLen;

private:
	static int checkSensorAvailable(int sensor_id);
};


/*****************************************************************************/

#endif  // __BST_SENSOR_EXT_H

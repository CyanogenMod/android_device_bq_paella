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
 * @file         BstSensorPressure.h
 * @date         "Fri Jan 9 17:45:01 2015 +0800"
 * @commit       "7c424a4"
 *
 * @brief
 *
 * @detail
 *
 */


#ifndef __BST_SENSOR_PRESSURE_H
#define __BST_SENSOR_PRESSURE_H

#include <stdint.h>
#include <errno.h>
#include <sys/cdefs.h>
#include <sys/types.h>


#include "sensors.h"
#include "SensorBase.h"
#include "InputEventReader.h"

struct input_event;

class PressureSensor:public SensorBase {
public:
	PressureSensor(const char *InputName);
	virtual ~PressureSensor();

	virtual int setDelay(int32_t handle, int64_t ns);
	virtual int enable(int32_t handle, int enabled);
	virtual int readEvents(sensors_event_t *data, int count);

#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
	virtual int batch(int handle, int flags, int64_t period_ns, int64_t timeout);
	virtual int flush(int handle);
#endif

private:
	char mName[128];
	int sensor_get_class_path(char *class_path, const char* InputName);
	int set_sysfs_input_attr(char *class_path, const char *attr,
				char *value, int len);

	int update_delay();
	int set_delay(int64_t ns);

	int write_enable(int newState);
	int write_delay(int64_t ns);
	int write_mode(int64_t ns);
	void processEvent(int code, int value);

	uint32_t mEnabled;
	uint32_t mPendingMask;
	int64_t mDelay;
	char mClassPath[PATH_MAX];
	sensors_event_t mPendingEvent;
	InputEventCircularReader mInputReader;
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
	uint32_t mPendingFlushFinishEvent;
#endif
};

#endif  //__BST_SENSOR_PRESSURE_H

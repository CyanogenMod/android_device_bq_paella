/*
 * Copyright (C) 2008 The Android Open Source Project
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
 */

#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <poll.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/select.h>
#include <string.h>
#include "LightSensor.h"
#include "TargetPlatform.h"

/*****************************************************************************/

LightSensor::LightSensor()
    : SensorBase(NULL, "light"),
      mEnabled(0),
      mInputReader(4),
      mHasPendingEvent(false)
{
    mPendingEvent.version = sizeof(sensors_event_t);
    mPendingEvent.sensor = ID_L;
    mPendingEvent.type = SENSOR_TYPE_LIGHT;
    memset(mPendingEvent.data, 0, sizeof(mPendingEvent.data));
#ifdef __SENSORS_DEVICE_API_VERSION_1_3__
	mPendingFlushFinishEvent = 0;
#endif

    if (data_fd) {
        strcpy(input_sysfs_path, "/sys/class/input/");
        strcat(input_sysfs_path, input_name);
        strcat(input_sysfs_path, "/device/");
        input_sysfs_path_len = strlen(input_sysfs_path);
        enable(0, 1);
    }
}

LightSensor::~LightSensor() {
    if (mEnabled) {
        enable(0, 0);
    }
}

int LightSensor::setDelay(int32_t handle, int64_t ns)
{
    int fd;
    char buf[80];
    UNUSED_PARAM(handle);
    strcpy(&input_sysfs_path[input_sysfs_path_len], "als_poll_delay");
    fd = open(input_sysfs_path, O_RDWR);

    if (fd < 0)
    {
        return -1;
    }

    sprintf(buf, "%lld", (long long int)ns);
    write(fd, buf, strlen(buf)+1);
    close(fd);

    return 0;
}

int LightSensor::enable(int32_t handle, int en)
{
    int flags = en ? 1 : 0;
    UNUSED_PARAM(handle);
    if (flags != mEnabled) {
        int fd;
        char buf[2];
        strcpy(&input_sysfs_path[input_sysfs_path_len], "als_enable");
        fd = open(input_sysfs_path, O_RDWR);

        if (fd < 0)
        {
			PERR("LightSensor: open %s failed.(%s)\n",
				input_sysfs_path, strerror(errno));
            return -1;
        }

        buf[1] = 0;
        if (flags) {
            buf[0] = '1';
        } else {
            buf[0] = '0';
        }
        write(fd, buf, sizeof(buf));
        close(fd);
        mEnabled = flags;
    }
    return 0;
}

bool LightSensor::hasPendingEvents() const {
    return mHasPendingEvent;
}

int LightSensor::readEvents(sensors_event_t* data, int count)
{
	int numEventReceived = 0;
	input_event const* event;
    if (count < 1)
	{
        return 0;
	}
#ifdef __SENSORS_DEVICE_API_VERSION_1_3__
	sensors_meta_data_event_t flush_finish_event;
#endif
    if (mHasPendingEvent) {
        mHasPendingEvent = false;
        mPendingEvent.timestamp = getTimestamp();
        *data = mPendingEvent;
        return mEnabled ? 1 : 0;
    }

#ifdef __SENSORS_DEVICE_API_VERSION_1_3__
	if (mEnabled) {
		//LOGI("<BST> " "mPendingFlushFinishEvent = %d ", mPendingFlushFinishEvent);
		flush_finish_event.version = META_DATA_VERSION;
		flush_finish_event.type = SENSOR_TYPE_META_DATA;
		flush_finish_event.meta_data.what = META_DATA_FLUSH_COMPLETE;
		flush_finish_event.meta_data.sensor = SENSORS_LIGHT_HANDLE;
		while(mPendingFlushFinishEvent){
			LOGI("<BST> " "report flush finish event for sensor id: %d", flush_finish_event.meta_data.sensor);
			*data++ = flush_finish_event;
			count--;
			numEventReceived++;
			mPendingFlushFinishEvent--;
		}
	}
#endif

    ssize_t n = mInputReader.fill(data_fd);
    if (n < 0)
	{
		return 0;
	}

    while (count && mInputReader.readEvent(&event)) {
        int type = event->type;
        if (type == EV_ABS) {
            if (event->code == EVENT_TYPE_LIGHT) {
                // Convert adc value to lux assuming:
                // I = 10 * log(Ev) uA
                // R = 47kOhm
                // Max adc value 4095 = 3.3V
                // 1/4 of light reaches sensor
                mPendingEvent.light = event->value;
				//powf(10, event->value * (330.0f / 4095.0f / 47.0f)) * 4;
            }
        } else if (type == EV_SYN) {
            mPendingEvent.timestamp = timevalToNano(event->time);
            if (mEnabled) {
                *data++ = mPendingEvent;
                count--;
                numEventReceived++;
            }
        } else {
            PERR("LightSensor: unknown event (type=%d, code=%d)",
                    type, event->code);
        }
        mInputReader.next();
    }

    return numEventReceived;
}

#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
int LightSensor::flush(int id)
{
	int ret = 0;
	mPendingFlushFinishEvent++;
	//PINFO("<BST> flush sensor id: %d for %d times", id, mPendingFlushFinishEvent);
	return ret;
}

int LightSensor::batch(int id, int flags, int64_t period_ns, int64_t timeout)
{
	int ret = 0;

	PDEBUG("batch id %d, flags %d, period_ns %lld, timeout %lld", id, flags, (long long int)period_ns, (long long int)timeout);

	UNUSED_PARAM(id);
	UNUSED_PARAM(flags);
	UNUSED_PARAM(period_ns);
	UNUSED_PARAM(timeout);
	//ret = LightSensor::setDelay(id, period_ns);
	return ret;
}
#endif


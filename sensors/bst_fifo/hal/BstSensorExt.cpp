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
 * @file         BstSensorExt.cpp
 * @date         "Fri Jan 30 18:07:49 2015 +0800"
 * @commit       "6732061"
 *
 * @brief
 *
 * @detail
 *
 */

#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <poll.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/select.h>
#include <sys/stat.h>

#include "BstSensorExt.h"

#include "TargetPlatform.h"

/*****************************************************************************/
const struct sensor_t BstSensorExt::g_bstext_sensor_list[] =
{
#ifdef __SIGNIFICANT_MOTION_SENSOR_SUPPORT__
	{ "BOSCH HW Significant Motion Sensor",
	  "Bosch Sensortec, GmbH",
	  1, SENSORS_SIGNIFICANT_MOTION_HANDLE,
	  SENSOR_TYPE_SIGNIFICANT_MOTION, 1.0f, 1.0f, 0.0f, -1,
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
         0,0,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_3__
         SENSOR_STRING_TYPE_SIGNIFICANT_MOTION,
         "",
         -1,
         (SENSOR_FLAG_ONE_SHOT_MODE | SENSOR_FLAG_WAKE_UP),
#endif
	  {}},
#endif

};


BstSensorExt::BstSensorExt()
    : SensorBase(NULL, BST_SENSOR_EXT_INPUT_DEV),
      mInputReader(4)
{
	mPendingEvent.version = sizeof(sensors_event_t);
	memset(mPendingEvent.data, 0, sizeof(mPendingEvent.data));
	memset(input_sysfs_path, 0, sizeof(input_sysfs_path));
	input_sysfs_path_len = 0;

	if (data_fd < 0)
		return;

	if (data_fd) {
		memset(mInputSysfsPath, 0, sizeof(mInputSysfsPath));
		strcpy(mInputSysfsPath, "/sys/class/input/");
		strcat(mInputSysfsPath, input_name);
		strcat(mInputSysfsPath, "/device/");
		mInputSysfsPathLen = strlen(mInputSysfsPath);
	}

}

BstSensorExt::~BstSensorExt()
{
#ifdef __SIGNIFICANT_MOTION_SENSOR_SUPPORT__
	enable(ID_SMT, 0);
#endif
}

int BstSensorExt::enableSensor(int en, char * sensor_path, char * enable_mode)
{
	int ret = 0;
	int fd;
	char buf[4];
	const char *p_buf = buf;
	
	memset(input_sysfs_path, 0, sizeof(input_sysfs_path));
	strncpy(input_sysfs_path, sensor_path, strlen(sensor_path));
	input_sysfs_path_len = strlen(input_sysfs_path);
	strncpy(&input_sysfs_path[input_sysfs_path_len], enable_mode, strlen(enable_mode));
	fd = open(input_sysfs_path, O_RDWR);
	if (fd >= 0)
	{
		if (en)
		{
			p_buf = "0 1";/*enable anymotion x axis*/
			write(fd, p_buf, sizeof(buf));
			p_buf = "1 1";/*enable anymotion y axis*/
			write(fd, p_buf, sizeof(buf));
			p_buf = "2 1";/*enable anymotion z axis*/
			write(fd, p_buf, sizeof(buf));
		}
		else
		{
			p_buf = "0 0";/*disable anymotion x axis*/
			write(fd, p_buf, sizeof(buf));
			p_buf = "1 0";/*disable anymotion y axis*/
			write(fd, p_buf, sizeof(buf));
			p_buf = "2 0";/*disable anymotion z axis*/
			write(fd, p_buf, sizeof(buf));
		}
		close(fd);
		ret = 0;
	}
	else
	{
		ret = -EIO;
	}
	return ret;
}

int BstSensorExt::enable(int32_t id, int en)
{
	int ret = 0;

	
	PDEBUG("BstSensorExt: id=%d, en=%d", id, en);
#ifdef __SIGNIFICANT_MOTION_SENSOR_SUPPORT__
	if (ID_SMT == id)
	{
		/*ret = BstSensorExt::enableSensor(en, (char *)INPUT_SYSFS_PATH_SIGNIFICANT_MOTION_SENSOR,
								(char *)INPUT_SYSFS_PATH_SIGNIFICANT_MOTION_SENSOR_ENABLE_NODE);*/
		ret = BstSensorExt::enableSensor(en, mInputSysfsPath,
								(char *)BMI160_SIGNIFICANT_MOTION_SENSOR_ENABLE_NODE);
		LOGD("BstSensorExt: id=%d, en=%d, ret=%d", id, en, ret);
		ret = 0;
	}
	else
#endif
	{
		PERR("sensor id %d not found", id);
	}

	return ret;
}

int BstSensorExt::getInputSysfsNodeInt(const char *name, int *val)
{
	int err = 0;
	int ret = 0;
	int fd;
	/* 32 is enough for an integer */
	char buf[32] = "";

	strncpy(&mInputSysfsPath[mInputSysfsPathLen], name,
		sizeof(mInputSysfsPath) - mInputSysfsPathLen - 1);

	PDEBUG("<BST> path to read: %s", mInputSysfsPath);

	fd = open(mInputSysfsPath, O_RDONLY);
	if (fd >= 0) {
		ret = read(fd, buf, sizeof(buf) - 1);
		if (ret > 0) {
			err = sscanf(buf, "%10d", val);
			if (1 != err) {
				LOGE("<BST> fail to scan int");
				err = -EINVAL;
			} else {
				err = 0;
			}
		} else {
			LOGE("<BST> fail to read int: %s", strerror(errno));
			err = -EIO;
		}
		close(fd);
	} else {
		LOGE("<BST> fail to open file: %s", strerror(errno));
		err = -ENOENT;
	}

	return err;
}




int BstSensorExt::readEvents(sensors_event_t* data, int count)
{
	if (count < 1)
	{
		return 0;
	}

	ssize_t n = mInputReader.fill(data_fd);
	if (n < 0)
	{
		return 0;
	}

	int numEventReceived = 0;
	input_event const* event;

	while (count && mInputReader.readEvent(&event))
	{
		PDEBUG("%s,event.type is %d,event value is %d,event code is %d",__FUNCTION__,event->type,event->value,event->code);
		if(event->type == EV_REL || event->type == EV_MSC)
		{
			switch(event->code)
			{

			#ifdef __SIGNIFICANT_MOTION_SENSOR_SUPPORT__
				case SIGNIFICANT_MOTION_INTERRUPT:
					// significant motion sensor is one-shot, and disabled in driver.
					mPendingEvent.sensor = ID_SMT;
					mPendingEvent.type = SENSOR_TYPE_SIGNIFICANT_MOTION;
					mPendingEvent.timestamp = timevalToNano(event->time);
					PDEBUG("Sig motion happend!, %d\n", EV_MSC);
					mPendingEvent.data[0] = 1.0;
					break;
			#else
				case SLOP_INTERRUPT:
					break;
			#endif

				default:
					break;

			}
			*data++ = mPendingEvent;
			count--;
			numEventReceived++;
		}

		mInputReader.next();
	}

	return numEventReceived;
}

int BstSensorExt::checkSensorAvailable(int sensor_id)
{
	int fd;
	int ret = 0;
	char sysfs_path[PATH_MAX];
	int sysfs_path_len;
	char *p_path;
	char *p_enable_node;
	
	switch (sensor_id)
	{
	#ifdef __SIGNIFICANT_MOTION_SENSOR_SUPPORT__
		case BSTEXT_SID_SMT:
			return 0;
	#endif

		default:
			return 0;
	}

	if (sensor_id < NUM_BSTEXT_SENSORS)
	{
		strcpy(sysfs_path, p_path);
		sysfs_path_len = strlen(sysfs_path);
		strcpy(&sysfs_path[sysfs_path_len], p_enable_node);

		fd = open(sysfs_path, O_RDONLY);
		if (fd >= 0)
		{
			close(fd);
			ret = 0;
		}
		else
			ret = -EIO;
	}

	PINFO("BstSensorExt::checkSensorAvailable, id, ret= %d, %d", sensor_id, ret);
	return ret;
}


int BstSensorExt::getSensorList(struct sensor_t *list, int len)
{
	int             num = 0;
	int j;

	UNUSED_PARAM(len);
	for (j = 0; j < NUM_BSTEXT_SENSORS; j++)
	{
		if ( BstSensorExt::checkSensorAvailable(j) == 0)
		{
			memcpy(list++,
				&BstSensorExt::g_bstext_sensor_list[j],
				sizeof(struct sensor_t));
			num++;
		}
	}

	return num;
}

const struct sensor_t * BstSensorExt::getSensor(int handle)
{
	const struct sensor_t *s = NULL;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(g_bstext_sensor_list); i++) {
		if (g_bstext_sensor_list[i].handle == handle) {
			LOGD("i %d, g_handle %d, handlerID %d ", i, g_bstext_sensor_list[i].handle, handle);
			break;
		}
	}

	if (i < ARRAY_SIZE(g_bstext_sensor_list)) {
		s = (const struct sensor_t *) g_bstext_sensor_list + i;
	}

	return s;
}

#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
int BstSensorExt::flush(int id)
{
	PDEBUG("flush id %d", id);

	UNUSED_PARAM(id);
	return -EINVAL;
}

int BstSensorExt::batch(int id, int flags, int64_t period_ns, int64_t timeout)
{
	int ret = 0;

	PDEBUG("batch id %d, flags %d, period_ns %lld, timeout %lld", id, flags, (long long int)period_ns, (long long int)timeout);

	UNUSED_PARAM(id);
	UNUSED_PARAM(flags);
	UNUSED_PARAM(period_ns);
	UNUSED_PARAM(timeout);
	//ret = BstSensorExt::setDelay(id, period_ns);
	return ret;
}
#endif


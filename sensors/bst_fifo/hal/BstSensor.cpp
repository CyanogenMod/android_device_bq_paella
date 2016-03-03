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
 * @file         BstSensor.cpp
 * @date         "Fri Jan 9 17:45:01 2015 +0800"
 * @commit       "7c424a4"
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
#include <time.h>

#include <linux/fs.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils/SystemClock.h>
#include <utils/Timers.h>
#include <string.h>
#include "BstSensor.h"
#include "BstSensorInfo.h"
#include "sensors.h"

#include "TargetPlatform.h"

#define GET_HANDLES_TRY_NUM         20

const int BstSensor::s_tab_id2handle[BST_SENSOR_NUM_MAX] = {
	BST_SENSOR_HANDLE_ACCELERATION,         /* 0 */
#ifdef __USECASE_TYPE_ACCEL_ONLY__
	-1,
	-1,
	-1,
	-1,
	-1,
	-1,
	-1,
	BST_SENSOR_HANDLE_GEST_FLIP,
#else
	BST_SENSOR_HANDLE_MAGNETIC_FIELD,       /* 1 */
	BST_SENSOR_HANDLE_GYROSCOPE,            /* 2 */
	BST_SENSOR_HANDLE_ORIENTATION,          /* 3 */
	BST_SENSOR_HANDLE_GRAVITY,              /* 4 */
	BST_SENSOR_HANDLE_LINEAR_ACCELERATION,  /* 5 */
	BST_SENSOR_HANDLE_ROTATION_VECTOR,      /* 6 */
	BST_SENSOR_HANDLE_PRESSURE,             /* 7 */
	BST_SENSOR_HANDLE_GEST_FLIP,            /* 8 */
#ifdef __UNSTANDARD_SENSOR_SUPPORT__
	-1,//BST_SENSOR_HANDLE_SW_SIGNIFICANT_MOTION,
#else
	-1,
#endif
#ifdef __UNCALIBRATED_VIRTUAL_SENSOR_SUPPORT__
	BST_SENSOR_HANDLE_GAME_ROTATION_VECTOR,
	BST_SENSOR_HANDLE_GYROSCOPE_UNCALIBRATED,
	BST_SENSOR_HANDLE_MAGNETIC_FIELD_UNCALIBRATED,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
	BST_SENSOR_HANDLE_GEOMAGNETIC_ROTATION_VECTOR,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_0__
#ifdef __UNSTANDARD_SENSOR_SUPPORT__
	BST_SENSOR_HANDLE_STEP_COUNTER,
	BST_SENSOR_HANDLE_STEP_DETECTOR,
#else
	-1,
	-1,
#endif
#endif
#endif
	-1,                                     /* 11 */
	-1                                      /* 12 */
};


const int BstSensor::s_tab_handle2id[BST_SENSOR_NUM_MAX] = {
	ID_A,           /* 1 */
	ID_M,           /* 2 */
	ID_O,           /* 3 */
	ID_GY,          /* 4 */
	-1,             /* 5 */
	ID_PR,          /* 6 */
	-1,             /* 7 */
	-1,             /* 8 */
	ID_GR,          /* 9 */
	ID_LA,          /* 10 */
	ID_RV,          /* 11 */
	-1,             /* 12 */
	ID_GEST_FLIP,    /* 13 */
	ID_SGM,
#ifdef __UNCALIBRATED_VIRTUAL_SENSOR_SUPPORT__
	ID_GRV,          /* 9: game rotation vector */
	ID_GYU,          /* 10: gyro uncalibrated */
	ID_MU,          /* 11: magnetic uncalibrated */
#endif

#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
	ID_GEOM_RV,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_0__
	ID_STC,
	ID_STD,
#endif
};

int8_t  handles[BST_SENSOR_NUM_MAX];
int     numOfHandles = 0;

static int64_t cur_delay = 0;
static int64_t cur_mag_delay = 0;
static int64_t cur_ns = 0;
static int64_t pre_ts[BST_SENSOR_HANDLE_END] = {0};

int BstSensor::initStorage()
{
	char *path = NULL;
	int err = 0;
	struct stat st;
	int retry = 0;

	path = (char *)PATH_DIR_SENSOR_STORAGE;
	err = access(path, F_OK);
	if (!err) {
		st.st_mode = ~S_IFDIR;
		err = stat(path, &st);
		if (!S_ISDIR(st.st_mode)) {
			PERR("<BST>" "a file of the same name exists");
			/* mark error explicitly for creating the dir */
			err = -ENOTDIR;
		}
	}

	while (0 !=err && retry < 4) {
		PERR("<BST>" "create path of storage, err: %d, retry count %d", err, retry);
		unlink(path);
		err = mkdir(path, 0775);
		if (err) {
			PERR("<BST>" "error creating storage dir");
		}
		retry++;
		usleep(1000);
	}

	return err;
}


int BstSensor::initIPC()
{
	int err = 0;
	char *filename;

	err = initStorage();
	if (err) {
		PERR("initStorage return %d", err);
		return err;
	}

	filename = (char *)FIFO_CMD;
	err = access(filename, F_OK | R_OK | W_OK);
	if (err) {
		PERR("<BST> " "can not access %s", filename);
		return err;
	}

	mCmdFd = open(filename, O_RDWR);
	if (mCmdFd < 0) {
		PERR("<BST> " "error openning file: %s", filename);
		mCmdFd = -abs(errno);
		err = mCmdFd;
		return err;
	}

	filename = (char *)FIFO_DAT;
	err = access(filename, F_OK | R_OK | W_OK);
	if (err) {
		PERR("<BST> " "can not access %s", filename);
		return err;
	}

	data_fd = open(filename, O_RDWR);
	if (data_fd < 0) {
		PERR("<BST> " "error openning file: %s", filename);
		err = data_fd;
		return err;
	}

	filename = (char *)FIFO_LIST;
	err = access(filename, F_OK | R_OK | W_OK);
	if (err) {
		PERR("<BST> " "can not access %s", filename);
		return err;
	}

	mListFd = open(filename, O_RDWR);
	if (mListFd < 0) {
		PERR("<BST> " "error openning file: %s", filename);
		mListFd = -abs(errno);
		err = mListFd;
		return err;
	}

	data_name = filename;

	return err;
}

BstSensor::BstSensor()
	: SensorBase(NULL, NULL),
	mEnabled(0)
{
	struct exchange cmd;
	int             i = 0;
	int             ret = 0;
	int             fData = -1;

	do {
		if (i ++ > GET_HANDLES_TRY_NUM)
		{
			PERR("initIPC failed:%d", ret);
			return;
		}
		ret = initIPC();
		if (!ret)
		{
			break;
		}
		sleep(1);
	} while(ret);

	/* if handles already initialized */
	if (numOfHandles > 0)
	{
		return;
	}

	fData = open(FIFO_LIST, O_RDONLY|O_NONBLOCK);
	if (fData == -1)
	{
		PERR("open fifo data failed:%d", fData);
		return;
	}

	memset(&cmd, 0, sizeof(cmd));
	cmd.magic = CHANNEL_PKT_MAGIC_LIST;
	while (numOfHandles <= 0)
	{
		write(mCmdFd, &cmd, sizeof(cmd));
		sleep(1);
		numOfHandles = read(fData, handles,
			BST_SENSOR_NUM_MAX);
		PDEBUG("get num of handles %d", numOfHandles);
		if (i ++ > GET_HANDLES_TRY_NUM)
		{
			PERR("reading num of handles time out");
			break;
		}
	}
	close(fData);
	memset(pre_ts, 0, sizeof(pre_ts));
}

BstSensor::~BstSensor()
{
	/* mCmdFd is added by BstSensor, while
	 * data_fd is added by SensorBase
	 * so here, only close mCmdFd */
	if (mCmdFd >= 0) {
		close(mCmdFd);
	}
	if (mListFd >= 0)
	{
		close (mListFd);
	}
}


int BstSensor::id2handle(int32_t id)
{
	if ( (id <= ID_SENSOR_BASE_BST) ||
			(id >= ID_SENSOR_END_BST) ) {
		return -1;
	} else {
		return BstSensor::s_tab_id2handle[id - 1 - ID_SENSOR_BASE_BST];
	}
}


int BstSensor::handle2id(int32_t handle)
{
	if ( (handle - 1 < 0) || (handle - 1 >= BST_SENSOR_NUM_MAX) ) {
		PERR("<BST> " "Invalid handle %d", handle);
		return -1;
	} else {
		return BstSensor::s_tab_handle2id[handle - 1];
	}
}


int BstSensor::enable(int32_t id, int enable)
{
	int err = 0;
	int handle;
	struct exchange cmd;
	int pos = (int)id;

	const struct sensor_t *s;

	handle = BstSensor::id2handle(id);
	if (-1 == handle) {
		return -EINVAL;
	}

	if (mCmdFd < 0) {
		PERR("<BST> " "cannot tx cmd: %s",
				(char *)strerror(-mCmdFd));
		return mCmdFd;
	}

	enable = !!enable;


	s = BstSensorInfo::getSensor(id);
	PINFO("<BST> " "%s sensor <%s>",
			enable ? "enable" : "disable",
			(s != NULL) ? s->name : "unknown");

	cmd.magic = CHANNEL_PKT_MAGIC_CMD;
	cmd.command.cmd = SET_SENSOR_ACTIVE;
	cmd.command.code = handle;
	cmd.command.value = enable;
	cmd.ts = 0;
	err = write(mCmdFd, &cmd, sizeof(cmd));
	err = err < (int)sizeof(cmd) ? -1 : 0;

	if (!err) {
		if (enable) {
			mEnabled |= (1 << pos);
		} else {
			mEnabled &= ~(1 << pos);
		}
	}

	if (!enable)
	{
		pre_ts[handle] = 0;
	}

	return err;
}


int BstSensor::setDelay(int32_t id, int64_t ns)
{
	int err = 0;
	int handle;
	struct exchange cmd;
	const struct sensor_t *s;

	handle = BstSensor::id2handle(id);
	if (-1 == handle) {
		return -EINVAL;
	}

	if (mCmdFd < 0) {
		PERR("<BST> " "cannot tx cmd: %s",
				(char *)strerror(-mCmdFd));
		return mCmdFd;
	}

	cur_ns = ns;
	if (ns > 200 * SCALE_TIME_MS2NS)
	{
		PWARN("<BST> Set delay ns too big %jdms, reset it as mindelay %jdms",
			ns/SCALE_TIME_MS2NS, 200*SCALE_TIME_MS2NS);
		ns = 200 * SCALE_TIME_MS2NS;
	}
	else if (ns == 66667000LL || ns == 100000000LL)
	{
		if (ns == 100000000LL)
			cur_ns = 100000000LL;

		ns = 40 * SCALE_TIME_MS2NS;
	}
	else if (ns == 40000000LL)
	{
		if (handle == BST_SENSOR_HANDLE_MAGNETIC_FIELD || handle == BST_SENSOR_HANDLE_MAGNETIC_FIELD_UNCALIBRATED)
			ns = 40 * SCALE_TIME_MS2NS;
		else
			ns = 20 * SCALE_TIME_MS2NS;
	}

	if (handle == BST_SENSOR_HANDLE_MAGNETIC_FIELD || handle == BST_SENSOR_HANDLE_MAGNETIC_FIELD_UNCALIBRATED)
		{
	#ifdef __USECASE_TYPE_M4G__
		if (ns <= 20 * SCALE_TIME_MS2NS)
                        ns = 20 * SCALE_TIME_MS2NS;
	#else
		if (ns <= 40 * SCALE_TIME_MS2NS)
			ns = 40 * SCALE_TIME_MS2NS;
	#endif
	}
	cmd.magic = CHANNEL_PKT_MAGIC_CMD;

	cmd.command.cmd = SET_SENSOR_DELAY;
	cmd.command.code = handle;
	cmd.command.value = ns / SCALE_TIME_MS2NS;
	cmd.ts = 0;

	s = BstSensorInfo::getSensor(id);
	PINFO("<BST> cur_ns %lld" "set delay of <%s> to %lldms",
			cur_ns, (s != NULL) ? s->name : "unknown",
			ns / SCALE_TIME_MS2NS);

	err = write(mCmdFd, &cmd, sizeof(cmd));
	err = err < (int)sizeof(cmd) ? -1 : 0;

	if (!err) {
		mDelays[id - ID_SENSOR_BASE_BST] = ns / SCALE_TIME_MS2NS;
	}
	if (handle == BST_SENSOR_HANDLE_MAGNETIC_FIELD || handle == BST_SENSOR_HANDLE_MAGNETIC_FIELD_UNCALIBRATED)
		cur_mag_delay = ns;
	else
		cur_delay = ns;
	return err;
}


int64_t BstSensor::getTimestamp()
{
    return android::elapsedRealtimeNano();
}


int BstSensor::readEvents(sensors_event_t *pdata, int count)
{
	int rslt;
	int err;
	struct exchange sensor_data;
	int sensor;
	sensors_event_t *pdata_cur;
	volatile int64_t cur_ts = 0;
	int64_t continueloop_ts = 0;
	static int64_t timestamp_last = 0;
	int current_total_count = 0;
	int64_t check_delay = 0;

#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_3__
	sensors_meta_data_event_t *p_flush_finish_event;
#endif

	if (count > 1) {
		count = 1;
	}
	rslt = 0;
	pdata_cur = pdata;
	while (rslt < count) {
#if 0
		fds.revents = 0;
		err = poll(&fds, 1, BST_DATA_POLL_TIMEOUT);
		if (err <= 0) {
			return rslt;
		}
#endif

		err = read(data_fd, &sensor_data, sizeof(sensor_data));
		if (err < (int)sizeof(sensor_data)) {
			PERR("<BST> " "bad condition, stream needs sync");
			return rslt;
		}

		if (CHANNEL_PKT_MAGIC_DAT != sensor_data.magic) {
			PERR("<BST> " "discard invalid data packet from stream,%d,%d,%d ", sensor_data.magic, sensor_data.data.sensor, sensor_data.data.type );
			return rslt;
		}

#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_3__
		/*flush finish event*/
		if(SENSOR_TYPE_META_DATA == sensor_data.data.type)
		{
			sensor = sensor_data.data.sensor;
			p_flush_finish_event = pdata_cur;
			p_flush_finish_event->version = META_DATA_VERSION;
			p_flush_finish_event->type = SENSOR_TYPE_META_DATA;
			p_flush_finish_event->meta_data.what = META_DATA_FLUSH_COMPLETE;
			p_flush_finish_event->meta_data.sensor = BstSensor::handle2id(sensor);
			PINFO("<BST> " "report flush finish event for sensor id: %d",
					p_flush_finish_event->meta_data.sensor);
			count--;
			goto FLUSH_FINISH_EVENT_HANDLED;
		}
#endif

		sensor = sensor_data.data.sensor;
		pdata_cur->version = sizeof(*pdata_cur);
		pdata_cur->sensor = BstSensor::handle2id(sensor);
		
		cur_ts = getTimestamp();
		pdata_cur->timestamp = cur_ts;

		if (sensor == BST_SENSOR_HANDLE_MAGNETIC_FIELD || sensor == BST_SENSOR_HANDLE_MAGNETIC_FIELD_UNCALIBRATED)
		{
			check_delay = cur_mag_delay;
		}
		else
		{
			check_delay = cur_delay;
		}

		if ((cur_ts - timestamp_last < 100000000) && (timestamp_last != 0))
		{
			if (((check_delay == 10000000) && (cur_ts - timestamp_last > 17000000))
				|| ((check_delay == 20000000) && (cur_ts - timestamp_last > 34000000)) 
				|| ((check_delay == 40000000) && (cur_ns != 100000000LL) && (cur_ts - timestamp_last > 72000000)))
			{
				if ((cur_ts - timestamp_last)/check_delay >= 1)
				{
					count += (cur_ts - timestamp_last)/check_delay;
					current_total_count = count;	
					PINFO("count_calc:%lld, current_total_count:%d, cur_ts:%lld, last_ts:%lld, delat_time:%lld",
						(cur_ts - timestamp_last)/check_delay, current_total_count, cur_ts, timestamp_last,
						(cur_ts - timestamp_last));
				}
			}
		}

	while (count--)
	{

		pdata_cur->version = sizeof(*pdata_cur);
		pdata_cur->sensor = BstSensor::handle2id(sensor);
		if (!count)
		{
			if ((cur_ns == 100000000LL) && (cur_ts - timestamp_last) <= check_delay + 1000000)
				return rslt;//continue;
			pdata_cur->timestamp = cur_ts;	
		}
		else
		{	
			if ((check_delay == 40000000) && (cur_ns != 100000000LL))
			{
				PINFO("last_ts %lld, simulat_ts %lld, check_delay %lld", timestamp_last, (timestamp_last + check_delay*(current_total_count - count)), check_delay);
				if (timestamp_last + check_delay*(current_total_count - count) >= cur_ts)
					continue;
			}
			pdata_cur->timestamp = timestamp_last + check_delay*(current_total_count - count);
		}

		if (pdata_cur->timestamp == 0)
		{

			cur_ts = getTimestamp();
			pdata_cur->timestamp = cur_ts;
			PINFO("xxxx after ts %lld\n", pdata_cur->timestamp);
		}
		switch (BstSensor::handle2id(sensor)) {
		case SENSORS_ACCELERATION_HANDLE:
			pdata_cur->acceleration.x = sensor_data.data.acceleration.x;
			pdata_cur->acceleration.y = sensor_data.data.acceleration.y;
			pdata_cur->acceleration.z = sensor_data.data.acceleration.z;
			pdata_cur->acceleration.status =
				sensor_data.data.status;
			pdata_cur->type = SENSOR_TYPE_ACCELEROMETER;
			break;
		case SENSORS_GYROSCOPE_HANDLE:
			pdata_cur->gyro.x = sensor_data.data.gyro.x;
			pdata_cur->gyro.y = sensor_data.data.gyro.y;
			pdata_cur->gyro.z = sensor_data.data.gyro.z;
			pdata_cur->gyro.status = sensor_data.data.status;
			pdata_cur->type = SENSOR_TYPE_GYROSCOPE;
			break;
		case SENSORS_MAGNETIC_FIELD_HANDLE:
			pdata_cur->magnetic.x = sensor_data.data.magnetic.x;
			pdata_cur->magnetic.y = sensor_data.data.magnetic.y;
			pdata_cur->magnetic.z = sensor_data.data.magnetic.z;
			pdata_cur->magnetic.status = sensor_data.data.status;
			pdata_cur->type = SENSOR_TYPE_MAGNETIC_FIELD;
			break;
		case SENSORS_ORIENTATION_HANDLE:
			pdata_cur->orientation.azimuth = sensor_data.data.orientation.azimuth;
			pdata_cur->orientation.pitch = sensor_data.data.orientation.pitch;
			pdata_cur->orientation.roll = sensor_data.data.orientation.roll;
			pdata_cur->orientation.status = sensor_data.data.status;
			pdata_cur->type = SENSOR_TYPE_ORIENTATION;
			break;
		case SENSORS_PRESSURE_HANDLE:
			pdata_cur->pressure = sensor_data.data.pressure;
			pdata_cur->type = SENSOR_TYPE_PRESSURE;
			break;
		case SENSORS_GRAVITY_HANDLE:
			pdata_cur->data[0] = sensor_data.data.data[0];
			pdata_cur->data[1] = sensor_data.data.data[1];
			pdata_cur->data[2] = sensor_data.data.data[2];
			pdata_cur->type = SENSOR_TYPE_GRAVITY;
			break;
		case SENSORS_LINEAR_ACCEL_HANDLE:
			pdata_cur->data[0] = sensor_data.data.data[0];
			pdata_cur->data[1] = sensor_data.data.data[1];
			pdata_cur->data[2] = sensor_data.data.data[2];
			pdata_cur->type = SENSOR_TYPE_LINEAR_ACCELERATION;
			break;
		case SENSORS_ROTATION_VECTOR_HANDLE:
			pdata_cur->data[0] = sensor_data.data.data[0];
			pdata_cur->data[1] = sensor_data.data.data[1];
			pdata_cur->data[2] = sensor_data.data.data[2];
		#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_0__
			pdata_cur->data[3] = sensor_data.data.data[3];
			pdata_cur->data[4] = sensor_data.data.data[4];
		#endif
			pdata_cur->type = SENSOR_TYPE_ROTATION_VECTOR;
			break;
		case SENSORS_GEST_FLIP_HANDLE:
			pdata_cur->data[0] = sensor_data.data.data[0];
			pdata_cur->data[1] = sensor_data.data.data[1];
			pdata_cur->data[2] = sensor_data.data.data[2];
			pdata_cur->type = BST_SENSOR_TYPE_GEST_FLIP;
			break;

	#ifdef __UNCALIBRATED_VIRTUAL_SENSOR_SUPPORT__
		case SENSORS_GAME_ROTATION_VECTOR_HANDLE:
			pdata_cur->data[0] = sensor_data.data.data[0];
			pdata_cur->data[1] = sensor_data.data.data[1];
			pdata_cur->data[2] = sensor_data.data.data[2];
			pdata_cur->data[3] = sensor_data.data.data[3];
			pdata_cur->data[4] = sensor_data.data.data[4];
			pdata_cur->type = SENSOR_TYPE_GAME_ROTATION_VECTOR;
			break;
		case SENSORS_GYROSCOPE_UNCALIBRATED_HANDLE:
			pdata_cur->uncalibrated_gyro.x_uncalib = sensor_data.data.uncalibrated_gyro.x_uncalib;
			pdata_cur->uncalibrated_gyro.y_uncalib = sensor_data.data.uncalibrated_gyro.y_uncalib;
			pdata_cur->uncalibrated_gyro.z_uncalib = sensor_data.data.uncalibrated_gyro.z_uncalib;
			pdata_cur->uncalibrated_gyro.x_bias = sensor_data.data.uncalibrated_gyro.x_bias;
			pdata_cur->uncalibrated_gyro.y_bias = sensor_data.data.uncalibrated_gyro.y_bias;
			pdata_cur->uncalibrated_gyro.z_bias = sensor_data.data.uncalibrated_gyro.z_bias;
			pdata_cur->type = SENSOR_TYPE_GYROSCOPE_UNCALIBRATED;
			break;
		case SENSORS_MAGNETIC_UNCALIBRATED_HANDLE:
			pdata_cur->uncalibrated_magnetic.x_uncalib = sensor_data.data.uncalibrated_magnetic.x_uncalib;
			pdata_cur->uncalibrated_magnetic.y_uncalib = sensor_data.data.uncalibrated_magnetic.y_uncalib;
			pdata_cur->uncalibrated_magnetic.z_uncalib = sensor_data.data.uncalibrated_magnetic.z_uncalib;
			pdata_cur->uncalibrated_magnetic.x_bias = sensor_data.data.uncalibrated_magnetic.x_bias;
			pdata_cur->uncalibrated_magnetic.y_bias = sensor_data.data.uncalibrated_magnetic.y_bias;
			pdata_cur->uncalibrated_magnetic.z_bias = sensor_data.data.uncalibrated_magnetic.z_bias;
			pdata_cur->type = SENSOR_TYPE_MAGNETIC_FIELD_UNCALIBRATED;

			break;
	#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
		case SENSORS_GEOMAGNETIC_ROTATION_VECTOR_HANDLE:
			pdata_cur->data[0] = sensor_data.data.data[0];
			pdata_cur->data[1] = sensor_data.data.data[1];
			pdata_cur->data[2] = sensor_data.data.data[2];
			pdata_cur->data[3] = sensor_data.data.data[3];
			pdata_cur->data[4] = sensor_data.data.data[4];
			pdata_cur->type = SENSOR_TYPE_GEOMAGNETIC_ROTATION_VECTOR;
			break;
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_0__
		case SENSORS_STEP_COUNTER_HANDLE:
		#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
			pdata_cur->u64.step_counter = sensor_data.data.step_counter;
			pdata_cur->u64.data[0] = sensor_data.data.step_counter;
			pdata_cur->u64.data[1] = 0;
			pdata_cur->u64.data[2] = 0;
		#else
			pdata_cur->step_counter = sensor_data.data.step_counter;
			pdata_cur->data[0] = sensor_data.data.step_counter;
			pdata_cur->data[1] = 0;
			pdata_cur->data[2] = 0;
		#endif
			pdata_cur->type = SENSOR_TYPE_STEP_COUNTER;
			break;
		case SENSORS_STEP_DETECTOR_HANDLE:
			pdata_cur->data[0] = sensor_data.data.data[0];
			pdata_cur->data[1] = 0;
			pdata_cur->data[2] = 0;
			pdata_cur->type = SENSOR_TYPE_STEP_DETECTOR;
			break;
#endif
		case SENSORS_SW_SIGNIFICANT_MOTION_HANDLE:
			pdata_cur->data[0] = sensor_data.data.data[0];
			pdata_cur->data[1] = sensor_data.data.data[1];
			pdata_cur->data[2] = sensor_data.data.data[2];
			pdata_cur->type = BSTEXT_SENSOR_TYPE_SW_SGM;
			break;


		default:
			PERR("<BST> " "Invalid data pkt");
			return rslt;
		}

#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_3__
FLUSH_FINISH_EVENT_HANDLED:
#endif
		rslt++;
		pdata_cur++;
	}
	timestamp_last = cur_ts;
	};

	return rslt;
}

int BstSensor::getSensorList(struct sensor_t *list, int len)
{
	int             num = 0;
	int             i, j;
	int             handlerID = 0;

	UNUSED_PARAM(len);
	for (i = 0; i < numOfHandles; i++)
	{
		for (j = 0; j < NUM_SENSORS; j++)
		{
			handlerID = id2handle(BstSensorInfo::g_bst_sensor_list[j].handle);
			if (handles[i] == handlerID)
			{
				memcpy(list++,
					&BstSensorInfo::g_bst_sensor_list[j],
					sizeof(struct sensor_t));
				num++;
			}
		}
	}

	PINFO("<BST> " "BST HAL version: %s",
			get_hal_version());
	PINFO("build date : %s", get_build_date());

	return num;
}

#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
int BstSensor::flush(int id)
{
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_3__
	int err = 0;
	int ret = 0;
	struct exchange cmd;
	const struct sensor_t *s;
	int handle;

	if (mCmdFd < 0) {
		PERR("<BST> " "cannot tx cmd: %s",
				(char *)strerror(-mCmdFd));
		return mCmdFd;
	}

	handle = BstSensor::id2handle(id);
	if (-1 == handle) {
		PERR("<BST> " "flush: cannot get handle for id %d", id);
		return 0;
	}

	cmd.magic = CHANNEL_PKT_MAGIC_CMD;

	cmd.command.cmd = SET_SENSOR_FLUSH;
	cmd.command.code = handle;

	s = BstSensorInfo::getSensor(id);
	PINFO("<BST> " "flush <%s>, id: %d",
			(s != NULL) ? s->name : "unknown", id);

	err = write(mCmdFd, &cmd, sizeof(cmd));
	ret = err < (int)sizeof(cmd) ? -1 : 0;

	return ret;

#else
	UNUSED_PARAM(id);
	return -EINVAL;
#endif
}

int BstSensor::batch(int id, int flags, int64_t period_ns, int64_t timeout)
{
	int ret = 0;

	UNUSED_PARAM(flags);
	UNUSED_PARAM(timeout);
	ret = BstSensor::setDelay(id, period_ns);
	return ret;
}
#endif


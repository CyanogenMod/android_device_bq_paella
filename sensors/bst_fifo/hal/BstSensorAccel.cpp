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
 * @file         BstSensorAccel.cpp
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
#include <linux/input.h>
#include <sys/stat.h>


#include "BstSensor.h"
#include "BstSensorAccel.h"
#include "TargetPlatform.h"

const struct bst_axis_remap
BstSensorAccel::sTabAxisRemapDft[BST_DFT_AXIS_REMAP_TAB_SZ] = {
	/* src_x src_y src_z  sign_x  sign_y  sign_z */
	{  1,    0,    2,     -1,     1,      1 }, /* P0 */
	{  0,    1,    2,     1,      1,      1 }, /* P1 */
	{  0,    1,    2,    -1,     -1,      1 }, /* P2 */
	{  1,    0,    2,     1,     -1,      1 }, /* P3 */

	{  0,    1,    2,    -1,      1,     -1 }, /* P4 */
	{  1,    0,    2,     1,      1,     -1 }, /* P5 */
	{  1,    0,    2,    -1,     -1,     -1 }, /* P6 */
	{  0,    1,    2,     1,     -1,     -1 }, /* P7 */

};

//odr is scaled by 1000
const sensor_accel_bw
BstSensorAccel::sTabHWBW[SENSOR_DEV_ACC_ODR_MAX] = {
	{3125,   0x03},
	{6250,  0x04},
	{12500,  0x05},
	{25000,  0x06},
	{50000, 0x07},
	{100000, 0x08},
	{200000, 0x09},
	{400000, 0x0a},
	{800000, 0x0b},
	{1600000, 0x0c},

};

const int BstSensorAccel::sArrAccRange[HW_A_RANGE_MAX] = {3,5,8,12};
const int64_t
BstSensorAccel::MIN_DELAY = 5 * SCALE_TIME_MS2NS;
const int32_t
BstSensorAccel::BASE_DELAY_WAKEUP = 256 * SCALE_TIME_MS2NS;

BstSensorAccel::BstSensorAccel(const char* name, SensorBase *delegate)
: SensorBase(NULL, name),
	mEnabled(0),
	mInputReader(4),
	mDelegate(delegate)
{
	int chip_id;
	int err;
	int range;

	mPendingEvent.version = sizeof(sensors_event_t);
	mPendingEvent.sensor = ID_A;
	mPendingEvent.type = SENSOR_TYPE_ACCELEROMETER;
	memset(mPendingEvent.data, 0, sizeof(mPendingEvent.data));

	if (data_fd < 0)
		return;

	if (data_fd) {
		memset(mInputSysfsPath_A, 0, sizeof(mInputSysfsPath_A));
		strcpy(mInputSysfsPath_A, "/sys/class/input/");
		strcat(mInputSysfsPath_A, input_name);
		strcat(mInputSysfsPath_A, "/device/");
		mInputSysfsPathLen = strlen(mInputSysfsPath_A);
	}

	mRef = 0;

	mBW = -1;
	range = HW_A_RANGE_4G;/*need to follow the latest Android definition*/
	setRange(range);

#ifdef BST_SENSOR_PLACE_A
	mPlace = BST_SENSOR_PLACE_A;
#else
	mPlace = 7;
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_3__
		mPendingFlushFinishEvent = 0;
#endif

	mScale = 1;
	err = getInputSysfsNodeInt((const char*)"chip_id", &chip_id);
	if (!err)
	{
		switch (chip_id)
		{
			case BMA_CHIPID_BMI160C2:
			case BMA_CHIPID_BMI160C3:
				if (range == HW_A_RANGE_4G)
					mScale = 2;
				if (range == HW_A_RANGE_2G)
					mScale = 1;
				break;
			default:
				PERR("<BST> unknow chip_id %d", chip_id);
		}
	}
}


BstSensorAccel::~BstSensorAccel() {
	if (mEnabled) {
		enable(ID_A, 0);
	}
}

void BstSensorAccel::bmi_saveCalibOffset(int sensor_calib_sel)
{
	int tmp = 0;
	int err = 0;
	int offset_x = 0;
	int offset_y = 0;
	int offset_z = 0;
	int fd = -1;
	char buf[64] = "";
	char * filename;

	if (ACC_CALIB_DONE_STATUS == sensor_calib_sel)
		filename = (char *)SENSOR_CFG_FILE_FAST_CALIB_A;
	else if (GYRO_CALIB_DONE_STATUS == sensor_calib_sel)
		filename = (char *)SENSOR_CFG_FILE_FAST_CALIB_G;
	else
		return;
	
	PINFO("file: %s does not exist, will be created", filename);
	fd = open(filename, O_RDWR | O_CREAT,
				S_IRUSR | S_IWUSR |
				S_IRGRP | S_IWGRP |
	            S_IROTH | S_IWOTH);
	if (-1 == fd) 
	{
		PERR("fail to create file: %s", filename);
		return;
	}

	if (ACC_CALIB_DONE_STATUS == sensor_calib_sel)
	{
		getInputSysfsNodeInt((const char*)"acc_offset_x", &offset_x);
		getInputSysfsNodeInt((const char*)"acc_offset_y", &offset_y);
		getInputSysfsNodeInt((const char*)"acc_offset_z", &offset_z);
	}
	if (GYRO_CALIB_DONE_STATUS == sensor_calib_sel)
	{
		getInputSysfsNodeInt((const char*)"gyro_offset_x", &offset_x);
		getInputSysfsNodeInt((const char*)"gyro_offset_y", &offset_y);
		getInputSysfsNodeInt((const char*)"gyro_offset_z", &offset_z);
	}

	tmp = sprintf(buf, "%d,%d,%d", offset_x, offset_y, offset_z);
	err = write(fd, buf, tmp);

	if (-1 == err)
	{
	        PERR("save fast calib offset failed: %s", buf);
	}
	else
	{
	        PINFO(" save fast calib offset success, %s", buf);
	}
	close (fd);

}


int BstSensorAccel::setDelay(int32_t handle, int64_t ns)
{
	int err = 0;
	int delay;
	int fifo_mode = 0;

	getInputSysfsNodeInt((const char*)"fifo_data_sel", &fifo_mode);
	PDEBUG("<BST> set delay: %jdns, fifo_data_sel:%d", ns, fifo_mode);
	if (!mDelegate) {
		if (ns < MIN_DELAY) {
			PWARN("delay too short: %jd", ns);
			ns = MIN_DELAY;
		}
		if (66667000 == ns)
			delay = 50;
		else
			delay = (int32_t)(ns / SCALE_TIME_MS2NS);
		if (fifo_mode == 0)
		{
			setBW(getBWFromDelay(ns));
		}
		err = setInputSysfsNodeInt("delay", delay);
	} else {
		err = mDelegate->setDelay(handle, ns);
	}

	if (err) {
		PERR("<BST> fail to set delay of accel");
	}

	return err;
}

int BstSensorAccel::enable(int32_t handle, int en)
{
	int err = -1;
	struct timespec ts;

	en = en ? 1 : 0;

	PDEBUG("<BST> %s accel, orig state: %d",
			en ? "enable" : "disable", mEnabled);
	if (en != mEnabled) {
		if (!mDelegate) {
			err = setInputSysfsNodeInt("enable", en);
			
		} else {
			err = mDelegate->enable(handle, en);
		}

		if (!err) {
			mEnabled = en;
		} else {
			PERR("<BST> fail to enable accel");
		}
	}

	return err;
}

int BstSensorAccel::processEvent(const input_event * event)
{
	int err = 0;
	int value;

	if (EV_ABS == event->type)
	{
		value = event->value;

		switch (event->code)
		{
			case ABS_X:
				mPendingEvent.acceleration.x =
					value * mScale * SCALE_GRAVITY;
				break;
			case ABS_Y:
				mPendingEvent.acceleration.y =
					value * mScale * SCALE_GRAVITY;
				break;
			case ABS_Z:
				mPendingEvent.acceleration.z =
					value * mScale * SCALE_GRAVITY;
				uevent_flag = 1;
				break;
			default:
				break;
		}
		
	}

	if (EV_MSC == event->type)
	{
		switch(event->code)
		{
		#ifdef __BMI_FAST_CALIB_FEATURE__
			case BMI_FAST_CALIB_ACC_DONE:
				PDEBUG("save acc calibrated offset value");
				BstSensorAccel::bmi_saveCalibOffset(ACC_CALIB_DONE_STATUS);
				break;
			case BMI_FAST_CALIB_GYRO_DONE:
				PDEBUG("save gyro calibrated offset value");
				BstSensorAccel::bmi_saveCalibOffset(GYRO_CALIB_DONE_STATUS);
				break;
		#endif

			default:
				break;
		}
		uevent_flag = 0;
	}

	return err;

}

int BstSensorAccel::readEvents(sensors_event_t* data, int count)
{
	int numEventReceived = 0;
	input_event const* event;
	int type;
	int err = 0;
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_3__
	sensors_meta_data_event_t flush_finish_event;
#endif

	if (count < 1)
		return 0;

#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_3__
	if (mEnabled) {
		/*PINFO("<BST> " "mPendingFlushFinishEvent = %d ",
				mPendingFlushFinishEvent);*/

		flush_finish_event.version = META_DATA_VERSION;
		flush_finish_event.type = SENSOR_TYPE_META_DATA;
		flush_finish_event.meta_data.what = META_DATA_FLUSH_COMPLETE;
		flush_finish_event.meta_data.sensor = SENSORS_ACCELERATION_HANDLE;

		while(mPendingFlushFinishEvent){
			PINFO("<BST> " "report flush finish event for sensor id: %d",
					flush_finish_event.meta_data.sensor);
			*data++ = flush_finish_event;
			count--;
			numEventReceived++;
			mPendingFlushFinishEvent--;
		}
	}
#endif

	ssize_t n = mInputReader.fill(data_fd);
	if (n < 0)
		return 0;
	while (count && mInputReader.readEvent(&event)) {
		type = event->type;
		
		if (EV_SYN == type) {
			mPendingEvent.timestamp = timevalToNano(event->time);
			if (mEnabled & uevent_flag) {
				*data = mPendingEvent;
				remapSensorData(data, mPlace);
				data++;
				count--;
				numEventReceived++;
			}
		} else {
			err = processEvent((event));
			if (err) {
				PWARN("<BST> accel unknown event"
					"(type=%d code=%d value=%d)",
					event->type, event->code, event->value);
				return 0;
			}
		}
		mInputReader.next();
	}

	return numEventReceived;
}

int BstSensorAccel::getInputSysfsNodeInt(const char *name, int *val)
{
	int err = 0;
	int ret = 0;
	int fd;
	/* 32 is enough for an integer */
	char buf[32] = "";
	strncpy(&mInputSysfsPath_A[mInputSysfsPathLen], name,
		sizeof(mInputSysfsPath_A) - mInputSysfsPathLen - 1);

	PINFO("getinputsysfsnode: mInputSysfsPath:%s", mInputSysfsPath_A);
	fd = open(mInputSysfsPath_A, O_RDONLY);
	if (fd >= 0) {
		ret = read(fd, buf, sizeof(buf) - 1);
		if (ret > 0) {
			err = sscanf(buf, "%10d", val);
			if (1 != err) {
				PERR("<BST> fail to scan int");
				err = -EINVAL;
			} else {
				err = 0;
			}
		} else {
			PERR("<BST> fail to read int: %s", strerror(errno));
			err = -EIO;
		}
		close(fd);
	} else {
		PERR("<BST> fail to open file: %s", strerror(errno));
		err = -ENOENT;
	}

	return err;
}


int BstSensorAccel::setInputSysfsNodeInt(const char *name, int val)
{
	int err = 0;
	int ret = 0;
	int fd;
	/* 32 is enough for an integer */
	char buf[32] = "";

	strncpy(&mInputSysfsPath_A[mInputSysfsPathLen], name,
		sizeof(mInputSysfsPath_A) - mInputSysfsPathLen - 1);

	fd = open(mInputSysfsPath_A, O_RDWR);
	if (fd >= 0) {
		snprintf(buf, sizeof(buf) - 1, "%d", val);
		ret = write(fd, buf, strlen(buf) + 1);
		if (ret > 0) {
			err = 0;
		} else {
			PERR("write error");
			err = -EIO;
		}
		close(fd);
	} else {
		err = -ENOENT;
	}
	PINFO("mInputSysfsPath_A:%s,buf:%s,%d",mInputSysfsPath_A, buf, err);
	return err;
}


int BstSensorAccel::setBW(int bw)
{
	int err;

	if (bw == mBW) {
		return 0;
	}

	err = setInputSysfsNodeInt("acc_odr", sTabHWBW[bw].reg_val);

	if (!err) {
		mBW = bw;
	}
	return err;
}


int BstSensorAccel::setRange(int range)
{
	int err = 0;
	err = setInputSysfsNodeInt("acc_range", sArrAccRange[range]);
	if (!err) {
		mRange = range;
	}
	return err;
}

void BstSensorAccel::lock()
{
	if (1) {
		pthread_mutex_lock(&mLock);
	}
}

void BstSensorAccel::unlock()
{
	if (1) {
		pthread_mutex_unlock(&mLock);
	}
}

void BstSensorAccel::remapSensorData(sensors_event_t *event,
				     const struct bst_axis_remap *remap)
{

	sensors_event_t tmp;
	tmp.data[0] = event->data[remap->src_x] * remap->sign_x;
	tmp.data[1] = event->data[remap->src_y] * remap->sign_y;
	tmp.data[2] = event->data[remap->src_z] * remap->sign_z;

	memcpy(event->data, tmp.data, sizeof(event->data[0]) * 3);
}

void BstSensorAccel::remapSensorData(sensors_event_t *event, int place)
{
	if ((0 < place) && (BST_DFT_AXIS_REMAP_TAB_SZ > place)) {
		remapSensorData(event,
				BstSensorAccel::sTabAxisRemapDft + place);
	}
}

int BstSensorAccel::getBWFromDelay(uint64_t delay_ns)
{
	int bw;
	int odr;
	int64_t tmp;
	int i;

	if (1000 > delay_ns) {
		i = ARRAY_SIZE(sTabHWBW) - 1;
		bw = i;
		return bw;
	}

	//data rate is scaled
	delay_ns /= 1000;
	odr = (int32_t)(SCALE_TIME_S2NS / delay_ns);
	tmp = SCALE_TIME_S2NS - odr * delay_ns;

	/* always use higher datarate than requested */
	if (tmp > 0) {
		odr += 1;
	}

	for (i = 0; i < (int)ARRAY_SIZE(sTabHWBW); i++) {
		if (sTabHWBW[i].odr >= odr) {
			break;
		}
	}

	if (i >= (int)ARRAY_SIZE(sTabHWBW)) {
		i = ARRAY_SIZE(sTabHWBW) - 1;
	}

	bw = i;

	return bw;
}
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
int BstSensorAccel::flush(int id)
{
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_3__
	int ret = 0;

	mPendingFlushFinishEvent++;

	PINFO("<BST> flush sensor id: %d for %d times", id, mPendingFlushFinishEvent);

	return ret;

#else
	UNUSED_PARAM(id);
	return -EINVAL;
#endif
}
int BstSensorAccel::batch(int id, int flags, int64_t period_ns, int64_t timeout)
{
	int ret = 0;

	UNUSED_PARAM(flags);
	UNUSED_PARAM(timeout);
	ret = BstSensorAccel::setDelay(id, period_ns);
	return ret;
}
#endif

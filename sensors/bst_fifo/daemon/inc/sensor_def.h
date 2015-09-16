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
 * @file         sensor_def.h
 * @date         "Fri Jan 9 17:45:01 2015 +0800"
 * @commit       "7c424a4"
 *
 * @brief
 *
 * @detail
 *
 */

#ifndef __SENSOR_DEF_H
#define __SENSOR_DEF_H


enum SENSOR_HW_TYPE {
	SENSOR_HW_TYPE_A,	/* 0 */
	SENSOR_HW_TYPE_G,	/* 2 */
	SENSOR_HW_TYPE_M,	/* 4 */
	SENSOR_HW_TYPE_MAX	/* 7 */
};

#define SENSOR_TYPE_META_DATA (0)
/*bmi fifo sensor type combination*/
enum BMI_SENSOR_COMBINATION {
	BMI_HW_A = 1,
	BMI_HW_G,
	BMI_HW_G_A,
	BMI_HW_M,
	BMI_HW_M_A,
	BMI_HW_M_G,
	BMI_HW_M_G_A,
	BMI_HW_COM_MAX
};


/*! Accelerator sensor */
#define SENSOR_TYPE_A 1

/*! Magnetic sensor, not supported by IMU */
#define SENSOR_TYPE_M 2

/*! Gyroscope sensor, not suppported by Compass, m4g */
#define SENSOR_TYPE_G 3

/*! Orientation sensor, not supported by IMU, confirm later */
#define SENSOR_TYPE_O 4

/*! Virtual gravity sensor, not suppported by compass, m4g */
#define SENSOR_TYPE_VG 5

/*! Virtual linear accelerator sensor, not suppported by compass, m4g */
#define SENSOR_TYPE_VLA 6

/*! Virtual rotation vector sensor, not suppported by compass, confirm later
		for m4g */
#define SENSOR_TYPE_VRV 7

#ifdef __UNCALIBRATED_VIRTUAL_SENSOR_SUPPORT__
/*! Virtual game rortation vector sensor */
#define SENSOR_TYPE_GRV 8
/*! Virtual gyro uncalibrated sensor */
#define SENSOR_TYPE_GYU 9
/*! Virtual magnetic uncalibrated sensor */
#define SENSOR_TYPE_MU 10
#endif
/*! Virtual geomagnetic rotation vector */
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
#define SENSOR_TYPE_GEOM_RV 11
#endif

#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_0__
#define SENSOR_TYPE_STC 14
#define SENSOR_TYPE_STD 15
#endif


/* non-standard sensor types */
#define SENSOR_TYPE_NONSTD_START 24
#define SENSOR_TYPE_GEST_FLIP (SENSOR_TYPE_NONSTD_START + 0)
#define SENSOR_TYPE_SW_SIGNIFICANT_MOTION (SENSOR_TYPE_NONSTD_START + 1)
/*!
 * @brief This enumeration is to identify handle for each sensor and keep
 *  matching with hal, pls donot add, remove, or modify sequence
 */
enum SENSOR_HANDLE {
	SENSOR_HANDLE_START = 0,
	SENSOR_HANDLE_ACCELERATION,	/* 1 */
	SENSOR_HANDLE_MAGNETIC_FIELD,	/* 2 */
	SENSOR_HANDLE_ORIENTATION,	/* 3 */
	SENSOR_HANDLE_GYROSCOPE	,	/* 4 */
	SENSOR_HANDLE_LIGHT,		/* 5 */
	SENSOR_HANDLE_PRESSURE,		/* 6 */
	SENSOR_HANDLE_TEMPERATURE,	/* 7 */
	SENSOR_HANDLE_PROXIMITY,	/* 8 */
	SENSOR_HANDLE_GRAVITY,		/* 9 */
	SENSOR_HANDLE_LINEAR_ACCELERATION,	/* 10 */
	SENSOR_HANDLE_ROTATION_VECTOR,	/* 11 */
	SENSOR_HANDLE_ORIENTATION_RAW,	/* 12 */
	SENSOR_HANDLE_GEST_FLIP,        /* 13 */
	SENSOR_HANDLE_SW_SIGNIFCANT_MOITON,
#ifdef __UNCALIBRATED_VIRTUAL_SENSOR_SUPPORT__
	SENSOR_HANDLE_GAME_ROTATION_VECTOR,	/* 14*/
	SENSOR_HANDLE_GYROSCOPE_UNCALIBRATED,	/* 15 */
	SENSOR_HANDLE_MAGNETIC_FIELD_UNCALIBRATED,	/* 16 */
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
	SENSOR_HANDLE_GEOMAGNETIC_ROTATION_VECTOR,
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_0__
	SENSOR_HANDLE_STEP_COUNTER,
	SENSOR_HANDLE_STEP_DETECTOR,
#endif


	SENSOR_HANDLE_END
};


enum DEV_AVAILABILITY{
	UNAVAILABLE = 0,
	AVAILABLE,
	VIRTUAL
};


enum GEST_FLIP_VAL {
	SENSOR_GEST_FLIP_VAL_UNKNOWN = 0,
	SENSOR_GEST_FLIP_VAL_UP,               /* 1 */
	SENSOR_GEST_FLIP_VAL_DOWN,             /* 2 */
	SENSOR_GEST_FLIP_VAL_NEUTRAL,          /* 3 */
	SENSOR_GEST_FLIP_VAL_END
};

#define SET_SENSOR_ACTIVE	0x01
#define SET_SENSOR_DELAY	0x02
#define SET_SENSOR_FLUSH	0x03


#define CHANNEL_PKT_MAGIC_CMD   (int)'C'
#define CHANNEL_PKT_MAGIC_DAT   (int)'D'
#define CHANNEL_PKT_MAGIC_LIST  (int)'L'


#define SENSOR_ACCURACY_UNRELIABLE	0
#define SENSOR_ACCURACY_LOW		1
#define SENSOR_ACCURACY_MEDIUM		2
#define SENSOR_ACCURACY_HIGH		3


#define SENSOR_MAGIC_A 'a'
#define SENSOR_MAGIC_G 'g'
#define SENSOR_MAGIC_M 'm'

#define SENSOR_MAGIC_VG 'G'
#define SENSOR_MAGIC_VLA 'A'
#define SENSOR_MAGIC_VRV 'v'

#ifdef __UNCALIBRATED_VIRTUAL_SENSOR_SUPPORT__
#define SENSOR_MAGIC_GRV 'R'
#define SENSOR_MAGIC_GYU 'Y'
#define SENSOR_MAGIC_MU 'F'
#endif
#ifdef __SIGNIFICANT_MOTION_SENSOR_SUPPORT__
#define SENSOR_MAGIC_SMT 'S'
#endif
#ifdef __SIGNIFICANT_MOTION_SENSOR_SUPPORT__
#define SENSOR_MAGIC_TAP 'T'
#endif


/* other definitions */
/* gb: 1, ics: 0 */
#define SAMPLE_INTERVAL_MIN 0
#define SAMPLE_INTERVAL_MAX 1000


#ifndef GRAVITY_EARTH
#define GRAVITY_EARTH (9.80665f)
#endif

#ifndef PI
#define PI 3.1415926f
#endif

#define RADIAN2DEGREE  (180 / PI)

#endif

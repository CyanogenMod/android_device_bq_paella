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
 * @file         BstSensorDataType.h
 * @date         "Thu Jan 8 18:20:01 2015 +0800"
 * @commit       "4b0860f"
 *
 * @brief
 *
 * @detail
 *
 */


#ifndef SENSOR_DATA_TYPE_H
#define SENSOR_DATA_TYPE_H

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>

typedef struct {
	union {
		int32_t v[4];
		struct {
			int32_t x;
			int32_t y;
			int32_t z;
			/* might be used for quaternion */
			int32_t w;
		};
	};
} sensor_data_ival_t;


typedef struct {
	union {
		float v[4];
		struct {
			float x;
			float y;
			float z;
			/* might be used for quaternion */
			float w;
		};
		struct {
			float azimuth;
			float pitch;
			float roll;
			float reserved;
		};
	};
} sensor_data_vec_t;

/**
 * Union of the various types of sensor data
 * that can be returned.
 */
typedef struct {
	/* must be sizeof(struct sensor_data_t) */
	int32_t version;

	uint32_t status;
	uint32_t corrected;
	uint32_t filtered;

	/* sensor identifier */
	int32_t sensor;

	/* sensor type */
	int32_t type;

	/* time is in nanosecond */
	union {
		int64_t timestamp;
		uint32_t reserved[2];
	};

	union {
	#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_0__
		float           data[16];

		/* relative humidity in percent */
		float           relative_humidity;

		/* step-counter */
		uint64_t        step_counter;

		/* uncalibrated gyroscope values are in rad/s */
		uncalibrated_event_t uncalibrated_gyro;

		/* uncalibrated magnetometer values are in micro-Teslas */
		uncalibrated_event_t uncalibrated_magnetic;
	#else
		float           data[4];
	#endif

		/* acceleration values are in meter per second per second (m/s^2) */
		sensor_data_vec_t   acceleration;

		/* magnetic vector values are in micro-Tesla (uT) */
		sensor_data_vec_t   magnetic;

		/* orientation values are in degrees */
		sensor_data_vec_t   orientation;

		/* gyroscope values are in rad/s */
		sensor_data_vec_t   gyro;

		/* temperature is in degrees centigrade (Celsius) */
		float           temperature;

		/* distance in centimeters */
		float           distance;

		/* light in SI lux units */
		float           light;

		/* pressure in hectopascal (hPa) */
		float           pressure;
	};
} sensor_data_t;


struct exchange {
	int magic;

	union {
		struct {
			int32_t cmd;
			int32_t code;
			int32_t value;

			int32_t reserved[6];
		} command;

		sensor_data_t data;
	};

	int64_t ts;
};


typedef char BS_S8;
typedef uint8_t BS_U8;
typedef int16_t BS_S16;
typedef uint16_t BS_U16;
typedef int32_t BS_S32;
typedef uint32_t BS_U32;

typedef float BS_F32;
typedef double BS_F64;


struct value_map {
	int l;
	int r;
};

#endif  /* ANDROID_SENSORS_INTERFACE_H */

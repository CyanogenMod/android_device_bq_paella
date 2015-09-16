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
 * @file         sensor_hw.h
 * @date         "Wed Dec 31 15:33:20 2014 +0800"
 * @commit       "7b2e44c"
 *
 * @brief
 *
 * @detail
 *
 */

#ifndef __SENSOR_HW_H
#define __SENSOR_HW_H
#include <stdint.h>

/* a bitmap of dependencies */
/* NOTE: limitations: hw number limited to 16 */
typedef int16_t hw_dep_set_t;

typedef struct axis_remap {
	unsigned int rx;
	unsigned int ry;
	unsigned int rz;

	unsigned int sx;
	unsigned int sy;
	unsigned int sz;
} axis_remap_t;


struct sensor_hw {
	const char const *name;

	/* defined as SENSOR_HW_TYPE_X */
	const int32_t type;

	uint32_t available;
	uint32_t fd_pollable;
	/* NOTE: limitations: */
	uint32_t wakeup_time;

	int32_t ref;
	uint32_t enabled;
	uint32_t drdy;
	int32_t delay;

	int fd_poll;
	uint32_t ts_last_update;

	void *private_data;

	pthread_mutex_t lock_ref;
	/* mandatory: */
	int (*init)(struct sensor_hw *);
	/* mandatory: */
	int (*enable)(struct sensor_hw *, int);

	/* optional: */
	int (*restore_cfg)(struct sensor_hw *);
	/* optional: */
	int (*set_delay)(struct sensor_hw *, int);

	/* mandatory if the device is not pollable */
	int (*get_drdy_status)(struct sensor_hw *);

	/* either get_data_nb() or get_data() or both should be provided */
	/* optional: 
	 * this function should get the data from the device in a non-blocking way
	 */
	int (*get_data_nb)(void *val);
	/* optional: this function get the data from the device and it might block */
	int (*get_data)(void *val);
};


struct sensor_hw_a {
	struct sensor_hw hw;

	uint32_t bw;
	uint32_t range;
	uint32_t data_bits;
	uint32_t place;

	int (*set_bw)(struct sensor_hw_a *, uint32_t bw);
	int (*set_range)(struct sensor_hw_a *, uint32_t range);
};


struct sensor_hw_m {
	struct sensor_hw hw;

	uint32_t data_bits;
	uint32_t place;
};


struct sensor_hw_g {
	struct sensor_hw hw;

	uint32_t bw;
	uint32_t range;
	uint32_t data_bits;
	uint32_t place;

	int (*set_bw)(struct sensor_hw_g *, uint32_t bw);
	int (*set_range)(struct sensor_hw_g *, uint32_t range);
};
#endif

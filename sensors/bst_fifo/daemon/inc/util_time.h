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
 * @file         util_time.h
 * @date         "Wed Dec 31 15:33:20 2014 +0800"
 * @commit       "7b2e44c"
 *
 * @brief
 *
 * @detail
 *
 */

#ifndef __UTIL_TIME_H
#define __UTIL_TIME_H

#define TIME_SCALE_S2NS 1000000000LL
#define TIME_SCALE_US2NS 1000LL
#define TIME_SCALE_S2US 1000000L
#define TIME_SCALE_S2MS 1000L

#include <time.h>
#include <stdint.h>
#include <unistd.h>


struct clock_spec {
	time_t tv_sec;
	long tv_nsec;
};


enum {
	TIME_UNIT_START = -1,
	TIME_UNIT_S,
	TIME_UNIT_MS,
	TIME_UNIT_US,
	TIME_UNIT_NS
};


typedef int64_t time_tick_t;
typedef time_tick_t time_tick_ns_t;

struct clock_provider {
	const char *name;
	struct clock_spec res;
	/* when it is started */
	struct clock_spec start;
	struct clock_spec start_ref;

	uint32_t available:1;

	int (*init)(struct clock_provider *);
	void (*reset)(struct clock_provider *);
	void (*get_tick_ns)(struct clock_provider *, time_tick_ns_t*);
};

uint32_t get_current_timestamp(void);
void get_curr_time_str(char *buf_str, int len);
unsigned int get_time_tick();
void eusleep(uint32_t);
void adv_nsleep_short(long ns, int restart);

void time_init();

extern struct clock_provider *g_cp_dft;
#endif

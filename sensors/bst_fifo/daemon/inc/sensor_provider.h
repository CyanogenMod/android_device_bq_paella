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
 * @file         sensor_provider.h
 * @date         "Wed Dec 31 15:33:20 2014 +0800"
 * @commit       "7b2e44c"
 *
 * @brief
 *
 * @detail
 *
 */

#ifndef __SENSOR_PROVIDER_H
#define __SENSOR_PROVIDER_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#include <linux/fs.h>

#include <fcntl.h>
#include <signal.h>
#include <pthread.h>

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "configure.h"
#include "options.h"

#include "util_misc.h"

struct run_entity {
	pthread_t ptid;
	int32_t tid;

	volatile uint32_t started:1;
	uint32_t op_blk:1;
	volatile uint32_t sleeping:1;

	/* NOTE: limitations */
	uint32_t interval:16;

	/* optional, can be NULL */
	void *private_data;

	void *func_fp;
	/* the owner of the run entity */
	//void *owner;
	/* condition for thread */
	pthread_cond_t cond;

	void *(*func)(void *);
};


struct sensor_provider {
	const char *name;
	/* a bitmap of sensors supported */
	uint32_t sensors;

	uint32_t available:1;
	/* type of the provider, not used now */
	uint32_t type:4;
	uint32_t client_num:6;
	int32_t ref:6;

	hw_dep_set_t curr_hw_dep;
	struct list_node *clients;
	void *buf_out;
	void *private_data;
	pthread_mutex_t lock_ref;
	struct run_entity re;

	/* return value of 0 means success, otherwise failure */
	/* mandatory */
	int (*init)(struct sensor_provider *sp);
	/* mandatory: notify the provider that a channel will be enabled or disabled,
	 * thus the provider can change its internal state, and some
	 * provider such as an algo relies on this to know the new hw dep, etc */
	int (*on_ch_enabled)(struct channel *, int);
	/* mandatory: an owner such as an algo might provide this
	 * function to indicate the scheduling interval requirement
	 */
	int (*on_ch_interval_changed)(struct channel *, int);

	/* optional: an owner such an algo might provide this
	 * function to do singal processing
	 */
	void (*proc_data)(uint32_t);

	/* optional: */
	int32_t (*get_hint_proc_interval)();
	/* mandatory: get current dependency of hw needed to produce
	 * all the required products
	 */
	void (*get_curr_hw_dep)(hw_dep_set_t *);

	/* optional: after the h/ws are enabled/disabled as needed,
	 * the provider will be notified */
	int (*on_hw_dep_checked)(const hw_dep_set_t *);

	/* optional: */
	void (*exit)(void *);
};


void sp_preinit();
void sp_init();
void sp_dump();
struct sensor_provider *sp_scan_for_provider(struct channel *ch);
void sp_register_ch(struct sensor_provider *sp, struct channel *ch);
void sp_recalc_interval_re(struct sensor_provider *sp);
void sp_enable_ch(struct sensor_provider *sp, struct channel *ch, int enable);
void* re_proc(void* pparam);

void* re_proc(void* pparam);
#endif

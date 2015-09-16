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
 * @file         channel_gest_flip.c
 * @date         "Wed Dec 31 15:33:20 2014 +0800"
 * @commit       "7b2e44c"
 *
 * @brief
 *  This file implements a virtual flip sensor, initialize and get data
 *
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <linux/ioctl.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define LOG_TAG_MODULE "<channel_gest_flip>"
#include "sensord.h"

int channel_gest_flip_get_data(void *pbuf, int n)
{
	struct exchange *pmsg = (struct exchange *)pbuf;

	UNUSED_PARAM(n);

	return algo_get_proc_data_gest_flip(&pmsg->data);
}


int channel_gest_flip_init(struct channel *ch)
{
	ch->cfg.interval_min = CFG_DELAY_GEST_FLIP_MIN;
	ch->cfg.interval_max = CFG_DELAY_GEST_FLIP_MAX;
	ch->cfg.no_delay = 1;
	bsx_set_flipgesture_detecttime(1000);
	bsx_set_flipgesture_angle(FLIP_FACE_UP, FLIP_FACE_DOWN);
	return 0;
}

int channel_gest_flip_enable(struct channel *ch, int en)
{
	if (NULL == ch)
	{
		return -1;
	}

	(void)algo_set_opmode(SENSOR_TYPE_GEST_FLIP,en);

	return 0;
 }


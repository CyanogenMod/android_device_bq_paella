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
 * @file         channel_vla.c
 * @date         "Thu Jan 8 18:20:01 2015 +0800"
 * @commit       "4b0860f"
 *
 * @brief
 *
 * @detail
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

#ifdef TARGET_OS_ANDROID
#include <cutils/log.h>
#endif

#include <time.h>
#include <sys/time.h>

#define LOG_TAG_MODULE "<channel_vla>"
#include "sensord.h"

int get_data_vla(void *pbuf, int n)
{
	struct exchange *pmsg = (struct exchange *)pbuf;

	UNUSED_PARAM(n);
	algo_get_proc_data_vla(&pmsg->data);

	return 1;
}

int channel_init_vla(struct channel *ch)
{
	if (NULL == ch)
	{
		return -1;
	}

	ch->cfg.no_delay     = 0;
	ch->cfg.interval_min = CFG_DELAY_VLA_MIN;
	ch->cfg.interval_max = CFG_DELAY_VLA_MAX;
	ch->cfg.dep_hw = CFG_HW_DEP_VLA;
	return 0;
}


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
 * @file         sensor_fusion.c
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
#include <time.h>
#include <sys/time.h>

#define LOG_TAG_MODULE "<channel_fusion>"
#include "sensord.h"

BS_U8 g_dr_a = 0;
BS_U8 g_dr_m = 0;
BS_U8 g_dr_g = 0;


struct algo_product g_products_fusion[] = {
	{
		type: SENSOR_TYPE_A,
	},
	{
		type: SENSOR_TYPE_G,
	},
	{
		type: SENSOR_TYPE_M,
	},
	{
		type: SENSOR_TYPE_O,
	},
	{
		type: SENSOR_TYPE_VG,
	},
	{
		type: SENSOR_TYPE_VLA,
	},
	{
		type: SENSOR_TYPE_VRV,
	},
	{
		type: SENSOR_TYPE_GEST_FLIP,
	},
	{
		type: SENSOR_TYPE_SW_SIGNIFICANT_MOTION,
	},
#ifdef __UNCALIBRATED_VIRTUAL_SENSOR_SUPPORT__
	{
		type: SENSOR_TYPE_GRV,
	},
	{
		type: SENSOR_TYPE_GYU,
	},
	{
		type: SENSOR_TYPE_MU,
	},
#endif

#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
	{
		type: SENSOR_TYPE_GEOM_RV,
	},
#endif
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_0__
	{
		type: SENSOR_TYPE_STC,
	},
	{
		type: SENSOR_TYPE_STD,
	},
#endif


};

static struct exchange g_buf_out_fusion[ARRAY_SIZE(g_products_fusion)];

struct algo_product *fusion_get_product(uint32_t type)
{
	struct algo_product *ap = NULL;
	int i;

	for (i = 0; i < ARRAY_SIZE(g_products_fusion); i++) {
		ap = g_products_fusion + i;
		if (type == ap->type) {
			return ap;
		}
	}

	return NULL;
}


int fusion_init(struct sensor_provider *sp)
{
	int err = 0;
	struct algo_product *ap;
	int i = 0;

	UNUSED_PARAM(sp);

	for (i = 0; i < ARRAY_SIZE(g_products_fusion); i++) {
		ap = g_products_fusion + i;
		ap->enable = 0;
		ap->dr_a = 0;
		ap->dr_m = 0;
		ap->dr_g = 0;

		ap->dr_acc_min = 0;
		ap->dr_acc_max = 0;
		ap->dr_mag_min = 0;
		ap->dr_mag_max = 0;
		ap->dr_gyro_min = 0;
		ap->dr_gyro_max = 0;
	}

	err = algo_init();
	if (err) {
		PINFO("algorithm init error");
	}

	sp->buf_out = g_buf_out_fusion;

	return err;
}


void fusion_proc_data(uint32_t ts)
{
	algo_proc_data(ts);
}


void fusion_arbitrate_dr()
{
	struct algo_product *ap;
	int i;
	uint8_t dr_a = 0;
	uint8_t dr_m = 0;
	uint8_t dr_g = 0;

	for (i = 0; i < ARRAY_SIZE(g_products_fusion); i++) {
		ap = g_products_fusion + i;

		if (ap->enable) {
			if (dr_a < ap->dr_a) {
				dr_a = ap->dr_a;
			}

			if (dr_m < ap->dr_m) {
				dr_m = ap->dr_m;
			}

			if (dr_g < ap->dr_g) {
				dr_g = ap->dr_g;
			}
		}
	}

	PINFO("arbitrated dr: %d %d %d", dr_a, dr_m, dr_g);
	g_dr_a = dr_a;
	g_dr_m = dr_m;
	g_dr_g = dr_g;
}


int fusion_on_ch_enabled(struct channel *ch, int enable)
{
	int err = 0;
	struct algo_product *ap;

	ap = fusion_get_product(ch->type);
	if (NULL != ap) {
		ap->enable = enable;
		ap->bypass_proc = ch->cfg.bypass_proc;
		algo_enable_product(ap, enable);
	} else {
		err = -EINVAL;
	}
	return err;
}


int fusion_on_ch_interval_changed(struct channel *ch, int interval)
{
	int err = 0;
	int new_intv = interval;
	struct algo_product *ap;

	ap = fusion_get_product(ch->type);
	if (NULL != ap) {
		algo_on_interval_changed(ap, &new_intv);
	} else {
		err = -EINVAL;
	}

	ch->interval = new_intv;
	return err;
}


int fusion_get_hint_proc_interval()
{
	return algo_get_hint_interval();
}


void fusion_get_curr_hw_dep(hw_dep_set_t *dep)
{
	algo_get_curr_hw_dep(dep);
}


int fusion_on_hw_dep_checked(const hw_dep_set_t *dep)
{
	return algo_on_hw_dep_checked(dep);
}


struct algo g_sp_algo_fusion = {
	sp:
	{
		name: "SP_FUSION",
		sensors: ((1 << SENSOR_TYPE_A)
				| (1 << SENSOR_TYPE_G)
				| (1 << SENSOR_TYPE_M)
				| (1 << SENSOR_TYPE_O)
				| (1 << SENSOR_TYPE_VG)
				| (1 << SENSOR_TYPE_VLA)
				| (1 << SENSOR_TYPE_VRV)
				| (1 << SENSOR_TYPE_GEST_FLIP)
				| (1 << SENSOR_TYPE_SW_SIGNIFICANT_MOTION)
			#ifdef __UNCALIBRATED_VIRTUAL_SENSOR_SUPPORT__
				| (1 << SENSOR_TYPE_GRV)
				| (1 << SENSOR_TYPE_GYU)
				| (1 << SENSOR_TYPE_MU)
			#endif
			#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
				| (1 << SENSOR_TYPE_GEOM_RV)
			#endif
			#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_0__
				| (1 << SENSOR_TYPE_STC)
				| (1 << SENSOR_TYPE_STD)
			#endif
				),
		ref:0,
		init:fusion_init,
		proc_data:fusion_proc_data,
		on_ch_enabled:fusion_on_ch_enabled,
		on_ch_interval_changed:fusion_on_ch_interval_changed,
		get_hint_proc_interval:fusion_get_hint_proc_interval,
		get_curr_hw_dep: fusion_get_curr_hw_dep,
		on_hw_dep_checked:fusion_on_hw_dep_checked,
		exit:NULL,
		re:
			{
				func:re_proc
			}
	}
};

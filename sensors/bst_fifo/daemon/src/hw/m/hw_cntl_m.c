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
 * @file         hw_cntl_m.c
 * @date         "Fri Jan 30 18:07:49 2015 +0800"
 * @commit       "6732061"
 *
 * @brief
 *
 * @detail
 *
 */

#include <stdio.h>
#include <errno.h>

#include <linux/input.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define LOG_TAG_MODULE "<hw_cntl_m>"
#include "sensord.h"

#define HW_PLACE_UNDEFINED (-1)

int g_input_dev_num_m = -1;

static int g_fd_value_m = -1;
static int g_fd_op_mode_m = -1;
static int g_fd_input_ev_m = -1;

int g_place_m = HW_INFO_DFT_PLACE_M;
extern struct axis_remap axis_remap_tab_m[8];


enum MAG_FIFO_DATA_EN_T {
	MAG_FIFO_DISABLE = 0,
	MAG_FIFO_ENABLE
};

struct bmm_cfg {
	int rept_xy;
	int rept_z;
} g_bmm_cfg;

static const char *driver_names_tbl[] = {
#ifdef __HW_2ND_MAG_INTF_CONFIG__
	"bmi160",
#else
#ifdef __AMM202__
	"akm09911",
#elif defined (__AMM205__)
        "yas537",
#else
	"bmm050",
#endif
#endif
	NULL
};

static int hw_mag_set_opmode(BS_U8 mode)
{
	int err = 0;
	char path[128] = "";

	PDEBUG("mag op_mode: %d", mode);
	sprintf(path, "%s/input%d/%s",
			SYSFS_PATH_INPUT_DEV, g_input_dev_num_m, SYSFS_NODE_NAME_BMM_OP_MODE);

	err = sysfs_write_int(path, mode);

	return err;
}

static void hw_mag_validate_val(sensor_data_ival_t *val)
{
	sensor_data_ival_t tmp_val = *val;

	if ((int32_t)(INT_MIN) != tmp_val.x) {
	} else {
		PWARN("overflow in x");
		val->x = -(int32_t)(SHRT_MAX);
	}

	if ((int32_t)(INT_MIN) != tmp_val.y) {
	} else {
		PWARN("overflow in y");
		val->y = -(int32_t)(SHRT_MAX);
	}

	if ((int32_t)(INT_MIN) != tmp_val.z) {
	} else {
		PWARN("overflow in z");
		val->z = -(int32_t)(SHRT_MAX);
	}
}

int hw_get_bmm_data_register(sensor_data_ival_t *mag_val)
{
	int err = 0;
	int tmp;

	char buf[128] = "";


	if (-1 != g_fd_value_m) {
		lseek(g_fd_value_m, 0, SEEK_SET);
		tmp = read(g_fd_value_m, buf, sizeof(buf) - 1);
		if (0 < tmp) {
			buf[tmp] = 0;
			tmp = sscanf(buf, "%11d %11d %11d",
					(&mag_val->x), (&mag_val->y), (&mag_val->z));
			if (3 != tmp) {
				err = -EINVAL;
			}
		} else {
			PERR("error reading from bmm data register");
			err = -EIO;
		}
	}

	PDEBUG("[mag] x: %d y: %d z: %d", mag_val->x, mag_val->y, mag_val->z);

	return err;

}

static int hw_mag_read_xyzdata(void *data)
{
	int err = 0;
	int tmp;
	char buf[64] = "";
	sensor_data_ival_t *val = (sensor_data_ival_t *)data;

	val->x = 0;
	val->y = 0;
	val->z = 0;

	if (-1 != g_fd_value_m) {
		lseek(g_fd_value_m, 0, SEEK_SET);
		tmp = read(g_fd_value_m, buf, sizeof(buf) - 1);
		if (0 < tmp) {
			buf[tmp] = 0;
			tmp = sscanf(buf, "%11d %11d %11d",
					(&val->x), (&val->y), (&val->z));

			if (3 != tmp) {
				err = -EINVAL;
			}
		} else {
			PERR("error reading from mag");
			err = -EIO;
		}
	}
	if (-1 != g_fd_op_mode_m) {
		lseek(g_fd_op_mode_m, 0, SEEK_SET);
		/* forced mode */
		tmp = write(g_fd_op_mode_m, "1", 1);
		if (1 != tmp) {
			PERR("err setting forced mode");
		}
	}
	hw_mag_validate_val(val);

	if (g_place_m >= 0) {
		hw_remap_sensor_data(val, axis_remap_tab_m + g_place_m);
	}

	return err;
}


static int hw_mag_read_xyzdata_input_ev(void *data)
{
	struct input_event ev;
	int sync = 0;
	int err = 0;
	sensor_data_ival_t *val = (sensor_data_ival_t *)data;

	while (!sync) {
		err = read(g_fd_input_ev_m, &ev, sizeof(ev));
		if (err < (int)sizeof(ev)) {
			PERR("error reading event");
			err = -EIO;
			return -1;
		}

		switch (ev.type) {
		case EV_ABS:
			switch (ev.code) {
			case ABS_X:
				val->x = ev.value;
				break;
			case ABS_Y:
				val->y = ev.value;
				break;
			case ABS_Z:
				val->z = ev.value;
				break;
			}
			break;
		case EV_SYN:
			PDEBUG("EV_SYN got");
			sync = 1;
			err = 0;
			break;
		}
	}

	hw_mag_validate_val(val);
	if (g_place_m >= 0) {
		hw_remap_sensor_data(val, axis_remap_tab_m + g_place_m);
	}

	return err;
}


#ifdef HW_M_USE_INPUT_EVENT
static int hw_mag_set_enable_input_ev(BS_U8 enable)
{
	int err = 0;

	char path[128] = "";

	PDEBUG("mag enable: %d", enable);

	sprintf(path, "%s/input%d/%s",
			SYSFS_PATH_INPUT_DEV, g_input_dev_num_m, SYSFS_NODE_NAME_BMM_ENABLE);

	enable = !!enable;

	err = sysfs_write_int(path, enable);

	return err;
}
#endif


static int hw_mag_set_delay(struct sensor_hw *hw, BS_S32 delay)
{
	int err = 0;
	char path[128] = "";

	PINFO("delay: %d", delay);

	sprintf(path, "%s/input%d/%s",
			SYSFS_PATH_INPUT_DEV,
			g_input_dev_num_m,
			SYSFS_NODE_NAME_BMM_DELAY);

	err = sysfs_write_int(path, delay);
	if (!err) {
		hw->delay = delay;
	}

	return err;
}

static void hw_init_m_settings(struct sensor_hw *hw)
{
	g_bmm_cfg.rept_xy = BMM_REGULAR_REPXY;
	g_bmm_cfg.rept_z = BMM_REGULAR_REPZ;
	hw->private_data = &g_bmm_cfg;
}


static int hw_init_m(struct sensor_hw *hw)
{
	int err = 0;
	char path[128] = "";
	int place;
	int i = 0;

	g_input_dev_num_m = -1;
	while(driver_names_tbl[i])
	{
		g_input_dev_num_m = sysfs_get_input_dev_num(driver_names_tbl[i]);
		i++;
		if (g_input_dev_num_m >= 0)
		{
			break;
		}
	}
	PINFO("g_input_dev_num_m: %d", g_input_dev_num_m);

	g_fd_op_mode_m = sysfs_open_input_dev_node(g_input_dev_num_m,
			SYSFS_NODE_NAME_BMM_OP_MODE, O_WRONLY);
	g_fd_value_m = sysfs_open_input_dev_node(g_input_dev_num_m,
			SYSFS_NODE_NAME_BMM_VALUE, O_RDONLY);

	PINFO("g_fd_value_m: %d g_fd_op_mode_m: %d",
			g_fd_value_m, g_fd_op_mode_m);

	hw->fd_pollable = 1;
	g_fd_input_ev_m = hw->fd_poll = input_open_ev_fd(g_input_dev_num_m);

	#if 0
	sprintf(path, "%s/input%d/%s",
			SYSFS_PATH_INPUT_DEV, g_input_dev_num_m, "place");
	err = sysfs_read_int(path, &place);
	if (!err && (HW_PLACE_UNDEFINED != place)) {
		PINFO("place of mag in driver: %d", place);
		/* assign -1 to g_place_m to disble further remapping */
		g_place_m = -1;
	} else {
		err = 0;
	}
	#endif

	hw_init_m_settings(hw);

	return err;
}

static int hw_mag_set_fifo_enable(BS_U8 enable)
{
	int err = 0;

#ifdef __HW_2ND_MAG_INTF_CONFIG__
	char path[64] = "";
	int fifo_data_sel = 0;
	
	PDEBUG("mag fifo enable: %d", enable);

	sprintf(path, "%s/input%d/%s",
			SYSFS_PATH_INPUT_DEV, g_input_dev_num_m, SYSFS_NODE_NAME_FIFO_DATA_SEL);

	sysfs_read_int(path,&fifo_data_sel);/*get current fifo_data_sel*/

	sprintf(path, "%s/input%d/%s",
			SYSFS_PATH_INPUT_DEV, g_input_dev_num_m, SYSFS_NODE_NAME_FIFO_DATA_SEL);
	
	if (enable)
	{
		enable = fifo_data_sel | (enable << SENSOR_HW_TYPE_M);
		err = sysfs_write_int(path, enable);
		PINFO("Enable MAG fifo out, write fifo_data_sel:%d, the old one:%d",enable, fifo_data_sel);
	} else {
		enable = fifo_data_sel & ~(1 << SENSOR_HW_TYPE_M);
		err = sysfs_write_int(path, enable);
		PINFO("Disable MAG fifo out, write fifo_data_sel:%d, the old one:%d",enable, fifo_data_sel);
	}
#else
		PDEBUG("No need to use mag fifo enable: %d", enable);
#endif
	return err;
}

static int hw_enable_m(struct sensor_hw *hw, int enable)
{
	int err = 0;

	if (enable) {
#ifdef __HW_2ND_MAG_INTF_CONFIG__
		err += hw_mag_set_opmode(HW_M_OMMODE_NORMAL);
#else
		err += hw_mag_set_opmode(HW_M_OMMODE_SLEEP);
#endif
		err += hw_mag_set_fifo_enable(MAG_FIFO_ENABLE);
		//eusleep(1000);
		hw_init_m_settings(hw);
		PINFO("======enable mag enable:%d", enable);
	}
	else {
		err += hw_mag_set_fifo_enable(MAG_FIFO_DISABLE);
		err += hw_mag_set_opmode(HW_M_OMMODE_SUSPEND);
		PINFO("======disable mag enable:%d", enable);
	}

#ifdef HW_M_USE_INPUT_EVENT
		err += hw_mag_set_enable_input_ev(enable);
#endif
	return err;
}


static int hw_restore_cfg_m(struct sensor_hw *hw)
{
	int err = 0;

#ifndef __HW_2ND_MAG_INTF_CONFIG__
	struct bmm_cfg *data = (struct bmm_cfg *)hw->private_data;
	char path[128] = "";

	sprintf(path, "%s/input%d/%s",
			SYSFS_PATH_INPUT_DEV, g_input_dev_num_m, SYSFS_NODE_NAME_BMM_REPT_XY);
#ifdef L9100_COMMON
	err = sysfs_write_int(path, 50);
#else
	err = sysfs_write_int(path, data->rept_xy);
#endif

	sprintf(path, "%s/input%d/%s",
			SYSFS_PATH_INPUT_DEV, g_input_dev_num_m, SYSFS_NODE_NAME_BMM_REPT_Z);
	err |= sysfs_write_int(path, data->rept_z);

	eusleep(2000);
	hw_mag_set_opmode(HW_M_OMMODE_FORCED);
	/* 10ms is enough for current rept settings, a little longer make it safe */
	eusleep(18000);

#else

	UNUSED_PARAM(hw);

#endif
	return err;
}


struct sensor_hw_m g_hw_m = {
	hw: {
			name: DEV_NAME_M,
			type: SENSOR_HW_TYPE_M,
			init:hw_init_m,
			enable:hw_enable_m,
			restore_cfg:hw_restore_cfg_m,
			set_delay:hw_mag_set_delay,
			get_data_nb:hw_mag_read_xyzdata,
			get_data:hw_mag_read_xyzdata_input_ev
		},
};


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
 * @file         hw_cntl_g.c
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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <linux/input.h>

#define LOG_TAG_MODULE "<hw_cntl_g>"
#include "sensord.h"

#define HW_PLACE_UNDEFINED (-1)

int g_input_dev_num_g = -1;

static int g_fd_value_g = -1;

static int g_fd_input_ev_g = -1;

int g_place_g = HW_INFO_DFT_PLACE_G;
extern struct axis_remap axis_remap_tab_g[8];



enum GYRO_FIFO_DATA_EN_T {
	GYRO_FIFO_DISABLE = 0,
	GYRO_FIFO_ENABLE
};


static const struct value_map map_g_range[HW_G_RANGE_MAX] = {
	{HW_G_RANGE_2000, 0},
	{HW_G_RANGE_1000, 1},
	{HW_G_RANGE_500, 2},
	{HW_G_RANGE_250, 3},
	{HW_G_RANGE_125, 4}
};

static const struct value_map map_g_bw[HW_G_BW_MAX] = {
	{SENSOR_DEV_GYRO_ODR_25HZ, 0x06},
	{SENSOR_DEV_GYRO_ODR_50HZ, 0x07},
	{SENSOR_DEV_GYRO_ODR_100HZ, 0x08},
	{SENSOR_DEV_GYRO_ODR_200HZ, 0x09},
	{SENSOR_DEV_GYRO_ODR_400HZ, 0x0a}
};

static const char *driver_names_tbl[] = {
	"bmi160",
	NULL
};

static int hw_gyro_read_xyzdata_input_ev(void *data)
{
	struct input_event ev;
	int sync = 0;
	int err = 0;
	sensor_data_ival_t *val = (sensor_data_ival_t *)data;

	while (!sync) {
		err = read(g_fd_input_ev_g, &ev, sizeof(ev));
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

	if (g_place_g >= 0) {
		hw_remap_sensor_data(val, axis_remap_tab_g + g_place_g);
	}

	return err;
}


static int hw_gyro_read_xyzdata(void *data)
{
	int err = 0;
	int tmp;
	sensor_data_ival_t *val = (sensor_data_ival_t *)data;
	char buf[64] = "";

	val->x = 0;
	val->y = 0;
	val->z = 0;

	if (-1 != g_fd_value_g) {
		lseek(g_fd_value_g, 0, SEEK_SET);
		tmp = read(g_fd_value_g, buf, sizeof(buf) - 1);
		if (0 < tmp) {
			buf[tmp] = 0;
			tmp = sscanf(buf, "%11d %11d %11d",
					(&val->x), (&val->y), (&val->z));
			if (3 != tmp) {
				err = -EINVAL;
			}
		} else {
			PERR("error reading from acc");
		}
	}

	if (g_place_g >= 0) {
		hw_remap_sensor_data(val, axis_remap_tab_g + g_place_g);
	}

	PDEBUG("[gyro] x: %d y: %d z: %d", val->x, val->y, val->z);

	return err;
}

static void hw_set_gyro_fast_calib_offset(void)
{
#ifdef HW_G_OFFSET_USE_FS
	int fd_fast_calib_g;

	int offset_filt_x;
	int offset_filt_y;
	int offset_filt_z;

	char *filename;
	int tmp;

	char path[128] = "";
	char buf[64] = "";

	filename = SENSOR_CFG_FILE_FAST_CALIB_G;
	fd_fast_calib_g = open(filename, O_RDONLY);
	if (-1 != fd_fast_calib_g) {
		tmp = read(fd_fast_calib_g, buf, ARRAY_SIZE(buf) - 1);
		close(fd_fast_calib_g);
		if (tmp > 0) {
			tmp = sscanf(buf, "%11d,%11d,%11d",
					&offset_filt_x,
					&offset_filt_y,
					&offset_filt_z);
		} else {
			PERR("error read from file: %s", filename);
			return;
		}

		if (3 != tmp) {
			PWARN("invalid format in file: %s", filename);
			return;
		} else {
			PINFO("offset_g: %d %d %d",
					offset_filt_x,
					offset_filt_y,
					offset_filt_z);
		}
	} else {
		PERR("error openning file: %s", filename);
		close(fd_fast_calib_g);
		return;
	}


	tmp = 0;
	sprintf(path, "%s/input%d/%s",
			SYSFS_PATH_INPUT_DEV, g_input_dev_num_g,
			SYSFS_NODE_NAME_GYRO_OFFSET_FILT_X);
	tmp |= sysfs_write_int(path, offset_filt_x) ? (1<<0) : 0;

	sprintf(path, "%s/input%d/%s",
			SYSFS_PATH_INPUT_DEV, g_input_dev_num_g,
			SYSFS_NODE_NAME_GYRO_OFFSET_FILT_Y);
	tmp |= sysfs_write_int(path, offset_filt_y) ? (1<<1) : 0;

	sprintf(path, "%s/input%d/%s",
			SYSFS_PATH_INPUT_DEV, g_input_dev_num_g,
			SYSFS_NODE_NAME_GYRO_OFFSET_FILT_Z);
	tmp |= sysfs_write_int(path, offset_filt_z) ? (1<<2) : 0;

	if (0 == tmp) {
		PINFO("fast_calib_g set successfully");
	} else {
		PERR("error setting gyro fast calib offset: %#x", tmp);
	}
#endif
}


int hw_gyro_set_opmode(BS_U8 mode)
{
	int err = 0;
	char path[64] = "";

	PDEBUG("gyro op_mode: %d", mode);

	sprintf(path, "%s/input%d/%s",
			SYSFS_PATH_INPUT_DEV, g_input_dev_num_g, SYSFS_NODE_NAME_BMG_OPMODE);

	err = sysfs_write_int(path, mode);

	return err;
}

static int hw_gyro_set_fifo_enable(BS_U8 enable)
{
	int err = 0;
	char path[64] = "";
	int fifo_data_sel = 0;

	sprintf(path, "%s/input%d/%s",
			SYSFS_PATH_INPUT_DEV, g_input_dev_num_g, SYSFS_NODE_NAME_FIFO_DATA_SEL);
	
	sysfs_read_int(path,&fifo_data_sel);/*get current fifo_data_sel*/
	sprintf(path, "%s/input%d/%s",
			SYSFS_PATH_INPUT_DEV, g_input_dev_num_g, SYSFS_NODE_NAME_FIFO_DATA_SEL);
	if (enable)
	{
		enable = fifo_data_sel | (enable << SENSOR_HW_TYPE_G);
		err = sysfs_write_int(path, enable);
		PDEBUG("Enable GYRO fifo out, write fifo_data_sel:%d, the old one:%d",enable, fifo_data_sel);
	} else {
		enable = fifo_data_sel & ~(1 << SENSOR_HW_TYPE_G);
		err = sysfs_write_int(path, enable);
		PDEBUG("Disable GYRO fifo out, write fifo_data_sel:%d, the old one:%d",enable, fifo_data_sel);
	}

	return err;
}


static int hw_gyro_set_delay(struct sensor_hw *hw, BS_S32 delay)
{
	int err = 0;
	char path[128] = "";

	PWARN("gyro delay: %d", delay);

	sprintf(path, "%s/input%d/%s",
			SYSFS_PATH_INPUT_DEV,
			g_input_dev_num_g,
			SYSFS_NODE_NAME_BMG_DELAY);

	err = sysfs_write_int(path, delay);
	if (!err) {
		hw->delay = delay;
	}

	return err;
}


static int hw_gyro_set_bw(struct sensor_hw_g *hw, uint32_t bw)
{
	int err = 0;
	char path[64] = "";

	PDEBUG("gyro set bw: %d", bw);
	sprintf(path, "%s/input%d/%s",
			SYSFS_PATH_INPUT_DEV, g_input_dev_num_g, SYSFS_NODE_NAME_BMG_BW);

	err = sysfs_write_int(path, bw);
	if (!err) {
			hw->bw = bw;
	} else {
			PWARN("invalid bw");
			err = -EINVAL;
	}

	return err;
}


static int hw_gyro_set_range(struct sensor_hw_g *hw, uint32_t range)
{
	int err = 0;
	char path[64] = "";
	int i;
	int tmp;

	sprintf(path, "%s/input%d/%s",
			SYSFS_PATH_INPUT_DEV, g_input_dev_num_g, SYSFS_NODE_NAME_BMG_RANGE);

	for (i = 0; i < HW_G_RANGE_MAX; i++) {
		if (map_g_range[i].l == (int)range) {
			tmp = map_g_range[i].r;
			break;
		}
	}

	if (i < HW_G_RANGE_MAX) {
		err = sysfs_write_int(path, tmp);
		if (!err) {
			hw->range = range;
		}
	} else {
		PWARN("invalid range");
		err = -EINVAL;
	}

	return err;
}


static void hw_init_g_settings(struct sensor_hw *hw)
{
	/* currently we use suspend mode instead of deep suspend mode,
	 * so the settings can be done only once in init stage
	 */
	struct sensor_hw_g *hw_g = CONTAINER_OF(hw, struct sensor_hw_g, hw);
	hw_gyro_set_opmode(HW_G_OPMODE_SUSPEND);
	//eusleep(HW_INFO_DELAY_WAKE_UP_G);
	hw_gyro_set_bw(hw_g, SENSOR_DEV_GYRO_ODR_100HZ);
	hw_gyro_set_range(hw_g, HW_G_RANGE_2000);
}


#ifdef HW_G_USE_INPUT_EVENT
static int hw_gyro_set_enable_inputev(BS_U8 enable)
{
	int err = 0;
	char path[128] = "";

	PDEBUG("gyro enable: %d", enable);

	sprintf(path, "%s/input%d/%s",
			SYSFS_PATH_INPUT_DEV, g_input_dev_num_g, SYSFS_NODE_NAME_BMG_ENABLE);

	enable = !!enable;

	err = sysfs_write_int(path, enable);

	return err;
}
#endif


static int hw_init_g(struct sensor_hw *hw)
{
	int err = 0;
	char path[128] = "";
	int place;
	int i = 0;

	g_input_dev_num_g = -1;
	while(driver_names_tbl[i])
	{
		g_input_dev_num_g = sysfs_get_input_dev_num(driver_names_tbl[i]);
		i ++;
		if (g_input_dev_num_g >= 0)
		{
			break;
		}
	}
	PINFO("g_input_dev_num_g: %d", g_input_dev_num_g);

	g_fd_value_g = sysfs_open_input_dev_node(g_input_dev_num_g,
			SYSFS_NODE_NAME_BMG_VALUE, O_RDONLY);

	PINFO("g_fd_value_g: %d", g_fd_value_g);

	hw->fd_pollable = 1;
	g_fd_input_ev_g = hw->fd_poll = input_open_ev_fd(g_input_dev_num_g);
	hw_set_gyro_fast_calib_offset();

	sprintf(path, "%s/input%d/%s",
			SYSFS_PATH_INPUT_DEV, g_input_dev_num_g, "place");
	if (-1 != util_fs_is_file_exist(path))
	{
		err = sysfs_read_int(path, &place);
		if (!err && (HW_PLACE_UNDEFINED != place)) {
			PINFO("place of gyro in driver: %d", place);
			/* assign -1 to g_place_g to disble further remapping */
			g_place_g = -1;
		} else {
			err = 0;
		}
	}

	hw_init_g_settings(hw);

	return err;
}


int hw_enable_g(struct sensor_hw *hw, int enable)
{
	int err = 0;
	UNUSED_PARAM(hw);
	
	PDEBUG("\t==============enable gyro:%d\n", enable);
	if (enable) {
		err = hw_gyro_set_opmode(HW_G_OPMODE_NORMAL);
		eusleep(10);
		err += hw_gyro_set_fifo_enable(GYRO_FIFO_ENABLE);
		eusleep(10);
	} else {
		err += hw_gyro_set_fifo_enable(GYRO_FIFO_DISABLE);
		eusleep(10);
		err += hw_gyro_set_opmode(HW_G_OPMODE_SUSPEND);
		eusleep(10);
	}

#ifdef HW_G_USE_INPUT_EVENT
		err += hw_gyro_set_enable_inputev(enable);
#endif
	return err;
}


static int hw_restore_cfg_g(struct sensor_hw *hw)
{
	int err = 0;
	/* TODO: currently BW is set to 32, hence this delay */
	int delay_drdy = 10000;
	/* if we use deep suspend mode, then this macro should be defined */
#ifdef HW_INFO_G_CFG_LOST_IN_SUSPEND
	struct sensor_hw_g *hw_g = CONTAINER_OF(hw, struct sensor_hw_g, hw);

	err = hw_g->set_bw(hw_g, hw_g->bw);
	err |= hw_g->set_range(hw_g, hw_g->range);
#endif
	UNUSED_PARAM(hw);
	eusleep(delay_drdy);

	return err;
}


struct sensor_hw_g g_hw_g = {
	hw: {
			name: DEV_NAME_G,
			type: SENSOR_HW_TYPE_G,
			init:hw_init_g,
			enable:hw_enable_g,
			restore_cfg:hw_restore_cfg_g,
			set_delay:hw_gyro_set_delay,
			get_data_nb:hw_gyro_read_xyzdata,
			get_data:hw_gyro_read_xyzdata_input_ev
		},

	set_bw:hw_gyro_set_bw,
	set_range:hw_gyro_set_range,
};


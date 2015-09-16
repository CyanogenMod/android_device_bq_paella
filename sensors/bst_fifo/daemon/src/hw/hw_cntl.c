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
 * @file         hw_cntl.c
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
#include <poll.h>

#include <linux/input.h>

#define LOG_TAG_MODULE "<hw_cntl>"
#include "sensord.h"

extern struct sensor_hw_a g_hw_a;
extern struct sensor_hw_m g_hw_m;
extern struct sensor_hw_g g_hw_g;
static int g_fd_value_bmi_fifo;

extern int g_place_a;	/* placement of acc sensor */
extern int g_place_m;	/* placement of mag sensor */
extern int g_place_g;	/* placement of mag sensor */

extern struct axis_remap axis_remap_tab_a[8];
extern struct axis_remap axis_remap_tab_g[8];
extern struct axis_remap axis_remap_tab_m[8];

extern int g_input_dev_num_a;
extern int g_input_dev_num_g;
extern int g_input_dev_num_m;

static int g_fd_bmi_input_num;

uint16_t g_frame_to_read = 0;

static const struct sensor_hw *g_list_hw[] = {
#if SPT_SENSOR_HW_A
	&g_hw_a.hw,
#endif

#if SPT_SENSOR_HW_G
	&g_hw_g.hw,
#endif

#if SPT_SENSOR_HW_M
	&g_hw_m.hw,
#endif

	/* use NULL as a mark of end */
	NULL,
};


void hw_remap_sensor_data(sensor_data_ival_t *data, axis_remap_t *remap)
{
	sensor_data_ival_t tmp;
	int t;

	tmp.v[0] = data->v[0];
	tmp.v[1] = data->v[1];
	tmp.v[2] = data->v[2];

	data->x = tmp.v[remap->rx];

	t = tmp.v[0];
	tmp.v[0] = tmp.v[1];
	tmp.v[1] = t;
	data->y = tmp.v[remap->ry];

	t = tmp.v[0];
	tmp.v[0] = tmp.v[2];
	tmp.v[2] = t;
	data->z = tmp.v[remap->rz];

	if (remap->sx) {
		data->x = 0 - data->x;
	}

	if (remap->sy) {
		data->y = 0 - data->y;
	}

	if (remap->sz) {
		data->z = 0 - data->z;
	}
}


struct sensor_hw * hw_get_hw_by_id(int hw_id)
{
	struct sensor_hw *hw = NULL;
	int i;

	i = 0;
	while (NULL != (hw = (struct sensor_hw *)g_list_hw[i++])) {
		if ((hw->type == hw_id) && hw->available) {
			break;
		}
	}

	if (NULL == hw) {
		PWARN("Invalid hw: %d", hw_id);
	}

	return hw;
}


int hw_ref_up(int hw_id)
{
	int err = 0;
	struct sensor_hw *hw = NULL;

	hw = hw_get_hw_by_id(hw_id);
	if (NULL == hw) {
		return -ENODEV;
	}
	
	pthread_mutex_lock(&hw->lock_ref);
	hw->ref += 1;
	if (1 == hw->ref) {
		if (NULL != hw->enable) {
			
			err = hw->enable(hw, 1);
			PINFO("==enable hw: %s, err:%d",
						hw->name, err);
			/* generally it takes some time to power up a device, but
			 * the wake up time is really hw specific, so
			 * it's assumed the delay is implemented in the enable()
			 * call back function
			 * */
			if (err) {
				PERR("error enable hw: %s",
						hw->name);
			} else {
				hw->enabled = 1;

				if (NULL != hw->restore_cfg) {
					err = hw->restore_cfg(hw);
					if (err) {
						PWARN("error restoring hw cfg of %s", hw->name);
					}
				}
			}
		}
	}

	PINFO("ref count for hw %s: %d",
			hw->name, hw->ref);
	pthread_mutex_unlock(&hw->lock_ref);

	return err;
}


int hw_ref_down(int hw_id)
{
	int err = 0;
	struct sensor_hw *hw = NULL;

	hw = hw_get_hw_by_id(hw_id);
	if (NULL == hw) {
		return -ENODEV;
	}

	pthread_mutex_lock(&hw->lock_ref);
	if (1 == hw->ref) {
		if (NULL != hw->enable) {
			err = hw->enable(hw, 0);
			if (err) {
				PWARN("error disable hw: %s",
						hw->name);
			} else {
				hw->enabled = 0;
			}
		}
	}

	if (hw->ref > 0) {
		hw->ref -= 1;
	}

	PINFO("ref count for hw %s: %d",
			hw->name, hw->ref);
	pthread_mutex_unlock(&hw->lock_ref);

	return err;
}


int hw_cntl_init()
{
	int err = 0;
	int i = 0;
	struct sensor_hw *hw;

	i = 0;
	while (NULL != (hw = (struct sensor_hw *)g_list_hw[i++])) {
		hw->available = 0;
		hw->ref = 0;
		pthread_mutex_init(&hw->lock_ref, NULL);
		hw->drdy = 0;
		hw->fd_poll = -1;
		hw->ts_last_update = 0;

		PINFO("init hw: %s, type: %d", hw->name, hw->type);
		err = hw->init(hw);
		if (err) {
			PWARN("error init hw: %s %d", hw->name, err);
		} else {
			hw->available = 1;

			err = hw->enable(hw, 0);
			if (err) {
				PWARN("error disable hw: %s %d", hw->name, err);
			}
		}

	}

	if (g_input_dev_num_a >= g_input_dev_num_g)
		g_fd_bmi_input_num = g_input_dev_num_a;
	else
		g_fd_bmi_input_num = g_input_dev_num_g;
/*NOT 3rd mag*/
	if ((g_fd_bmi_input_num<0) && (g_input_dev_num_m >0))
		g_fd_bmi_input_num = g_input_dev_num_m;
	

	return 0;
}


uint32_t hw_peek_data_status(uint32_t bitmap_hw_ids)
{
	uint32_t ret = 0;
	int err = 0;
	struct pollfd fds[SENSOR_HW_TYPE_MAX];
	int idx[SENSOR_HW_TYPE_MAX];
	int i;
	int count = 0;

	struct sensor_hw *hw;

	for (i = 0; i < SENSOR_HW_TYPE_MAX; i++) {
		if (!(bitmap_hw_ids & (1 << i))) {
			continue;
		}

		hw = hw_get_hw_by_id(i);
		if (NULL != hw) {
			if (!hw->fd_pollable) {
				ret |= (!!(hw->get_drdy_status(hw))) << i;
			} else {
				fds[count].fd = hw->fd_poll;
				idx[count] = i;
				fds[count].events = POLLIN;
				fds[count].revents = 0;

				count++;
			}
		}
	}

	if (count > 0) {
		err = poll(fds, count, 0);

		if (err >= 0) {
			for (i = 0; i < count; i++) {
				if (fds[i].revents & POLLIN) {
					ret |= (1 << idx[i]);
				}
			}
		} else {
			PERR("error during polling");
		}
	}


	return ret;
}


void hw_cntl_dump()
{
	int i;
	struct sensor_hw *hw;

	PINFO("dump of h/w info...");

	i = 0;
	while (NULL != (hw = (struct sensor_hw *)g_list_hw[i++])) {
		PINFO("name: %s", hw->name);
		PINFO("addr: %p", hw);
		PINFO("ref: %d", hw->ref);
	}
}

static __inline int32_t hw_get_one_data(int32_t *p_data, char *input)
{
	int i = 0;
	char buf[32];
	char *p_buf = buf;
	char *ptr = input;
	int32_t   value;

	/* search for the first string */
	while(((*ptr < '0') || (*ptr > '9')) && (*ptr != '-'))
	{
		if ((*ptr == 0) || (*ptr == '\n'))
		{
			return -ERANGE;
		}
		ptr ++;
		i ++;
		/* can not find data after long string */
		if (i > 10)
		{
			PERR("failed at parsing data!");
			return -ENOENT;
		}
	}

	while (((*ptr >= '0') && (*ptr <= '9')) || (*ptr == '-'))
	{
		if ((*ptr == 0) || (*ptr == '\n'))
		{
			return -ERANGE;
		}
		*p_buf++ = *ptr++;
	}
	*p_buf = 0;
	value = atoi(buf);
	if (NULL != p_data)
	{
		*p_data = value;
	}

	return (int)(ptr - input);
}


int hw_get_one_frame_bmi160(char *p_data, char *p_current_sensor_flag,
		int32_t *p_x, int32_t *p_y, int32_t *p_z, uint32_t *p_sensor_ts)
{
	int ret = 0;
	char *ptr = NULL;
	/*sensor head*/
	ptr = strstr(p_data, p_current_sensor_flag);
	if (ptr == NULL)
		return -1;

	ret = hw_get_one_data(p_x, ptr);
	if (ret < 0)
	{
		PERR("\t\tfailed");
		return ret;
	}
	ptr += ret;
	ret = hw_get_one_data(p_y, ptr);
	if (ret < 0)
	{
		PERR("\t\tfailed");
		return ret;
	}
	ptr += ret;
	ret = hw_get_one_data(p_z, ptr);
	if (ret < 0)
	{
		PERR("\t\tfailed");
		return ret;
	}
	ptr += ret;

	ret = hw_get_one_data((int32_t *)p_sensor_ts, ptr);
	if (ret < 0)
	{
		PERR("\t\tfailed");
		return ret;
	}
	ptr += ret;
	return (int)(ptr - p_data);


}

/*!
 * @brief This function gets all frames with xyz value from the input string 'p_data',
 * and push to sensor fifo stack
 *
 * @param[i] hw            instance of sensor_hw_t
 * @param[i] p_data      input string of sensor data which is read from driver
 * @param[i] count        count of frames to be analysised
 *
 * @return frame count
 */
void hw_get_all_frames_bmi160(struct sensor_hw *hw, char *p_data, int len,
				char *p_sensor_data_flag, sensordata_t *p_val, uint8_t *frame_cnt)
{
	int ret = 0;
	char *ptr = p_data;
	int buf_bytecount = 0;
	uint8_t frame_count = 0;
	if (hw->enabled == FALSE)
		return ;
	char sensor_flag;
	if (strcmp(p_sensor_data_flag, "acc") == 0)
		sensor_flag = 'a';
	if (strcmp(p_sensor_data_flag, "gyro") == 0)
		sensor_flag = 'g';
	if (strcmp(p_sensor_data_flag, "mag") == 0)
		sensor_flag = 'm';

	sensor_data_ival_t remap_ival;
	
	memset(&remap_ival, 0, sizeof(sensor_data_ival_t));
	while(buf_bytecount <= len)
	{
		ret = hw_get_one_frame_bmi160(ptr, p_sensor_data_flag, &p_val->data.x, &p_val->data.y,
			&p_val->data.z, &p_val->time_stamp);
		if (ret > 0)
		{
			ptr += ret;
		}
		else
		{
			break;
		}

		buf_bytecount += ret;
		if (sensor_flag == 'g')
		{
			remap_ival.x = p_val->data.x;
			remap_ival.y = p_val->data.y;
			remap_ival.z = p_val->data.z;
		}
		else
		{
			remap_ival.x = p_val->data.x;
			remap_ival.y = p_val->data.y;
			remap_ival.z = p_val->data.z;
		}

		switch (sensor_flag)
		{
			case 'a':
				if (g_place_a >= 0) {
						hw_remap_sensor_data(&remap_ival, axis_remap_tab_a + g_place_a);
				}
				break;

			case 'g':
				if (g_place_g >= 0) {
						hw_remap_sensor_data(&remap_ival, axis_remap_tab_g + g_place_g);
				}
				break;

			case 'm':
				if (g_place_m >= 0) {
						hw_remap_sensor_data(&remap_ival, axis_remap_tab_m + g_place_m);
				}
				
				break;

		}

		p_val->data.x = remap_ival.x;
		p_val->data.y = remap_ival.y;
		p_val->data.z = remap_ival.z;

		p_val++;
		frame_count++;
		
	}

	*frame_cnt = frame_count;
	return ;
}


/*!
 * @brief This function is to load FIFO data into fifo stack
 *
 * @param[i] hw          instance of senosr_hw structure
 *
 * @return zero success, none-zero failed to write mode to driver
 *
 */
int hw_load_fifo_bmi160(uint32_t diff_ap_ts,uint32_t expected_interval,
	uint8_t bytes_pre_frame, sensordata_t *p_acc_val, sensordata_t *p_gyro_val,
			sensordata_t *p_mag_val, uint8_t *p_frame_cnt)
{
	int len = 0;
	int ret = 0;
	uint32_t bytescount = 0;
	char temp_buf[HW_CNTL_FIFO_SIZE]="";
	int err = 0;
	char path[128] = "";

	bytescount = ((diff_ap_ts+ expected_interval/2)/expected_interval)*bytes_pre_frame + 4;
	if (bytescount > 100) {
		PERR("bytescount:%d", bytescount);
		bytescount = 100;
	}
	
	sprintf(path, "%s/input%d/%s",
			SYSFS_PATH_INPUT_DEV, g_fd_bmi_input_num, SYSFS_NODE_NAME_FIFO_BYTESCOUNT);

	err = sysfs_write_int(path, bytescount);
	
	if(err)
		PERR("failed to write fifo_bytecount:%d ", bytescount);


	g_fd_value_bmi_fifo = sysfs_open_input_dev_node(g_fd_bmi_input_num,
			SYSFS_NODE_NAME_BMI_FIFO, O_RDONLY);
	
	/*read driver all mixed data */
	len = read(g_fd_value_bmi_fifo, temp_buf, HW_CNTL_FIFO_SIZE-1);
	if (len < 0)
	{
		PERR("read fifo failed:%d, fd:%d", len, g_fd_value_bmi_fifo);
		close(g_fd_value_bmi_fifo);
		return -EACCES;
	}
	temp_buf[len]='\n';
	close(g_fd_value_bmi_fifo);

	/* get acc frame if acc is enabled */
	#ifdef __HW_2ND_MAG_INTF_CONFIG__
	hw_get_all_frames_bmi160(&g_hw_m.hw, temp_buf, len, "mag", p_mag_val, &p_frame_cnt[2]);
	#else
	UNUSED_PARAM(p_mag_val);
	#endif
	hw_get_all_frames_bmi160(&g_hw_a.hw, temp_buf, len, "acc", p_acc_val, &p_frame_cnt[0]);

	hw_get_all_frames_bmi160(&g_hw_g.hw, temp_buf, len, "gyro", p_gyro_val, &p_frame_cnt[1]);

	return ret;
}


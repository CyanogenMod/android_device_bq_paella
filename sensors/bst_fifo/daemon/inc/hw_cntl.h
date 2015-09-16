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
 * @file         hw_cntl.h
 * @date         "Wed Dec 31 15:33:20 2014 +0800"
 * @commit       "7b2e44c"
 *
 * @brief
 *
 * @detail
 *
 */

#ifndef __HW_CNTL_H
#define __HW_CNTL_H
#include <pthread.h>

#include "options.h"
#include "sensor_priv.h"
#include "sensor_data_type.h"
#include "configure_hw.h"
#include "sensor_hw.h"
#include "hw_def.h"
#include "algo_if.h"


#define DELAY_TIME_UI_PROXIMITY (60000)	/* max delay response time of user interaction in ms */

/* this delay actually depends on the
 * h/w performance, so it's per-sensor-specific
 * but generally 10ms is enough
 */

#define DELAY_TIME_HW_WAKE_UP (10)

/* hardware fifo buffer size */
#define HW_CNTL_FIFO_SIZE                     65536


int hw_cntl_init();
void hw_remap_sensor_data(sensor_data_ival_t *data, axis_remap_t *remap);
struct sensor_hw * hw_get_hw_by_id(int hw_id);
int hw_ref_up(int);
int hw_ref_down(int);
uint32_t hw_peek_data_status(uint32_t bitmap_hw_ids);
void hw_cntl_dump();
int hw_get_bmi_data_register(sensor_data_ival_t *acc_val, sensor_data_ival_t *gyro_val);
int hw_get_bmm_data_register(sensor_data_ival_t *mag_val);
int hw_load_fifo_bmi160(uint32_t diff_ap_ts,uint32_t expected_interval,
	uint8_t bytes_pre_frame, sensordata_t *p_acc_val, sensordata_t *p_gyro_val,
			sensordata_t *p_mag_val, uint8_t *p_frame_cnt);

extern int hw_get_step_counter_value(uint64_t *value);
extern int hw_get_step_detector_status(uint8_t *std_st);
extern int hw_set_step_detector_enable(BS_U8 std_en);



#endif

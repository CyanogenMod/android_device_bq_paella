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
 * @file         hw_if_g.h
 * @date         "Wed Dec 31 15:33:20 2014 +0800"
 * @commit       "7b2e44c"
 *
 * @brief
 *
 * @detail
 *
 */


#ifndef __HW_IF_G_H
#define __HW_IF_G_H

#define DEV_NAME_G "bmg160"
#define HW_G_OFFSET_USE_FS


#define SYSFS_NODE_NAME_BMG_ENABLE "enable"
#define SYSFS_NODE_NAME_BMG_VALUE "gyro_value"
#define SYSFS_NODE_NAME_BMG_BW "gyro_odr"
#define SYSFS_NODE_NAME_BMG_DELAY "delay"
#define SYSFS_NODE_NAME_BMG_RANGE "gyro_range"
#define SYSFS_NODE_NAME_BMG_OPMODE "gyro_op_mode"
#define SYSFS_NODE_NAME_FIFO_DATA_SEL "fifo_data_sel"


#define SYSFS_NODE_NAME_GYRO_OFFSET_FILT_X "gyro_offset_x"
#define SYSFS_NODE_NAME_GYRO_OFFSET_FILT_Y "gyro_offset_y"
#define SYSFS_NODE_NAME_GYRO_OFFSET_FILT_Z "gyro_offset_z"


enum {
	HW_G_BW_INVALID = -1,
	HW_G_BW_32,
	HW_G_BW_64,
	HW_G_BW_12,
	HW_G_BW_23,
	HW_G_BW_47,
	HW_G_BW_116,
	HW_G_BW_230,
	HW_G_BW_523,
	HW_G_BW_MAX
};

#define HW_G_OPMODE_NORMAL 0
#define HW_G_OPMODE_SUSPEND 2
#endif

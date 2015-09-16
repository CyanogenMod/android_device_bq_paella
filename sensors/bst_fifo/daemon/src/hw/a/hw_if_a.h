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
 * @file         hw_if_a.h
 * @date         "Fri Jan 30 18:07:49 2015 +0800"
 * @commit       "6732061"
 *
 * @brief
 *
 * @detail
 *
 */

#ifndef __HW_IF_A_H
#define __HW_IF_A_H
#define DEV_NAME_A "bmi160"

#define HW_A_DATA_FULLRANGE
#define HW_A_OFFSET_USE_FS

#define HW_A_OPMODE_NORMAL 0
#define HW_A_OPMODE_SUSPEND 2

#define SYSFS_NODE_NAME_BMI_VALUE "bmi_value"

#define SYSFS_NODE_NAME_BMI_FIFO "fifo_data_frame"


#define SYSFS_NODE_NAME_BMA_VALUE "acc_value"
#define SYSFS_NODE_NAME_BMA_UPDATE "update"
#define SYSFS_NODE_NAME_BMA_ENABLE "enable"
#define SYSFS_NODE_NAME_BMA_GRANGE "acc_range"
#define SYSFS_NODE_NAME_BMA_BW "acc_odr"
#define SYSFS_NODE_NAME_BMA_MODE "acc_op_mode"
#define SYSFS_NODE_NAME_FIFO_DATA_SEL "fifo_data_sel"
#define SYSFS_NODE_NAME_FIFO_BYTESCOUNT "fifo_bytecount"
#define SYSFS_NODE_NAME_ENABLE "enable"



/*step counter support*/
#define SYSFS_NODE_NAME_STC_ENABLE "stc_enable"
#define SYSFS_NODE_NAME_STC_MODE "stc_mode"
#define SYSFS_NODE_NAME_STC_VALUE "stc_value"
#define SYSFS_NODE_NAME_STD_STATUS "std_stu"
#define SYSFS_NODE_NAME_STD_EN "std_en"



#define SYSFS_NODE_NAME_BMA_DELAY "delay"
#define SYSFS_NODE_NAME_BMA_OFFSET_FILT_X "acc_offset_x"
#define SYSFS_NODE_NAME_BMA_OFFSET_FILT_Y "acc_offset_y"
#define SYSFS_NODE_NAME_BMA_OFFSET_FILT_Z "acc_offset_z"

#endif

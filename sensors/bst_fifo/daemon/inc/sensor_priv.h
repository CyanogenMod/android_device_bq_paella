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
 * @file         sensor_priv.h
 * @date         "Wed Dec 31 15:33:20 2014 +0800"
 * @commit       "7b2e44c"
 *
 * @brief
 *
 * @detail
 *
 */

#ifndef __SENSOR_PRIV_H
#define __SENSOR_PRIV_H
#include "options.h"
#include "hw_if.h"
#include "hw_info.h"

/* this path must exist and user <system> must have permission to write to it */
#define PATH_DIR_DATA "/data/misc"
#define PATH_DIR_SENSOR_STORAGE "/data/misc/sensor"

#define FIFO_CMD (PATH_DIR_SENSOR_STORAGE "/fifo_cmd")
#define FIFO_DAT (PATH_DIR_SENSOR_STORAGE "/fifo_dat")
#define FIFO_LIST (PATH_DIR_SENSOR_STORAGE "/fifo_list")
#define PROCESS_LANDMARK (PATH_DIR_SENSOR_STORAGE "/.id")

#define SYSFS_PATH_INPUT_DEV "/sys/class/input"
#define MAX_INPUT_DEV_NUM 32

#define SENSOR_CFG_FILE_SYS_AXIS  (PATH_DIR_SENSOR_STORAGE "/sensord_cfg_axis.txt")
#define SENSOR_CFG_FILE_ALGO   (PATH_DIR_SENSOR_STORAGE "/cfg_algo.txt")
#define SENSOR_CFG_FILE_PATH   PATH_DIR_SENSOR_STORAGE
#define SENSOR_CFG_FILE_DATA_LOG_LEVEL  (PATH_DIR_SENSOR_STORAGE "/data_log_level.txt")

#define SENSOR_CFG_FILE_SYS_PROFILE_CALIB_A (PATH_DIR_SENSOR_STORAGE "/profile_calib_a")
#define SENSOR_CFG_FILE_SYS_PROFILE_CALIB_M (PATH_DIR_SENSOR_STORAGE "/profile_calib_m")
#define SENSOR_CFG_FILE_SYS_PROFILE_CALIB_G (PATH_DIR_SENSOR_STORAGE "/profile_calib_g")
#define SENSOR_CFG_FILE_FAST_CALIB_A (PATH_DIR_SENSOR_STORAGE "/fast_calib_a")
#define SENSOR_CFG_FILE_FAST_CALIB_G (PATH_DIR_SENSOR_STORAGE "/fast_calib_g")
#endif

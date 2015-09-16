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
 * @file         hw_if_m.h
 * @date         "Wed Dec 31 15:33:20 2014 +0800"
 * @commit       "7b2e44c"
 *
 * @brief
 *
 * @detail
 *
 */

#ifndef __HW_IF_M_H
#define __HW_IF_M_H
#define BMM_LOWPOWER_REPXY		1
#define BMM_REGULAR_REPXY		4
#define BMM_HIGHACCURACY_REPXY	23
#define BMM_ENHANCED_REPXY	7

#define BMM_LOWPOWER_REPZ		2
#define BMM_REGULAR_REPZ			15
#define BMM_HIGHACCURACY_REPZ	82
#define BMM_ENHANCED_REPZ	26

#define DEV_NAME_M "bmi160_m"

#ifdef __HW_2ND_MAG_INTF_CONFIG__
#define SYSFS_NODE_NAME_BMM_VALUE "mag_value"
#define SYSFS_NODE_NAME_BMM_OP_MODE "mag_op_mode"
#define SYSFS_NODE_NAME_BMM_DELAY "mag_odr"
#define SYSFS_NODE_NAME_FIFO_DATA_SEL "fifo_data_sel"
#else
#define SYSFS_NODE_NAME_BMM_VALUE "value"
#define SYSFS_NODE_NAME_BMM_OP_MODE "op_mode"
#define SYSFS_NODE_NAME_BMM_DELAY "odr"
#endif

#define SYSFS_NODE_NAME_BMM_ENABLE "enable"
#define SYSFS_NODE_NAME_BMM_POWER_MODE "power_mode"
#define SYSFS_NODE_NAME_BMM_REPT_XY "rept_xy"
#define SYSFS_NODE_NAME_BMM_REPT_Z "rept_z"



#define ALGO_M_OPMODE_LOWPOWER_REPXY			BMM_LOWPOWER_REPXY
#define ALGO_M_OPMODE_REGULAR_REPXY 			BMM_REGULAR_REPXY
#define ALGO_M_OPMODE_HIGHACCURACY_REPXY		BMM_HIGHACCURACY_REPXY
#define ALGO_M_OPMODE_ALWAYSON_REPXY			BMM_LOWPOWER_REPXY

#define ALGO_M_OPMODE_LOWPOWER_REPZ			BMM_LOWPOWER_REPZ
#define ALGO_M_OPMODE_REGULAR_REPZ			BMM_REGULAR_REPZ
#define ALGO_M_OPMODE_HIGHACCURACY_REPZ			BMM_HIGHACCURACY_REPZ
#define ALGO_M_OPMODE_ALWAYSON_REPZ			BMM_LOWPOWER_REPZ


#define HW_M_OMMODE_NORMAL 0
#define HW_M_OMMODE_FORCED 1
#define HW_M_OMMODE_SUSPEND 2
#define HW_M_OMMODE_SLEEP 3
#endif

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
 * @file         hw_info.h
 * @date         "Wed Dec 31 15:33:20 2014 +0800"
 * @commit       "7b2e44c"
 *
 * @brief
 *
 * @detail
 *
 */


#ifndef __HW_INFO_H
#define __HW_INFO_H
#include "configure_hw.h"

#if SPT_SENSOR_HW_A
#include "hw_info_a.h"
#endif

#if SPT_SENSOR_HW_M
#include "hw_info_m.h"
#endif

#if SPT_SENSOR_HW_G
#include "hw_info_g.h"
#endif

#if SPT_SENSOR_HW_D
#include "hw_info_d.h"
#endif

#if SPT_SENSOR_HW_L
#include "hw_info_l.h"
#endif

#endif

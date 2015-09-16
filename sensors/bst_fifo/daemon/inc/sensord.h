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
 * @file         sensord.h
 * @date         "Wed Dec 31 15:33:20 2014 +0800"
 * @commit       "7b2e44c"
 *
 * @brief
 *
 * @detail
 *
 */

#ifndef __SENSORD_H
#define __SENSORD_H

#include "version.h"
#include "configure.h"
#include "options.h"

#include "hw_if.h"
#include "hw_info.h"
#include "hw_cntl.h"
#include "sensor_hw.h"

#include "util_misc.h"
#include "util_time.h"
#include "util_sysfs.h"
#include "util_input_dev.h"
#include "trace.h"
#include "bs_log.h"

#include "channel.h"
#include "sensor_provider.h"

#include "sensor_priv.h"

#include "sensor_data_type.h"
#include "sensor_def.h"
#include "sensor_cfg.h"

#include "algo.h"
#include "algo_adapter.h"
#include "algo_if.h"
#include "algo_data_log.h"

#include "event_handler.h"


void dump_ver();
void write_version(int fd);

#endif

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
 * @file         hw_info_a.h
 * @date         "Thu Jan 8 18:20:01 2015 +0800"
 * @commit       "4b0860f"
 *
 * @brief
 *
 * @detail
 *
 */

#ifndef __HW_INFO_A_H
#define __HW_INFO_A_H
#include "hw_def.h"

#ifndef HW_ID_A
#define HW_ID_A HW_ID_A_BMA255
#endif

#ifdef __BMC056__
#define HW_INFO_DFT_PLACE_A 6	/* default layout is P6 */
#elif defined __BMA222E__
#define HW_INFO_DET_PLACE_A 6 	/* default layout is P6 */
#else
#define HW_INFO_DFT_PLACE_A 7	/* default layout is P7 */
#endif
#define HW_INFO_DELAY_WAKE_UP_A 10000 /* in us */

#endif

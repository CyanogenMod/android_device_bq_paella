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
 * @file         hw_info_g.h
 * @date         "Wed Dec 31 15:33:20 2014 +0800"
 * @commit       "7b2e44c"
 *
 * @brief
 *
 * @detail
 *
 */


#ifndef __HW_INFO_G_H
#define __HW_INFO_G_H
#include "hw_def.h"

#ifndef HW_ID_G
#define HW_ID_G HW_ID_G_BMG160
#endif

#ifdef __BMG160__ /* BMG160 */
#define HW_INFO_DFT_PLACE_G 6
#else
#define HW_INFO_DFT_PLACE_G 7
#endif

#define HW_INFO_DELAY_WAKE_UP_G 30000 /* in us */

#endif

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
 * @file         axis_remap_m.c
 * @date         "Fri Jan 30 18:07:49 2015 +0800"
 * @commit       "6732061"
 *
 * @brief
 *
 * @detail
 *
 */

#include "sensord.h"

#if SPT_SENSOR_HW_M

struct axis_remap axis_remap_tab_m[8] = { /* BMM050 */
#if ((defined __BMC056__) || (defined __AMM201__) || (defined __AMM202__)\
	|| (defined __AMM203__) || (defined __AMM204__) || (defined __AMM205__)\
	|| (defined __AMM206__))
	/* rx ry rz sx sy sz */
	{0, 0, 0, 1, 1, 0}, /* P0 */
	{1, 1, 0, 1, 0, 0}, /* P1 */
	{1, 1, 0, 0, 1, 0}, /* P2 */
	{0, 0, 0, 0, 0, 0}, /* P3 */
	{1, 1, 0, 0, 0, 1}, /* P4 */
	{0, 0, 0, 0, 1, 1}, /* P5 */
	{0, 0, 0, 1, 0, 1}, /* P6 */
	{1, 1, 0, 1, 1, 1}, /* P7 */
#elif (defined __BMC050__) || (defined __BMC055__)
	/* rx ry rz sx sy sz */
	{1, 1, 0, 1, 0, 0}, /* P0 */
	{0, 0, 0, 0, 0, 0}, /* P1 */
	{0, 0, 0, 1, 1, 0}, /* P2 */
	{1, 1, 0, 0, 1, 0}, /* P3 */
	{0, 0, 0, 1, 0, 1}, /* P4 */
	{1, 1, 0, 0, 0, 1}, /* P5 */
	{1, 1, 0, 1, 1, 1}, /* P6 */
	{0, 0, 0, 0, 1, 1}, /* P7 */
#elif defined __BMM150__
	/*  rx ry rz sx sy sz */
	{1, 1, 0, 0, 0, 1}, /*  P0 */
	{0, 0, 0, 0, 1, 1}, /*  P1 */
	{0, 0, 0, 1, 0, 1}, /*  P2 */
	{1, 1, 0, 1, 1, 1}, /*  P3 */
	{0, 0, 0, 1, 1, 0}, /*  P4 */
	{1, 1, 0, 1, 0, 0}, /*  P5 */
	{1, 1, 0, 0, 1, 0}, /*  P6 */
	{0, 0, 0, 0, 0, 0}, /*  P7 */
#else	/* use BMM150 matrix as default remap matrix*/
	/*  rx ry rz sx sy sz */
	{1, 1, 0, 0, 0, 1}, /*  P0 */
	{0, 0, 0, 0, 1, 1}, /*  P1 */
	{0, 0, 0, 1, 0, 1}, /*  P2 */
	{1, 1, 0, 1, 1, 1}, /*  P3 */
	{0, 0, 0, 1, 1, 0}, /*  P4 */
	{1, 1, 0, 1, 0, 0}, /*  P5 */
	{1, 1, 0, 0, 1, 0}, /*  P6 */
	{0, 0, 0, 0, 0, 0}, /*  P7 */
#endif
};
#endif

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
 * @file         hw_def.h
 * @date         "Fri Jan 30 18:07:49 2015 +0800"
 * @commit       "6732061"
 *
 * @brief
 *
 * @detail
 *
 */

#ifndef __HW_DEF_H
#define __HW_DEF_H
#include <stdint.h>

#include "sensor_def.h"


typedef uint32_t hw_id_t;

#define HW_ID_PART_POS_MAGIC 24
#define HW_ID_PART_LEN_MAGIC 8

#define HW_ID_PART_POS_VENDOR	20
#define HW_ID_PART_LEN_VENDOR	4

#define HW_ID_PART_POS_PRIV	16
#define HW_ID_PART_LEN_PRIV	4

#define HW_ID_PART_POS_MAJOR	8
#define HW_ID_PART_LEN_MAJOR	8

#define HW_ID_PART_POS_MINOR 0
#define HW_ID_PART_LEN_MINOR 8


#define HW_ID_PART(name, val) (((val) & ((1 << HW_ID_PART_LEN_##name) - 1)) << HW_ID_PART_POS_##name)

#define HW_ID_PART_MAGIC(magic)		HW_ID_PART(MAGIC, magic)
#define HW_ID_PART_VENDOR(vendor) 	HW_ID_PART(VENDOR, vendor)
#define HW_ID_PART_PRIV(priv) 		HW_ID_PART(PRIV, priv)
#define HW_ID_PART_MAJOR(major) 	HW_ID_PART(MAJOR, major)
#define HW_ID_PART_MINOR(minor) 	HW_ID_PART(MINOR, minor)


#define HW_ID(magic, vendor, priv, major, minor)\
	(HW_ID_PART_MAGIC(magic) | HW_ID_PART_VENDOR(vendor) | HW_ID_PART_PRIV(priv)\
	 | HW_ID_PART_MAJOR(major) | (HW_ID_PART_MINOR(minor)))


#define HW_ID_GET_PART(name, id)	(((1 << HW_ID_PART_LEN_##name) - 1) & (id >> HW_ID_PART_POS_##name))

#define HW_ID_GET_PART_MAGIC(id)	HW_ID_GET_PART(MAGIC, id)
#define HW_ID_GET_PART_VENDOR(id)	HW_ID_GET_PART(VENDOR, id)
#define HW_ID_GET_PART_PRIV(id)		HW_ID_GET_PART(PRIV, id)
#define HW_ID_GET_PART_MAJOR(id)	HW_ID_GET_PART(MAJOR, id)
#define HW_ID_GET_PART_MINOR(id)	HW_ID_GET_PART(MINOR, id)

#define	VENDOR_ID_BST	0
#define	VENDOR_ID_AKM	1
#define	VENDOR_ID_IVS	2

/* ID of accels */
/*
 *A: 0
 *M: 1
 *G: 2
 *C: 3
 *I: 4
 *X: 5
*/

#define BST_PRIV_ID_A 0
#define BST_PRIV_ID_M 1
#define BST_PRIV_ID_G 2
#define BST_PRIV_ID_C 3
#define BST_PRIV_ID_I 4
#define BST_PRIV_ID_X 5

/* ---single BMAs--- */
#define HW_ID_A_BMA220  HW_ID(SENSOR_MAGIC_A, VENDOR_ID_BST, BST_PRIV_ID_A,  6, 0)

#define HW_ID_A_BMA222  HW_ID(SENSOR_MAGIC_A, VENDOR_ID_BST, BST_PRIV_ID_A,  8, 0)
#define HW_ID_A_BMA222E HW_ID(SENSOR_MAGIC_A, VENDOR_ID_BST, BST_PRIV_ID_A,  8, 1)

#define HW_ID_A_BMA250  HW_ID(SENSOR_MAGIC_A, VENDOR_ID_BST, BST_PRIV_ID_A, 10, 0)
#define HW_ID_A_BMA250E HW_ID(SENSOR_MAGIC_A, VENDOR_ID_BST, BST_PRIV_ID_A, 10, 1)
#define HW_ID_A_BMA150  HW_ID(SENSOR_MAGIC_A, VENDOR_ID_BST, BST_PRIV_ID_A, 10, 2)

#define HW_ID_A_BMA255  HW_ID(SENSOR_MAGIC_A, VENDOR_ID_BST, BST_PRIV_ID_A, 12, 0)

#define HW_ID_A_BMA280  HW_ID(SENSOR_MAGIC_A, VENDOR_ID_BST, BST_PRIV_ID_A, 14, 0)

/* ---BMAs within compass--- */
/* major and minor ID compatible with BMA250 */
#define HW_ID_A_BMC050  HW_ID(SENSOR_MAGIC_A, VENDOR_ID_BST, BST_PRIV_ID_C, 10, 0)
/* major and minor ID compatible with BMA250E */
#define HW_ID_A_BMC050E HW_ID(SENSOR_MAGIC_A, VENDOR_ID_BST, BST_PRIV_ID_C, 10, 1)
#define HW_ID_A_BMC022  HW_ID(SENSOR_MAGIC_A, VENDOR_ID_BST, BST_PRIV_ID_C, 10, 2)
#define HW_ID_A_BMC022E HW_ID(SENSOR_MAGIC_A, VENDOR_ID_BST, BST_PRIV_ID_C, 10, 3)

/* major and minor ID compatible with BMA255 */
#define HW_ID_A_BMC055  HW_ID(SENSOR_MAGIC_A, VENDOR_ID_BST, BST_PRIV_ID_C, 12, 0)
#define HW_ID_A_BMC056  HW_ID(SENSOR_MAGIC_A, VENDOR_ID_BST, BST_PRIV_ID_C, 12, 1)
#define HW_ID_A_BMC150  HW_ID(SENSOR_MAGIC_A, VENDOR_ID_BST, BST_PRIV_ID_C, 12, 2)

/* ---BMAs within IMU --- */
#define HW_ID_A_BMI055  HW_ID(SENSOR_MAGIC_A, VENDOR_ID_BST, BST_PRIV_ID_I, 12, 0)

/* ID of magnetics */

/* ---BMMs within compass--- */
#define HW_ID_M_BMC050  HW_ID(SENSOR_MAGIC_M, VENDOR_ID_BST, BST_PRIV_ID_C, 13, 0)
#define HW_ID_M_BMC050E HW_ID(SENSOR_MAGIC_M, VENDOR_ID_BST, BST_PRIV_ID_C, 13, 1)
#define HW_ID_M_BMC022  HW_ID(SENSOR_MAGIC_M, VENDOR_ID_BST, BST_PRIV_ID_C, 13, 2)
#define HW_ID_M_BMC022E HW_ID(SENSOR_MAGIC_M, VENDOR_ID_BST, BST_PRIV_ID_C, 13, 3)
#define HW_ID_M_BMC055  HW_ID(SENSOR_MAGIC_M, VENDOR_ID_BST, BST_PRIV_ID_C, 13, 4)
#define HW_ID_M_BMC056  HW_ID(SENSOR_MAGIC_M, VENDOR_ID_BST, BST_PRIV_ID_C, 13, 5)
#define HW_ID_M_BMC150  HW_ID(SENSOR_MAGIC_M, VENDOR_ID_BST, BST_PRIV_ID_C, 13, 6)

#define HW_ID_M_BMM150  HW_ID(SENSOR_MAGIC_M, VENDOR_ID_BST, BST_PRIV_ID_M, 13, 0)


/* ID of gyros */
#define HW_ID_G_BMG160  HW_ID(SENSOR_MAGIC_G, VENDOR_ID_BST, BST_PRIV_ID_G, 16, 0)

#define HW_ID_G_BMI055  HW_ID(SENSOR_MAGIC_G, VENDOR_ID_BST, BST_PRIV_ID_I, 16, 0)


#define HW_ID_G_MPU3050 HW_ID(SENSOR_MAGIC_G, VENDOR_ID_IVS, 16, 0, 0)


enum {
	HW_A_RANGE_INVALID = -1,
	/* 0 */
	HW_A_RANGE_2G,
	/* 1 */
	HW_A_RANGE_4G,
	/* 2 */
	HW_A_RANGE_8G,
	/* 3 */
	HW_A_RANGE_16G,
	/* 4 */
	HW_A_RANGE_MAX
};

enum {
	SENSOR_DEV_ACC_ODR_INVALID = -1,

	SENSOR_DEV_ACC_ODR_3_125HZ,

	SENSOR_DEV_ACC_ODR_6_25HZ,

	SENSOR_DEV_ACC_ODR_12_5HZ,

	SENSOR_DEV_ACC_ODR_25HZ,

	SENSOR_DEV_ACC_ODR_50HZ,

	SENSOR_DEV_ACC_ODR_100HZ,

	SENSOR_DEV_ACC_ODR_200HZ,

	SENSOR_DEV_ACC_ODR_400HZ,

	SENSOR_DEV_ACC_ODR_800HZ,

	SENSOR_DEV_ACC_ODR_1600HZ,

	SENSOR_DEV_ACC_ODR_MAX
};

enum {

	SENSOR_DEV_GYRO_ODR_25HZ = 6,

	SENSOR_DEV_GYRO_ODR_50HZ = 7,

	SENSOR_DEV_GYRO_ODR_100HZ = 8,

	SENSOR_DEV_GYRO_ODR_200HZ = 9,

	SENSOR_DEV_GYRO_ODR_400HZ = 10,

	SENSOR_DEV_GYRO_ODR_800HZ = 11,

	SENSOR_DEV_GYRO_ODR_1600HZ = 12,

	SENSOR_DEV_GYRO_ODR_MAX
};

enum {
	HW_G_RANGE_INVALID = -1,
	/* 0 */
	HW_G_RANGE_125,
	/* 1 */
	HW_G_RANGE_250,
	/* 2 */
	HW_G_RANGE_500,
	/* 3 */
	HW_G_RANGE_1000,
	/* 4 */
	HW_G_RANGE_2000,
	/* 5 */
	HW_G_RANGE_MAX
};
#endif

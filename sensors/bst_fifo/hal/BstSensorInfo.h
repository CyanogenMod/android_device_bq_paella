/*!
 * @section LICENSE
 * $license$
 *
 * @file         $filename$
 * @date         $date$
 * @commit       $id$
 *
 * @brief
 *
 * @detail
 *
 */


#ifndef __BST_SENSOR_INFO_H
#define __BST_SENSOR_INFO_H
#include "sensors.h"

#define BST_HAL_VER_MAIN 3
#define BST_HAL_VER_SUB_LEVEL 0
#define BST_HAL_VER_PATCH_LEVEL 0
#define BST_HAL_VER_EXTRA_LEVEL 0

#define BST_HAL_VER\
	((BST_HAL_VER_MAIN << 24) | (BST_HAL_VER_SUB_LEVEL << 16)\
	| (BST_HAL_VER_PATCH_LEVEL << 8) | (BST_HAL_VER_EXTRA_LEVEL))

#define BST_HAL_VER_STR "2013-04-03"

#ifndef BST_HW_NAME_A
#define BST_HW_NAME_A ""
#endif

#ifndef BST_HW_NAME_M
#define BST_HW_NAME_M ""
#endif

#ifndef BST_HW_NAME_G
#define BST_HW_NAME_G ""
#endif

#define BST_SENSOR_NAME_A BST_HW_NAME_A "Acceleration"
#define BST_SENSOR_NAME_M BST_HW_NAME_M "Magnetic Field"
#define BST_SENSOR_NAME_G BST_HW_NAME_G "Gyroscope"
#define BST_SENSOR_NAME_O "Orientation"
#define BST_SENSOR_NAME_P "Pressure"
#define BST_SENSOR_NAME_VG "Gravity"
#define BST_SENSOR_NAME_VLA "Linear Acceleration"
#define BST_SENSOR_NAME_VRV "Rotation Vector"

#ifdef __UNCALIBRATED_VIRTUAL_SENSOR_SUPPORT__
#define BST_SENSOR_NAME_GRV "Game Rotation Vector"
#define BST_SENSOR_NAME_GYU BST_HW_NAME_G "Gyroscope Uncalibrated"
#define BST_SENSOR_NAME_MU BST_HW_NAME_M "Magnetic Field Uncalibrated"
#endif

#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
#define BST_SENSOR_NAME_GEOM_RY "Geomagnetic Rotation Vector"
#endif

#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_0__
#define BST_SENSOR_NAME_STC "Step Counter"
#define BST_SENSOR_NAME_STD "Step Detector"
#endif

#define BST_SENSOR_NAME_SGM "Software Signaficant Motion"
#define BST_SENSOR_NAME_GEST_FLIP "Flip"




class BstSensorInfo {
public:
	static const struct sensor_t g_bst_sensor_list[];
	static const struct sensor_t * getSensor(int handle);
};
#endif

#ifndef __BSXLIBRARYCALIBCONSTANTS_H__
#define __BSXLIBRARYCALIBCONSTANTS_H__
/*!
* @section LICENCE
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
* @file      bsxlibrarycalibconstants.h
* @date      2013/02/12 created
*
* @brief
* This file provides constants definition for calibration modules
*
*
*/

/************************************************************************************************************/
/*												INCLUDES													*/
/************************************************************************************************************/

#include "BsxLibraryDataTypes.h"

/************************************************************************************************************/
/*											CONSTANT DEFINITIONS										 	*/
/************************************************************************************************************/

/**\name Calibration modes */

#define BSX_CALIB_SLEEP     			(0U)		/**< sleep mode for calibration */
#define BSX_CALIB_MONITORING  			(1U)		/**< Calibration monitoring is active*/
#define BSX_CALIB_MODEOFFSETACTIVE		(2U)		/**< Calibration offsets estimation is active */

/**\name Data correction modes */

#define BSX_DATACORRECTION_SLEEP		(0U)       /**< 0 => No Data correction */
#define BSX_DATACORRECTION_OFFSET		(1U)		/**<  1 = Only offset correction is included */
#define BSX_DATACORRECTION_SENSDOFFSET	(2U)       /**<   2 = offset + diagonal sensitivity correction are included*/
#define BSX_DATACORRECTION_SENSFOFFSET	(3U)       /**<  3 = offset + full sensitivity correction are used for data correction */

/**\name Calibration Source types */

#define BSX_CALIBSOURCE_NONE     		(0U)		/**< no Calibration source*/
#define BSX_CALIBSOURCE_CLASSIC  		(1U)		/**< Calibration source is classical*/
#define BSX_CALIBSOURCE_FAST			(2U) 		/**< Calibration source is FMC*/

/**\name Gyro calibration modes */

#define BSX_GYROCALIB_SLEEP     		(0U)      /**<  0= Gyroscope Calibration is not Active */
#define BSX_GYROCALIB_GYRODATA			(1U)      /**<   1= Gyroscope Calibration based on (Gyroscope) data only */
#define BSX_GYROCALIB_GYROACC  			(2U)      /**<   2= Gyroscope Calibration based on  (Gyroscope+Accelerometer) Data */
#define BSX_GYROCALIB_GYROACCMAG		(3U)      /**<   3= Gyroscope Calibration based on (Gyroscope+Accelerometer+Magnetometer) Data */

#endif







































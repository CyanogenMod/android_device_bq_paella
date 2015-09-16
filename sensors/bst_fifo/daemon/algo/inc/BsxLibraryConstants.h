#ifndef __BSXLIBRARYCONSTANTS_H__
#define __BSXLIBRARYCONSTANTS_H__
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
* @file      bsxlibraryconstants.h
* @date      2013/02/12 created
*
* @brief
* This file provides constants definition used by library
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


/* gravity on earth = 9.80665 m/s2 */
#define BSX_GRAVITY     					(9.80665f)	/**< gravity equivalent in ms^2*/

/**\name Conversion factors */
#define BSX_CONVFACTOR_RES16BIT_UNITS2LSB	(32767.0f)		/**< conversion factor res16bit units to lsb */
#define BSX_CONVFACTOR_RES16BIT_LSB2UNITS	(3.0519e-005f)	/**< 1/32767 */
#define BSX_CONVFACTOR_RES15BIT_UNITS2LSB	(16384.0f)		/**<conversion factor res15bit units to lsb */
#define BSX_CONVFACTOR_INV_RES15BIT_UNITS2LSB (6.10351563e-005f)  /**< 1/16384*/
#define BSX_CONVFACTOR_RES15BIT_LSB2UNITS	(6.1035e-005f)	/**< calculated as 1/16384 */
#define PI_OVER_TWO  						(1.570796326794897f)	/**< pi/2*/
#define PI_TIMES_TWO  						(6.283185307179586f)   /**< 2*pi*/
#define SQRT_TWO_OVER_TWO  					(0.7071067811865476f)   /**< 0.5*sqrt(2)*/

#define UNIT_SCALING_ACC_INTERNAL2MPS2		(0.00980665f)   /**< milli gravity -> metre per second squared  */
#define UNIT_SCALING_ACC_MPS22INTERNAL		(1.019835806435164e+02f) /**< calculated as 1/0.00980665f */
#define UNIT_SCALING_ACC_INTERNAL2G			(1e-3f) /**< internal unit [mg] to [g]*/
#define UNIT_SCALING_ACC_G2INTERNAL         (1000U)	/**< [g] to internal unit [mg]*/
#define UNIT_SCALING_GYRO_INTERNAL2DEGPS	(6.1e-2f)  /**< internal unit [0.061 deg/s] to [deg/s]; note: 2000/2^15 = 0.061 ;1/BSX_CONVFACTOR_DPS2LSB */
#define UNIT_SCALING_GYRO_DEGPS2INTERNAL	(16.384f) /**< [deg/s] to internal unit [0.061 deg/s]; note: 2^15/2000 = 16.384*/
#define	UNIT_SCALING_GYRO_INTERNAL2RADPS	(0.001065264436031695f)		/**< internal unit [0.0011 rad/s] to [deg/s]; note: 2000/2^15*pi/180 = 0.0011*/
#define UNIT_SCALING_GYRO_RADPS2INTERNAL	(938.7341f)	/**< calculated as BSX_CONVFACTOR_DPS2LSB*180/pi */
#define UNIT_SCALING_MAG_INTERNAL2UTESLA	(0.1f)   /**< internal unit [0.1 uT] to [uT]*/
#define UNIT_SCALING_MAG_UTESLA2INTERNAL	(10U)   /**< [uT] to internal unit [0.1 uT]*/
/**\name Supported Data Rate */
#define BSX_DATARATE_1HZ      				(0U) /**< Library constant for 1hz datarate*/
#define BSX_DATARATE_5HZ      				(1U) /**< Library constant for 5Hz  datarate*/	
#define BSX_DATARATE_6_25HZ    				(2U) /**< Library constant for 6_25Hz datarate*/
#define BSX_DATARATE_10HZ     				(3U) /**< Library constant for 10Hz datarate*/
#define BSX_DATARATE_12_50HZ   				(4U) /**< Library constant for 12_50hz datarate*/
#define BSX_DATARATE_20HZ     				(5U) /**< Library constant for 20hz datarate*/
#define BSX_DATARATE_25HZ     				(6U) /**< Library constant for 25hz datarate*/
#define BSX_DATARATE_40HZ					(7U) /**< Library constant for 40hz datarate*/
#define BSX_DATARATE_50HZ     				(8U) /**< Library constant for 50hz datarate*/
#define BSX_DATARATE_100HZ    				(9U) /**< Library constant for 100hz datarate*/
#define BSX_DATARATE_125HZ					(10U) /**< Library constant for 125hz datarate*/
#define BSX_DATARATE_200HZ    				(11U) /**< Library constant for 200hz datarate*/
#define BSX_DATARATE_400HZ					(12U) /**< Library constant for 400hz datarate*/
#define DATARATE_INVALIDUPPER				(13U)  /**< Upper boundary on allowed values*/

/**\name Operational modes */
#define BSX_OPMODE_SLEEP     				(0U) /**< Operation mode -> sleep(0)*/
#define BSX_OPMODE_REGULAR  				(1U) /**< Operation mode -> Regular(1)*/
#define BSX_OPMODE_FIFO   					(2U) /**< Operation mode -> fifo(2)*/

/**\name Geomagnetic rotation  modes */
#define BSX_NDOFGRV_SLEEP				(0U) /**< Geomagnetic rotation mode sleep*/
#define BSX_NDOFGRV_ACTIVE				(1U) /**< Geomagnetic rotation mode active*/

/**\name Filter modes  (0 = bypass; 1 = forward; 2 = backward;) */
#define BSX_FILTERMODE_BYPASS     			(0U) /**< Filter mode -> BYPASS */
#define BSX_FILTERMODE_FORWARD  			(1U) /**< Filter Mode -> FORWARD */
#define BSX_FILTERMODE_BACKWARD   			(2U) /**< Filter mode -> BACKWARD */


/**\name Measurement range of the accelerometer */
#define BSX_ACCRANGE_2G                     (0U) /**< Accel range -> 2g*/
#define BSX_ACCRANGE_4G                     (1U) /**< Accel range -> 4g*/
#define BSX_ACCRANGE_8G                     (2U) /**< Accel range -> 8g*/
#define BSX_ACCRANGE_16G                    (3U) /**< Accel range -> 16g*/

/**\name Measurement range of the Gyroscope */
#define BSX_GYRORANGE_2048DPS				(0U)  /**< Measurement Range -> 2048 Degrees/sec */
#define BSX_GYRORANGE_2000DPS				(1U)  /**< Measurement Range -> 2000 Degrees/sec */
#define BSX_GYRORANGE_1000DPS				(2U)  /**< Measurement Range -> 1000 Degrees/sec */
#define BSX_GYRORANGE_500DPS				(3U)  /**< Measurement Range -> 500 Degrees/sec */
#define BSX_GYRORANGE_250DPS				(4U)  /**< Measurement Range -> 250 Degrees/sec */
#define BSX_GYRORANGE_MAX					(4U)  /**< Maximum gyro measurement range */

/** \name Sensor Accuracy Information */
#define BSX_SENSOR_STATUS_UNRELIABLE       	(0U) /**< Sensor accuracy : unreliable */
#define BSX_SENSOR_STATUS_ACCURACY_LOW     	(1U) /**< Sensor accuracy status:low*/
#define BSX_SENSOR_STATUS_ACCURACY_MEDIUM  	(2U) /**< Sensor accuracy status: medium*/
#define BSX_SENSOR_STATUS_ACCURACY_HIGH		(3U) /**< Sensor accuracy status: high*/

/**\name  Constants representing a sensor */
#define BSX_TYPE_ACCELEROMETER				(1) /**< Represents Accelerometer sensor */
#define BSX_TYPE_AMBIENT_TEMPERATURE		(13)/**< Represents Ambient Temperature sensor */
#define BSX_TYPE_GRAVITY					(9)/**< Represents Gravity sensor */
#define BSX_TYPE_GYROSCOPE					(4)/**< Represents Gyro sensor */
#define BSX_TYPE_LIGHT						(5)/**< Represents Light sensor */
#define BSX_TYPE_LINEAR_ACCELERATION		(10)/**< Represents Linear Acceleration sensor */
#define BSX_TYPE_MAGNETIC_FIELD				(2)/**< Represents Magnetic Field sensor */
#define BSX_TYPE_ORIENTATION				(3)/**< Represents Orientaion sensor */
#define BSX_TYPE_PRESSURE					(6)/**< Represents Pressure sensor */
#define BSX_TYPE_PROXIMITY					(8)/**< Represents Proximity sensor */
#define BSX_TYPE_RELATIVE_HUMIDITY			(12)/**< Represents Relative Humidity sensor */
#define BSX_TYPE_ROTATION_VECTOR			(11)/**< Represents RotationVector sensor */
#define BSX_TYPE_TEMPERATURE				 (7)/**< Represents Temperature sensor */

/**\name Datarate Array in Hz */
#define BSX_ARRAY_DATARATE					{(1.0f), (5.0f), (6.25f), (10.0f), (12.5f), (20.0f), (25.0f), (40.0f), (50.0f), (100.0f), (125.0f), (200.0f), (400.0f)} /**< Datarate array*/
#define BSX_ARRAY_ACCMEASRANGE				{(2U), (4U), (8U), (16U)}	/**<  Accelerometer Measurment Range Array in G */
#define BSX_ARRAY_GYROMEASRANGE				{(2048), (2000), (1000), (500), (250)} /**< Gyroscope measurement range in dps */
#define BSX_ARRAY_FILTERIIRCOEFF			{(0.0f), (0.0f), (0.0f), (0.0f), (0.0f), (0.0f), (0.0f), (0.0f), (0.35f), (0.55f), (0.55f), (0.7f), (0.7f)} /**< filtering coefficient : 0 => no filtering*/
#define BSX_REF_ARRAY						{(1000.0f), (200.0f),(160.0f),(100.0f),(80.0f), (50.0f), (40.0f), (25.0f), (20.0f), (10.0f), (8.0f), (5.0f), (2.5f)} /**< Reference time array in ms */

/**\name Opmode Shift Defines*/
#define BSX_BITSHIFT_ACCOPMODE				(0U) /**< Constant used for bitshifting  opmode (accel)*/
#define BSX_BITSHIFT_MAGOPMODE				(2U)/**< Constant used for bitshifting  opmode (Mag)*/
#define BSX_BITSHIFT_GYROOPMODE				(4U)/**< Constant used for bitshifting  opmode (Gyro)*/
#define BSX_BITSHIFT_COMPASSOPMODE			(6U)/**< Constant used for bitshifting  opmode (Compass)*/
#define BSX_BITSHIFT_M4GOPMODE				(8U)/**< Constant used for bitshifting  opmode (M4g)*/
#define BSX_BITSHIFT_NDOFOPMODE				(10U)/**< Constant used for bitshifting  opmode (Ndof)*/
#define BSX_BITSHIFT_FASTMAGCALIBOPMODE		(12U)/**< Constant used for bitshifting  opmode (FastMagcalib)*/
#define BSX_BITSHIFT_CLASSICALMAGCALIBOPMODE (14U)/**< Constant used for bitshifting  opmode (Classical Mag calib)*/
#define BSX_BITSHIFT_MAGCALIBSOURCE			(16U)/**< Constant used for bitshifting  opmode (Mag calib source)*/
#define BSX_BITSHIFT_GYROCALIBOPMODE		(18U)/**< Constant used for bitshifting  opmode (gyro calib)*/
#define BSX_BITSHIFT_NDOFGEORVOPMODE        (20U)/**< Constant used for bitshifting  opmode (Ndof Geo Rv)*/


#define BSX_BITMASKING						(0x03U) /**< Hex Constant used for Bit Masking */

/**\name Working Modes */
#define BSX_WORKINGMODE_SLEEP				(BSX_U32)((BSX_NDOFGRV_SLEEP<<BSX_BITSHIFT_NDOFGEORVOPMODE)|(BSX_GYROCALIB_SLEEP << BSX_BITSHIFT_GYROCALIBOPMODE)|(BSX_CALIB_SLEEP << BSX_BITSHIFT_MAGCALIBSOURCE)|(BSX_CALIB_SLEEP<<BSX_BITSHIFT_CLASSICALMAGCALIBOPMODE)|(BSX_CALIB_SLEEP<<BSX_BITSHIFT_FASTMAGCALIBOPMODE)|(BSX_OPMODE_NDOF_SLEEP<<BSX_BITSHIFT_NDOFOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_M4GOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_COMPASSOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_GYROOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_MAGOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_ACCOPMODE)) /**< working mode => sleep (no sensor is active)*/
#define BSX_WORKINGMODE_ACCONLY				(BSX_U32)((BSX_NDOFGRV_SLEEP<<BSX_BITSHIFT_NDOFGEORVOPMODE)|(BSX_GYROCALIB_SLEEP << BSX_BITSHIFT_GYROCALIBOPMODE)|(BSX_CALIB_SLEEP << BSX_BITSHIFT_MAGCALIBSOURCE)|(BSX_CALIB_SLEEP<<BSX_BITSHIFT_CLASSICALMAGCALIBOPMODE)|(BSX_CALIB_SLEEP<<BSX_BITSHIFT_FASTMAGCALIBOPMODE)|(BSX_OPMODE_NDOF_SLEEP<<BSX_BITSHIFT_NDOFOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_M4GOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_COMPASSOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_GYROOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_MAGOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_ACCOPMODE))/**< Only accelerometer sensor is active and related modules will be processed*/
#define BSX_WORKINGMODE_MAGONLY				(BSX_U32)((BSX_NDOFGRV_SLEEP<<BSX_BITSHIFT_NDOFGEORVOPMODE)|(BSX_GYROCALIB_SLEEP << BSX_BITSHIFT_GYROCALIBOPMODE)|(BSX_CALIBSOURCE_CLASSIC << BSX_BITSHIFT_MAGCALIBSOURCE)|(BSX_CALIB_MODEOFFSETACTIVE<<BSX_BITSHIFT_CLASSICALMAGCALIBOPMODE)|(BSX_CALIB_SLEEP<<BSX_BITSHIFT_FASTMAGCALIBOPMODE)|(BSX_OPMODE_NDOF_SLEEP<<BSX_BITSHIFT_NDOFOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_M4GOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_COMPASSOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_GYROOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_MAGOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_ACCOPMODE))/**< Only Magnetometer sensor is active and related modules will be processed*/
#define BSX_WORKINGMODE_ACCMAG				(BSX_U32)((BSX_NDOFGRV_SLEEP<<BSX_BITSHIFT_NDOFGEORVOPMODE)|(BSX_GYROCALIB_SLEEP << BSX_BITSHIFT_GYROCALIBOPMODE)|(BSX_CALIBSOURCE_CLASSIC << BSX_BITSHIFT_MAGCALIBSOURCE)|(BSX_CALIB_MODEOFFSETACTIVE<<BSX_BITSHIFT_CLASSICALMAGCALIBOPMODE)|(BSX_CALIB_SLEEP<<BSX_BITSHIFT_FASTMAGCALIBOPMODE)|(BSX_OPMODE_NDOF_SLEEP<<BSX_BITSHIFT_NDOFOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_M4GOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_COMPASSOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_GYROOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_MAGOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_ACCOPMODE))/**< Only Accelerometer and Magnetometer sensors are active and related modules will be processed*/
#define BSX_WORKINGMODE_ACCGYRO				(BSX_U32)((BSX_NDOFGRV_SLEEP<<BSX_BITSHIFT_NDOFGEORVOPMODE)|(BSX_GYROCALIB_GYROACC << BSX_BITSHIFT_GYROCALIBOPMODE)|(BSX_CALIB_SLEEP << BSX_BITSHIFT_MAGCALIBSOURCE)|(BSX_CALIB_SLEEP<<BSX_BITSHIFT_CLASSICALMAGCALIBOPMODE)|(BSX_CALIB_SLEEP<<BSX_BITSHIFT_FASTMAGCALIBOPMODE)|(BSX_OPMODE_NDOF_SLEEP<<BSX_BITSHIFT_NDOFOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_M4GOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_COMPASSOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_GYROOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_MAGOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_ACCOPMODE))/**<Accelerometer and Gyroscope sensors will be active and related modules will be processed*/
#define BSX_WORKINGMODE_IMUPLUS				(BSX_U32)((BSX_NDOFGRV_SLEEP<<BSX_BITSHIFT_NDOFGEORVOPMODE)|(BSX_GYROCALIB_GYROACC << BSX_BITSHIFT_GYROCALIBOPMODE)|(BSX_CALIB_SLEEP << BSX_BITSHIFT_MAGCALIBSOURCE)|(BSX_CALIB_SLEEP<<BSX_BITSHIFT_CLASSICALMAGCALIBOPMODE)|(BSX_CALIB_SLEEP<<BSX_BITSHIFT_FASTMAGCALIBOPMODE)|(BSX_OPMODE_NDOFIMU<<BSX_BITSHIFT_NDOFOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_M4GOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_COMPASSOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_GYROOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_MAGOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_ACCOPMODE))/**< IMU mode (Accelerometer + Gyroscope) are active and related modules will be processed*/
#define BSX_WORKINGMODE_GYROONLY			(BSX_U32)((BSX_NDOFGRV_SLEEP<<BSX_BITSHIFT_NDOFGEORVOPMODE)|(BSX_GYROCALIB_GYRODATA << BSX_BITSHIFT_GYROCALIBOPMODE)|(BSX_CALIB_SLEEP << BSX_BITSHIFT_MAGCALIBSOURCE)|(BSX_CALIB_SLEEP<<BSX_BITSHIFT_CLASSICALMAGCALIBOPMODE)|(BSX_CALIB_SLEEP<<BSX_BITSHIFT_FASTMAGCALIBOPMODE)|(BSX_CALIB_SLEEP<<BSX_BITSHIFT_NDOFOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_M4GOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_COMPASSOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_GYROOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_MAGOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_ACCOPMODE))/**< Only Gyroscope sensor is active and related modules will be processed*/
#define BSX_WORKINGMODE_MAGGYRO				(BSX_U32)((BSX_NDOFGRV_SLEEP<<BSX_BITSHIFT_NDOFGEORVOPMODE)|(BSX_GYROCALIB_GYRODATA << BSX_BITSHIFT_GYROCALIBOPMODE)|(BSX_CALIBSOURCE_FAST << BSX_BITSHIFT_MAGCALIBSOURCE)|(BSX_CALIB_SLEEP<<BSX_BITSHIFT_CLASSICALMAGCALIBOPMODE)|(BSX_CALIB_MODEOFFSETACTIVE<<BSX_BITSHIFT_FASTMAGCALIBOPMODE)|(BSX_OPMODE_NDOF_SLEEP<<BSX_BITSHIFT_NDOFOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_M4GOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_COMPASSOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_GYROOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_MAGOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_ACCOPMODE))/**< Mag and Gyro are active and related modules will be processed*/
#define BSX_WORKINGMODE_AMG					(BSX_U32)((BSX_NDOFGRV_SLEEP<<BSX_BITSHIFT_NDOFGEORVOPMODE)|(BSX_GYROCALIB_GYROACCMAG << BSX_BITSHIFT_GYROCALIBOPMODE)|(BSX_CALIBSOURCE_FAST << BSX_BITSHIFT_MAGCALIBSOURCE)|(BSX_CALIB_SLEEP<<BSX_BITSHIFT_CLASSICALMAGCALIBOPMODE)|(BSX_CALIB_MODEOFFSETACTIVE<<BSX_BITSHIFT_FASTMAGCALIBOPMODE)|(BSX_OPMODE_NDOF_SLEEP<<BSX_BITSHIFT_NDOFOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_M4GOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_COMPASSOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_GYROOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_MAGOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_ACCOPMODE))/**< Accel, Mag and gyro will be active and related modules will be processed*/
#define BSX_WORKINGMODE_COMPASS				(BSX_U32)((BSX_NDOFGRV_SLEEP<<BSX_BITSHIFT_NDOFGEORVOPMODE)|(BSX_GYROCALIB_SLEEP << BSX_BITSHIFT_GYROCALIBOPMODE)|(BSX_CALIBSOURCE_CLASSIC << BSX_BITSHIFT_MAGCALIBSOURCE)|(BSX_CALIB_MODEOFFSETACTIVE<<BSX_BITSHIFT_CLASSICALMAGCALIBOPMODE)|(BSX_CALIB_SLEEP<<BSX_BITSHIFT_FASTMAGCALIBOPMODE)|(BSX_OPMODE_NDOF_SLEEP<<BSX_BITSHIFT_NDOFOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_M4GOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_COMPASSOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_GYROOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_MAGOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_ACCOPMODE)) /**< COMPASS mode - Accel + Mag and related modules will be processed*/
#define BSX_WORKINGMODE_M4G					(BSX_U32)((BSX_NDOFGRV_SLEEP<<BSX_BITSHIFT_NDOFGEORVOPMODE)|(BSX_GYROCALIB_SLEEP << BSX_BITSHIFT_GYROCALIBOPMODE)|(BSX_CALIBSOURCE_CLASSIC << BSX_BITSHIFT_MAGCALIBSOURCE)|(BSX_CALIB_MODEOFFSETACTIVE<<BSX_BITSHIFT_CLASSICALMAGCALIBOPMODE)|(BSX_CALIB_SLEEP<<BSX_BITSHIFT_FASTMAGCALIBOPMODE)|(BSX_OPMODE_NDOF_SLEEP<<BSX_BITSHIFT_NDOFOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_M4GOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_COMPASSOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_GYROOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_MAGOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_ACCOPMODE)) /**< M4G mode - Accel +Mag and related modules will be processed*/

#define BSX_WORKINGMODE_NDOF_FMC_OFF		(BSX_U32)((BSX_NDOFGRV_SLEEP<<BSX_BITSHIFT_NDOFGEORVOPMODE)|(BSX_GYROCALIB_GYROACCMAG << BSX_BITSHIFT_GYROCALIBOPMODE)|(BSX_CALIBSOURCE_CLASSIC << BSX_BITSHIFT_MAGCALIBSOURCE)|(BSX_CALIB_MODEOFFSETACTIVE<<BSX_BITSHIFT_CLASSICALMAGCALIBOPMODE)|(BSX_CALIB_SLEEP<<BSX_BITSHIFT_FASTMAGCALIBOPMODE)|(BSX_OPMODE_NDOF_REGULAR<<BSX_BITSHIFT_NDOFOPMODE)|(BSX_OPMODE_NDOF_SLEEP<<BSX_BITSHIFT_M4GOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_COMPASSOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_GYROOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_MAGOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_ACCOPMODE)) /**<NDOF - FMC off mode (NDOF with classical calibration) and related modules will be processed*/
#define BSX_WORKINGMODE_NDOF				(BSX_U32)((BSX_NDOFGRV_SLEEP<<BSX_BITSHIFT_NDOFGEORVOPMODE)|(BSX_GYROCALIB_GYROACCMAG << BSX_BITSHIFT_GYROCALIBOPMODE)|(BSX_CALIBSOURCE_FAST << BSX_BITSHIFT_MAGCALIBSOURCE)|(BSX_CALIB_SLEEP<<BSX_BITSHIFT_CLASSICALMAGCALIBOPMODE)|(BSX_CALIB_MODEOFFSETACTIVE<<BSX_BITSHIFT_FASTMAGCALIBOPMODE)|(BSX_OPMODE_NDOF_REGULAR<<BSX_BITSHIFT_NDOFOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_M4GOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_COMPASSOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_GYROOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_MAGOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_ACCOPMODE)) /**<NDOF regular mode (with FMC calibration) and related modules will be processed */

#define BSX_WORKINGMODE_NDOF_GEORV          (BSX_U32)((BSX_NDOFGRV_ACTIVE<<BSX_BITSHIFT_NDOFGEORVOPMODE)|(BSX_GYROCALIB_GYROACCMAG << BSX_BITSHIFT_GYROCALIBOPMODE)|(BSX_CALIBSOURCE_FAST << BSX_BITSHIFT_MAGCALIBSOURCE)|(BSX_CALIB_SLEEP<<BSX_BITSHIFT_CLASSICALMAGCALIBOPMODE)|(BSX_CALIB_MODEOFFSETACTIVE<<BSX_BITSHIFT_FASTMAGCALIBOPMODE)|(BSX_OPMODE_NDOF_REGULAR<<BSX_BITSHIFT_NDOFOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_M4GOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_COMPASSOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_GYROOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_MAGOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_ACCOPMODE)) /**<NDOF mode with Geomagnetic Rotation Vector output(FMC enabled) and related modules will be processed*/
#define BSX_WORKINGMODE_NDOF_GEORV_FMC_OFF  (BSX_U32)((BSX_NDOFGRV_ACTIVE<<BSX_BITSHIFT_NDOFGEORVOPMODE)|(BSX_GYROCALIB_GYROACCMAG << BSX_BITSHIFT_GYROCALIBOPMODE)|(BSX_CALIBSOURCE_CLASSIC << BSX_BITSHIFT_MAGCALIBSOURCE)|(BSX_CALIB_MODEOFFSETACTIVE<<BSX_BITSHIFT_CLASSICALMAGCALIBOPMODE)|(BSX_CALIB_SLEEP<<BSX_BITSHIFT_FASTMAGCALIBOPMODE)|(BSX_OPMODE_NDOF_REGULAR<<BSX_BITSHIFT_NDOFOPMODE)|(BSX_OPMODE_NDOF_SLEEP<<BSX_BITSHIFT_M4GOPMODE)|(BSX_OPMODE_SLEEP<<BSX_BITSHIFT_COMPASSOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_GYROOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_MAGOPMODE)|(BSX_OPMODE_REGULAR<<BSX_BITSHIFT_ACCOPMODE)) /**<NDOF mode with Geomagnetic Rotation Vector output(FMC disabled) and related modules will be processed */

#define BSX_WORKINGMODE_DEFAULT				BSX_WORKINGMODE_SLEEP  /**< Default working mode - "BSX_WORKINGMODE_SLEEP"*/

/**\name Orientation Sensor Modes */
/**\name Ndof*/
#define BSX_OPMODE_NDOF_SLEEP				(0U) /**< Ndof Operation mode is in  sleep state */
#define BSX_OPMODE_NDOFIMU					(1U) /**< Ndof Operation mode => 1 indicates IMU mode*/
#define BSX_OPMODE_NDOF_REGULAR				(2U) /**< Regular Ndof mode*/

/**\name Time related */
#define BSX_SAMPLETIMETOLERANCE				(0.95f)   /**< Decreasing of RefTime by this factor => 10ms * 0.95 = 9.5ms --> 105.2Hz */

/**\name Orientation sensor model */
#define BSX_OPMODE_ORIENT_SLEEP             (0U)	/**< Orient Opmode:sleep	 */
#define BSX_OPMODE_ORIENT_COMPASS           (1U)	/**< Orient Opmode:Compass */
#define BSX_OPMODE_ORIENT_M4G               (2U)	/**< Orient Opmode:M4G     */
#define BSX_OPMODE_ORIENT_IMU               (3U)	/**< Orient Opmode:IMU	 */
#define BSX_OPMODE_ORIENT_NDOF              (4U)	/**< Orient Opmode:NDOF 	 */

/**\name Flip gesture Operation mode */
#define BSX_FLIP_GESTURE_MODE_SLEEP			(0U)	/**< Flig Gesture mode :sleep	 */
#define BSX_FLIP_GESTURE_MODE_REGULAR		(1U)	/**< Flip Gesture mode : regular */

/**\name Significant Motion Operation mode */
#define BSX_SIGNIFICANT_MOTION_SLEEP		(0U)	/**< Significant Motion opmode :Sleep	 */
#define BSX_SIGNIFICANT_MOTION_REGULAR		(1U)	/**< Significant Motion opmode :Regular */

/**\name Pedometer Support Operation Mode */
#define BSX_PEDO_SUPPORT_SLEEP              (0U) /**< Pedometer operation mode: sleep*/
#define BSX_PEDO_SUPPORT_REGULAR            (1U) /**< Pedometer operation mode:regular*/

/**\name Orient coordinate system*/
#define BSX_ORIENTCOORDINATESYSTEM_ANDROID	(1U)   /**< Coordinate system: Android */
#define BSX_ORIENTCOORDINATESYSTEM_WIN8		(2U)	/**<  Coordinate system: Win8 */

/**\name Compass Orient Filter modes*/
#define BSX_COMPASSORIENTFILTER_MODE_BYPASS   (0U) /**< Orient filter mode : Bypass(0)*/
#define BSX_COMPASSORIENTFILTER_MODE_LOW      (1U) /**< Orient filter mode : low(1)*/
#define BSX_COMPASSORIENTFILTER_MODE_MEDIUM   (2U) /**< Orient filter mode : medium(2)*/
#define BSX_COMPASSORIENTFILTER_MODE_HIGH     (3U) /**< Orient filter mode : high(3)*/

#define BSX_COMPASSORIENTFILTERCOEFFCALC_MODE_BYPASS   (0U) /**< Coeff Calc  mode : bypass(0)*/
#define BSX_COMPASSORIENTFILTERCOEFFCALC_MODE_FORWARD  (1U) /**< Coeff Calc  mode : forward(1)*/
#define BSX_COMPASSORIENTFILTERCOEFFCALC_MODE_BACKWARD (2U) /**< Coeff Calc mode : Backward(2)*/

/**\name Predefined levels*/
#define BSX_PREDEFINED_LEVEL_ZERO             (0U) /**< Predefined level: zero*/
#define BSX_PREDEFINED_LEVEL_ONE              (1U) /**< Predefined level:  one*/
#define BSX_PREDEFINED_LEVEL_TWO              (2U) /**< Predefined level:  two*/
#define BSX_PREDEFINED_LEVEL_THREE            (3U) /**< Predefined level:  three*/
#define BSX_PREDEFINED_LEVEL_FOUR             (4U) /**< Predefined level:  four*/
#define BSX_PREDEFINED_LEVEL_FIVE             (5U) /**< Predefined level:  five*/

#define BSX_PREDEFINED_LEVEL_MIN     BSX_PREDEFINED_LEVEL_ZERO /**< predefined level minimum: level zero*/
#define BSX_PREDEFINED_LEVEL_DEFAULT BSX_PREDEFINED_LEVEL_ONE  /**< predefined level default : level one*/
#define BSX_PREDEFINED_LEVEL_MAX     BSX_PREDEFINED_LEVEL_FIVE /**< predefined level maximum :level five*/
#endif






































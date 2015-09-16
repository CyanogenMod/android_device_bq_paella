#ifndef __BSXFUSIONLIBRARY_H__
#define __BSXFUSIONLIBRARY_H__
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
* @file      bsxfusionlibrary.h
* @date      2013/02/12 created
*
* @brief
* This file provides an interface to use the functionality of nine degree of freedom software library
*
*
*  bsxfusionlibrary - nine degree of freedom software library for the processing of the
* accelerometer, magnetometer and gyroscope sensor data.The library supports different
* operational modes of the sensors. Additionally, the library provides the virtual sensors
* like compass, imu, 9dof sensors for orientation processing, which uses the sensor fusion
* algorithm for estimation of the orientation processing or sensor calibration methods.
*
*/

/************************************************************************************************************/
/**\name										INCLUDES													*/
/************************************************************************************************************/

#include "BsxLibraryDataTypes.h"

/************************************************************************************************************/
/**\name									GENERAL INTERFACE												*/
/************************************************************************************************************/

/*!
* @brief		Get version of the BSX Fusion Library.
* 				Version is a structure of four element which
* 				consists of major, minor, minorbugfix and majorbugfix.
* 			 	e.g. major=3, minor=0, minorbugfix =1 and
* 			  	majorbugfix = 0 implies its bsx 3.0.1.0
* @param 	*version-> Pointer to version structure
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_version(ts_version*);

/*!
* @brief		This API initializes the main library process.
* 				If the input pointer is NULL then it will
* 				initialize with default values defined in the library.
*
* @param  		inputparams  -> pointer to acc,mag,gyro specs and usecase config
*
*				Inputparam->accelspec : Pointer to accelspec char array that holds settings for particular accelerometer sensor
*				Inputparam->magspec : Pointer to magspec char array that holds settings for particular magnetometer sensor
*				Inputparam->gyrospec : Pointer to gyrospec char array that holds settings for particular gyroscope sensor
*				Inputparam->usecaseconfig : Pointer to usecase char array that holds settings for particular usecase 
*
*				Inputparam->accelspec_status holds the status if the spec is error free and not modified from original
*
*				0 -> error in accelerometer spec char array
*				1 -> No error in accelerometer spec array and spec corresponds to bma250
*				2 -> No error in accelerometer spec array and spec corresponds to bma255
*				3 -> No error in accelerometer spec array and spec corresponds to bma280
*
*				Inputparam->magspec_status holds the status if the spec is error free and not modified from original
*
*				0 -> error in magnetometer spec char array
*				1 -> No error in magnetometer spec array and spec corresponds to bmm050
*				2 -> No error in magnetometer spec array and spec corresponds to bmm150
*
*				Inputparam->gyrospec_status holds the status if the spec is error free and not modified from original
*
*				0 -> error in gyroscope spec char array
*				1 -> No error in gyroscope spec array and spec corresponds to bmg160
*
*				Inputparam->usecase_status holds the status if the spec is error free and not modified from original
*
*				0 -> error in usecase char array
*				1 -> No error in usecase char array
*
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_init(initParam_t*);

/*!
* @brief    reset dynamic state of the library
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_reset(void);

/*!
* @brief    Main library process - divided into three process running at different frequency - dopreprocess , docalibration and dousecase
* @brief    dopreprocess - preprocessing sensor - accel , mag , gyro, compass ->includes conversions to units from lsb and other preprocessing

* @brief    docalibration - calibration of accel,mag,gyro -> includes classical and fmc calibration for mag

* @brief     dousecase - COMPASS/M4G , IMU , NDOF processing
* @param    libraryinput_p -> pointer to sensor data
*       	structure which includes sensor data S32 type and
*         	 time stamp in microseconds of U64 type
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_dostep(libraryinput_t* );

/*!
* @brief    Pre Process Library (includes preprocessing of accel, mag, gyro,fmc, compass)
* @param    libraryinput_p -> pointer to sensor data
*       	structure which includes sensor data S32 type and
*         	 time stamp in microseconds of U64 type
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_dopreprocess(libraryinput_t*);

/*!
* @brief    Sensor Calibration Layer - (includes calibration of accel, mag, gyro, fmc when corresponding tick.calib is enabled)
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_docalibration(void);


/*!
* @brief    Sensor Usecase Layer - responsible for all use-case processing (COMPASS,M4G,IMU,NDOF)
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_dousecase(void);

/************************************************************************************************************/
/**\name									ACCELEROMETER API												*/
/************************************************************************************************************/

/*!
* @brief 	Initialization of accelerometer modules with the settings of particular accel sensor.
*			If NULL is passed,the default values(BMA250) are loaded.
* @param 	*p_accelspec -> Pointer to accelspec char array that holds settings for particular accel sensor
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_init_acc(BSX_U8*);

/*!
* @brief	Sets the measurement range for accelerometer
* @param	measrange -> measurement range of accelerometer.
*
*			Permissible values 
*						0 -> BSX_ACCRANGE_2G ;
*                       1 -> BSX_ACCRANGE_4G ;
*                       2 -> BSX_ACCRANGE_8G ;
*                       3 -> BSX_ACCRANGE_16G; 
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_accrange(BSX_U8);

/*!
* @brief	Get the measurement range for accelerometer
* @param	*measrange -> pointer to measurement range of accelerometer
*
*			 0 -> BSX_ACCRANGE_2G;
*            1 -> BSX_ACCRANGE_4G;
*            2 -> BSX_ACCRANGE_8G;
*            3 -> BSX_ACCRANGE_16G;
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_accrange(BSX_U8*);

/*!
* @brief	Set the calling datarate for the accelerometer
* @param	accDataRate-> calling data rate of accelerometer
*
*			permissible values
*				0 -> 1Hz
*				1 -> 5Hz
*				2 -> 6.25Hz
*				3 -> 10Hz
*				4 -> 12.5Hz
*				5 -> 20Hz
*				6 -> 25Hz
*				7 -> 40Hz
*				8 -> 50Hz
*				9 -> 100Hz
*				10 -> 125Hz
*				11 -> 200Hz
*				12 -> 400Hz
*				13 -> Invalid upper data rate
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_accdatarate(BSX_U8);

/*!
* @brief	Get the datarate for the accelerometer
* @param	accDataRate -> parameter to get data rate of accelerometer that is being set
*
*			Output values
*				0 -> 1Hz
*				1 -> 5Hz
*				2 -> 6.25Hz
*				3 -> 10Hz
*				4 -> 12.5Hz
*				5 -> 20Hz
*				6 -> 25Hz
*				7 -> 40Hz
*				8 -> 50Hz
*				9 -> 100Hz
*				10 -> 125Hz
*				11 -> 200Hz
*				12 -> 400Hz
*				13 -> Invalid upper data rate
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_accdatarate(BSX_U8*);

/*!
* @brief	Set the accelerometer calibration accuracy threshold 
* @param	accThreshold	-> calibration accuracy threshold of accelerometer
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_acccalib_accuracythreshold(BSX_U8);

/*!
* @brief	Set the accelerometer calibration profile(calibration offset and accuracy status)
* @param	calibprofile-> variable to Accelerometer calibration profile structure
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_acccalibprofile(ts_calibprofile*);

/*!
* @brief	Get the acceleromter calibration profile
* @param	*calibprofile -> Pointer to Accelerometer calibration profile
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_acccalibprofile(ts_calibprofile*);

/*!
* @brief	reset the accelerometer calibration module
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_reset_acccalib(void);

/************************************************************************************************************/
/**\name 									PEDOMETER DATA INTERFACE										*/
/************************************************************************************************************/
/*!
 * @brief   This API is used to set the step detection opmode.
 *          accel opmode should be enabled to enable the algorithm
 *          since it uses only accel data in the algorithm.
 *          As the Pedometer algorithm gives event for every change in steps
 *          this API should be called with Opmode = 1.By default, Pedometer feature
 * 			is OFF. To enable, this api can be called with param Opmode=1.
 * @param   Opmode -> to activate or deactivate step detection motion
                Opmode = 1 activate step detection motion
                Opmode = 0 deactivate step detection motion

 * @return  zero for success, non-zero failed
 * @retval  0 -> Success
 * @retval	1 -> Error
 */
BSX_S8  bsx_set_stepdetectionopmode(BSX_U8);

/*!
* @brief 	This API is used to get the stepdetection opmode.This API is called to 
*			know the step detection opmode is enabled or disabled
*			This API can be called only when BSX_PEDO_SUPPORT is ON
* @param  	*Opmodestatus -> to provide status of opmode
*            Opmodestatus = 1 step detection active
*            Opmodestatus = 0 step detection inactive.
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
 */
BSX_S8  bsx_get_stepdetectionopmode(BSX_U8*);

/*!
* @brief   This API is used to set the stepeventdetection opmode;BSX_PEDO_SUPPORT should be ON and internal step detection event 
*	will get enable based on this opmode. As the Pedometer algorithm will start 
*	detecting the event for every change in steps, this API should be called with event state = 1. 
*	If event state = 0((It will stop detecting the steps the last step count will be stored till 
*	system will call the start detection again).
*  @param   eventstate 
*           eventstate = 1 activate step detection motion
*           eventstate = 0 deactivate step detection motion
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
 */
BSX_S8  bsx_set_stepeventdetectionopmode(BSX_U8);

/*!
* @brief   This API is used to get the stepeventdetection opmode;
*			This API gives the status of step event detection opmode. 
* @param  *eventstatus -> pointer to get eventstatus
*          event status = 1 activate start step detection.
*          event status= 0 activate stop step detection .
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8  bsx_get_stepeventdetectionopmode(BSX_U8*);

/*!
 * @brief   This API is used to get the step detection robustness.
 *          The stepdetection robustness will tell the robustness
 *          (i.e. the steps detected by algorithm in robust or un robust).
 * @param   *robuststatus -> to get robuststatus
 *           robuststatus = 1 activate robustness
 *           robuststatus = 0 deactivate robustness
 * @return  zero for success, non-zero failed
 * @retval  0 -> Success
 * @retval	1 -> Error
 */
BSX_S8 bsx_get_stepdetectionrobustness(BSX_U8*);

/*!
 * @brief   This API is used to get the step detection status.
 *          This step detection status will Update for every step get detected from algorithm.
 *          The status will retain from the last step detection based on the datarate.
 *			This API can be called only when BSX_PEDO_SUPPORT is ON
 * @param   activity -> status variable
            activity = 1 new step get detected
            activity = 0 no new step get detected
 * @return  zero for success, non-zero failed
 * @retval  0 -> stationary
 * @retval	1 -> step detected
 */
BSX_S8  bsx_get_stepdetectionstatus(BSX_U8*);

/*!
 * @brief  This API is used to get the steps count.
 *          The  steps will update for every change in valid movements of a user.
 *          This steps count will be updated till the next time the system gets reboot.
 *			This API can be called only when BSX_PEDO_SUPPORT is ON
 * @param   steps -> it will return the number of steps detected by algorithm.
 * @return  zero for success, non-zero failed
 * @retval  0 -> Success
 * @retval	1 -> Error
 */
BSX_S8  bsx_get_stepcount(BSX_U64*);

/*!
 * @brief  This API is used to set the step detection mean constant
 *          This value helps to evaluate valid step count and Detection
 *			This API can be called only when BSX_PEDO_SUPPORT is ON 
 * @param   meanconst-> parameter to set meanconst
 * @return  zero for success, non-zero failed
 * @retval  0 -> Success
 * @retval	1 -> Error
 */
BSX_S8 bsx_set_stepdetectionmeanconst(BSX_F32 meanconst);

/*!
 * @brief  This API is used to get the step detection mean constant
 *			This API can be called only when BSX_PEDO_SUPPORT is ON 
 * @param   *meanconst-> parameter to get meanconst value
 * @return  zero for success, non-zero failed
 * @retval  0 -> Success
 * @retval	1 -> Error
 */
BSX_S8 bsx_get_stepdetectionmeanconst(BSX_F32* meanconst);

/*!
 * @brief  This API is used to set the step detection envmin variable
 *			This API can be called only when BSX_PEDO_SUPPORT is ON 
 * @param   envmin -> to set envmin varaiable
 * @return  zero for success, non-zero failed
 * @retval  0 -> Success
 * @retval	1 -> Error
 */
BSX_S8 bsx_set_stepdetectionenvmin(BSX_F32 envmin);

/*!
 * @brief  This API is used to get the step detection envmin variable
 *			This API can be called only when BSX_PEDO_SUPPORT is ON 
 * @param   envmin-> parameter to get envmin value
 * @return  zero for success, non-zero failed
 * @retval  0 -> Success
 * @retval	1 -> Error
 */
BSX_S8 bsx_get_stepdetectionenvmin(BSX_F32* envmin);

/*!
 * @brief  This API is used to set the step detection coefficient variable
 * @param   coefficient -> parameter to set step detection coefficient
 * @return  zero for success, non-zero failed
 * @retval  0 -> Success
 * @retval	1 -> Error
 */
BSX_S8 bsx_set_stepdetectioncoefficient(BSX_F32 coefficient);

/*!
 * @brief  This API is used to get the step detection coefficient variable
 *			This API can be called only when BSX_PEDO_SUPPORT is ON 
 * @param   *coefficient ->  to get step detection coefficient
 * @return  zero for success, non-zero failed
 * @retval  0 -> Success
 * @retval	1 -> Error
 */
BSX_S8 bsx_get_stepdetectioncoefficient(BSX_F32* coefficient);

/*!
 * @brief  This API is used to set the step detection mean step frequency variable
 * 			This step detection frequency value will be help in evaluating 
 * 			the valid time duration  for step detection & count.
 *			This API can be called only when BSX_PEDO_SUPPORT is ON 
 * @param   meanstepfreq-> parameter holding value of meanstepfreq
 * @return  zero for success, non-zero failed
 * @retval  0 -> Success
 * @retval	1 -> Error
 */
BSX_S8 bsx_set_stepdetectionmeanstepfreq(BSX_F32 meanstepfreq);
/*!
 * @brief  This API is used to get the step detection mean step frequency variable
 *   		This step detection frequency value will be help in evaluating the 
 *			valid time duration  for step detection & count.
 *			This API can be called only when BSX_PEDO_SUPPORT is ON 
 * @param   meanstepfreq-> parameter to get meanstepfreq value
 * @return  zero for success, non-zero failed
 * @retval  0 -> Success
 * @retval	1 -> Error
 */
BSX_S8 bsx_get_stepdetectionmeanstepfreq(BSX_F32* meanstepfreq);

/*!
 * @brief  This API is used to set the step detection steps to buffer;
 * 			This step detection frequency value will be help in evaluating 
 * 			the valid time duration  for step detection & count.
 *			This API can be called only when BSX_PEDO_SUPPORT is ON 
 * @param   nstepstobuff -> holds nstepstobuff to be set
 * @return  zero for success, non-zero failed
 * @retval  0 -> Success
 * @retval	1 -> Error
 */
BSX_S8 bsx_set_stepdetectionnstepstobuff(BSX_U32 nstepstobuff);

/*!
 * @brief  This API is used to get the step detection steps to buffer
 *			This step detection frequency value will be help in evaluating 
 *			the valid time duration  for step detection & count.
 *			This API can be called only when BSX_PEDO_SUPPORT is ON 
 * @param   nstepstobuff ->to get value of nstepstobuff
 * @return  zero for success, non-zero failed
 * @retval  0 -> Success
 * @retval	1 -> Error
 */
BSX_S8 bsx_get_stepdetectionnstepstobuff(BSX_U32* nstepstobuff);

/*!
* @brief  	Resets the stepcounter value to zero it will resets
*           the StepCount to initial vlaue as zero.
*			This API can be called only when BSX_PEDO_SUPPORT is ON 
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_reset_stepcount(void);

/************************************************************************************************************/
/**\name								ACCELEROMETER DATA INTERFACE										*/
/************************************************************************************************************/
/*!
* @brief  	Get the raw accelerometer data(x,y and z direction) in m/s^2
* @param  	*rawAccData: pointer to accelerometer raw data structure
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_accrawdata(ts_dataxyzf32*);

/*!
* @brief  	Get the corrected accelerometer data(x,y and z direction)
* 			in m/s^2. Corrected data = raw data – offset.
* @param  	corAccData 	-> accel data in ms^2
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_acccordata(ts_dataxyzf32*);


/*!
* @brief  	Get the filtered accelerometer data in ms^2
*			from digital filter 1
* @param  	filtaccdata -> pointer to accelerometer  data structure
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_accfiltdata1(ts_dataxyzf32*);

/*!
* @brief  	Get the filtered accelerometer data in ms^2
*		    from digital filter 2
* @param  	*filtAccData: pointer to accelerometer data structure
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_accfiltdata2(ts_dataxyzf32*);

/*!
* @brief  	Get the estimated offsets of the accelerometer in m/s^2
* @param  	*offset: pointer to structure having estimated offsets
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_accoffset(ts_dataxyzf32*);

/*!
* @brief  	Get the accelerometer calibration accuracy status
* @param  	*calibaccuracy -> current accelerometer calibration accuracy status
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_acccalibaccuracy(BSX_U8*);

/*!
* @brief  	Get the accelerometer raw data in mg
* @param  	*rawdata_mg -> current accelerometer raw data in mg
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_accrawdata_mg(ts_dataxyzf32* );

/*!
* @brief  	Get the accelerometer cor data in mg
* @param  	*cordata_mg -> current accelerometer cor data in mg
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_acccordata_mg(ts_dataxyzf32* );

/*!
* @brief  	Get the accelerometer filt data1 in mg
* @param  	*filtdata1_mg -> current accelerometer filter data1 in mg
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_accfiltdata1_mg(ts_dataxyzf32* );

/*!
* @brief  	Get the accelerometer filt data2 in mg
* @param  	*filtdata2_mg -> current accelerometer filter data2 in mg
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_accfiltdata2_mg(ts_dataxyzf32* );

/*!
* @brief  	Get the accelerometer offsets in mg
* @param  	*accoffsets_mg -> current accelerometer offsets in mg
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_accoffsets_mg(ts_dataxyzs32* );

/************************************************************************************************************/
/**\name									MAGNETOMETER API												*/
/************************************************************************************************************/
/*!
* @brief	Initialization of magnetometer modules with the settings for particular mag sensor.
* 			If NULL is passed,the default values(bmm050) are loaded.
* @param	p_magspec-> Pointer to magspec char array that holds settings for particular mag sensor
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_init_mag(BSX_U8*);

/*!
* @brief	Set the calling datarate for the magnetometer
* @param	magdatarate -> calling data rate of magnetometer\

*			permissible values
*				0 -> 1Hz
*				1 -> 5Hz
*				2 -> 6.25Hz
*				3 -> 10Hz
*				4 -> 12.5Hz
*				5 -> 20Hz
*				6 -> 25Hz
*				7 -> 40Hz
*				8 -> 50Hz
*				9 -> 100Hz
*				10 -> 125Hz
*				11 -> 200Hz
*				12 -> 400Hz
*				13 -> Invalid upper data rate
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_magdatarate(BSX_U8);

/*!
* @brief	based on datarate, gyrosyncdelay and gyro buffer size is updated.
* @brief	Allowed values for gyrosyncdelay are
*
* 				12.5Hz -> delay used is 7;
* 				20Hz   -> delay used is 4;
* 				25Hz   -> delay used is 3;
* @param	datarate : mag datarate

* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_updatefmcparam(BSX_U8 );

/*!
* @brief	Get the datarate for the magnetometer
* @param	dataRate -> parameter to get data rate of magnetometer  that is being set
*
*			Output values
*				0 -> 1Hz
*				1 -> 5Hz
*				2 -> 6.25Hz
*				3 -> 10Hz
*				4 -> 12.5Hz
*				5 -> 20Hz
*				6 -> 25Hz
*				7 -> 40Hz
*				8 -> 50Hz
*				9 -> 100Hz
*				10 -> 125Hz
*				11 -> 200Hz
*				12 -> 400Hz
*				13 -> Invalid upper data rate
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_magdatarate(BSX_U8*);

/*!
* @brief	Set the magnetomter calibration profile(calibration offset and status)
* @param	*calibprofile-> pointer to magnetometer calibration profile
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_magcalibprofile(ts_calibprofile*);

/*!
* @brief	Get the magnetomter calibration profile (includes offsets and accuracy status)
* @param	*calibprofile-> pointer to magnetometer calibration profile structure
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_magcalibprofile(ts_calibprofile*);

/*!
* @brief 	reset magnetometer calibration
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_reset_magcalib(void);

/************************************************************************************************************/
/**\name										MAGNETOMETER CALIB INTERFACE								*/
/************************************************************************************************************/
/*!
* @brief 	set magnetometer calibration process Noise. This API
* 			should be invoked only on special request from the
* 			customer. It is expected to use in daemon for specific
* 			customer requirement only. Input noise parameters should
* 			be provided by system engineers only. Parameters will
* 			be provided if required to meet specific customer requirement.
* @param 	processNoise -> pointer to processNoise vector
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_magcalib_processnoise( BSX_F32*);

/*!
* @brief 	Get magnetometer calibration process Noise. This
* 			API is invoked to get the process noise either
* 			default parameters or parameters set by using set
* 			API. It can be used to check the set parameters
* 			in algorithm.
* @param 	*processNoise -> pointer to processNoise vector
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_magcalib_processnoise( BSX_F32 *);

/************************************************************************************************************/
/**\name									       SOFT IRON CORRECTION INTERFACE								    */
/************************************************************************************************************/
/*!
* @brief  	Used to set the sensitivity correction matrix for soft iron
* 			correction.this API should be used with correct matrix as
* 			input else algorithm will behave unexpectedly. SIC matrix
* 			is predetermined either from SIC app, customer provided
* 			or other methods based on customer platform.
* @param  	correctMatrix : correction matrix 3x3 (pointer to float
* 			array of 9 elements i.e. 3 by 3 matrix)
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_softiron_correctionmatrix(ts_sensmatrix);

/*!
* @brief  	get the sensitivity correction matrix.
* 			This API can be used to retrieve the default
* 			SIC matrix (If it’s not set explicitly using set API)
* 			or set by using set API.
* @param  	*correctMatrix : pointer to correction matrix 3x3
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_softiron_correctionmatrix(ts_sensmatrix*);
/************************************************************************************************************/
/**\name									      ACCEL DYNAMIC FOR DISTORTION INTERFACE						    */
/************************************************************************************************************/

/*!
* @brief	Sets the accelerometer dynamic detection mode.
* 			This API is used to set the mode of distortion
* 			detection based on accelerometer dynamics. It
* 			can be made 0->1 when accel dynamics should be
* 			used for distortion detection and 1->0 when it
* 			is preferred not to use accel dynamics for distortion
* 			detection. This provision was provide for special
* 			usecase of coil testing when magnetic field is moved
* 			around and sensor is static, in this case the flag
* 			should be 1->0.
* @param	mode -> Enable/Disable mode
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_accdyn_distdetmode(BSX_U8 );

/*!
* @brief	gets the accelerometer dynamic detection mode
* @param	mode -> pointer to mode (Enable/Disable mode status)
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_accdyn_distdetmode(BSX_U8 *);
/************************************************************************************************************/
/**\name										MAGNETOMETER DATA INTERFACE									*/
/************************************************************************************************************/

/*!
* @brief 	Get the raw 3-axis magnetometer data in MicroTesla
* @param  	*rawmagdata	-> mag data in MicroTesla
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_magrawdata(ts_dataxyzf32*);

/*!
* @brief  	Get the 3-axis corrected magnetometer data in MicroTesla
*			Corrected = raw – offset.
* @param  	*corMagData	-> mag data in MicroTesla
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_magcordata(ts_dataxyzf32*);

/*!
* @brief  	Get the filtered 3-axis magnetometer data in MicroTesla
* 			from digital filter 1
* @param  	*filtMagData -> mag data in MicroTesla
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_magfiltdata1(ts_dataxyzf32*);

/*!
* @brief  	Get the filtered 3-axis magnetometer data in MicroTesla
* 			from digital filter 2
* @param  	*filtMagData: mag data in MicroTesla
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_magfiltdata2(ts_dataxyzf32*);

/*!
* @brief  	Get the estimated parameter of the magnetometer
* @param 	offset -> estimated offsets in MicroTesla
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_magoffsets(ts_dataxyzf32*);

/*!
* @brief  	Get the magnetometer calibration accuracy status
* @param  	calibaccuracy	-> current magnetometer calibration accuracy status
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_magcalibaccuracy(BSX_U8 *);

/*!
* @brief  	Get the soft iron correction data.
* 			This API is the interface for magnetometer soft iron corrected(using SIC matrix) and uncalibrated data
* 			from generic data preprocessing. Data interface is only for ndof and compass module.
* @param  	sicdata -> pointer to corrected data
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_magsoftironcorrecteddata(ts_dataxyzf32* );

/*!
* @brief  	get the soft iron correction data in lsb.
* 			This API is the interface for magnetometer soft iron corrected(using SIC matrix) and uncalibrated data
* 			from generic data preprocessing. Data interface is only for ndof and compass module.
* @param  	sicdatalsb -> pointer to corrected data microtesla
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_magsoftironcorrecteddata_lsb(ts_dataxyzf32*);

/************************************************************************************************************/
/**\name									GYROSCOPE API													*/
/************************************************************************************************************/

/*!
* @brief	Initialization of gyroscope modules with the settings of particular gyro sensor. Default values(bmg160)
* @param	p_gyrospec-> Pointer to gyrospec char array that holds settings for particular gyro sensor
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_init_gyro(BSX_U8*);

/*!
* @brief	Set the measurement range for gyroscope
* @param	measrange -> measurement range of gyroscope
*				Permissible Range
*					0 -> 2048 Dps
*					1 -> 2000 Dps
*					2 -> 1000 Dps
*					3 -> 500 Dps
*					4 -> 250 Dps
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_gyrorange(BSX_U8);

/*!
* @brief	Get the measurement range for gyroscope
* @param	*measrange -> pointer to measurement range of gyroscope
*				Output Range
*					0 -> 2048 Dps
*					1 -> 2000 Dps
*					2 -> 1000 Dps
*					3 -> 500 Dps
*					4 -> 250 Dps
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_gyrorange(BSX_U8*);

/*!
* @brief	Set the calling datarate for the gyroscope
* @param	datarate-> datarate of gyroscope
*
*				permissible values
*				0 -> 1Hz
*				1 -> 5Hz
*				2 -> 6.25Hz
*				3 -> 10Hz
*				4 -> 12.5Hz
*				5 -> 20Hz
*				6 -> 25Hz
*				7 -> 40Hz
*				8 -> 50Hz
*				9 -> 100Hz
*				10 -> 125Hz
*				11 -> 200Hz
*				12 -> 400Hz
*				13 -> Invalid upper data rate
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/

BSX_S8 bsx_set_gyrodatarate(BSX_U8);

/*!
* @brief	Get the calling datarate for the gyroscope
* @param	*datarate-> pointer to datarate of gyroscope
*
*				permissible values
*				0 -> 1Hz
*				1 -> 5Hz
*				2 -> 6.25Hz
*				3 -> 10Hz
*				4 -> 12.5Hz
*				5 -> 20Hz
*				6 -> 25Hz
*				7 -> 40Hz
*				8 -> 50Hz
*				9 -> 100Hz
*				10 -> 125Hz
*				11 -> 200Hz
*				12 -> 400Hz
*				13 -> Invalid upper data rate
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_gyrodatarate(BSX_U8*);

/*!
* @brief	Set the gyroscope calibration profile(includes offsets and accuracy status)
* @param	calibprofile->  gyroscope calibration profile structure variable
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_gyrocalibprofile(ts_calibprofile*);

/*!
* @brief	Get the gyroscope calibration profile (includes offsets and accuracy status)
* @param	*calibprofile-> pointer to gyroscope calibration profile structure
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_gyrocalibprofile(ts_calibprofile*);

/*!
* @brief 	reset gyroscope calibration
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_reset_gyrocalib(void);

/************************************************************************************************************/
/**\name								GYROSCOPE DATA INTERFACE											*/
/************************************************************************************************************/

/*!
* @brief  	Get the raw 3-axis gryoscope data in degrees/sec
* @param  	rawgyrodata 	-> gyro data in degrees/sec
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_gyrorawdata_dps(ts_dataxyzf32*);

/*!
* @brief  	Get the raw 3-axis gryoscope data in radians/sec
* @param  	rawgyrodata 	-> gyro data in radians/sec
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_gyrorawdata_rps(ts_dataxyzf32*);

/*!
* @brief  	Get the corrected 3-axis gryoscope data in degrees/sec
* @param  	corgyrodata 	-> gyro data in degrees/sec
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_gyrocordata_dps(ts_dataxyzf32*);

/*!
* @brief  	Get the raw 3-axis gryoscope data in radians/sec
* @param  	corgyrodata 	-> gyro data in radians/sec
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_gyrocordata_rps(ts_dataxyzf32*);

/*!
* @brief  	Get filtered 3-axis gyroscope data in degrees/sec
*			from digital filter 1
* @param  	filtgyrodata 	-> gyro data in degrees/sec
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_gyrofiltdata1_dps(ts_dataxyzf32*);

/*!
* @brief  	Get filtered 3-axis gyroscope data in radians/sec
*			from digital filter 1
* @param  	filtgyrodata 	-> gyro data in radians/sec
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_gyrofiltdata1_rps(ts_dataxyzf32*);

/*!
* @brief  	Get filtered 3-axis gyroscope data in degrees/sec
*			from digital filter 2
* @param  	filtgyrodata 	-> gyro data in degrees/sec
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_gyrofiltdata2_dps(ts_dataxyzf32*);

/*!
* @brief  	Get filtered 3-axis gyroscope data in radians/sec
*			from digital filter 2
* @param  	filtgyrodata 	-> gyro data in radians/sec
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_gyrofiltdata2_rps(ts_dataxyzf32*);

/*!
* @brief  	Get the estimated parameter of the gyroscope
* @param  	offset 	-> estimated offsets in degrees per sec
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_gyrooffset_dps(ts_dataxyzf32*);

/*!
* @brief  	Get the estimated parameter of the gyroscope
* @param  	offset 	-> estimated offsets in radians per sec
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_gyrooffset_rps(ts_dataxyzf32*);

/*!
* @brief  	Get the gyroscope calibration accuracy status
* @param  	*gyrocalibaccuracy 	-> current gyroscope calibration accuracy status
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_gyrocalibaccuracy(BSX_U8*);

/************************************************************************************************************/
/**\name							ORIENTATION PROCESSING API												*/
/************************************************************************************************************/

/*!
* @brief	Initialization of orientation modules
*			For compass mode -> compass module is initialized
*			For IMU or NDOF mode -> NDOF module
*			For ALL mode -> compass and NDOF module
* @param	p_usecaseconfig -> Pointer to usecase char array that holds settings for particular usecase
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_init_orient(BSX_U8*);

/*!
* @brief	Reset of Orientation module
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_reset_orient(void);

/*!
* @brief	Restart of Orientation module
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_restart_orient(void);

/*!
* @brief	Heading base threshold for calcuting accuracy status
*			Accuracy levels are defined as
*
*			Status 0: Unreliable
*			Status 1: Low
*			Status 2: Medium
*			Status 3: High
* @param	basethresholddeg ->parameter to set base threshold
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_HeadingAccuracyBaseThresh(BSX_F32 );
/************************************************************************************************************/
/**\name								ORIENTATION DATA INTERFACE											*/
/************************************************************************************************************/

/*!
* @brief  	Get the orientation quaternion data
* @param  	*quatData -> quaternion data (w,x,y,z)
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_orientdata_quat(ts_dataquatf32 *);

/*!
* @brief  	Get the orientation quaternion data in lsb(scaling factor 2^14=16384)
* @param  	quatDataLsb 	->  quaternion data (w,x,y,z)
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_orientdata_quat_lsb(ts_dataquat *);

/*!
* @brief  	Get the orientation euler data(heading, pitch and roll) in degrees
* @param  	*eulerData -> euler data (h,p,r)
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_orientdata_euler_deg(ts_dataeulerf32 *);

/*!
* @brief  	Get the orientation euler data(heading, pitch and roll) in radians
* @param  	eulerDataRad 	-> euler data (h,p,r)
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_orientdata_euler_rad(ts_dataeulerf32 *);


/*!
* @brief  	Get the imu orientation quaternion data
* @param  	*imuquatData -> quaternion data (w,x,y,z)
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_imuorientdata_quat(ts_dataquatf32 *);


/*!
* @brief  	Get the imu orientation quaternion data in lsb
* @param  	*quatDataLsb -> quaternion data (w,x,y,z)
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_imuorientdata_quat_lsb(ts_dataquat *);

/*!
* @brief  	Get the imu orientation euler data(heading, pitch and roll) in degrees
* @param  	imueulerDatadeg -> euler data (h,p,r)
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_imuorientdata_euler_deg(ts_dataeulerf32 *);

/*!
* @brief  	Get the imu orientation euler data(heading, pitch and roll) in radians
* @param  	imueulerDataRad ->  pointer to get imu euler dat in rad(h,p,r)
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_imuorientdata_euler_rad(ts_dataeulerf32 *);

/*!
* @brief  	Get the orientation data accuracy status
* @param  	datastatus 	-> pointer to orientation accuracy status as 0,1,2,3: Which 3 indicates 
*			heading is close to true magnetic heading and similarly 0 indicates unreliable.
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_orient_datastatus( BSX_U8* );

/*!
* @brief  	Get the heading data accuracy in radians
* @brief    Heading status refers to accuracy level of orientation data(from library) from
* @brief	true heading calculation. This comparison is done with magnetic data coupling.
* @param 	*headingaccrad -> Pointer to read the error in heading in radians
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_headingaccuracy_rad( BSX_F32* );

/*!
* @brief  	Get the heading data accuracy in degree
* @brief    Heading status refers to accuracy level of orientation data(from library) from
* @brief	true heading calculation. This comparison is done with magnetic data coupling.
* @param 	*headingaccdeg -> Pointer to read the error in heading in degrees
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_headingaccuracy_deg( BSX_F32* );

/************************************************************************************************************/
/**\name							COMPASS CONFIG  INTERFACE    											*/
/************************************************************************************************************/
/*!
* @brief	Get the filter mode for compass and M4G
*
*		Permissible values
*		0 -> Bypass mode. No filtering
*		1 -> Low. Low orientation filtering for high dynamic level
*		2 -> Medium. Medium orientation filtering for medium dynamic level
*		3-> High. High orientation filtering for low dynamic level
* @param	mode -> filter mode for compass
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_compass_filtermode(BSX_U8*);

/*!
* @brief	Set the magnetometer noise threshold for compass and M4G
* @param	magnoise-> magnetometer noise threshold
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_compass_magnoise( BSX_F32);

/*!
* @brief	Set the filter noise parameters
* @param	basecoef	-> value to set base coefficient
* @param	dyncoef		-> value to set dynamic coefficient
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_compass_magfilterparam(BSX_F32,BSX_F32);


//BSX_S8 bsx_set_compass_filternoise(BSX_F32,BSX_F32);

/*!
* @brief	Set the accelerometer noise threshold for compass and M4G
* @param	accnoisethresh	-> accelerometer noise threshold
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_compass_accel_filternoise(BSX_F32);

/*!
* @brief	Get the accelerometer and magnetometer noise threshold for compass and M4G
* @param	*accnoisethresh	-> accelerometer noise threshold
* @param	*magnoisethresh	-> magnetometer noise threshold
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_compass_filternoise(BSX_F32*,BSX_F32*);/* TODO: check the name */


//BSX_S8 bsx_set_compass_filterparam(BSX_F32, BSX_F32);

/*!
* @brief	Set the accelerometer filter noise parameters
* @param	accelbasecoef -> value to set accelerometer base coefficient
* @param	acceldyncoef  -> value to set accelerometer dynamic coefficient
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_compass_accel_filterparam(BSX_F32, BSX_F32);

/*!
* @brief	Get the filter noise param for compass and M4G
* @param	accbasecoef	-> base coefficient for accelerometer
* @param	accdyncoef	-> dynamic coefficient for accelerometer
* @param	magbasecoef	-> base coefficient for Magnetometer
* @param    magdyncoef  -> dynamic coefficient for magnetometer
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_compass_filterparam(BSX_F32*, BSX_F32*,BSX_F32*, BSX_F32*); /* TODO: check the name */


/*!
* @brief	Set the accelerometer dynamic threshold for  M4G
* @param	accdynthres	-> accelerometer dynamic threshold
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_m4g_accdynthreshold( BSX_U8);

/*!
* @brief	Get the accelerometer dynamic threshold for  M4G
* @param	accdynthres	-> accelerometer dynamic threshold
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_m4g_accdynthreshold( BSX_U8*);
/************************************************************************************************************/
/**\name								GRAVITY VECTOR DATA INTERFACE										*/
/************************************************************************************************************/

/*!
* @brief  	Get the gravity vector data in ms^2
* @param  	*gravity -> gravity vector data in ms^2
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_gravity(ts_dataxyzf32 *);

/************************************************************************************************************/
/**\name							LINEAR ACCELERATION DATA INTERFACE										*/
/************************************************************************************************************/

/*!
* @brief  	Get the linear acceleration data in ms^2
* @param  	linearAcc 	-> linear accel data in ms^2
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_linearacceleration(ts_dataxyzf32 *);
/************************************************************************************************************/
/**\name									  POWER MODES INTERFACE										    */
/************************************************************************************************************/


/*!
* @brief 	Sets the working operation mode. Input is a structure of one
* 			element of BSX_U32 type and contains encoded operation mode.
* @param 	workingModes ->Pointer to working mode
*			  e.g.
*
*        		BSX_WORKINGMODE_MAGONLY  -> 98308;
*        		BSX_WORKINGMODE_ACCMAG   -> 98309;
*        		BSX_WORKINGMODE_ACCGYRO  -> 524305;
*        		BSX_WORKINGMODE_IMUPLUS  -> 525329;
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_workingmode(ts_workingModes*);

/*!
* @brief 	Get the sensor switch list for the current working mode.
* 			HWsensorSwitchList  is a structure of three elements
* 			BSX_U8 acc,BSX_U8 mag,BSX_U8 gyro.This function gets
* 			the status of these three alements for the
* 			given working mode.e.g. if working mode
* 			is BSX_WORKINGMODE_MAGONLY then acc = 0,mag = 1,gyro = 0;
* @param 	*workingModes -> Pointer to working mode constants
* @param	*HWsensorSwitchList -> Pointer to hardware switch list
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/      
BSX_S8 bsx_get_hwdependency(ts_workingModes,ts_HWsensorSwitchList* );

/************************************************************************************************************/
/**\name								Significant Motion API												*/
/************************************************************************************************************/

/*!
* @brief 	This API is used to set the significant motion opmode.
* 			Compiler switch constant BSX_SIGNIFICANTMOTION_SUPPORT
* 			should be declared and accel opmode should be enabled
* 			to enable the algorithm since it uses only accel data
* 			in the algorithm. As the significant motion algorithm
* 			gives event one time only when motion is detected, after
* 			that it is disabled, hence to restart the detection
* 			this API should be called with mode = 1.
* 			Note: If the library is initialized for the first time
* 			with BSX_SIGNIFICANTMOTION_SUPPORT enabled the algorithm
* 			is already enabled no need to use set API
* @param	mode-> to activate/deactivate motion
*				mode = 1 activate significant motion
*				mode = 0 deactivate significant motion
*			when mode is set to 1, the significant motion
*			initializes to Initial values
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8  bsx_set_significantmotiondetectionopmode(BSX_U16);

/*!
* @brief 	This API is used to get the significant motion opmode
* @param	*mode -> to get the significant motion opmode
*				mode = 1 significant motion active
*				mode = 0 significant motion inactive
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8  bsx_get_significantmotiondetectionopmode(BSX_U16*);

/*!
* @brief 	This API is used to get the significant motion detection status
* 			once the motion is detected the significant motion
* 			is deactivated. algorithm can be activated by calling 
* 			bsx_set_significantmotiondetectionopmode API.
* @param	*status [out] 
*				status = 1 motion detected
*				status >=0 no motion detected
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8  bsx_get_significantmotiondetectionstatus(BSX_U16*);

/************************************************************************************************************/
/**\name									FLIP GESTURE API												*/
/************************************************************************************************************/

/*!
* @brief 	returns flip gesture opmode
* @param	*opmode -> pointer to get flip gesture operation mode that is being set
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_flipgesture_opmode(BSX_U8* );

/*!
* @brief 	sets flip gesture opmode
*
*				opmode <= 1 implies value set to s_bsxfusionlibrary.flipgestureOpmode structure variable
*				opmode > 1, returns error state (BSX_STATE_ERROR)
* @param	opmode -> variable holding the value to be set
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_flipgesture_opmode(BSX_U8 );

/*!
* @brief 	Gets the threshold of faceUp and faceDown angle
* @param	faceup -> Angle for faceup
* @param	facedown -> Angle for facedown;
*			Expected values:
*			100 < faceup <170
*			10 < facedown < 80
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_flipgesture_angle(BSX_F32* ,BSX_F32* );

/*!
* @brief 	sets flip gesture angle
* @param	faceUp -> Angle for faceup
* @param	faceDown -> Angle for facedown
*			Range ->values should be between specified minimum and maximum limit,
*			else values wont be set
*
*				 Minimum angle limit for FaceUp      100;
*				 Maximum angle limit for FaceUp      170;
*				 Minimum angle limit for Facedown    10;
*				 Maximum angle limit for Facedown    80;
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_flipgesture_angle(BSX_F32 ,BSX_F32 );

/*!
* @brief 	Get the detect time in mili seconds for flip gesture module
* @param	dettime : Detection time
*			300 ms < Time < 2000 ms
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_flipgesture_detecttime(BSX_U16* );

/*!
* @brief 	To set the detect time for flip gesture module in milliseconds
* @param	time : Detection time
*			300 ms < Time < 2000 ms
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_flipgesture_detecttime(BSX_U16 );

/*!
* @brief 	This API gives the calibration tick;– It is an external task calling tick which will be 
*			set at the end of bsx_dopreprocess , and is used as a trigger input for calibration.
* @param	calibtick -> pointer to get calib tick
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_calibrationcalltick(BSX_U8* );

/*!
* @brief 	This Api gives the Usecase tick;It is an external task calling tick which will be set at the
*			 end of bsx_dousecase, and is used as a trigger input for usecase processing.
* @param	usecasetick -> pointer to get usecase tick
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_usecasecalltick(BSX_U8* );

/*!
* @brief 	returns flip gesture status
* @param	status: Detection Status
*				status = 0 implies facing is unknown
*				status = 1 implies facing Up
*				status = 2 implies facing Down
*				status = 3 implies facing Neutral
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_flipgesture_status(BSX_U8* );

/*!
* @brief	This API is used to get the co-ordinate system (WIN 8 or Android) which has been set already
* @param	*coordinatesys -> coordinate systems
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_orientcoordinatesystem(BSX_U8* );

/*!
* @brief	Sets orient coordinate system ( this api sets co - ordinate system corresponding to win 8 or android that has been passed as argument)
* @param	coordinatesys -> parameter to set ANDROID or WIN8 coordinate system
*
* 			coordinatesys -1 -> ANDROID (default)
* 			coordinatesys -2 -> WIN8
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_orientcoordinatesystem(BSX_U8 );

/*!
* @brief  	Get rotation matrix
* @param  	*rotmatrix 	-> pointer to get orientation rotation matrix
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_orientrotationmatrix( BSX_F32* );

/*!
 * @brief calcualtes orient accuracy from accel ,mag and gyro status
 * @param accStatus -> to get accel accuracy status
 * @param magStatus -> to get mag accuracy status
 * @param gyroStatus -> to get gyro accuracy status
 * @return   zero for success, non-zero failed
 * @retval  0 -> Success
 * @retval	1 -> Error
 */
BSX_U8 bsx_calcorientaccuracy(BSX_U8 accStatus,BSX_U8 magStatus,BSX_U8 gyroStatus);

/*!
* @brief  	Get the geo magnetic rotationvector(compass rotation quat)
* @param  	*georotationquat -> Orientation quaternion data (w,x,y,z)
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_georotationvector_quat(ts_dataquatf32*);

/*!
* @brief  	Get the geo magnetic rotation vector heading data accuracy in radians
* @brief    Heading status refers to accuracy level of orientation data(from library) from
* @brief	true heading calculation. This comparison is done with magnetic data coupling.
* @param 	*headingaccrad -> Pointer to read the error in heading in radians
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_geoheadingaccuracy_rad( BSX_F32*);

/*!
* @brief  	Get the geo magnetic rotation vector heading data accuracy in Degrees
* @brief    Heading status refers to accuracy level of orientation data(from library) from
* @brief	true heading calculation. This comparison is done with magnetic data coupling.
* @param 	*headingaccdeg -> Pointer to read the error in heading in Degrees
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_geoheadingaccuracy_deg( BSX_F32*);

/************************************************************************************************************/
/**\name								PRE-FILTER PARAMETERS API										    */
/************************************************************************************************************/


/*!
* @brief	Set the heading sensitivity for compass and M4G
* 				Permissible values
*					0 - 5: sensitivity mode values of 0 to 5 is defined
* 		If sensitivity is “0”, there will be a lowest heading sensitivity but have high stability level. If high heading stability 
*		is desired and heading response is not of importance, this value can be set.
* 		If sensitivity is “5”, highest heading sensitivity with low stability. 
*		If high heading sensitivity is desired and small heading jitter can be acceptable, this mode can be set
* @param	 sensitivity_val -> sensitivity mode for compass
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_compass_headingsensitivity(BSX_U8);

/*!
* @brief	Set the orientation correction speed for NDOF
* 				Permissible values
*					0 - 5: correction speed values of 0 to 5 is defined
*
*			speed = 0 => slow orientation correction with less jitter noise.
*			speed = 5 => fast orientation correction with more jitter noise.
* @param	speed_val -> orientation correction speed for NDOF
* 				Permissible values
*					0 - 5: correction speed values of 0 to 5 is defined
*			speed = 0 => slow orientation correction with less jitter noise.
*			speed = 5 => fast orientation correction with more jitter noise.
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_ndof_orientcorrectionspeed(BSX_U8);

/*!
* @brief	Set the Magnetic data filter mode
* 				Permissible values: 0 - 5;
*
*			mode = 0 -> lowest filtering, high noise but better response time.
*			mode = 5 -> Highest filtering, low noise but slow response time.
* @param	mode -> mode for magnetic filter				
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_magfiltermode(BSX_U8);

/*!
* @brief	Set the Magnetic calibration accuracy status sensitivity
* 				Permissible values
*					0 - 5: sensitivity values of 0 to 5 is defined
*
* 			sensitivity = 0 -> lowest magnetic calibration accuracy sensitivity with high accuracy status stability.
*			sensitivity = 5 -> highest magnetic calibration accuracy sensitvity with low accuracy status stability.

* @param	sensitivity -> sensitivity mode for magnetic calibration accuracy status
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_magcalibacc_sensitivity(BSX_U8);

/*!
* @brief	Set the Magnetic calibration speed
* 				Permissible values
*					0 - 5: correction speed values of 0 to 5 is defined
*
*			speed = 0 -> slow magnetic calibration speed, high accuracy after calibration accuracy level 3;
*			speed = 5 -> fast magnetic calibration speed, low heading accuracy after calibration accuracy level 3.
* @param	speed -> magnetic calibration speed
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_magcalibrationspeed(BSX_U8);

/*!
* @brief	Set the Magnetic calibration accuracy auto recovery mode
* @param	mode -> auto recovery mode for magnetic calibration accuracy
* 				Permissible values [0,1]
*					0:  Auto recovery mode disabled
*					1:  Auto recovery mode Enabled
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_set_compass_magcalibaccautorecmode(BSX_U8);

/*!
* @brief  	 Get the geo magnetic rotationvector values in lsb
* @param  	*georotationquatlsb -> Orientation quaternion data (w,x,y,z)
* @return   zero for success, non-zero failed
* @retval   0 -> Success
* @retval	1 -> Error
*/
BSX_S8 bsx_get_georotationvector_quat_lsb(ts_dataquat*);

#endif


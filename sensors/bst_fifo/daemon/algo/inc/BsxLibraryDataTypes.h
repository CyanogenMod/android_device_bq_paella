#ifndef __BSXLIBRARYDATATYPES_H__
#define __BSXLIBRARYDATATYPES_H__
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
* @file      bsxlibrarydatatypes.h
* @date      2013/02/12 created
*
* @brief
* This file provides datatypes used by library
*/

/************************************************************************************************************/
/*												INCLUDES													*/
/************************************************************************************************************/

#include <limits.h>
#include "BsxLibraryConstants.h"
#include "BsxLibraryCalibConstants.h"
#include "BsxLibraryErrorConstants.h"
#include <stdlib.h>
#include <stdint.h>

/************************************************************************************************************/
/*												TYPE DEFINITIONS										 	*/
/************************************************************************************************************/

/** \def Basic Datatypes */
#if __STDC_VERSION__ >= 199901L
  /** C99 standard */
    typedef int16_t			BSX_S16;  /**< signed short */
    typedef	uint16_t		BSX_U16;  /**<unsigned short */
    typedef int32_t		    BSX_S32;  /**<signed int */
    typedef uint32_t	    BSX_U32;  /**<unsigned int */

    typedef int8_t			BSX_S8;  /**< signed char */ 
    typedef uint8_t			BSX_U8;  /**< unsigned char */
    typedef int64_t			BSX_S64; /**< signed long long */ 
    typedef uint64_t		BSX_U64; /**< unsigned long long*/
    typedef uint8_t			BSX_BIT; /**< unsigned char */
    typedef uint32_t		BSX_BOOL;/**<unsigned int */
#else
    /* C89 standard */
    /* find correct data type for signed 16 bit variables */
#if USHRT_MAX == 0xFFFF
    typedef unsigned short BSX_U16; 			/**< 16 bit achieved with short */
    typedef signed short BSX_S16;
#elif UINT_MAX == 0xFFFF
    typedef unsigned int BSX_U16;  				/**< 16 bit achieved with int */
    typedef signed int BSX_S16;
#else
#error U16 and S16 could not be defined automatically, please do so manually
#endif
    /* find correct data type for signed 32 bit variables */
#if INT_MAX == 0x7FFFFFFF
    typedef signed int BSX_S32; 				/**< 32 bit achieved with int */
    typedef unsigned int BSX_U32;
#elif LONG_MAX == 0x7FFFFFFF
    typedef signed long int BSX_S32;       		/**< 32 bit achieved with long int */
    typedef unsigned long int BSX_U32; 			/**< 32 bit achieved with long int */
#else
#error S32 could not be defined automatically, please do so manually
#endif
    typedef signed char					BSX_S8; /**< signed char */
    typedef unsigned char				BSX_U8; /**< unsigned char*/
    typedef signed long long			BSX_S64; /**< signed long long */
    typedef unsigned long long			BSX_U64; /**< unsigned long long*/
    typedef unsigned char				BSX_BIT; /**< unsigned char */
    typedef unsigned int				BSX_BOOL; /**<unsigned int */
#endif

/** \def Basic Datatypes */

typedef float						BSX_F32; /**< float*/
typedef double						BSX_F64; /**< double*/


/**\name Basic numbers in use */
#define	BSX_NULL					(BSX_U8)0  /**< zero*/
#define BSX_ZERO					(0U)	   /**< zero in unsigned*/
#define BSX_ONE						(1U)	   /**< one in unsigned*/
#define BSX_TWO						(2U)	   /**< two in unsigned*/
#define BSX_THREE					(3U)		/**< three in unsigned*/
#define BSX_FOUR					(4U)		/**< four in unsigned*/
#define BSX_FIVE					(5U)		/**< five in unsigned*/
#define BSX_SIX						(6U)		/**< six in unsigned*/
#define BSX_SEVEN					(7U)		/**< seven in unsigned*/
#define BSX_EIGHT					(8U)		/**< eight in unsigned*/
#define BSX_NINE					(9U)		/**< nine in unsigned*/
#define BSX_TEN						(10U)		/**< ten in unsigned*/
#define BSX_ELEVEN					(11U)		/**< eleven in unsigned*/
#define BSX_TWELVE					(12U)		/**< twelve in unsigned*/
#define BSX_THIRTEEN				(13U)		/**< thirteen in unsigned*/
#define BSX_SIXTEEN					(16U)		/**< sixteen in unsigned*/
#define BSX_TWENTYFOUR				(24U)		/**< twentyfour in unsigned*/
#define BSX_THIRTYTWO				(32U)		/**< thirtytwo in unsigned*/
#define BSX_SIXTYFOUR				(64U)		/**< sixtyfour in unsigned*/
#define BSX_HUNDRED					(100)		/**< hundred in unsigned*/
#define BSX_ONETWENTYSEVEN			(127)		/**< one twenty seven in unsigned*/
#define BSX_TWOFIFTYFIVE			(255)		/**< two fifty five in unsigned*/
#define BSX_TWOFIFTYSIX				(256)		/**< two fifty six in unsigned*/

#define BSX_ZERO_S					(0)			/**< zero in signed*/
#define BSX_ONE_S					(1)			/**< one in signed*/
#define BSX_TWO_S					(2)			/**< two in signed*/
#define BSX_THREE_S					(3)			/**< three in signed*/
#define BSX_FOUR_S					(4)			/**< four in signed*/
#define BSX_FIVE_S					(5)			/**< five in signed*/
#define BSX_SIX_S					(6)			/**< six in signed*/
#define BSX_SEVEN_S					(7)			/**< seven in signed*/
#define BSX_EIGHT_S					(8)			/**< eight in signed*/
#define BSX_NINE_S					(9)			/**< nine in signed*/
#define BSX_TEN_S					(10)		/**< ten in signed*/
#define BSX_ELEVEN_S				(11)		/**< eleven in signed*/
#define BSX_TWELVE_S				(12)		/**< twelve in signed*/
#define BSX_SIXTEEN_S				(16)		/**< sixteen in signed*/
#define BSX_TWENTYFOUR_S			(24)		/**< twentyfour in signed*/
#define BSX_THIRTYTWO_S				(32)		/**< thirtytwo in signed*/
#define BSX_SIXTYFOUR_S				(64)		/**< sixtyfour in signed*/
#define BSX_HUNDRED_S				(100)		/**< hundred in signed*/
#define BSX_ONETWENTYSEVEN_S		(127)		/**< one twenty seven in signed*/
#define BSX_TWOFIFTYFIVE_S			(255)		/**< two fifty five in signed*/
#define BSX_TWOFIFTYSIX_S			(256)		/**< two fifty six in signed*/


#define BSX_ZERO_F					(0.0f)			/**< zero in float*/
#define BSX_ONE_F					(1.0f)			/**< one in float*/
#define BSX_TWO_F					(2.0f)			/**< two in float*/
#define BSX_THREE_F					(3.0f)			/**< three in float*/
#define BSX_FOUR_F					(4.0f)			/**< four in float*/
#define BSX_FIVE_F					(5.0f)			/**< five in float*/
#define BSX_SIX_F					(6.0f)			/**< six in float*/
#define BSX_SEVEN_F					(7.0f)			/**< seven in float*/
#define BSX_EIGHT_F					(8.0f)			/**< eight in float*/
#define BSX_NINE_F					(9.0f)			/**< nine in float*/
#define BSX_TEN_F					(10.0f)			/**< ten in float*/
#define BSX_ELEVEN_F				(11.0f)			/**< eleven in float*/
#define BSX_TWELVE_F				(12.0f)			/**< twelve in float*/
#define BSX_SIXTEEN_F				(16.0f)			/**< sixteen in float*/
#define BSX_TWENTYFOUR_F			(24.0f)			/**< twentyfour in float*/
#define BSX_THIRTYTWO_F				(32.0f)			/**< thirtytwo in float*/
#define BSX_SIXTYFOUR_F				(64.0f)			/**< sixtyfour in float*/
#define BSX_HUNDRED_F				(100.0f)			/**< hundred in float*/
#define BSX_ONETWENTYSEVEN_F		(127.0f)			/**< one twenty seven in float*/
#define BSX_TWOFIFTYFIVE_F			(255.0f)			/**< two fifty five in float*/
#define BSX_TWOFIFTYSIX_F			(256.0f)			/**< two fifty six in float*/

/**\name Standard Conversion Factors */
#define BSX_CONVFACTOR_UNIT2MILLI	(1e3f)		/**< unit to milli */
#define BSX_CONVFACTOR_UNIT2MICRO	(1e6f)		/**< unit to micro */
#define BSX_CONVFACTOR_UNIT2NANO	(1e9f)		/**< unit to nano  */
#define BSX_CONVFACTOR_RAD2DEG		(57.295647f)  /**< radiant to degree conversion factor (180/3.1416)*/
#define BSX_CONVFACTOR_DEG2RAD		(0.0175f)		/**< degree to radiant conversion factor (3.1416/180)*/
#define BSX_NORMFACTOR				(0.008726646259722f) /**< pi/(180*2)*/
#define BSX_CONVERSIONFACTOR		(0.008726666666667f) /**<(BSX_PI/(180*2))*/

/**\name Standard Values */
#define BSX_PI						(3.1416f)		/**< Ratio of circle's circumference to its diameter */
#define C_LSB2uT_F32X				(0.25f)			/**< conversion factor - lsb to ut */
#define C_uT2LSB_F32X				(4.0f)			/**< conversion factor - uT to lsb (1/0.25f)*/
/**\name Basic Status/Controls */
#define BSX_DEACTIVATE				(0U)			/**< to deactivate any mode*/
#define BSX_ACTIVATE				(1U)			/**< to activate any mode*/

#define BSX_FAILURE					(0U)			/**< denotes failure case */
#define BSX_SUCCESS					(1U)			/**< denotes success case */

#define BSX_DISABLE					(0U)			/**< to disable any mode */
#define BSX_ENABLE					(1U)			/**< to enable any mode */

#define BSX_FALSE					(0U)			/**< denotes false scenario*/
#define BSX_TRUE					(1U)			/**< denotes true */

#define BSX_RESET					(0U)			/**< denotes reset*/
#define BSX_SET						(1U)			/**< denotes set */

/************************************************************************************************************/
/*												STRUCTURES DEFINITION										*/
/************************************************************************************************************/
/** \struct ts_version
        \brief Version format
*/
typedef struct
{
	BSX_S16 major;		/**< major version */
	BSX_S16 minor;		/**< minor version */
	BSX_S16 majorbugFix;		/**< major bux fix version */
	BSX_S16 minorbugFix;		/**< minor bux fix version */
}ts_version;

/** \struct ts_dataxyz
        \brief 3-axis data as S16
*/
typedef struct
{
	BSX_S16 x;			/**< x-axis data of type S16 */
	BSX_S16 y;			/**< y-axis data of type S16*/
	BSX_S16 z;			/**< z-axis data of type S16*/
}ts_dataxyz;

/** \struct ts_dataxyzs32
        \brief 3-axis data as S32
*/
typedef struct
{
	BSX_S32 x;			/**< x-axis data of type S32 */
	BSX_S32 y;			/**< y-axis data of type S32 */
	BSX_S32 z;			/**< z-axis data of type S32 */
}ts_dataxyzs32;

/** \struct ts_dataxyzu8
        \brief 3-axis data as U8
*/
typedef struct
{
	BSX_U8 x;			/**< x-axis data of type U8  */
	BSX_U8 y;			/**< y-axis data of type U8 */
	BSX_U8 z;			/**< z-axis data of type U8  */
}ts_dataxyzu8;

/** \struct ts_dataxyzf32
        \brief 3-axis data as F32
*/
typedef struct{
	BSX_F32 x;			/**< x-axis data of type F32 */
	BSX_F32 y;			/**< y-axis data of type F32 */
	BSX_F32 z;			/**< z-axis data of type F32 */
}ts_dataxyzf32;

/** \struct ts_dataeuler
        \brief Euler angles data as S16
*/
typedef struct
{
     BSX_S16 h;			/**< heading data */
     BSX_S16 p;			/**< pitch data  */    
     BSX_S16 r;			/**< roll data  */
     BSX_S16 y;			/**< 3D Yaw data  */
}ts_dataeuler;

/** \struct ts_dataquat
        \brief Quaternion angles data
*/
typedef struct
{
	BSX_S16  w;			/**< q[0] data of vector q  */
	BSX_S16  x;			/**< q[1] data of vector q  */
	BSX_S16  y;			/**< q[2] data of vector q  */
	BSX_S16  z;			/**< q[3] data of vector q  */
}ts_dataquat;

/** \struct ts_dataeulerf32
        \brief Euler angles data as F32 
*/
typedef struct
{
     BSX_F32 h;			/**< heading data */
     BSX_F32 p;			/**< pitch data  */       
     BSX_F32 r;			/**< roll data  */
     BSX_F32 y;			/**< 3D Yaw data  */
}ts_dataeulerf32;

/** \struct ts_dataquatf32
        \brief Quaternion data in F32
*/
typedef struct
{
	BSX_F32  w;			/**< q[0] data of vector q  */
	BSX_F32  x;			/**< q[1] data of vector q  */
	BSX_F32  y;			/**< q[2] data of vector q  */
	BSX_F32  z;			/**< q[3] data of vector q  */
}ts_dataquatf32;

/** \struct ts_sensmatrix
        \brief 3x3 sensitivity matrix
*/

typedef struct
{
	ts_dataxyzf32 x;	/**< x-axis sensitivity with respect to 3-axis */
	ts_dataxyzf32 y;	/**< y-axis sensitivity with respect to 3-axis */
	ts_dataxyzf32 z;	/**< z-axis sensitivity with respect to 3-axis */
}ts_sensmatrix;

/** \struct ts_axisconfig
        \brief Axis Configuration
*/
typedef struct
{
	BSX_S32 update_remaparray[3*3] ;/**< array of 3*3 size to update after remapping*/
	BSX_U8 axisConfig;/**< Axis Configuration parameter */
	BSX_U8 axisSign;/**< AxisSign parameter */

}ts_axisconfig;


/** \struct ts_calibparam
        \brief Calibration parameters 
*/
typedef struct
{
	ts_dataxyz  offset; /**< 3-axis offset */
	BSX_S16		radius; /**< radius */
}ts_calibparam;


/** \struct ts_tick
        \brief Ticks to enable calibration and usecase modules
*/
typedef struct
{
	BSX_U8  calib; /**< enabled when calibration module is to be used */
	BSX_U8	usecase; /**< enable when usecase module is to be used */
}ts_tick;

/** \struct ts_callflag
        \brief Selection for Magnetometer or usecase mode
*/
typedef struct
{
	BSX_U8  acccalib; /**< select for Accelerometer calibration module */
	BSX_U8	magcalib; /**< select for Magnetometer calibration module */
	BSX_U8	gyrocalib; /**< select for Gyroscope calibration module */
	BSX_U8	usecase; /**< select for usecase module */
}ts_callflag;

/** \struct ts_calibparamf32
        \brief Calibration parameters and radius in float 
*/
typedef struct
{
	ts_dataxyzf32  offset;	/**< 3-axis offset */
	BSX_F32		radius;		/**< radius */
}ts_calibparamf32;

/** \struct ts_calibprofile
        \brief Calibration parameters and accuracy of calibration structure - calibprofile
*/
typedef struct
{
	ts_calibparam calibParam;	/**< calibration parameters - offset and radius */
	BSX_U8	accuracy;			/**< calibration accuracy */
}ts_calibprofile;

/** \struct ts_bsxfusionlibrary
        \brief General Library Structure 
*/
typedef struct
{
	BSX_U32 workingModes;				/**< working operation modes */
	BSX_U32 prev_workingMode;			/**< previous working mode */
	BSX_U8 opMode;						/**< bsx library operation mode of the library: bit[0] = accelerometer mode; bit[1] = magnetometer mode; bit[2] = gyroscope mode;*/
	BSX_U8 flipgestureOpmode;			/**< Operation mode for flip gesture */
	BSX_U8 orientcoordinatesystem;		/**< to select win 8 or ANDROID co ordinate sys */


}ts_bsxfusionlibrary;

/** \struct ts_workingModes
        \brief Working Modes
*/
typedef struct
{
	BSX_U32 opMode;						/**< working operation modes set*/
	/*Reserved*/
}ts_workingModes;

/** \struct ts_HWsensorSwitchList
        \brief HW sensor Switch List
*/
typedef struct
{
	BSX_U8 acc;						    /**< selecting hardware sensor Accelerometer */
	BSX_U8 mag;							/**< selecting hardware sensor Magnetometer */
	BSX_U8 gyro;						/**< selecting hardware sensor Gyroscope */
}ts_HWsensorSwitchList;

/** \struct sensordata_t
        \brief sensor Data
*/
typedef struct {
	ts_dataxyzs32 data;					/**< data in s32*/
	BSX_U32 time_stamp;					/**< time stamp in U32 */
}sensordata_t;

/** \struct libraryinput_t
        \brief Library input
*/
typedef struct {
	sensordata_t acc;					/**< Accelerometer data and Accelerometer timestamp*/
	sensordata_t mag;					/**< Magnetometer data and Magnetometer timestamp*/
	sensordata_t gyro;					/**< Gyroscope data and Gyroscope timestamp*/
} libraryinput_t;

/*!
 * @brief struct flip_t
 * Vector of face up and face down
 */
typedef struct
{
	 BSX_F32 faceup;      /**< holds the faceup angle */
	 BSX_F32 facedown;    /**< holds the facedown angle */
}flip_t;

/*!
 * @brief struct initParam_t 
 * Includes pointers to spec, usecase array and CRC check status for each spec and usecase config.
 */
typedef struct {
	BSX_U8 *accelspec;  /**< Pointer to Accelerometer spec char array data*/
	BSX_U8 *magspec;    /**< Pointer to Magnetometer spec char array data*/
	BSX_U8 *gyrospec;   /**< Pointer to Gyroscope spec char array data*/
	BSX_U8 *usecase;    /**< Pointer to usecase char array data*/
	BSX_U8 accelspec_status; /**< Status of initialization on Accelerometer spec data*/
	BSX_U8 magspec_status;   /**< Status of  initialization on Magnetometer spec data*/
	BSX_U8 gyrospec_status;  /**< Status of  initialization on Gyroscope spec data*/
	BSX_U8 usecase_status;   /**< Status of  initialization on use case data*/
}initParam_t;
#endif



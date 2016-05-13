# daemon version
DAEMON_VERSION=3.0.39

# hal version
HAL_VERSION=3.0.17

# For Android version
android_version ?= 5.0

# bma250e
# bma255
# bma280
# bma222
bma ?=

# bmm150
bmm ?= amm2

# bmg160
bmg ?=

# bmc055 contains bma255+bmm050
# bmc056 contains bma255+bmm050
# bmc150 contains bma255+bmm150
bmc ?=

# bmi160
bmi ?= bmi160

# ndof, m4g, compass, imu
usecase ?= ndof

#hw_2nd_interface_config for mag: true or false
hw_2nd_interface_config ?= false

#======================================
# sensor feature configurations
#======================================
# Android 4.3 new virtual sensor(gyro/mag uncalibrated, game rotation vector) support:: true or false
# will be auto disabled if android_version is less than 4.3
uncalibrated_virtual_sensor_support ?= true

# Android 4.3 new virtual sensor(significant motion) support:: true or false
# will be auto disabled if android_version is less than 4.3
significant_motion_sensor_support ?= false

# New feature about fast calibation automatically
# will be supported in hal layer, both acc and gyro sensor
fast_calibration_feature_automatic_support ?= true

# support bmp sensor in HAL : true or false
bmp_support ?= false

# flip gesture recognize
flip_gesture_support ?= false

# soft iron support
softiron_support ?= true

# fast magnetic calibration :off on
ifneq ($(filter piccolo,$(TARGET_PRODUCT)),)
fast_fmc ?= on
else
fast_fmc ?= on
endif

# fastest mode configuration
# 100Hz or 200Hz
fastest_mode ?= 100Hz

# use calibrated timestamp as sensor scheduling timestamp
scheduling_timestamp_calibrated ?= false

# use scheduling timestamp as sensor data timestamp
sensor_timestamp_scheduling ?= false

# for compass and m4g usecases, RV is disabled by defalut.
# It will be enabled by default when in ndof and imu usecase.
sensor_rotation_vector ?= true

# unstandard sensor support. It will enable/disable the sensors
# which are not fullfill Google defination but implemented by algorithm
unstandard_sensor_support ?= false

# reset calibration profile after reboot
calibration_reset ?= false

# record accel fast calibration offset values
fast_calib_offset ?= false

# hybrid hal support bypass accel sensor
hybrid_hal = false

#======================================
# debug configurations
#======================================
# enable the debug trace level, will allow sensord generate run time
# information : quiet, error, warning, notice, information, debug
# quiet   - print no information
# error   - print same or higher level than error
# warning - print same or higher level than warning
# notice  - print same or higher level than notice
# information   - print same or higher level than information,
# 				provide addtional information as reference
# debug   - print same or higher level than debug, normally for develop engineer use
debug_trace_level ?= debug

# add the flag to mark the data trace relative function.
# to reduce code/ram size when customer release
# when it is TRUE, trace function can still be enabled/disabled by the data_log_level setting
debug_data_log ?= true

# use ram buffer instead of write to data log file each time, only for input data to algo
data_log_using_ram_buffer ?= true

# log path : none, file, logcat
# file - log file is stored at the path /data/misc/sensor/sensord.log
# logcat - log to android logcat, information can be retrieved by "adb logcat"
# notice : this macro must be enabled together with debug_trace_level
debug_log_method ?= file

# debug timing accuracy of data sampling
# notice that this macro must be disabled before release
# debug information have big influence with performace
debug_timing_accuracy ?= false

# debug data log with accuracy information
datalog_with_accuracy ?= false

# whether install axis configuration file the value will be
# recognized as part of the axis configuration file name, ex.
# if set as samsung_note, while executing "mm install", a file
# which named "axis_cfg_samsung_note" will be installed to target
axis_config ?=

#custom_suffix of sensord
sensord_suffix ?=


#======================================
# algorithm configurations
#======================================

# These parameters are to set the orientation filter base and
# dynamic coefficients for accelerator and magnetic
# notice that, these two parameters must be set together
# range [0...1.0f]
# empty to use algorithm default
orientation_filt_coef = # 0.4
orientation_filt_dyna = # 0.3

# Orientation filter mode
# 0 -> bypass
# 1 -> low
# 2 -> medium
# 3 -> high
# empty to use algorithm default
orientation_filtermode = # 1

# magnetic calibration accuracy threshold
# range [0.4...1.0f]
# empty to use algorithm default
magnetic_accuracy_thres = # 1

ifneq ($(filter paella,$(TARGET_DEVICE)),)
LOCAL_CFLAGS += -DL8910_COMMON
else ifneq ($(filter piccolo,$(TARGET_PRODUCT)),)
LOCAL_CFLAGS += -DL9100_COMMON
endif

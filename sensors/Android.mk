ifneq ($(filter msm8960 msm8610 msm8916 msm8909,$(TARGET_BOARD_PLATFORM)),)
# Exclude SSC targets
ifneq ($(TARGET_USES_SSC),true)
# Disable temporarily for compilling error
ifneq ($(BUILD_TINY_ANDROID),true)
ifneq ($(filter cm_paella,$(TARGET_PRODUCT)),)
#BOSCH bst sensors HAL
include $(all-subdir-makefiles)
else
LOCAL_PATH := $(call my-dir)

# HAL module implemenation stored in
include $(CLEAR_VARS)

ifeq ($(USE_SENSOR_MULTI_HAL),true)
  LOCAL_MODULE := sensors.native
else
  ifneq ($(filter msm8610,$(TARGET_BOARD_PLATFORM)),)
    LOCAL_MODULE := sensors.$(TARGET_BOARD_PLATFORM)
    LOCAL_CFLAGS := -DTARGET_8610
  else
    ifneq ($(filter msm8916 msm8909,$(TARGET_BOARD_PLATFORM)),)
      LOCAL_MODULE := sensors.$(TARGET_BOARD_PLATFORM)
    else
      LOCAL_MODULE := sensors.msm8960
    endif
  endif

  ifdef TARGET_2ND_ARCH
    LOCAL_MODULE_RELATIVE_PATH := hw
  else
    LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw
  endif
endif

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS += -DLOG_TAG=\"Sensors\"
ifeq ($(call is-board-platform,msm8960),true)
  LOCAL_CFLAGS += -DTARGET_8930
endif

LOCAL_C_INCLUDES := $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr/include
LOCAL_ADDITIONAL_DEPENDENCIES := $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr

# Export calibration library needed dependency headers
LOCAL_COPY_HEADERS_TO := sensors/inc
LOCAL_COPY_HEADERS := 	\
		CalibrationModule.h \
		sensors_extension.h \
		sensors.h

LOCAL_SRC_FILES :=	\
		sensors.cpp 			\
		SensorBase.cpp			\
		LightSensor.cpp			\
		ProximitySensor.cpp		\
		CompassSensor.cpp		\
		Accelerometer.cpp				\
		Gyroscope.cpp				\
		Bmp180.cpp				\
		InputEventReader.cpp \
		CalibrationManager.cpp \
		NativeSensorManager.cpp \
		VirtualSensor.cpp	\
		sensors_XML.cpp \
		SignificantMotion.cpp

LOCAL_C_INCLUDES += external/libxml2/include	\

ifeq ($(call is-platform-sdk-version-at-least,20),true)
    LOCAL_C_INCLUDES += external/icu/icu4c/source/common
else
    LOCAL_C_INCLUDES += external/icu4c/common
endif

LOCAL_SHARED_LIBRARIES := liblog libcutils libdl libxml2 libutils

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := libcalmodule_common
LOCAL_SRC_FILES := \
		   algo/common/common_wrapper.c \
		   algo/common/compass/AKFS_AOC.c \
		   algo/common/compass/AKFS_Device.c \
		   algo/common/compass/AKFS_Direction.c \
		   algo/common/compass/AKFS_VNorm.c

LOCAL_SHARED_LIBRARIES := liblog libcutils
LOCAL_MODULE_TAGS := optional

ifdef TARGET_2ND_ARCH
LOCAL_MODULE_PATH_32 := $(TARGET_OUT_VENDOR)/lib
LOCAL_MODULE_PATH_64 := $(TARGET_OUT_VENDOR)/lib64
else
LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR_SHARED_LIBRARIES)
endif

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := calmodule.cfg
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR_ETC)
LOCAL_SRC_FILES := calmodule.cfg

include $(BUILD_PREBUILT)

endif ##
endif #BUILD_TINY_ANDROID
endif #TARGET_USES_SSC
endif #TARGET_BOARD_PLATFORM

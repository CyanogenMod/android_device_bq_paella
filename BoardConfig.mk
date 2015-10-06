#
# Copyright (C) 2014 The CyanogenMod Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

FORCE_32_BIT := true

-include device/cyanogen/msm8916-common/BoardConfigCommon.mk

DEVICE_PATH := device/bq/paella
TARGET_VENDOR := bq

BOARD_USES_QCOM_HARDWARE := true

TARGET_SPECIFIC_HEADER_PATH := $(DEVICE_PATH)/include

TARGET_KERNEL_CONFIG := paella_defconfig
TARGET_USES_UNCOMPRESSED_KERNEL := false
KERNEL_DEFCONFIG := $(TARGET_KERNEL_CONFIG)

BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := $(DEVICE_PATH)/bluetooth

# Support form WiFi security modes EAP-SIM, PEAP and AKA
CONFIG_EAP_PROXY := qmi
CONFIG_EAP_PROXY_DUAL_SIM := true

# Camera
BOARD_CAMERA_SENSORS := \
    imx214_olqba22 \
    imx214_f13n05k \
    s5k5e2_olq5f20 \
    s5k5e2_s7b5

TARGET_USE_VENDOR_CAMERA_EXT := true
USE_DEVICE_SPECIFIC_CAMERA := true

BOARD_VENDOR_QCOM_GPS_LOC_API_HARDWARE := default
TARGET_CAMERA_HAL_PATH := $(DEVICE_PATH)/camera

#Audio
BOARD_USES_GENERIC_AUDIO := true

-include vendor/dolby/cmbuild.mk
ifeq ($(DOLBY_PRESENT),true)
DOLBY_PREBUILT_ARCH := armv7_float_neon_vfpv4
DOLBY_DAX_VERSION := 2
DOLBY_DAP := true
DOLBY_DAP2 := true
DOLBY_DAP_SW := true
DOLBY_DAP_PREGAIN := true
DOLBY_DAP_HW_QDSP_HAL_API := false
DOLBY_DAP_MOVE_EFFECT := true
DOLBY_DAP_BYPASS_SOUND_TYPES := false
DOLBY_UDC := false #true
DOLBY_UDC_VIRTUALIZE_AUDIO := false #true

include vendor/dolby/ds/dolby-buildspec.mk

AUDIO_FEATURE_ENABLED_DS2_DOLBY_DAP := true
BOARD_USES_SRS_TRUEMEDIA := false
endif

# CMHW
BOARD_HARDWARE_CLASS += $(DEVICE_PATH)/cmhw/src

# CNE
BOARD_USES_QCNE := true

# CPU
TARGET_CPU_CORTEX_A53 := true

# GPS
TARGET_GPS_HAL_PATH := $(DEVICE_PATH)/gps
TARGET_NO_RPC := true

# init
TARGET_LIBINIT_DEFINES_FILE := $(DEVICE_PATH)/init/init_paella.c

# liblights
TARGET_PROVIDES_LIBLIGHT := true

# Partitions
BOARD_FLASH_BLOCK_SIZE := 131072
BOARD_BOOTIMAGE_PARTITION_SIZE := 0x01000000
BOARD_CACHEIMAGE_FILE_SYSTEM_TYPE := ext4
BOARD_CACHEIMAGE_PARTITION_SIZE := 419430400
BOARD_PERSISTIMAGE_PARTITION_SIZE := 33552384
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 33554432
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 1610612736
BOARD_USERDATAIMAGE_PARTITION_SIZE := 13100366848

# Recovery
TARGET_RECOVERY_FSTAB := $(DEVICE_PATH)/rootdir/etc/fstab.qcom

# Video
TARGET_HAVE_SIGNED_VENUS_FW := true

#Encrypt
TARGET_HW_DISK_ENCRYPTION := false

BOARD_SEPOLICY_DIRS += \
    device/bq/paella/sepolicy

BOARD_SEPOLICY_UNION += \
    file.te \
    system_server.te \
    file_contexts

BOARD_KERNEL_CMDLINE := console=ttyHSL0,115200,n8 androidboot.console=ttyHSL0 androidboot.hardware=qcom msm_rtb.filter=0x237 ehci-hcd.park=3 androidboot.bootdevice=7824900.sdhci lpm_levels.sleep_disabled=1 earlyprintk

TARGET_KERNEL_SOURCE := kernel/bq/msm8916

TARGET_SYSTEM_PROP += $(DEVICE_PATH)/system.prop

# inherit from the proprietary version
-include vendor/bq/paella/BoardConfigVendor.mk

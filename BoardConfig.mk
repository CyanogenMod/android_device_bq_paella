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

-include device/cyanogen/msm8916-common/BoardConfigCommon.mk

DEVICE_PATH := device/bq/paella
TARGET_VENDOR := bq #Needed in the proprietary includes.

BOARD_USES_QCOM_HARDWARE := true

PRODUCT_DEFAULT_DEV_CERTIFICATE := build/target/product/security/releasekey

TARGET_SPECIFIC_HEADER_PATH := $(DEVICE_PATH)/include

TARGET_KERNEL_CONFIG := paella_defconfig
KERNEL_DEFCONFIG := $(TARGET_KERNEL_CONFIG)

BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := $(DEVICE_PATH)/bluetooth

# Support form WiFi security modes EAP-SIM, PEAP and AKA
CONFIG_EAP_PROXY := qmi
CONFIG_EAP_PROXY_DUAL_SIM := true

# Camera
BOARD_CAMERA_SENSORS := \
    ov5670_q5v41b \
    ov8865_q8v18a
TARGET_USE_VENDOR_CAMERA_EXT := true
USE_DEVICE_SPECIFIC_CAMERA := true

BOARD_VENDOR_QCOM_GPS_LOC_API_HARDWARE := default
TARGET_CAMERA_HAL_PATH := $(DEVICE_PATH)/camera

#Audio
BOARD_USES_GENERIC_AUDIO := true

# CMHW
BOARD_HARDWARE_CLASS += $(DEVICE_PATH)/cmhw/src

# CPU
TARGET_CPU_CORTEX_A53 := true

# GPS
TARGET_GPS_HAL_PATH := $(DEVICE_PATH)/gps
TARGET_NO_RPC := true

# Partitions
BOARD_FLASH_BLOCK_SIZE := 131072
BOARD_BOOTIMAGE_PARTITION_SIZE := 0x01000000
BOARD_CACHEIMAGE_FILE_SYSTEM_TYPE := ext4
BOARD_CACHEIMAGE_PARTITION_SIZE := 419430400
BOARD_PERSISTIMAGE_PARTITION_SIZE := 33552384
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 33554432
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 1610612736
BOARD_USERDATAIMAGE_PARTITION_SIZE := 13100366848

# Wifi
WIFI_DRIVER_MODULE_PATH := "/system/lib/modules/wlan.ko"
WIFI_DRIVER_MODULE_NAME := "wlan"


# Recovery
TARGET_RECOVERY_FSTAB := $(DEVICE_PATH)/rootdir/etc/fstab.qcom

# Video
TARGET_HAVE_SIGNED_VENUS_FW := true

#Encrypt
TARGET_HW_DISK_ENCRYPTION := false

BOARD_HAVE_FM := true
TARGET_QCOM_NO_FM_FIRMWARE := false

BOARD_SEPOLICY_DIRS += \
    device/bq/paella/sepolicy

BOARD_SEPOLICY_UNION += \
    file.te \
    system_server.te \
    file_contexts

BOARD_KERNEL_CMDLINE := console=ttyHSL0,115200,n8 androidboot.console=ttyHSL0 androidboot.hardware=qcom msm_rtb.filter=0x237 ehci-hcd.park=3 androidboot.bootdevice=7824900.sdhci lpm_levels.sleep_disabled=1 earlyprintk

TARGET_SYSTEM_PROP += $(DEVICE_PATH)/system.prop

# inherit from the proprietary version
-include vendor/bq/paella/BoardConfigVendor.mk

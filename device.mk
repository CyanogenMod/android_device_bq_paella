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
#
$(call inherit-product-if-exists, vendor/qcom/proprietary/common/config/device-vendor.mk)

#PRODUCT_DEFAULT_DEV_CERTIFICATE := build/target/product/security/releasekey

# Overlay
DEVICE_PACKAGE_OVERLAYS += $(LOCAL_PATH)/overlay

# Permissions
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.sensor.compass.xml:system/etc/permissions/android.hardware.sensor.compass.xml \
    frameworks/native/data/etc/android.hardware.sensor.gyroscope.xml:system/etc/permissions/android.hardware.sensor.gyroscope.xml \
    frameworks/native/data/etc/android.hardware.sensor.light.xml:system/etc/permissions/android.hardware.sensor.light.xml \
    frameworks/native/data/etc/android.hardware.sensor.proximity.xml:system/etc/permissions/android.hardware.sensor.proximity.xml \
    frameworks/native/data/etc/handheld_core_hardware.xml:system/etc/permissions/handheld_core_hardware.xml

# Screen density
PRODUCT_AAPT_CONFIG := normal
PRODUCT_AAPT_PREF_CONFIG := xhdpi

#Keylayout
PRODUCT_PACKAGES += \
	ft5x06_ts.kl

# Boot animation
TARGET_SCREEN_HEIGHT := 1280
TARGET_SCREEN_WIDTH := 720

$(call inherit-product, frameworks/native/build/phone-hdpi-2048-dalvik-heap.mk)
$(call inherit-product, frameworks/native/build/phone-xxhdpi-2048-hwui-memory.mk)

# Audio configuration
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/audio/audio_policy.conf:system/etc/audio_policy.conf \
    $(LOCAL_PATH)/audio/audio_effects.conf:system/vendor/etc/audio_effects.conf \
    $(LOCAL_PATH)/audio/mixer_paths_mtp.xml:system/etc/mixer_paths_mtp.xml \
    $(LOCAL_PATH)/audio/mixer_paths_qrd_skuh.xml:system/etc/mixer_paths_qrd_skuh.xml \
    $(LOCAL_PATH)/audio/mixer_paths_qrd_skui.xml:system/etc/mixer_paths_qrd_skui.xml \
    $(LOCAL_PATH)/audio/mixer_paths_qrd_skuhf.xml:system/etc/mixer_paths_qrd_skuhf.xml \
    $(LOCAL_PATH)/audio/mixer_paths_wcd9306.xml:system/etc/mixer_paths_wcd9306.xml \
    $(LOCAL_PATH)/audio/mixer_paths_skuk.xml:system/etc/mixer_paths_skuk.xml \
    $(LOCAL_PATH)/audio/mixer_paths.xml:system/etc/mixer_paths.xml \
    $(LOCAL_PATH)/audio/sound_trigger_mixer_paths.xml:system/etc/sound_trigger_mixer_paths.xml \
    $(LOCAL_PATH)/audio/sound_trigger_mixer_paths_wcd9306.xml:system/etc/sound_trigger_mixer_paths_wcd9306.xml \
    $(LOCAL_PATH)/audio/sound_trigger_platform_info.xml:system/etc/sound_trigger_platform_info.xml \
    $(LOCAL_PATH)/audio/mixer_paths_wcd9330.xml:system/etc/mixer_paths_wcd9330.xml


# Camera
PRODUCT_PACKAGES += \
    camera.msm8916 

# Lights
PRODUCT_PACKAGES += \
    lights.msm8916

# Media
#

TARGET_ENABLE_QC_AV_ENHANCEMENTS := true

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/media/media_profiles_8916.xml:system/etc/media_profiles.xml

# Sensor HAL
PRODUCT_PACKAGES += \
    calmodule.cfg \
    libcalmodule_akm.so \
    libcalmodule_common \

# Ramdisk
PRODUCT_PACKAGES += \
    fstab.qcom \
	init.paella.diag.rc \
	init.target.rc \
    init.qcom.fm.sh

# Wlan Driver
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/wifi/WCNSS_qcom_cfg.ini:system/etc/wifi/WCNSS_qcom_cfg.ini \
	$(LOCAL_PATH)/wifi/WCNSS_cfg.dat:system/etc/firmware/wlan/prima/WCNSS_cfg.dat \
	$(LOCAL_PATH)/wifi/WCNSS_qcom_wlan_nv.bin:system/etc/firmware/wlan/prima/WCNSS_qcom_wlan_nv.bin

PRODUCT_PACKAGES +=\
       prima_wlan.ko \
       pronto_wlan.ko \
       iwpriv \
       iwlist \
       iwpriv.agent.sh


PRODUCT_PACKAGES += \
    wpa_supplicant_overlay.conf \
	p2p_supplicant_overlay.conf
		

#Proprietaty
PRODUCT_PACKAGES += \
	rmt_storage \
	rfs_access \
	qseecomd \
	irsc_util \
	qmuxd \
	netmgrd \
	thermal-engine \
	loc_launcher \
	ssr_diag \
	mm-qcamera-daemon \
	time_daemon \
	mm-pp-daemon \
	loc_launcher

#Apps
PRODUCT_PACKAGES += \
	Camera2


#Sensors
PRODUCT_PACKAGES += \
	sensord

# Soft magnetic calibration
PRODUCT_COPY_FILES+= \
     hardware/qcom/sensors/bst_fifo/daemon/softiron_matrix.txt:system/etc/sensor/softiron_matrix.txt

#GPS
PRODUCT_PACKAGES += \
	gps.conf \
	gps.default \
	gps.mahimahi \
	libloc_adapter \
	libgps.utils \
	libloc_eng \
	libloc_api_v02


# Inherit the rest from msm8916-common
$(call inherit-product, device/cyanogen/msm8916-common/msm8916.mk)

#GAPPS
$(call inherit-product, vendor/google/Android.mk)
$(call inherit-product, vendor/google/products/gms.mk)

#BQ APPS
$(call inherit-product-if-exists, vendor/bq/app/config/products.mk)
$(call inherit-product-if-exists, vendor/bq/vendor-blobs.mk)

PRODUCT_PROPERTY_OVERRIDES += \
        persist.sys.language=en \
        persist.sys.country=GB \
        persist.sys.timezone=Europe/Amsterdam

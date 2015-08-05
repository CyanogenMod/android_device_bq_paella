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
    frameworks/native/data/etc/android.hardware.audio.low_latency.xml:system/etc/permissions/android.hardware.audio.low_latency.xml \
    frameworks/native/data/etc/android.hardware.camera.flash-autofocus.xml:system/etc/permissions/android.hardware.camera.flash-autofocus.xml \
    frameworks/native/data/etc/android.hardware.camera.front.xml:system/etc/permissions/android.hardware.camera.front.xml \
    frameworks/native/data/etc/android.hardware.location.gps.xml:system/etc/permissions/android.hardware.location.gps.xml \
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
	himax-touchscreen.kl \
	msm8x16-skui-snd-card_Button_Jack.kl

# Boot animation
TARGET_SCREEN_HEIGHT := 1280
TARGET_SCREEN_WIDTH := 720

$(call inherit-product, frameworks/native/build/phone-hdpi-2048-dalvik-heap.mk)
$(call inherit-product, frameworks/native/build/phone-xxhdpi-2048-hwui-memory.mk)

# Audio configuration
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/audio/audio_policy.conf:system/etc/audio_policy.conf \
    $(LOCAL_PATH)/audio/audio_effects.conf:system/vendor/etc/audio_effects.conf \
    $(LOCAL_PATH)/audio/mixer_paths_qrd_skui.xml:system/etc/mixer_paths_qrd_skui.xml \
    $(LOCAL_PATH)/audio/sound_trigger_mixer_paths.xml:system/etc/sound_trigger_mixer_paths.xml \
    $(LOCAL_PATH)/audio/sound_trigger_mixer_paths_wcd9306.xml:system/etc/sound_trigger_mixer_paths_wcd9306.xml \
    $(LOCAL_PATH)/audio/sound_trigger_platform_info.xml:system/etc/sound_trigger_platform_info.xml

# Audio calibration
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/audio/acdb/QRD_Bluetooth_cal.acdb:system/etc/acdbdata/QRD/QRD_Bluetooth_cal.acdb \
    $(LOCAL_PATH)/audio/acdb/QRD_General_cal.acdb:system/etc/acdbdata/QRD/QRD_General_cal.acdb \
    $(LOCAL_PATH)/audio/acdb/QRD_Global_cal.acdb:system/etc/acdbdata/QRD/QRD_Global_cal.acdb \
    $(LOCAL_PATH)/audio/acdb/QRD_Handset_cal.acdb:system/etc/acdbdata/QRD/QRD_Handset_cal.acdb \
    $(LOCAL_PATH)/audio/acdb/QRD_Hdmi_cal.acdb:system/etc/acdbdata/QRD/QRD_Hdmi_cal.acdb \
    $(LOCAL_PATH)/audio/acdb/QRD_Headset_cal.acdb:system/etc/acdbdata/QRD/QRD_Headset_cal.acdb \
    $(LOCAL_PATH)/audio/acdb/QRD_Speaker_cal.acdb:system/etc/acdbdata/QRD/QRD_Speaker_cal.acdb

# First api level, device has been commercially launched
PRODUCT_PROPERTY_OVERRIDES += \
    ro.product.first_api_level=22

# Camera
PRODUCT_PACKAGES += \
    camera.msm8916 \
    libmpbase

# Lights
PRODUCT_PACKAGES += \
    lights.msm8916

# Media
#

TARGET_ENABLE_QC_AV_ENHANCEMENTS := true

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/media/media_profiles_8916.xml:system/etc/media_profiles.xml \
    $(LOCAL_PATH)/media/media_codecs_performance_8916_32.xml:system/etc/media_codecs_performance.xml

# Sensor HAL
PRODUCT_PACKAGES += \
    calmodule.cfg \
    libcalmodule_akm.so \
    libcalmodule_common \

# Ramdisk
PRODUCT_PACKAGES += \
    fstab.qcom \
    init.target.rc

# Recovery
PRODUCT_EXTRA_RECOVERY_KEYS += \
    $(LOCAL_PATH)/paella-releasekey \
    $(LOCAL_PATH)/piccolo-releasekey

# USB ID
ADDITIONAL_DEFAULT_PROPERTIES += \
    ro.usb.id.charge=3009 \
    ro.usb.id.mtp=3003 \
    ro.usb.id.mtp_adb=3004 \
    ro.usb.id.ptp=3005 \
    ro.usb.id.ptp_adb=3006 \
    ro.usb.id.ums=3007 \
    ro.usb.id.ums_adb=3008 \
    ro.usb.vid=2a47

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
	mm-pp-daemon

#Apps
PRODUCT_PACKAGES += \
	Camera2

# Connectivity Engine support
PRODUCT_PACKAGES += \
    libcnefeatureconfig

PRODUCT_PACKAGES += \
    services-ext \
    init.cne.rc

# Tethering
PRODUCT_PACKAGES += \
    ebtables \
    ethertypes

PRODUCT_PROPERTY_OVERRIDES += \
    persist.cne.feature=1 \
    persist.dpm.feature=7

# Sensors
PRODUCT_PACKAGES += \
    AccCalibration \
    sensord \
    sensors.msm8916

# Soft magnetic calibration
PRODUCT_COPY_FILES+= \
     $(LOCAL_PATH)/sensors/bst_fifo/daemon/softiron_matrix.txt:system/etc/sensor/softiron_matrix.txt


# GPS
PRODUCT_PACKAGES += \
    gps.msm8916

# Power
PRODUCT_PACKAGES += \
    power.msm8916

# WAP Push
PRODUCT_PACKAGES += \
    WapPush

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/gps/flp.conf:system/etc/flp.conf \
    $(LOCAL_PATH)/gps/gps.conf:system/etc/gps.conf \
    $(LOCAL_PATH)/gps/izat.conf:system/etc/izat.conf \
    $(LOCAL_PATH)/gps/quipc.conf:system/etc/quipc.conf \
    $(LOCAL_PATH)/gps/sap.conf:system/etc/sap.conf

ifeq ($(QCPATH),)
# netmgr/dpm
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/data/netmgr_config.xml:system/etc/data/netmgr_config.xml \
    $(LOCAL_PATH)/configs/data/qmi_config.xml:system/etc/data/qmi_config.xml \
    $(LOCAL_PATH)/configs/data/dsi_config.xml:system/etc/data/dsi_config.xml \
    $(LOCAL_PATH)/configs/data/NsrmConfiguration.xml:system/etc/dpm/nsrm/NsrmConfiguration.xml \
    $(LOCAL_PATH)/configs/data/dpm.conf:system/etc/dpm/dpm.conf

# Connectivity Engine
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/cne/cneapiclient.xml:system/etc/permissions/cneapiclient.xml \
    $(LOCAL_PATH)/configs/cne/com.quicinc.cne.xml:system/etc/permissions/com.quicinc.cne.xml \
    $(LOCAL_PATH)/configs/cne/andsfCne.xml:system/etc/cne/andsfCne.xml \
    $(LOCAL_PATH)/configs/cne/SwimConfig.xml:system/etc/cne/SwimConfig.xml

endif

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/spn-conf.xml:system/etc/spn-conf.xml

# Inherit the rest from msm8916-common
$(call inherit-product, device/cyanogen/msm8916-common/msm8916.mk)

#BQ APPS
$(call inherit-product-if-exists, vendor/bq/app/config/products.mk)
$(call inherit-product-if-exists, vendor/bq/vendor-blobs.mk)
$(call inherit-product-if-exists, vendor/bq/paella/paella-vendor.mk)

PRODUCT_PROPERTY_OVERRIDES += \
        persist.sys.timezone=Europe/Amsterdam

PRODUCT_SYSTEM_PROPERTY_BLACKLIST += \
        ro.product.locale.language \
        ro.product.locale.region \
        ro.product.locale

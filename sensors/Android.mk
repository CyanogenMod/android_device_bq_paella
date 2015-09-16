ifneq ($(filter msm8960 msm8610 msm8916 msm8909,$(TARGET_BOARD_PLATFORM)),)
ifneq ($(BUILD_TINY_ANDROID),true)
	include $(all-subdir-makefiles)
endif #BUILD_TINY_ANDROID
endif #TARGET_BOARD_PLATFORM

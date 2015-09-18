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

$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)

# Inherit from paella device
$(call inherit-product, device/bq/paella/device.mk)

# Device identifier. This must come after all inclusions
PRODUCT_DEVICE := paella
PRODUCT_NAME := full_paella
PRODUCT_BRAND := bq
PRODUCT_MODEL := Aquaris X5
PRODUCT_MANUFACTURER := bq

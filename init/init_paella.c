/*
   Copyright (c) 2015, The CyanogenMod Project

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <stdio.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

#include "init_msm.h"

static short sku_match = 0;
static char sku_mcc[5] = {0,};

static void import_cmdline(char *name, int for_emulator)
{
    char *value = strchr(name, '=');
    int name_len = strlen(name);

    if (value == 0) return;
    *value++ = 0;
    if (name_len == 0) return;

    if (!strcmp(name,"androidboot.countrycode") && !strncmp(value,"ES",2)) {
        sprintf(sku_mcc, "214");
        sku_match++;
    } else if (!strcmp(name,"androidboot.countrycode") && !strncmp(value,"GB",2)) {
        sprintf(sku_mcc, "234");
        sku_match++;
    } else if (!strcmp(name,"androidboot.spncode") && strnlen(value,2)) {
        // Something with 2 or more chars is set... and it's not "None" nor "NONE"
        if (strncmp(value,"None",4) && strncmp(value,"NONE",4)) sku_match++;
    }
}

void init_msm_properties(unsigned long msm_id, unsigned long msm_ver, char *board_type)
{
    char device[PROP_VALUE_MAX];
    int rc;

    UNUSED(msm_id);
    UNUSED(msm_ver);
    UNUSED(board_type);

    rc = property_get("ro.cm.device", device);
    if (!rc || !ISMATCH(device, "paella"))
        return;

    char density[5];
    import_kernel_cmdline(0, import_cmdline);

    if (sku_match >= 2 && sku_mcc[0]) {
        // Matched 2 or more items. Set the customization
        property_set("ro.prebundled.mcc", sku_mcc);
    } else {
        // apply defaults
    }
}


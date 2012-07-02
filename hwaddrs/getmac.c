/*
 * Copyright (C) 2011 The CyanogenMod Project
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
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cutils/properties.h>

/* Read properties and set MAC addresses accordingly */

int main() {
	int fd1; FILE *fd;
	int macbyte;
	int i;
        char mMacAddr[PROPERTY_VALUE_MAX];

        property_get("service.brcm.wlan.mac",mMacAddr,"010203040506");

	fd = fopen("/data/misc/wifi/config","w");

	fprintf(fd,"vlan_mode=0\n\
mpc=1\n\
wme=1\n\
wme_apsd=0\n\
wme_qosinfo=0x00\n\
wme_auto_trigger=0\n\
wme_apsd_trigger=290000\n\
roam_off=0\n\
roam_scan_period=20\n\
roam_delta=20\n\
roam_trigger=-70\n\
PM=2\n\
assoc_listen=1\n\
assoc_retry_max=7\n\
cur_etheraddr=%c%c:%c%c:%c%c:%c%c:%c%c:%c%c\n",mMacAddr[0], mMacAddr[1], mMacAddr[2], mMacAddr[3], mMacAddr[4], mMacAddr[5], mMacAddr[6], mMacAddr[7], mMacAddr[8], mMacAddr[9], mMacAddr[10], mMacAddr[11]);


	fclose(fd);
        property_get("service.brcm.bt.mac",mMacAddr,"010203040506");
	fd = fopen("/data/misc/bd_addr","w");
	fprintf(fd,"%c%c:%c%c:%c%c:%c%c:%c%c:%c%c\n",mMacAddr[0], mMacAddr[1], mMacAddr[2], mMacAddr[3], mMacAddr[4], mMacAddr[5], mMacAddr[6], mMacAddr[7], mMacAddr[8], mMacAddr[9], mMacAddr[10], mMacAddr[11]);
	fclose(fd);
	return 0;
}

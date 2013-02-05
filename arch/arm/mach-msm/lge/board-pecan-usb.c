/* arch/arm/mach-msm/lge/board-pecan-usb.c
 * Copyright (C) 2013 PecanCM, Org.
 * Copyright (c) 20010 LGE. Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


#include <linux/init.h>

#include <mach/board.h>
#include <mach/msm_iomap.h>
#include <mach/msm_hsusb.h>

#ifdef CONFIG_USB_FUNCTION
#include <linux/usb/mass_storage_function.h>
#endif
#ifdef CONFIG_USB_ANDROID
#include <linux/usb/android.h>
#endif
#ifdef CONFIG_USB_ANDROID_ACCESSORY
#include <linux/usb/f_accessory.h>
#endif

#include <mach/board_lge.h>
#include <mach/gpio.h>

#include "devices.h"
#include "board-pecan.h"
#include "pm.h"


#ifdef CONFIG_USB_ANDROID

struct usb_composition usb_func_composition[] = {
	{
		/* Mass Storage only mode : UMS
		 * PID is dedicated for Thunder Global
		 */
		.product_id         = 0x61C5,
		.functions	    	= 0x2,
		.adb_product_id     = 0x61C5,
		.adb_functions	    = 0x2,
	},
	{
		/* Full or Light mode : ADB, UMS, NMEA, DIAG, MODEM */
		.product_id         = 0x618E,
		.functions	    	= 0x2743,
		.adb_product_id     = 0x618E,
		.adb_functions	    = 0x12743,
	},
	{
		/* Factory mode for WCDMA or GSM : DIAG, MODEM */
		/* We are in factory mode, ignore adb function */
		.product_id         = 0x6000,
		.functions	    	= 0x43,
		.adb_product_id     = 0x6000,
		.adb_functions	    = 0x43,
	},
#ifdef CONFIG_USB_ANDROID_CDC_ECM
	{
		/* CDC ECM Driver for matching LG Android Net driver */
		.product_id         = 0x61A2,
		.functions          = 0x27384,
		.adb_product_id     = 0x61A1,
		.adb_functions      = 0x127384,
	},
#endif	
#ifdef CONFIG_USB_ANDROID_ACCESSORY
	{
		.vendor_id	= USB_ACCESSORY_VENDOR_ID,
		.product_id	= USB_ACCESSORY_PRODUCT_ID,
		.num_functions	= ARRAY_SIZE(usb_functions_accessory),
		.functions	= usb_functions_accessory,
	},
	{
		.vendor_id	= USB_ACCESSORY_VENDOR_ID,
		.product_id	= USB_ACCESSORY_ADB_PRODUCT_ID,
		.num_functions	= ARRAY_SIZE(usb_functions_accessory_adb),
		.functions	= usb_functions_accessory_adb,
	},
#endif
#ifdef CONFIG_USB_ANDROID_RNDIS
	{
		/* Microsoft's RNDIS driver */
		.product_id         = 0xF00E,
		.functions	    	= 0xA,
		.adb_product_id     = 0xF00E,
		.adb_functions	    = 0xA,
	},
#endif
};

#define VENDOR_QCT	0x05C6
#define VENDOR_LGE	0x1004

struct android_usb_platform_data android_usb_pdata = {
	.vendor_id	= VENDOR_LGE,
	.version	= 0x0100,
	.compositions   = usb_func_composition,
	.num_compositions = ARRAY_SIZE(usb_func_composition),
	.product_name       = "LG Android USB Device",
	.manufacturer_name	= "LG Electronics Inc.",
	/* Default serial number(only for development) must
	   be 20 characters at LG WCDMA class model(because of IMEI size).
	   Currently we just have padding ;) */
	.serial_number		= "LG_ANDROID_P350****",
	.init_product_id	= 0x618E,
	.nluns = 1,
};

struct usb_mass_storage_platform_data mass_storage_pdata = {
	.nluns		= 1,
	.vendor		= "GOOGLE",
	.product	= "Mass Storage",
	.release	= 0xFFFF,
};

struct platform_device mass_storage_device = {
	.name           = "usb_mass_storage",
	.id             = -1,
	.dev            = {
		.platform_data          = &mass_storage_pdata,
	},
};

#endif /* CONFIG_USB_ANDROID */



static void __init msm7x2x_init(void)
{

msm_add_usb_devices();

}





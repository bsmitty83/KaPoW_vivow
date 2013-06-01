/* drivers/input/keyboard/pm8058-keypad.c
 *
 * Copyright (C) 2010 Google, Inc.
 * Copyright (C) 2009 Code Aurora Forum
 *
 * Author: Dima Zavin <dima@android.com>
 *    - Heavily based on the driver from the Code Aurora Forum.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/delay.h>
#include <linux/err.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/kernel.h>
#include <linux/mfd/pm8058.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/wait.h>

enum {
	DEBUG_IRQ = 1U << 0,
	DEBUG_KEYS = 1U << 1,
};
static int debug_mask = 0;
module_param_named(debug_mask, debug_mask, int, S_IRUGO | S_IWUSR | S_IWGRP);

#define REG_KEYP_CTRL		0x148
#define REG_KEYP_SCAN		0x149
#define REG_KEYP_TEST		0x14a
#define REG_KEYP_NEW_DATA	0x14b
#define REG_KEYP_OLD_DATA	0x14c

#define KP_SNS_MIN		5
#define KP_SNS_MAX		8
#define KP_DRV_MIN		5
#define KP_DRV_MAX		18

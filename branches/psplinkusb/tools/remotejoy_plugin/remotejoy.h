/*
 * PSPLINK
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPLINK root for details.
 *
 * remotejoy.h - PSPLINK PC remote joystick handler
 *
 * Copyright (c) 2006 James F <tyranid@gmail.com>
 *
 * $HeadURL: svn://svn.pspdev.org/psp/branches/psplinkusb/tools/remotejoy/remotejoy.h $
 * $Id: remotejoy.h 2145 2007-01-23 18:00:17Z tyranid $
 */
#ifndef __REMOTE_JOY__
#define __REMOTE_JOY__

#define JOY_MAGIC 0x909ACCEF

#define TYPE_BUTTON_DOWN 1
#define TYPE_BUTTON_UP   2
#define TYPE_ANALOG_Y    3
#define TYPE_ANALOG_X    4
#define TYPE_SCREEN_CMD  5

#define SCREEN_CMD_OFF   1
#define SCREEN_CMD_ON    2
#define SCREEN_CMD_HSIZE 4

struct JoyEvent
{
	unsigned int magic;
	int type;
	unsigned int value;
} __attribute__((packed));

struct JoyScrHeader
{
	unsigned int magic;
	int mode; /* 0-3 */
	unsigned short width;
	unsigned short height;
	int pad;
} __attribute__((packed));

#endif

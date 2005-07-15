/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

#include <pspkernel.h>
#include <pspge.h>

int sceGeListEnQueueHead(void* list, void* stall, int cbid, void* arg);

void sceGuSendList(unsigned int mode, const void* list, void* data)
{
	gu_settings.signal_offset = 0;

	unsigned int s[2];
	s[0] = 8;
	s[1] = (unsigned int)data;

	int list_id;
	int callback = gu_settings.ge_callback_id;

	if (mode == 1)
		list_id = sceGeListEnQueueHead(list,0,callback,s);
	else
		list_id = sceGeListEnQueue(list,0,callback,s);

	ge_list_executed[1] = list_id;
}

/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDrawBufferList(int pixel_size, void* frame_buffer, int frame_width)
{
	sendCommandi(210,pixel_size);
	sendCommandi(156,((unsigned int)frame_buffer) & 0xffffff);
	sendCommandi(157,((((unsigned int)frame_buffer) & 0xff000000) >> 8) | frame_width);
}

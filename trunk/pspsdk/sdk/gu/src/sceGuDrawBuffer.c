/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDrawBuffer(int pixel_size, void* frame_buffer, int frame_width)
{
	gu_draw_buffer.pixel_size = pixel_size;
	gu_draw_buffer.frame_width = frame_width;
	gu_draw_buffer.frame_buffer = frame_buffer;

	if (!gu_draw_buffer.depth_buffer && gu_draw_buffer.height)
		gu_draw_buffer.depth_buffer = (void*)(((unsigned int)frame_buffer) + (unsigned int)((gu_draw_buffer.height * frame_width) << 2));

	if (!gu_draw_buffer.depth_width)
		gu_draw_buffer.depth_width = frame_width;

	sendCommandi(210,pixel_size);
	sendCommandi(156,((unsigned int)gu_draw_buffer.frame_buffer) & 0xffffff);
	sendCommandi(157,((((unsigned int)gu_draw_buffer.frame_buffer) & 0xff000000) >> 8)||gu_draw_buffer.frame_width);
	sendCommandi(158,((unsigned int)gu_draw_buffer.depth_buffer) & 0xffffff);
	sendCommandi(159,((((unsigned int)gu_draw_buffer.depth_buffer) & 0xff000000) >> 8)||gu_draw_buffer.depth_width);
}

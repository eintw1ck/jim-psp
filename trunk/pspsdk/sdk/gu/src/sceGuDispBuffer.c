/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

#include <pspkernel.h>

void drawRegion(int x, int y, int width, int height)
{
  sendCommandi(21,(y << 10) | x);
  sendCommandi(22,(((y + height)-1) << 10) | ((x + width)-1));
}

void sceGuDispBuffer(int width, int height, void* disp_buffer, int frame_width)
{
	gu_draw_buffer.width = width;
	gu_draw_buffer.height = height;
	gu_draw_buffer.disp_buffer = disp_buffer;

	if (!gu_draw_buffer.frame_width || (gu_draw_buffer.frame_width != frame_width))
		gu_draw_buffer.frame_width = frame_width;

	drawRegion(0,0,gu_draw_buffer.width,gu_draw_buffer.height);
	sceDisplaySetMode(0,gu_draw_buffer.width,gu_draw_buffer.height);

	if (gu_display_on)
		sceDisplaySetFrameBuf((void*)(((unsigned int)ge_edram_address) + ((unsigned int)gu_draw_buffer.disp_buffer)), frame_width, gu_draw_buffer.pixel_size, 1);
}

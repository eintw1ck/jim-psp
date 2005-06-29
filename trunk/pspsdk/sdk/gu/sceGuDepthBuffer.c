/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDepthBuffer(void* depth_buffer, int depth_width)
{
	gu_draw_buffer.depth_buffer = depth_buffer;

	if (!gu_draw_buffer.depth_width || (gu_draw_buffer.depth_width != depth_width))
		gu_draw_buffer.depth_width = depth_width;

	sendCommandi(158,((unsigned int)depth_buffer) & 0xffffff);
	sendCommandi(159,((((unsigned int)depth_buffer) & 0xff000000) >> 8)|depth_width);
}

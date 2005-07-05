/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuLight(int index, int a1, int a2, const ScePspFVector3* position)
{
	GuLightSettings* settings = &light_settings[index];

	sendCommandf(settings->row0[2],position->x);
	sendCommandf(settings->row0[3],position->y);
	sendCommandf(settings->row1[0],position->z);

	int type = 2;
	if (a2 != 8)
		type = (a2^6) < 1 ? 1 : 0;

	sendCommandi(settings->row0[1],((a1 & 0x03) << 8)|type);
}

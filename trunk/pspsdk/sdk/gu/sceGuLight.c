/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuLight(int index, int a1, int a2, const float* position)
{
	GuLightSettings* settings = &light_settings[index];

	sendCommandf(settings->row0[2],position[0]);
	sendCommandf(settings->row0[3],position[1]);
	sendCommandf(settings->row1[0],position[2]);

	int type = 2;
	if (a2 != 8)
		type = (a2^6) < 1 ? 1 : 0;

	sendCommandi(settings->row0[1],((a1 & 0x03) << 8)|type);
}

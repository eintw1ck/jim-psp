/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuLightAtt(int index, float f12, float f13, float f14)
{
	GuLightSettings* settings = &light_settings[index];

	sendCommandf(settings->row2[3],f12);
	sendCommandf(settings->row3[0],f13);
	sendCommandf(settings->row3[1],f14);
}

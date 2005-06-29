/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuColorFunc(int a0, unsigned int color, int a2)
{
	sendCommandi(216,a0 & 0x03);
	sendCommandi(217,color & 0xffffff);
	sendCommandi(218,a2);
}

/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuBlendFunc(int a0, int a1, int a2, unsigned int a3, unsigned int t0)
{
	sendCommandi(223,a1 | (a2 << 4) | (a0 << 8));
	sendCommandi(224,a3 & 0xffffff);
	sendCommandi(225,t0 & 0xffffff);
}

/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuClutLoad(unsigned int a0, const void* cbp)
{
	sendCommandi(176,((unsigned int)cbp) & 0xffffff);
	sendCommandi(177,(((unsigned int)cbp) >> 8) & 0xf0000);
	sendCommandi(196,a0);
}

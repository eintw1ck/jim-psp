/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuFrontFace(unsigned int a0)
{
	if (a0)
		sendCommandi(155,0);
	else
		sendCommandi(155,1);
}

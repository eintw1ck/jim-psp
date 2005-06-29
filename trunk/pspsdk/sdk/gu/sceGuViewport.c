/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuViewport(int a0, int a1, int a2, int a3)
{
	sendCommandf(66,(float)a2);
	sendCommandf(67,(float)((-a3) + ((-a3) >> 31)));
	sendCommandf(69,(float)a0);
	sendCommandf(70,(float)a1);
}

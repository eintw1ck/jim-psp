/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuStencilOp(unsigned int a0, unsigned int a1, unsigned int a2)
{
	sendCommandi(221,a0 | (a1 << 8) | (a2 << 16));
}

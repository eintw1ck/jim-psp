/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuModelColor(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3)
{
	sendCommandi(84,a0 & 0xffffff);
	sendCommandi(86,a2 & 0xffffff);
	sendCommandi(85,a1 & 0xffffff);
	sendCommandi(87,a3 & 0xffffff);
}

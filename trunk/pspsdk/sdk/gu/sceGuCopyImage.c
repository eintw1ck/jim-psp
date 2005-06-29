/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuCopyImage(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int t0, unsigned int t1, void* ptr1, unsigned int t3, unsigned int stack0, unsigned int stack1, void* ptr2 )
{
	sendCommandi(178,((unsigned int)ptr1) & 0xffffff);
	sendCommandi(179,((((unsigned int)ptr1) & 0xff000000) >> 8)|t1);
	sendCommandi(235,(a2 << 10)|a1); // x/y relation?
	sendCommandi(180,((unsigned int)ptr2) & 0xffffff);
	sendCommandi(181,((((unsigned int)ptr2) & 0xff000000) >> 8)|stack1);
	sendCommandi(236,(stack0 << 10)|t3); // x/y relation?
	sendCommandi(238,((t0-1) << 10)|(a3-1)); // width/height?
	sendCommandi(234,(a0 ^ 0x03) ? 0 : 1); // upload-mode of some kind? local -> host, host -> local???
}

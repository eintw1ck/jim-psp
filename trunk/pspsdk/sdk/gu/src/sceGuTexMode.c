/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuTexMode(int a0, int a1, int a2, int a3)
{
	GuContext* context = &gu_contexts[gu_curr_context];
	context->texture_mode = a0;

	sendCommandi(194,(a1 << 16) | (a2 << 8) | (a3));
	sendCommandi(195,a0);

	sceGuTexFlush();
}

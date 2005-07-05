/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuTexMode(int tpsm, int a1, int a2, int swizzle)
{
	GuContext* context = &gu_contexts[gu_curr_context];
	context->texture_mode = tpsm;

	sendCommandi(194,(a1 << 16) | (a2 << 8) | (swizzle));
	sendCommandi(195,tpsm);

	sceGuTexFlush();
}

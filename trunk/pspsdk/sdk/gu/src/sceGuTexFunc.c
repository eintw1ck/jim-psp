/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuTexFunc(unsigned int a0, unsigned int a1)
{
	GuContext* context = &gu_contexts[gu_curr_context];
	context->texture_function = (a1 << 8) | a0;

	sendCommandi(201,((a1 << 8)|a0)|context->unknown_state);
}

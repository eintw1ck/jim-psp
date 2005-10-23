/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"
#include "vfpu_ops.h"

void sceGumLoadIdentity(void)
{
#ifdef GUM_USE_VFPU
	__asm__ volatile (
		cgen_asm(vmidt_q(Q_M300))
	);
#else
	gumLoadIdentity(gum_current_matrix);
#endif
	gum_matrix_update[gum_current_mode] = 1;
}

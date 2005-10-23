/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"
#include "vfpu_ops.h"

void sceGumUpdateMatrix(void)
{
	gum_stack_depth[gum_current_mode] = gum_current_matrix;

#ifdef GUM_USE_VFPU
	// flush dirty matrix from vfpu
	if (gum_matrix_update[gum_current_mode])
	{
		register void* m __asm("a0") = gum_current_matrix;
		__asm__ volatile (
			cgen_asm(sv_q(Q_C300,0,R_a0,0))
			cgen_asm(sv_q(Q_C310,4,R_a0,0))
			cgen_asm(sv_q(Q_C320,8,R_a0,0))
			cgen_asm(sv_q(Q_C330,12,R_a0,0))
		: "=r"(m) : "r"(m) : "memory");
	}
#endif

	unsigned int i;
	for (i = 0; i < 4; ++i)
	{
		if (gum_matrix_update[i])
		{
			sceGuSetMatrix(i,gum_stack_depth[i]);
			gum_matrix_update[i] = 0;
		}
	}
}

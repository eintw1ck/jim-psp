/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"
#include "vfpu_ops.h"

void sceGumMatrixMode(int mode)
{
#ifdef GUM_USE_VFPU
	{
		register void* m __asm("a1") = gum_current_matrix;
		__asm__ volatile (
			cgen_asm(sv_q(Q_C300, 0, R_a1, 0))
			cgen_asm(sv_q(Q_C310, 4, R_a1, 0))
			cgen_asm(sv_q(Q_C320, 8, R_a1, 0))
			cgen_asm(sv_q(Q_C330, 12, R_a1, 0))
		: : "r"(m) : "memory");
	}
#endif

	// switch stack
	gum_stack_depth[gum_current_mode] = gum_current_matrix;
	gum_current_matrix = gum_stack_depth[mode];
	gum_current_mode = mode;

#ifdef GUM_USE_VFPU
	{
		register void* m __asm("a1") = gum_current_matrix;
		__asm__ volatile (
			cgen_asm(lv_q(Q_C300, 0, R_a1, 0))
			cgen_asm(lv_q(Q_C310, 4, R_a1, 0))
			cgen_asm(lv_q(Q_C320, 8, R_a1, 0))
			cgen_asm(lv_q(Q_C330, 12, R_a1, 0))
		: : "r"(m) : "memory");
	}
#endif
}

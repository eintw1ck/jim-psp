/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"
#include "vfpu_ops.h"

void sceGumPopMatrix(void)
{
#ifdef GUM_USE_VFPU
	register void* m __asm("a0") = gum_current_matrix-1;
	__asm__ volatile (
		cgen_asm(lv_q(Q_C300,0,R_a0,0))
		cgen_asm(lv_q(Q_C310,4,R_a0,0))
		cgen_asm(lv_q(Q_C320,8,R_a0,0))
		cgen_asm(lv_q(Q_C330,12,R_a0,0))
	: "=r"(m) : "r"(m));
#endif
	gum_current_matrix--;
	gum_matrix_update[gum_current_mode] = 1;
}

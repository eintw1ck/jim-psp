/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"
#include "vfpu_ops.h"

#include <string.h>

void sceGumMultMatrix(const ScePspFMatrix4* m)
{
#ifdef GUM_USE_VFPU
	register ScePspFMatrix4* t __asm("a0") = GUM_ALIGNED_MATRIX();
	memcpy(t,m,sizeof(ScePspFMatrix4));
	__asm__ volatile (
		cgen_asm(lv_q(Q_C000,0,R_a0,0))
		cgen_asm(lv_q(Q_C010,4,R_a0,0))
		cgen_asm(lv_q(Q_C020,8,R_a0,0))
		cgen_asm(lv_q(Q_C030,12,R_a0,0))

		cgen_asm(vmmul_q(Q_M100,Q_M300,Q_M000))
		cgen_asm(vmmov_q(Q_M300,Q_M100))
	: "=r"(t) : "r"(t));
#else
	gumMultMatrix(gum_current_matrix,gum_current_matrix,m);  
#endif
	gum_matrix_update[gum_current_mode] = 1;
}

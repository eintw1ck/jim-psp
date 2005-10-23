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

void sceGumTranslate(const ScePspFVector3* v)
{
#ifdef GUM_USE_VFPU
	register ScePspFVector4* t __asm("a0") = GUM_ALIGNED_VECTOR();
	memcpy(t,v,sizeof(ScePspFVector4));
	t->w = 1.0f;

	__asm__ volatile (
		cgen_asm(vmidt_q(Q_M000))
		cgen_asm(lv_q(Q_C030,0,R_a0,0))
		cgen_asm(vmmul_q(Q_M100,Q_M300,Q_M000))
		cgen_asm(vmmov_q(Q_M300,Q_M100))
	: "=r"(t) : "r"(t));
#else
	gumTranslate(gum_current_matrix,v);
#endif
	gum_matrix_update[gum_current_mode] = 1;
}

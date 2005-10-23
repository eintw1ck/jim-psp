/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"
#include "vfpu_ops.h"

void sceGumRotateZ(float angle)
{
#ifdef GUM_USE_VFPU
	register ScePspFVector4* v __asm("a0") = GUM_ALIGNED_VECTOR();
	v->x = angle;

	__asm volatile (
		cgen_asm(vmidt_q(Q_M000))
		cgen_asm(lv_s(S_S100, 0, R_a0, 0))
		cgen_asm(vcst_s(S_S101, 5))
		cgen_asm(vmul_s(S_S100, S_S101, S_S100))
		cgen_asm(vcos_s(S_S000, S_S100))
		cgen_asm(vsin_s(S_S001, S_S100))
		cgen_asm(vneg_s(S_S010, S_S001))
		cgen_asm(vmov_s(S_S011, S_S000))
		cgen_asm(vmmul_q(Q_M100, Q_M300, Q_M000))
		cgen_asm(vmmov_q(Q_M300, Q_M100))
	: : "r"(v));
#else
	gumRotateZ(gum_current_matrix,angle);
#endif
	gum_matrix_update[gum_current_mode] = 1;
}

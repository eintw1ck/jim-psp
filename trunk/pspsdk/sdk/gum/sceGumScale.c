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

void sceGumScale(const ScePspFVector3* v)
{
#ifdef GUM_USE_VFPU
	register ScePspFVector4* t __asm("a1") = GUM_ALIGNED_VECTOR();
	memcpy(t,v,sizeof(ScePspFVector3));
	__asm__ volatile (
		cgen_asm(lv_q(Q_C000,0,R_a0,0))
		cgen_asm(vscl_t(Q_C300,Q_C300,S_S000))
		cgen_asm(vscl_t(Q_C310,Q_C310,S_S001))
		cgen_asm(vscl_t(Q_C320,Q_C320,S_S002))
	: : "r"(t));
#else
	gumScale(gum_current_matrix,v);
#endif
	gum_matrix_update[gum_current_mode] = 1;
}

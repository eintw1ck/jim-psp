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

void sceGumStoreMatrix(ScePspFMatrix4* m)
{
#ifdef GUM_USE_VFPU
	register ScePspFMatrix4* t __asm("a0") = GUM_ALIGNED_MATRIX();
	__asm__ volatile (
		cgen_asm(sv_q(Q_C300,0,R_a0,0))
		cgen_asm(sv_q(Q_C310,4,R_a0,0))
		cgen_asm(sv_q(Q_C320,8,R_a0,0))
		cgen_asm(sv_q(Q_C330,12,R_a0,0))
	: "=r"(t) : "r"(t) : "memory");
	memcpy(m,t,sizeof(ScePspFMatrix4));
#else
	memcpy(m,gum_current_matrix,sizeof(ScePspFMatrix4));
#endif
}

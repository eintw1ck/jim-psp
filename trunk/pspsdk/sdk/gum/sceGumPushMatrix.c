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

void sceGumPushMatrix(void)
{
#ifdef GUM_USE_VFPU
	register void* m __asm("a0") = gum_current_matrix;
	__asm__ volatile (
		cgen_asm(sv_q(Q_C300,0,R_a0,0))
		cgen_asm(sv_q(Q_C300,4,R_a0,0))
		cgen_asm(sv_q(Q_C300,8,R_a0,0))
		cgen_asm(sv_q(Q_C300,12,R_a0,0))
	: "=r"(m) : "r"(m) : "memory");
#else
	memcpy(gum_current_matrix+1,gum_current_matrix,sizeof(ScePspFMatrix4));
#endif
	gum_current_matrix++;
}

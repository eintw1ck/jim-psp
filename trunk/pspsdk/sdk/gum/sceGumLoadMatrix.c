/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"
#include <string.h>
#include "vfpu_ops.h"

void sceGumLoadMatrix(const ScePspFMatrix4* m)
{
#ifdef GUM_USE_VFPU
	register ScePspFMatrix4* r __asm("a0") = GUM_ALIGNED_MATRIX();
	memcpy(r,m,sizeof(ScePspFMatrix4));

	__asm__ volatile (
		cgen_asm(lv_q(Q_C300,0,R_a0,0))
		cgen_asm(lv_q(Q_C310,4,R_a0,0))
		cgen_asm(lv_q(Q_C320,8,R_a0,0))
		cgen_asm(lv_q(Q_C330,12,R_a0,0))
	: "=r"(r) : "r"(r), "r"(m) : "memory");
#else
  memcpy(gum_current_matrix,m,sizeof(ScePspFMatrix4));
#endif
  gum_matrix_update[gum_current_mode] = 1;
}

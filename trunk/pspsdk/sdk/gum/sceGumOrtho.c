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

void sceGumOrtho(float left, float right, float bottom, float top, float near, float far)
{
	register ScePspFMatrix4* t __asm("a0") = GUM_ALIGNED_MATRIX();
	float dx = right-left, dy = top-bottom, dz = far-near;

	memset(t,0,sizeof(ScePspFMatrix4));

	t->x.x = 2.0f / dx;
	t->w.x = -(right + left) / dx;
	t->y.y = 2.0f / dy;
	t->w.y = -(top + bottom) / dy;
	t->z.z = -2.0f / dz;
	t->w.z = -(far + near) / dz;
	t->w.w = 1.0f;

#ifdef GUM_USE_VFPU
	__asm__ volatile (
		cgen_asm(lv_q(Q_C000,0,R_a0,0))
		cgen_asm(lv_q(Q_C010,4,R_a0,0))
		cgen_asm(lv_q(Q_C020,8,R_a0,0))
		cgen_asm(lv_q(Q_C030,12,R_a0,0))
		cgen_asm(vmmul_q(Q_M100,Q_M300,Q_M000))
		cgen_asm(vmmov_q(Q_M300,Q_M100))
	: : "r"(t) );
        gum_matrix_update[gum_current_mode] = 1;
#else
	sceGumMultMatrix(t);
#endif
}

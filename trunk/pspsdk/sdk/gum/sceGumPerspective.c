/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"
#include "vfpu_ops.h"

#include <math.h>
#include <string.h>

void sceGumPerspective(float fovy, float aspect, float near, float far)
{
	float angle = (fovy / 2) * (GU_PI/180.0f);
	float cotangent = cosf(angle) / sinf(angle);
	float delta_z = near-far;
	register ScePspFMatrix4* t __asm("a0") = GUM_ALIGNED_MATRIX();

	memset(t,0,sizeof(ScePspFMatrix4));
	t->x.x = cotangent / aspect;
	t->y.y = cotangent;
	t->z.z = (far + near) / delta_z; // -(far + near) / delta_z
	t->w.z = 2.0f * (far * near) / delta_z; // -2 * (far * near) / delta_z
	t->z.w = -1.0f;
	t->w.w = 0.0f;

#ifdef GUM_USE_VFPU
	__asm__ volatile (
		cgen_asm(lv_q(Q_C000,0,R_a0,0))
		cgen_asm(lv_q(Q_C010,4,R_a0,0))
		cgen_asm(lv_q(Q_C020,8,R_a0,0))
		cgen_asm(lv_q(Q_C030,12,R_a0,0))
		cgen_asm(vmmul_q(Q_M100,Q_M300,Q_M000))
		cgen_asm(vmmov_q(Q_M300,Q_M100))
	: : "r"(t));
	gum_matrix_update[gum_current_mode] = 1;
#else
	sceGumMultMatrix(t);
#endif
}

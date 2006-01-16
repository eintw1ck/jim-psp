/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

#include <string.h>
#include <math.h>

// TODO: write most standalone routines in vfpu assembler as well
// TODO: get rid of all misalignments that require memcpy()-fixups

#ifdef F_gumFastInverse_vfpu
void gumFastInverse(ScePspFMatrix4* m, const ScePspFMatrix4* a)
{
	ScePspFMatrix4* r = GUM_ALIGNED_MATRIX();
	memcpy(r,a,sizeof(ScePspFMatrix4));

	__asm__ volatile (
		"lv.q C200, 0(%1)\n"
		"lv.q C210, 16(%1)\n"
		"lv.q C220, 32(%1)\n"
		"lv.q C230, 48(%1)\n"

		"vmidt.q M000\n"
		"vmmov.t M000, E200\n"
		"vneg.t C100, C230\n"
		"vdot.t S030, C100, C200\n"
		"vdot.t S031, C100, C210\n"
		"vdot.t S032, C100, C220\n"

		"sv.q C000, 0(%1)\n"
		"sv.q C010, 16(%1)\n"
		"sv.q C020, 32(%1)\n"
		"sv.q C030, 48(%1)\n"
	: "=r"(r) : "r"(r) : "memory" );

	memcpy(m,r,sizeof(ScePspFMatrix4));
}
#endif

/*
#ifdef F_gumMultMatrix_vfpu
void gumMultMatrix(ScePspFMatrix4* result, const ScePspFMatrix4* a, const ScePspFMatrix4* b)
{
	ScePspFMatrix4* t1 = GUM_ALIGNED_MATRIX();
	ScePspFMatrix4* t2 = GUM_ALIGNED_MATRIX();

	memcpy(t1,a,sizeof(ScePspFMatrix4));
	memcpy(t2,b,sizeof(ScePspFMatrix4));

	__asm__ volatile
	(
		"lv.q C000, 0(%1)\n"
		"lv.q C010, 16(%1)\n"
		"lv.q C020, 32(%1)\n"
		"lv.q C030, 48(%1)\n"

		"lv.q C100, 0(%2)\n"
		"lv.q C110, 16(%2)\n"
		"lv.q C120, 32(%2)\n"
		"lv.q C130, 48(%2)\n"

		"vmmul.q M200, M100, M000\n"

		"sv.q C200, 0(%1)\n"
		"sv.q C210, 16(%1)\n"
		"sv.q C220, 32(%1)\n"
		"sv.q C230, 48(%1)\n"
	: "=r"(t1) : "r"(t1), "r"(t2) : "memory");

	memcpy(result,t1,sizeof(ScePspFMatrix4));
}
#endif
*/

#ifdef F_sceGumFastInverse_vfpu
void sceGumFastInverse()
{
	__asm__ volatile (
		"vmidt.q M000\n"
		"vmmov.t M000, E300\n"
		"vneg.t  C100, C330\n"
		"vdot.t	 S030, C100, C300\n" // TODO: figure out if there is any op to multiply vector with matrix, and replace this sequence
		"vdot.t	 S031, C100, C310\n"
		"vdot.t	 S032, C100, C320\n"
		"vmmov.q M300, M000\n"
	);

	gum_current_matrix_update = 1;
}
#endif
/*
#ifdef F_sceGumFastInverse_vfpu
void sceGumFastInverse()
{
	ScePspFMatrix4* t = GUM_ALIGNED_MATRIX();

	__asm__ volatile (
		"sv.q C300, 0(%1)\n"
		"sv.q C310, 16(%1)\n"
		"sv.q C320, 32(%1)\n"
		"sv.q C330, 48(%1)\n"
	: "=r"(t) : "r"(t) : "memory");

	gumFastInverse(t,t);

	__asm__ volatile (
		"lv.q C300.q, 0(%0)\n"
		"lv.q C310.q, 16(%0)\n"
		"lv.q C320.q, 32(%0)\n"
		"lv.q C330.q, 48(%0)\n"
	: : "r"(t) : "memory");

	gum_current_matrix_update = 1;
}
#endif
*/

#ifdef F_sceGumFullInverse_vfpu
void sceGumFullInverse()
{
	ScePspFMatrix4* t = GUM_ALIGNED_MATRIX();

	__asm__ volatile (
		"sv.q C300, 0(%1)\n"
		"sv.q C310, 16(%1)\n"
		"sv.q C320, 32(%1)\n"
		"sv.q C330, 48(%1)\n"
	: "=r"(t) : "r"(t) : "memory");

	gumFastInverse(t,t);

	__asm__ volatile (
		"lv.q C300.q, 0(%0)\n"
		"lv.q C310.q, 16(%0)\n"
		"lv.q C320.q, 32(%0)\n"
		"lv.q C330.q, 48(%0)\n"
	: : "r"(t) : "memory");

	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumLoadIdentity_vfpu
void sceGumLoadIdentity(void)
{
	__asm__ volatile (
		"vmidt.q M300\n"
	);
	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumLoadMatrix_vfpu
void sceGumLoadMatrix(const ScePspFMatrix4* m)
{
	ScePspFMatrix4* r = GUM_ALIGNED_MATRIX();
	memcpy(r,m,sizeof(ScePspFMatrix4));
	
	__asm__ volatile (
		"lv.q C300.q, 0(%0)\n"
		"lv.q C310.q, 16(%0)\n"
		"lv.q C320.q, 32(%0)\n"
		"lv.q C330.q, 48(%0)\n"
	: : "r"(r) : "memory");

	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumLookAt_vfpu
void sceGumLookAt(ScePspFVector3* eye, ScePspFVector3* center, ScePspFVector3* up)
{
	ScePspFMatrix4* t = GUM_ALIGNED_MATRIX();
	gumLookAt(t,eye,center,up);

	__asm__ volatile (
		"lv.q C300.q, 0(%0)\n"
		"lv.q C310.q, 16(%0)\n"
		"lv.q C320.q, 32(%0)\n"
		"lv.q C330.q, 48(%0)\n"
		"vmmul.q M100, M300, M000\n"
		"vmmov.q M300, M100\n"
	: : "r"(t) );

	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumMatrixMode_vfpu
void sceGumMatrixMode(int mode)
{
	__asm__ volatile (
		"sv.q C300, 0(%1)\n"
		"sv.q C310, 16(%1)\n"
		"sv.q C320, 32(%1)\n"
		"sv.q C330, 48(%1)\n"
	: "=r"(gum_current_matrix) : "r"(gum_current_matrix) : "memory");

	// switch stack
	gum_matrix_update[gum_current_mode] = gum_current_matrix_update;
	gum_stack_depth[gum_current_mode] = gum_current_matrix;
	gum_current_matrix = gum_stack_depth[mode];
	gum_current_mode = mode;
	gum_current_matrix_update = gum_matrix_update[gum_current_mode];

	__asm__ volatile (
		"lv.q C300, 0(%0)\n"
		"lv.q C310, 16(%0)\n"
		"lv.q C320, 32(%0)\n"
		"lv.q C330, 48(%0)\n"
	: : "r"(gum_current_matrix) : "memory");
}
#endif

#ifdef F_sceGumMultMatrix_vfpu
void sceGumMultMatrix(const ScePspFMatrix4* m)
{
	ScePspFMatrix4* t = GUM_ALIGNED_MATRIX();
	memcpy(t,m,sizeof(ScePspFMatrix4));

	__asm__ volatile (
		"lv.q C000, 0(%0)\n"
		"lv.q C010, 16(%0)\n"
		"lv.q C020, 32(%0)\n"
		"lv.q C030, 48(%0)\n"
		"vmmul.q M100, M300, M000\n"
		"vmmov.q M300, M100\n"
	: "=r"(t) : "r"(t));

	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumOrtho_vfpu
void sceGumOrtho(float left, float right, float bottom, float top, float near, float far)
{
	ScePspFMatrix4* t = GUM_ALIGNED_MATRIX();
	float dx = right-left, dy = top-bottom, dz = far-near;

	memset(t,0,sizeof(ScePspFMatrix4));

	t->x.x = 2.0f / dx;
	t->w.x = -(right + left) / dx;
	t->y.y = 2.0f / dy;
	t->w.y = -(top + bottom) / dy;
	t->z.z = -2.0f / dz;
	t->w.z = -(far + near) / dz;
	t->w.w = 1.0f;

	__asm__ volatile (
		"lv.q C000, 0(%0)\n"
		"lv.q C010, 16(%0)\n"
		"lv.q C020, 32(%0)\n"
		"lv.q C030, 48(%0)\n"
		"vmmul.q M100, M300, M000\n"
		"vmmov.q M300, M100\n"
	: : "r"(t) );

	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumPerspective_vfpu
void sceGumPerspective(float fovy, float aspect, float near, float far)
{
	float angle = (fovy / 2) * (GU_PI/180.0f);
	float cotangent = cosf(angle) / sinf(angle);
	float delta_z = near-far;
	ScePspFMatrix4* t = GUM_ALIGNED_MATRIX();

	memset(t,0,sizeof(ScePspFMatrix4));
	t->x.x = cotangent / aspect;
	t->y.y = cotangent;
	t->z.z = (far + near) / delta_z; // -(far + near) / delta_z
	t->w.z = 2.0f * (far * near) / delta_z; // -2 * (far * near) / delta_z
	t->z.w = -1.0f;
	t->w.w = 0.0f;

	__asm__ volatile (
		"lv.q C000, 0(%0)\n"
		"lv.q C010, 16(%0)\n"
		"lv.q C020, 32(%0)\n"
		"lv.q C030, 48(%0)\n"
		"vmmul.q M100, M300, M000\n"
		"vmmov.q M300, M100\n"
	: : "r"(t));

	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumPopMatrix_vfpu
void sceGumPopMatrix(void)
{
	ScePspFMatrix4* m = gum_current_matrix-1;
	__asm__ volatile (
		"lv.q C300.q, 0(%0)\n"
		"lv.q C310.q, 16(%0)\n"
		"lv.q C320.q, 32(%0)\n"
		"lv.q C330.q, 48(%0)\n"
	: : "r"(m));

	gum_current_matrix--;
	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumPushMatrix_vfpu
void sceGumPushMatrix(void)
{
	ScePspFMatrix4* m = gum_current_matrix;
	__asm__ volatile (
		"sv.q C300, 0(%1)\n"
		"sv.q C310, 16(%1)\n"
		"sv.q C320, 32(%1)\n"
		"sv.q C330, 48(%1)\n"
	: "=r"(m) : "r"(m) : "memory");

	gum_current_matrix++;
}
#endif

#ifdef F_sceGumRotateX_vfpu
void sceGumRotateX(float angle)
{
	ScePspFVector4* v = GUM_ALIGNED_VECTOR();
	v->x = angle;

	__asm__ volatile (
		"vmidt.q M000\n"
		"lv.s S100, 0(%0)\n"
		"vcst.s S101, VFPU_2_PI\n"
		"vmul.s S100, S101, S100\n"
		"vcos.s S011, S100\n"
		"vsin.s S012, S100\n"
		"vneg.s S021, S012\n"
		"vmov.s S022, S011\n"
		"vmmul.q M100, M300, M000\n"
		"vmmov.q M300, M100\n"
	: : "r"(v));

	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumRotateY_vfpu
void sceGumRotateY(float angle)
{
	ScePspFVector4* v = GUM_ALIGNED_VECTOR();
	v->x = angle;

	__asm__ volatile (
		"vmidt.q M000\n"
		"lv.s S100, 0(%0)\n"
		"vcst.s S101, VFPU_2_PI\n"
		"vmul.s S100, S101, S100\n"
		"vcos.s S000, S100\n"
		"vsin.s S020, S100\n"
		"vneg.s S002, S020\n"
		"vmov.s S022, S000\n"
		"vmmul.q M100, M300, M000\n"
		"vmmov.q M300, M100\n"
	: : "r"(v));

	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumRotateZ_vfpu
void sceGumRotateZ(float angle)
{
	ScePspFVector4* v = GUM_ALIGNED_VECTOR();
	v->x = angle;

	__asm volatile (
		"vmidt.q M000\n"
		"lv.s S100, 0(%0)\n"
		"vcst.s S101, VFPU_2_PI\n"
		"vmul.s S100, S101, S100\n"
		"vcos.s S000, S100\n"
		"vsin.s S001, S100\n"
		"vneg.s S010, S001\n"
		"vmov.s S011, S000\n"
		"vmmul.q M100, M300, M000\n"
		"vmmov.q M300, M100\n"
	: : "r"(v));

	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumScale_vfpu
void sceGumScale(const ScePspFVector3* v)
{
	ScePspFVector4* t = GUM_ALIGNED_VECTOR();
	memcpy(t,v,sizeof(ScePspFVector3));
	__asm__ volatile (
		"lv.q C000, 0(%0)\n"
		"vscl.t C300, C300, S000\n"
		"vscl.t C310, C310, S001\n"
		"vscl.t C320, C320, S002\n"
	: : "r"(t));

	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumStoreMatrix_vfpu
void sceGumStoreMatrix(ScePspFMatrix4* m)
{
	ScePspFMatrix4* t = GUM_ALIGNED_MATRIX();
	__asm__ volatile (
		"sv.q C300, 0(%1)\n"
		"sv.q C310, 16(%1)\n"
		"sv.q C320, 32(%1)\n"
		"sv.q C330, 48(%1)\n"
	: "=r"(t) : "r"(t) : "memory");
	memcpy(m,t,sizeof(ScePspFMatrix4));
}
#endif

#ifdef F_sceGumTranslate_vfpu
void sceGumTranslate(const ScePspFVector3* v)
{
	ScePspFVector4* t = GUM_ALIGNED_VECTOR();
	memcpy(t,v,sizeof(ScePspFVector4));
	t->w = 1.0f;

	__asm__ volatile (
		"vmidt.q M000\n"
		"lv.q C030, 0(%0)\n"
		"vmmul.q M100, M300, M000\n"
		"vmmov.q M300, M100\n"
	: : "r"(t));

	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumUpdateMatrix_vfpu
void sceGumUpdateMatrix(void)
{
	gum_stack_depth[gum_current_mode] = gum_current_matrix;

	// flush dirty matrix from vfpu
	if (gum_current_matrix_update)
	{
		__asm__ volatile (
			"sv.q C300, 0(%1)\n"
			"sv.q C310, 16(%1)\n"
			"sv.q C320, 32(%1)\n"
			"sv.q C330, 48(%1)\n"
		: "=r"(gum_current_matrix) : "r"(gum_current_matrix) : "memory");
		gum_matrix_update[gum_current_mode] = gum_current_matrix_update;
		gum_current_matrix_update = 0;
	}


	unsigned int i;
	for (i = 0; i < 4; ++i)
	{
		if (gum_matrix_update[i])
		{
			sceGuSetMatrix(i,gum_stack_depth[i]);
			gum_matrix_update[i] = 0;
		}
	}
}
#endif

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

#include "pspvfpu.h"

#ifdef F_gumInit_vfpu
void gumInit(void)
{
	if (gum_vfpucontext == NULL)
		gum_vfpucontext = pspvfpu_initcontext();
}
#endif

#ifdef F_gumScale_vfpu
void gumScale(ScePspFMatrix4* m, const ScePspFVector3* v)
{
	pspvfpu_use_matrices(gum_vfpucontext, 0, VMAT0 | VMAT1);

	__asm__ volatile (
		"ulv.q C100,  0 + %0\n"
		"ulv.q C110, 16 + %0\n"
		"ulv.q C120, 32 + %0\n"
		"ulv.q C130, 48 + %0\n"

		"ulv.q C000, %1\n"

		"vscl.t C100, C100, S000\n"
		"vscl.t C110, C110, S001\n"
		"vscl.t C120, C120, S002\n"

		"usv.q C100,  0 + %0\n"
		"usv.q C110, 16 + %0\n"
		"usv.q C120, 32 + %0\n"
		"usv.q C130, 48 + %0\n"
	: "+m"(*m) : "m"(*v));
}
#endif

#ifdef F_gumTranslate_vfpu
void gumTranslate(ScePspFMatrix4* m, const ScePspFVector3* v)
{
#if 0
	pspvfpu_use_matrices(gum_vfpucontext, 0, VMAT0 | VMAT1 | VMAT2);

	__asm__ volatile (
		"ulv.q C100,  0 + %0\n"
		"ulv.q C110, 16 + %0\n"
		"ulv.q C120, 32 + %0\n"
		"ulv.q C130, 48 + %0\n"

		"vmidt.q M000\n"
		"ulv.q   C200, %1\n"
		"vmov.t  C030, C200\n"
		"vmmul.q M200, M100, M000\n"

		"usv.q C200,  0 + %0\n"
		"usv.q C210, 16 + %0\n"
		"usv.q C220, 32 + %0\n"
		"usv.q C230, 48 + %0\n"
		: "+m"(*m) : "m"(*v));
#else
	pspvfpu_use_matrices(gum_vfpucontext, 0, VMAT0 | VMAT1);

	/* This might be a little faster, since the vmmul is a
	   pretty long-latency instruction, compared to simple
	   scales and adds. Also uses fewer registers (M000 &
	   M100) */
	__asm__ volatile (
		"ulv.q C030, %1\n"

		"ulv.q C100,  0 + %0\n"
		"ulv.q C110, 16 + %0\n"
		"ulv.q C120, 32 + %0\n"
		"ulv.q C130, 48 + %0\n"

		"vscl.q	C000, C100, S030\n"
		"vscl.q	C010, C110, S031\n"
		"vscl.q	C020, C120, S032\n"

		"vadd.q	C130, C130, C000\n"
		"vadd.q	C130, C130, C010\n"
		"vadd.q	C130, C130, C020\n"

		"usv.q C130, 48 + %0\n"	// only C130 has changed
		: "+m"(*m) : "m"(*v));
#endif
}
#endif

#ifdef F_gumRotateX_vfpu
void gumRotateX(ScePspFMatrix4* m, float angle)
{
	pspvfpu_use_matrices(gum_vfpucontext, 0, VMAT0 | VMAT1 | VMAT2);

	__asm__ volatile (
		"ulv.q C200,  0 + %0\n"
		"ulv.q C210, 16 + %0\n"
		"ulv.q C220, 32 + %0\n"
		"ulv.q C230, 48 + %0\n"

		"vmidt.q M000\n"
		"mtv  %1, S100\n"
		"vcst.s S101, VFPU_2_PI\n"
		"vmul.s S100, S101, S100\n"
		"vrot.q C010, S100, [ 0, c, s, 0]\n"
		"vrot.q C020, S100, [ 0,-s, c, 0]\n"
		"vmmul.q M100, M200, M000\n"

		"usv.q C100,  0 + %0\n"
		"usv.q C110, 16 + %0\n"
		"usv.q C120, 32 + %0\n"
		"usv.q C130, 48 + %0\n"
	: "+m"(*m) : "r"(angle));
}
#endif

#ifdef F_gumRotateY_vfpu
void gumRotateY(ScePspFMatrix4* m, float angle)
{
	pspvfpu_use_matrices(gum_vfpucontext, 0, VMAT0 | VMAT1 | VMAT2);

	__asm__ volatile (
		"ulv.q C200,  0 + %0\n"
		"ulv.q C210, 16 + %0\n"
		"ulv.q C220, 32 + %0\n"
		"ulv.q C230, 48 + %0\n"

		"vmidt.q M000\n"
		"mtv  %1, S100\n"
		"vcst.s S101, VFPU_2_PI\n"
		"vmul.s S100, S101, S100\n"
		"vrot.q C000, S100, [ c, 0,-s, 0]\n"
		"vrot.q C020, S100, [ s, 0, c, 0]\n"
		"vmmul.q M100, M200, M000\n"

		"usv.q C100,  0 + %0\n"
		"usv.q C110, 16 + %0\n"
		"usv.q C120, 32 + %0\n"
		"usv.q C130, 48 + %0\n"
	: "+m"(*m) : "r"(angle));
}
#endif

#ifdef F_gumRotateZ_vfpu
void gumRotateZ(ScePspFMatrix4* m, float angle)
{
	pspvfpu_use_matrices(gum_vfpucontext, 0, VMAT0 | VMAT1 | VMAT2);

	__asm__ volatile (
		"ulv.q C200,  0 + %0\n"
		"ulv.q C210, 16 + %0\n"
		"ulv.q C220, 32 + %0\n"
		"ulv.q C230, 48 + %0\n"

		"vmidt.q M000\n"
		"mtv  %1, S100\n"
		"vcst.s S101, VFPU_2_PI\n"
		"vmul.s S100, S101, S100\n"
		"vrot.q C000, S100, [ c, s, 0, 0]\n"
		"vrot.q C010, S100, [-s, c, 0, 0]\n"
		"vmmul.q M100, M200, M000\n"

		"usv.q C100,  0 + %0\n"
		"usv.q C110, 16 + %0\n"
		"usv.q C120, 32 + %0\n"
		"usv.q C130, 48 + %0\n"
	: "+m"(*m) : "r"(angle));
}
#endif

#ifdef F_gumLoadIdentity_vfpu
void gumLoadIdentity(ScePspFMatrix4* m)
{
	pspvfpu_use_matrices(gum_vfpucontext, 0, VMAT0);

	__asm__ volatile (
		"vmidt.q M000\n"
		"usv.q C000,  0 + %0\n"
		"usv.q C010, 16 + %0\n"
		"usv.q C020, 32 + %0\n"
		"usv.q C030, 48 + %0\n"
	: "=m"(*m) : : "memory" );
}
#endif

#ifdef F_gumFastInverse_vfpu
void gumFastInverse(ScePspFMatrix4* m, const ScePspFMatrix4* a)
{
	pspvfpu_use_matrices(gum_vfpucontext, 0, VMAT0 | VMAT1 | VMAT2);

	__asm__ volatile (
		"ulv.q C200,  0 + %1\n"
		"ulv.q C210, 16 + %1\n"
		"ulv.q C220, 32 + %1\n"
		"ulv.q C230, 48 + %1\n"

		"vmidt.q M000\n"
		"vmmov.t M000, E200\n"
		"vneg.t C100, C230\n"
		"vtfm3.t C030, M200, C100\n"

		"usv.q C000,  0 + %0\n"
		"usv.q C010, 16 + %0\n"
		"usv.q C020, 32 + %0\n"
		"usv.q C030, 48 + %0\n"
	: "=m"(*m) : "m"(*a) : "memory" );
}
#endif

#ifdef F_gumMultMatrix_vfpu
void gumMultMatrix(ScePspFMatrix4* result, const ScePspFMatrix4* a, const ScePspFMatrix4* b)
{
	pspvfpu_use_matrices(gum_vfpucontext, 0, VMAT0 | VMAT1 | VMAT2);

	__asm__ volatile
	(
		"ulv.q C000,  0 + %1\n"
		"ulv.q C010, 16 + %1\n"
		"ulv.q C020, 32 + %1\n"
		"ulv.q C030, 48 + %1\n"

		"ulv.q C100,  0 + %2\n"
		"ulv.q C110, 16 + %2\n"
		"ulv.q C120, 32 + %2\n"
		"ulv.q C130, 48 + %2\n"

		"vmmul.q M200, M000, M100\n"

		"usv.q C200,  0 + %0\n"
		"usv.q C210, 16 + %0\n"
		"usv.q C220, 32 + %0\n"
		"usv.q C230, 48 + %0\n"
	: "=m"(*result) : "m"(*a), "m"(*b) : "memory");
}
#endif

#ifdef F_sceGumFastInverse_vfpu
void sceGumFastInverse()
{
	pspvfpu_use_matrices(gum_vfpucontext, VMAT3, VMAT0 | VMAT1);

	__asm__ volatile (
		"vmidt.q M000\n"
		"vmmov.t M000, E300\n"
		"vneg.t  C100, C330\n"
		"vtfm3.t C030, M300, C100\n"
		"vmmov.q M300, M000\n"
	);

	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumFullInverse_vfpu
void sceGumFullInverse()
{
	ScePspFMatrix4* t = GUM_ALIGNED_MATRIX();

	pspvfpu_use_matrices(gum_vfpucontext, VMAT3, VMAT0 | VMAT1);

	__asm__ volatile (
		"sv.q C300,  0 + %0\n"
		"sv.q C310, 16 + %0\n"
		"sv.q C320, 32 + %0\n"
		"sv.q C330, 48 + %0\n"
	: "=m"(*t) : : "memory");

	gumFastInverse(t,t);

	__asm__ volatile (
		"lv.q C300.q,  0 + %0\n"
		"lv.q C310.q, 16 + %0\n"
		"lv.q C320.q, 32 + %0\n"
		"lv.q C330.q, 48 + %0\n"
	: : "m"(*t) : "memory");

	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumLoadIdentity_vfpu
void sceGumLoadIdentity(void)
{
	if (gum_vfpucontext == NULL)
		gum_vfpucontext = pspvfpu_initcontext();
	pspvfpu_use_matrices(gum_vfpucontext, VMAT3, 0);

	__asm__ volatile (
		"vmidt.q M300\n"
	);
	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumLoadMatrix_vfpu
void sceGumLoadMatrix(const ScePspFMatrix4* m)
{
	if (gum_vfpucontext == NULL)
		gum_vfpucontext = pspvfpu_initcontext();
	pspvfpu_use_matrices(gum_vfpucontext, VMAT3, 0);

	__asm__ volatile (
		"ulv.q C300.q,  0 + %0\n"
		"ulv.q C310.q, 16 + %0\n"
		"ulv.q C320.q, 32 + %0\n"
		"ulv.q C330.q, 48 + %0\n"
	: : "m"(*m) : "memory");

	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumLookAt_vfpu
void sceGumLookAt(ScePspFVector3* eye, ScePspFVector3* center, ScePspFVector3* up)
{
	ScePspFMatrix4* t = GUM_ALIGNED_MATRIX();
	gumLookAt(t,eye,center,up);

	pspvfpu_use_matrices(gum_vfpucontext, VMAT3, VMAT0 | VMAT1);

	__asm__ volatile (
		"lv.q C000.q,  0 + %0\n"
		"lv.q C010.q, 16 + %0\n"
		"lv.q C020.q, 32 + %0\n"
		"lv.q C030.q, 48 + %0\n"
		"vmmul.q M100, M300, M000\n"
		"vmmov.q M300, M100\n"
	: : "m"(*t) );

	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumMatrixMode_vfpu
void sceGumMatrixMode(int mode)
{
	pspvfpu_use_matrices(gum_vfpucontext, VMAT3, 0);

	__asm__ volatile (
		"sv.q C300,  0 + %0\n"
		"sv.q C310, 16 + %0\n"
		"sv.q C320, 32 + %0\n"
		"sv.q C330, 48 + %0\n"
	: "=m"(*gum_current_matrix) : : "memory");

	// switch stack
	gum_matrix_update[gum_current_mode] = gum_current_matrix_update;
	gum_stack_depth[gum_current_mode] = gum_current_matrix;
	gum_current_matrix = gum_stack_depth[mode];
	gum_current_mode = mode;
	gum_current_matrix_update = gum_matrix_update[gum_current_mode];

	__asm__ volatile (
		"lv.q C300,  0 + %0\n"
		"lv.q C310, 16 + %0\n"
		"lv.q C320, 32 + %0\n"
		"lv.q C330, 48 + %0\n"
	: : "m"(*gum_current_matrix) : "memory");
}
#endif

#ifdef F_sceGumMultMatrix_vfpu
void sceGumMultMatrix(const ScePspFMatrix4* m)
{
	pspvfpu_use_matrices(gum_vfpucontext, VMAT3, VMAT0 | VMAT1);

	__asm__ volatile (
		"ulv.q C000,  0 + %0\n"
		"ulv.q C010, 16 + %0\n"
		"ulv.q C020, 32 + %0\n"
		"ulv.q C030, 48 + %0\n"
		"vmmul.q M100, M300, M000\n"
		"vmmov.q M300, M100\n"
	: : "m"(*m));

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

	pspvfpu_use_matrices(gum_vfpucontext, VMAT3, VMAT0 | VMAT1);

	__asm__ volatile (
		"ulv.q C000,  0 + %0\n"
		"ulv.q C010, 16 + %0\n"
		"ulv.q C020, 32 + %0\n"
		"ulv.q C030, 48 + %0\n"
		"vmmul.q M100, M300, M000\n"
		"vmmov.q M300, M100\n"
	: : "m"(*t));

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

	pspvfpu_use_matrices(gum_vfpucontext, VMAT3, VMAT0 | VMAT1);

	__asm__ volatile (
		"ulv.q C000,  0 + %0\n"
		"ulv.q C010, 16 + %0\n"
		"ulv.q C020, 32 + %0\n"
		"ulv.q C030, 48 + %0\n"
		"vmmul.q M100, M300, M000\n"
		"vmmov.q M300, M100\n"
	: : "m"(*t));

	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumPopMatrix_vfpu
void sceGumPopMatrix(void)
{
	ScePspFMatrix4* m = --gum_current_matrix;

	pspvfpu_use_matrices(gum_vfpucontext, VMAT3, 0);

	__asm__ volatile (
		"lv.q C300.q,  0 + %0\n"
		"lv.q C310.q, 16 + %0\n"
		"lv.q C320.q, 32 + %0\n"
		"lv.q C330.q, 48 + %0\n"
	: : "m"(*m));

	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumPushMatrix_vfpu
void sceGumPushMatrix(void)
{
	ScePspFMatrix4* m = gum_current_matrix++;

	pspvfpu_use_matrices(gum_vfpucontext, VMAT3, 0);

	__asm__ volatile (
		"sv.q C300,  0 + %0\n"
		"sv.q C310, 16 + %0\n"
		"sv.q C320, 32 + %0\n"
		"sv.q C330, 48 + %0\n"
	: "=m"(*m) : : "memory");
}
#endif

#ifdef F_sceGumRotateX_vfpu
void sceGumRotateX(float angle)
{
	pspvfpu_use_matrices(gum_vfpucontext, VMAT3, VMAT0 | VMAT1);

	__asm__ volatile (
		"vmidt.q M000\n"
		"mtv %0, S100\n"
		"vcst.s S101, VFPU_2_PI\n"
		"vmul.s S100, S101, S100\n"
		"vrot.q C010, S100, [ 0, c, s, 0]\n"
		"vrot.q C020, S100, [ 0,-s, c, 0]\n"
		"vmmul.q M100, M300, M000\n"
		"vmmov.q M300, M100\n"
	: : "r"(angle));

	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumRotateY_vfpu
void sceGumRotateY(float angle)
{
	pspvfpu_use_matrices(gum_vfpucontext, VMAT3, VMAT0 | VMAT1);

	__asm__ volatile (
		"vmidt.q M000\n"
		"mtv %0, S100\n"
		"vcst.s S101, VFPU_2_PI\n"
		"vmul.s S100, S101, S100\n"
		"vrot.q C000, S100, [ c, 0,-s, 0]\n"
		"vrot.q C020, S100, [ s, 0, c, 0]\n"
		"vmmul.q M100, M300, M000\n"
		"vmmov.q M300, M100\n"
	: : "r"(angle));

	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumRotateZ_vfpu
void sceGumRotateZ(float angle)
{
	pspvfpu_use_matrices(gum_vfpucontext, VMAT3, VMAT0 | VMAT1);

	__asm volatile (
		"vmidt.q M000\n"
		"mtv %0, S100\n"
		"vcst.s S101, VFPU_2_PI\n"
		"vmul.s S100, S101, S100\n"
		"vrot.q C000, S100, [ c, s, 0, 0]\n"
		"vrot.q C010, S100, [-s, c, 0, 0]\n"
		"vmmul.q M100, M300, M000\n"
		"vmmov.q M300, M100\n"
	: : "r"(angle));

	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumScale_vfpu
void sceGumScale(const ScePspFVector3* v)
{
	pspvfpu_use_matrices(gum_vfpucontext, VMAT3, VMAT0);

	__asm__ volatile (
		"ulv.q C000, %0\n"
		"vscl.t C300, C300, S000\n"
		"vscl.t C310, C310, S001\n"
		"vscl.t C320, C320, S002\n"
	: : "m"(*v));

	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumStoreMatrix_vfpu
void sceGumStoreMatrix(ScePspFMatrix4* m)
{
	pspvfpu_use_matrices(gum_vfpucontext, VMAT3, 0);

	__asm__ volatile (
		"usv.q C300,  0 + %0\n"
		"usv.q C310, 16 + %0\n"
		"usv.q C320, 32 + %0\n"
		"usv.q C330, 48 + %0\n"
	: "=m"(*m) : : "memory");
}
#endif

#ifdef F_sceGumTranslate_vfpu
void sceGumTranslate(const ScePspFVector3* v)
{
	pspvfpu_use_matrices(gum_vfpucontext, VMAT3, VMAT0 | VMAT1);

	__asm__ volatile (
		"vmidt.q M000\n"
		"ulv.q   C100, %0\n"
		"vmov.t  C030, C100\n"
		"vmmul.q M100, M300, M000\n"
		"vmmov.q M300, M100\n"
	: : "m"(*v));

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
		pspvfpu_use_matrices(gum_vfpucontext, VMAT3, 0);

		__asm__ volatile (
			"sv.q C300,  0 + %0\n"
			"sv.q C310, 16 + %0\n"
			"sv.q C320, 32 + %0\n"
			"sv.q C330, 48 + %0\n"
		: "=m"(*gum_current_matrix) : : "memory");
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

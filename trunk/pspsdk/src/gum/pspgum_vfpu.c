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
#include <math.h>

#ifdef F_sceGumFastInverse_vfpu
void sceGumFastInverse()
{
	ScePspFMatrix4* t = GUM_ALIGNED_MATRIX();

	{
		register ScePspFMatrix4* r __asm("a0") = t;

		__asm__ volatile (
			cgen_asm(sv_q(Q_C300,0,R_a0,0))
			cgen_asm(sv_q(Q_C310,4,R_a0,0))
			cgen_asm(sv_q(Q_C320,8,R_a0,0))
			cgen_asm(sv_q(Q_C330,12,R_a0,0))
		: "=r"(r) : "r"(r) : "memory");
	}

	gumFastInverse(t,t);

	{
		register ScePspFMatrix4* r __asm("a0") = t;

		__asm__ volatile (
			cgen_asm(lv_q(Q_C300,0,R_a0,0))
			cgen_asm(lv_q(Q_C310,4,R_a0,0))
			cgen_asm(lv_q(Q_C320,8,R_a0,0))
			cgen_asm(lv_q(Q_C330,12,R_a0,0))
		: "=r"(r) : "r"(r) : "memory");
	}

	gum_matrix_update[gum_current_mode] = 1;
}
#endif

#ifdef F_sceGumFullInverse_vfpu
void sceGumFullInverse()
{
	ScePspFMatrix4* t = GUM_ALIGNED_MATRIX();

	{
		register ScePspFMatrix4* r __asm("a0") = t;

		__asm__ volatile (
			cgen_asm(sv_q(Q_C300,0,R_a0,0))
			cgen_asm(sv_q(Q_C310,4,R_a0,0))
			cgen_asm(sv_q(Q_C320,8,R_a0,0))
			cgen_asm(sv_q(Q_C330,12,R_a0,0))
		: "=r"(r) : "r"(r) : "memory");
	}

	gumFastInverse(t,t);

	{
		register ScePspFMatrix4* r __asm("a0") = t;

		__asm__ volatile (
			cgen_asm(lv_q(Q_C300,0,R_a0,0))
			cgen_asm(lv_q(Q_C310,4,R_a0,0))
			cgen_asm(lv_q(Q_C320,8,R_a0,0))
			cgen_asm(lv_q(Q_C330,12,R_a0,0))
		: "=r"(r) : "r"(r) : "memory");
	}

	gum_matrix_update[gum_current_mode] = 1;
}
#endif

#ifdef F_sceGumLoadIdentity_vfpu
void sceGumLoadIdentity(void)
{
	__asm__ volatile (
		cgen_asm(vmidt_q(Q_M300))
	);
	gum_matrix_update[gum_current_mode] = 1;
}
#endif

#ifdef F_sceGumLoadMatrix_vfpu
void sceGumLoadMatrix(const ScePspFMatrix4* m)
{
	register ScePspFMatrix4* r __asm("a0") = GUM_ALIGNED_MATRIX();
	memcpy(r,m,sizeof(ScePspFMatrix4));
	
	__asm__ volatile (
		cgen_asm(lv_q(Q_C300,0,R_a0,0))
		cgen_asm(lv_q(Q_C310,4,R_a0,0))
		cgen_asm(lv_q(Q_C320,8,R_a0,0))
		cgen_asm(lv_q(Q_C330,12,R_a0,0))
	: "=r"(r) : "r"(r), "r"(m) : "memory");

	gum_matrix_update[gum_current_mode] = 1;
}
#endif

#ifdef F_sceGumLookAt_vfpu
void sceGumLookAt(ScePspFVector3* eye, ScePspFVector3* center, ScePspFVector3* up)
{
	ScePspFMatrix4* t = GUM_ALIGNED_MATRIX();
	gumLookAt(t,eye,center,up);

	{
		register ScePspFMatrix4* r __asm("a0") = t;
		__asm__ volatile (
			cgen_asm(lv_q(Q_C000,0,R_a0,0))
			cgen_asm(lv_q(Q_C010,4,R_a0,0))
			cgen_asm(lv_q(Q_C020,8,R_a0,0))
			cgen_asm(lv_q(Q_C030,12,R_a0,0))
			cgen_asm(vmmul_q(Q_M100,Q_M300,Q_M000))
			cgen_asm(vmmov_q(Q_M300,Q_M100))
		: : "r"(r) );
	}

	gum_matrix_update[gum_current_mode] = 1;
}
#endif

#ifdef F_sceGumMatrixMode_vfpu
void sceGumMatrixMode(int mode)
{
	{
		register void* m __asm("a1") = gum_current_matrix;
		__asm__ volatile (
			cgen_asm(sv_q(Q_C300, 0, R_a1, 0))
			cgen_asm(sv_q(Q_C310, 4, R_a1, 0))
			cgen_asm(sv_q(Q_C320, 8, R_a1, 0))
			cgen_asm(sv_q(Q_C330, 12, R_a1, 0))
		: : "r"(m) : "memory");
	}

	// switch stack
	gum_stack_depth[gum_current_mode] = gum_current_matrix;
	gum_current_matrix = gum_stack_depth[mode];
	gum_current_mode = mode;

	{
		register void* m __asm("a1") = gum_current_matrix;
		__asm__ volatile (
			cgen_asm(lv_q(Q_C300, 0, R_a1, 0))
			cgen_asm(lv_q(Q_C310, 4, R_a1, 0))
			cgen_asm(lv_q(Q_C320, 8, R_a1, 0))
			cgen_asm(lv_q(Q_C330, 12, R_a1, 0))
		: : "r"(m) : "memory");
	}
}
#endif

#ifdef F_sceGumMultMatrix_vfpu
void sceGumMultMatrix(const ScePspFMatrix4* m)
{
	register ScePspFMatrix4* t __asm("a0") = GUM_ALIGNED_MATRIX();
	memcpy(t,m,sizeof(ScePspFMatrix4));

	__asm__ volatile (
		cgen_asm(lv_q(Q_C000,0,R_a0,0))
		cgen_asm(lv_q(Q_C010,4,R_a0,0))
		cgen_asm(lv_q(Q_C020,8,R_a0,0))
		cgen_asm(lv_q(Q_C030,12,R_a0,0))

		cgen_asm(vmmul_q(Q_M100,Q_M300,Q_M000))
		cgen_asm(vmmov_q(Q_M300,Q_M100))
	: "=r"(t) : "r"(t));

	gum_matrix_update[gum_current_mode] = 1;
}
#endif

#ifdef F_sceGumOrtho_vfpu
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

	__asm__ volatile (
		cgen_asm(lv_q(Q_C000,0,R_a0,0))
		cgen_asm(lv_q(Q_C010,4,R_a0,0))
		cgen_asm(lv_q(Q_C020,8,R_a0,0))
		cgen_asm(lv_q(Q_C030,12,R_a0,0))
		cgen_asm(vmmul_q(Q_M100,Q_M300,Q_M000))
		cgen_asm(vmmov_q(Q_M300,Q_M100))
	: : "r"(t) );

	gum_matrix_update[gum_current_mode] = 1;
}
#endif

#ifdef F_sceGumPerspective_vfpu
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

	__asm__ volatile (
		cgen_asm(lv_q(Q_C000,0,R_a0,0))
		cgen_asm(lv_q(Q_C010,4,R_a0,0))
		cgen_asm(lv_q(Q_C020,8,R_a0,0))
		cgen_asm(lv_q(Q_C030,12,R_a0,0))
		cgen_asm(vmmul_q(Q_M100,Q_M300,Q_M000))
		cgen_asm(vmmov_q(Q_M300,Q_M100))
	: : "r"(t));

	gum_matrix_update[gum_current_mode] = 1;
}
#endif

#ifdef F_sceGumPopMatrix_vfpu
void sceGumPopMatrix(void)
{
	register void* m __asm("a0") = gum_current_matrix-1;
	__asm__ volatile (
		cgen_asm(lv_q(Q_C300,0,R_a0,0))
		cgen_asm(lv_q(Q_C310,4,R_a0,0))
		cgen_asm(lv_q(Q_C320,8,R_a0,0))
		cgen_asm(lv_q(Q_C330,12,R_a0,0))
	: "=r"(m) : "r"(m));

	gum_current_matrix--;
	gum_matrix_update[gum_current_mode] = 1;
}
#endif

#ifdef F_sceGumPushMatrix_vfpu
void sceGumPushMatrix(void)
{
	register void* m __asm("a0") = gum_current_matrix;
	__asm__ volatile (
		cgen_asm(sv_q(Q_C300,0,R_a0,0))
		cgen_asm(sv_q(Q_C310,4,R_a0,0))
		cgen_asm(sv_q(Q_C320,8,R_a0,0))
		cgen_asm(sv_q(Q_C330,12,R_a0,0))
	: "=r"(m) : "r"(m) : "memory");

	gum_current_matrix++;
}
#endif

#ifdef F_sceGumRotateX_vfpu
void sceGumRotateX(float angle)
{
	register ScePspFVector4* v __asm("a0") = GUM_ALIGNED_VECTOR();
	v->x = angle;

	__asm__ volatile (
		cgen_asm(vmidt_q(Q_M000))
		cgen_asm(lv_s(S_S100, 0, R_a0, 0))
		cgen_asm(vcst_s(S_S101, 5))
		cgen_asm(vmul_s(S_S100, S_S101, S_S100))
		cgen_asm(vcos_s(S_S011, S_S100))
		cgen_asm(vsin_s(S_S012, S_S100))
		cgen_asm(vneg_s(S_S021, S_S012))
		cgen_asm(vmov_s(S_S022, S_S011))
		cgen_asm(vmmul_q(Q_M100, Q_M300, Q_M000))
		cgen_asm(vmmov_q(Q_M300, Q_M100))
	: : "r"(v));

	gum_matrix_update[gum_current_mode] = 1;
}
#endif

#ifdef F_sceGumRotateY_vfpu
void sceGumRotateY(float angle)
{
	register ScePspFVector4* v __asm("a0") = GUM_ALIGNED_VECTOR();
	v->x = angle;

	__asm__ volatile (
		cgen_asm(vmidt_q(Q_M000))
		cgen_asm(lv_s(S_S100, 0, R_a0, 0))
		cgen_asm(vcst_s(S_S101, 5))
		cgen_asm(vmul_s(S_S100, S_S101, S_S100))
		cgen_asm(vcos_s(S_S000, S_S100))
		cgen_asm(vsin_s(S_S020, S_S100))
		cgen_asm(vneg_s(S_S002, S_S020))
		cgen_asm(vmov_s(S_S022, S_S000))
		cgen_asm(vmmul_q(Q_M100, Q_M300, Q_M000))
		cgen_asm(vmmov_q(Q_M300, Q_M100))
	: : "r"(v));

	gum_matrix_update[gum_current_mode] = 1;
}
#endif

#ifdef F_sceGumRotateZ_vfpu
void sceGumRotateZ(float angle)
{
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

	gum_matrix_update[gum_current_mode] = 1;
}
#endif

#ifdef F_sceGumScale_vfpu
void sceGumScale(const ScePspFVector3* v)
{
	register ScePspFVector4* t __asm("a1") = GUM_ALIGNED_VECTOR();
	memcpy(t,v,sizeof(ScePspFVector3));
	__asm__ volatile (
		cgen_asm(lv_q(Q_C000,0,R_a0,0))
		cgen_asm(vscl_t(Q_C300,Q_C300,S_S000))
		cgen_asm(vscl_t(Q_C310,Q_C310,S_S001))
		cgen_asm(vscl_t(Q_C320,Q_C320,S_S002))
	: : "r"(t));

	gum_matrix_update[gum_current_mode] = 1;
}
#endif

#ifdef F_sceGumStoreMatrix_vfpu
void sceGumStoreMatrix(ScePspFMatrix4* m)
{
	register ScePspFMatrix4* t __asm("a0") = GUM_ALIGNED_MATRIX();
	__asm__ volatile (
		cgen_asm(sv_q(Q_C300,0,R_a0,0))
		cgen_asm(sv_q(Q_C310,4,R_a0,0))
		cgen_asm(sv_q(Q_C320,8,R_a0,0))
		cgen_asm(sv_q(Q_C330,12,R_a0,0))
	: "=r"(t) : "r"(t) : "memory");
	memcpy(m,t,sizeof(ScePspFMatrix4));
}
#endif

#ifdef F_sceGumTranslate_vfpu
void sceGumTranslate(const ScePspFVector3* v)
{
	register ScePspFVector4* t __asm("a0") = GUM_ALIGNED_VECTOR();
	memcpy(t,v,sizeof(ScePspFVector4));
	t->w = 1.0f;

	__asm__ volatile (
		cgen_asm(vmidt_q(Q_M000))
		cgen_asm(lv_q(Q_C030,0,R_a0,0))
		cgen_asm(vmmul_q(Q_M100,Q_M300,Q_M000))
		cgen_asm(vmmov_q(Q_M300,Q_M100))
	: "=r"(t) : "r"(t));

	gum_matrix_update[gum_current_mode] = 1;
}
#endif

#ifdef F_sceGumUpdateMatrix_vfpu
void sceGumUpdateMatrix(void)
{
	gum_stack_depth[gum_current_mode] = gum_current_matrix;

	// flush dirty matrix from vfpu
	if (gum_matrix_update[gum_current_mode])
	{
		register void* m __asm("a0") = gum_current_matrix;
		__asm__ volatile (
			cgen_asm(sv_q(Q_C300,0,R_a0,0))
			cgen_asm(sv_q(Q_C310,4,R_a0,0))
			cgen_asm(sv_q(Q_C320,8,R_a0,0))
			cgen_asm(sv_q(Q_C330,12,R_a0,0))
		: "=r"(m) : "r"(m) : "memory");
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

/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#ifndef __pspgum_h__
#define __pspgum_h__

#include <psptypes.h>

#if defined(__cplusplus)
extern "C" {
#endif

// stack functions

void sceGumDrawArray(int prim, int vtype, int count, const void* indices, const void* vertices);
void sceGumDrawArrayN(int prim, int vtype, int count, int a3, const void* indices, const void* vertices);
void sceGumDrawBezier(int vtype, int ucount, int vcount, const void* indices, const void* vertices);
void sceGumDrawSpline(int vtype, int ucount, int vcount, int uedge, int vedge, const void* indices, const void* vertices);
void sceGumLoadIdentity(void);
void sceGumLoadMatrix(const ScePspFMatrix4* m);
void sceGumLookAt(ScePspFVector3* eye, ScePspFVector3* center, ScePspFVector3* up);
void sceGumMatrixMode(int mode);
void sceGumMultMatrix(const ScePspFMatrix4* m);
void sceGumOrtho(float left, float right, float bottom, float top, float near, float far);
void sceGumPerspective(float fovy, float aspect, float near, float far);
void sceGumPopMatrix(void);
void sceGumPushMatrix(void);
void sceGumRotateX(float angle);
void sceGumRotateXYZ(const ScePspFVector3* v);
void sceGumRotateY(float angle);
void sceGumRotateZ(float angle);
void sceGumRotateZYX(const ScePspFVector3* v);
void sceGumScale(const ScePspFVector3* v);
void sceGumStoreMatrix(ScePspFMatrix4* m);
void sceGumTranslate(const ScePspFVector3* v);
void sceGumUpdateMatrix(void);

// unimplemented functions

//sceGumLoadContext
//sceGumSetCurMatrix
//sceGumSetMatrixStack
//sceGumStoreContext

// standalone functions

void gumLoadIdentity(ScePspFMatrix4* m);
void gumLoadMatrix(ScePspFMatrix4* r, const ScePspFMatrix4* a);
void gumLookAt(ScePspFMatrix4* m, ScePspFVector3* eye, ScePspFVector3* center, ScePspFVector3* up);
void gumMultMatrix(ScePspFMatrix4* result, const ScePspFMatrix4* a, const ScePspFMatrix4* b);
void gumOrtho(ScePspFMatrix4* m, float left, float right, float bottom, float top, float near, float far);
void gumPerspective(ScePspFMatrix4* m, float fovy, float aspect, float near, float far);
void gumRotateX(ScePspFMatrix4* m, float angle);
void gumRotateXYZ(ScePspFMatrix4* m, const ScePspFVector3* v);
void gumRotateY(ScePspFMatrix4* m, float angle);
void gumRotateZ(ScePspFMatrix4* m, float angle);
void gumRotateZYX(ScePspFMatrix4* m, const ScePspFVector3* v);
void gumScale(ScePspFMatrix4* m, const ScePspFVector3* v);
void gumTranslate(ScePspFMatrix4* m, const ScePspFVector3* v);

// vector functions

void gumCrossProduct(ScePspFVector3* r, const ScePspFVector3* a, const ScePspFVector3* b);
void gumNormalize(ScePspFVector3* v);

#if defined(__cplusplus)
}
#endif

#endif


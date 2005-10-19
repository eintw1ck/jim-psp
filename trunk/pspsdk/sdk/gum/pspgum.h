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
void sceGumRotateX(float a);
void sceGumRotateY(float a);
void sceGumRotateZ(float a);
void sceGumRotateXYZ(const ScePspFVector3* v);
void sceGumRotateZYX(const ScePspFVector3* v);
void sceGumScale(const ScePspFVector3* v);
void sceGumStoreMatrix(ScePspFMatrix4* v);
void sceGumTranslate(const ScePspFVector3* v);
void sceGumUpdateMatrix(void);

// unimplemented functions

//sceGumLoadContext
//sceGumSetCurMatrix
//sceGumSetMatrixStack
//sceGumStoreContext

// standalone operations, lacking the sce*-prefix to separate them from the stack-based functions

void gumMultMatrix(ScePspFMatrix4* result, const ScePspFMatrix4* a, const ScePspFMatrix4* b);
void gumMakeIdentity(ScePspFMatrix4* m);

#if defined(__cplusplus)
}
#endif

#endif

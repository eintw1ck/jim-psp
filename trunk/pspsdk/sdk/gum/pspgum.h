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
//void sceGumDrawArrayN
//void sceGumDrawBezier
//void sceGumDrawSpline
//sceGumLoadContext
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
//sceGumSetCurMatrix
//sceGumSetMatrixStack
//sceGumStoreContext
void sceGumStoreMatrix(ScePspFMatrix4* v);
void sceGumTranslate(const ScePspFVector3* v);
void sceGumUpdateMatrix(void);

#if defined(__cplusplus)
}
#endif

#endif

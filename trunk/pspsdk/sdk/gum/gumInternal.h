/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#ifndef __gumInternal_h__
#define __gumInternal_h__

#include "pspgum.h"
#include "../gu/pspgu.h"

#define GUM_EPSILON 0.00001f

extern int gum_current_mode;
extern int gum_matrix_update[4];
extern ScePspFMatrix4* gum_current_matrix;
extern ScePspFMatrix4* gum_stack_depth[4];
extern ScePspFMatrix4 gum_matrix_stack[4][32];

void gumMultMatrix(ScePspFMatrix4* result, const ScePspFMatrix4* a, const ScePspFMatrix4* b);
void gumMakeIdentity(ScePspFMatrix4* m);

void gumCrossProduct(ScePspFVector3* r, const ScePspFVector3* a, const ScePspFVector3* b);
void gumNormalize(ScePspFVector3* v);

float gumCosf(float a);
float gumSinf(float a);

#endif

/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"
#include <math.h>
#include <string.h>

int gum_current_mode = GU_PROJECTION;

int gum_matrix_update[4] = { 0 };

ScePspFMatrix4* gum_current_matrix = gum_matrix_stack[GU_PROJECTION];

ScePspFMatrix4* gum_stack_depth[4] =
{
  gum_matrix_stack[GU_PROJECTION],
  gum_matrix_stack[GU_VIEW],
  gum_matrix_stack[GU_MODEL],
  gum_matrix_stack[GU_TEXTURE]
};

ScePspFMatrix4 gum_matrix_stack[4][32];

void gumMultMatrix(ScePspFMatrix4* result, const ScePspFMatrix4* a, const ScePspFMatrix4* b)
{
  ScePspFMatrix4 t;
  unsigned int i,j;
  const float* ma = (const float*)a;
  const float* mb = (const float*)b;
  float* mr = (float*)&t;

  for (i = 0; i < 4; ++i)
  {
    for (j = 0; j < 4; ++j)
    {
      *(mr++) = ma[(i<<2)+0]*mb[(0<<2)+j] + ma[(i<<2)+1]*mb[(1<<2)+j] +
                ma[(i<<2)+2]*mb[(2<<2)+j] + ma[(i<<2)+3]*mb[(3<<2)+j];
    }
  }  

  memcpy(result,&t,sizeof(ScePspFMatrix4));
}

void gumMakeIdentity(ScePspFMatrix4* m)
{
  unsigned int i;

  memset(m,0,sizeof(ScePspFMatrix4));

  for (i = 0; i < 4; ++i)
    ((float*)m)[(i << 2)+i] = 1.0f;
}

void gumCrossProduct(ScePspFVector3*r, const ScePspFVector3* a, const ScePspFVector3* b)
{
	r->x = (a->y * b->z) + (a->z * b->y);
	r->y = (a->z * b->x) + (a->x * b->z);
	r->z = (a->x * b->y) + (a->y * b->x);
}

void gumNormalize(ScePspFVector3* v)
{
	float l = (v->x*v->x) + (v->y*v->y) + (v->z*v->z);
	if (l > GUM_EPSILON)
	{
		float il = 1.0f / l;
		v->x *= il; v->y *= il; v->z *= il;
	}
}

/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"
#include <string.h>

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

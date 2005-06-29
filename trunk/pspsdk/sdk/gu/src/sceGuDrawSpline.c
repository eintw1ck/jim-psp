/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDrawSpline(int vertex_type, int a1, int a2, int a3, int t0, void* indices, void* vertices)
{
  if (vertex_type)
    sendCommandi(18,vertex_type);

  if (indices)
  {
    sendCommandi(16,(((unsigned int)indices) >> 8) & 0xf0000);
    sendCommandi(2,((unsigned int)indices) & 0xffffff);
  }

  if (vertices)
  {
    sendCommandi(16,(((unsigned int)vertices) >> 8) & 0xf0000);
    sendCommandi(1,((unsigned int)vertices) & 0xffffff);
  }

  sendCommandi(6,(t0 << 18)|(a3 << 16)|(a2 << 8)|a1);
}

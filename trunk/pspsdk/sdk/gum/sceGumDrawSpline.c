/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

void sceGumDrawSpline(int vtype, int ucount, int vcount, int uedge, int vedge, const void* indices, const void* vertices)
{
  sceGumUpdateMatrix();
  sceGuDrawSpline(vtype,ucount,vcount,uedge,vedge,indices,vertices);
}

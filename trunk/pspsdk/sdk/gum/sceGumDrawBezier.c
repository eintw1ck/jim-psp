/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

void sceGumDrawBezier(int vtype, int ucount, int vcount, const void* indices, const void* vertices)
{
  sceGumUpdateMatrix();
  sceGuDrawBezier(vtype,ucount,vcount,indices,vertices);
}

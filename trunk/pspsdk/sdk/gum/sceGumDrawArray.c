/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

void sceGumDrawArray(int prim, int vtype, int count, const void* indices, const void* vertices)
{
  sceGumUpdateMatrix();
  sceGuDrawArray(prim,vtype,count,indices,vertices);
}

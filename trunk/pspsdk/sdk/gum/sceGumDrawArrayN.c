/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

void sceGumDrawArrayN(int prim, int vtype, int count, int a3, const void* indices, const void* vertices)
{
  sceGumUpdateMatrix();
  sceGuDrawArrayN(prim,vtype,count,a3,indices,vertices);
}

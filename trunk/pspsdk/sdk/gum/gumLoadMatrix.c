/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"
#include <string.h>

void gumLoadMatrix(ScePspFMatrix4* r, const ScePspFMatrix4* a)
{
  memcpy(r,a,sizeof(ScePspFMatrix4));
}

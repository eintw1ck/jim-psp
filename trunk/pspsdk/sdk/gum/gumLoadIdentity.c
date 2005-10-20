/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"
#include <string.h>

void gumLoadIdentity(ScePspFMatrix4* m)
{
  unsigned int i;

  memset(m,0,sizeof(ScePspFMatrix4));

  for (i = 0; i < 4; ++i)
    ((float*)m)[(i << 2)+i] = 1.0f;
}

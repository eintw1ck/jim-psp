/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"
#include <string.h>

void sceGumLoadMatrix(const ScePspFMatrix4* m)
{
  memcpy(gum_current_matrix,m,sizeof(ScePspFMatrix4));
  gum_matrix_update[gum_current_mode] = 1;
}

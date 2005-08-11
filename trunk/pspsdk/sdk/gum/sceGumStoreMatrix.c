/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

#include <string.h>

void sceGumStoreMatrix(ScePspFMatrix4* m)
{
  memcpy(m,gum_current_matrix,sizeof(ScePspFMatrix4));
}

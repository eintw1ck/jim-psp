/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

#include <string.h>

void sceGumPushMatrix(void)
{
  memcpy(gum_current_matrix+1,gum_current_matrix,sizeof(ScePspFMatrix4));
  gum_current_matrix++;
}

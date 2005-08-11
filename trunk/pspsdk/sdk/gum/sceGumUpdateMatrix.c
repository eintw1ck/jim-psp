/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

void sceGumUpdateMatrix(void)
{
  gum_stack_depth[gum_current_mode] = gum_current_matrix;

  unsigned int i;
  for (i = 0; i < 4; ++i)
  {
    if (gum_matrix_update[i])
    {
      sceGuSetMatrix(i,gum_stack_depth[i]);
      gum_matrix_update[i] = 0;
    }
  }
}

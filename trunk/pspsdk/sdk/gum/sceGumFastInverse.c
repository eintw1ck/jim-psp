/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

void sceGumFastInverse()
{
	gumFastInverse(gum_current_matrix,gum_current_matrix);
	gum_matrix_update[gum_current_mode] = 1;
}

/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

void sceGumMultMatrix(const ScePspFMatrix4* m)
{
	gumMultMatrix(gum_current_matrix,gum_current_matrix,m);  
	gum_matrix_update[gum_current_mode] = 1;
}

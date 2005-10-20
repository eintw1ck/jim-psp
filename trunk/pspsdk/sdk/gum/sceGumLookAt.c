/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

void sceGumLookAt(ScePspFVector3* eye, ScePspFVector3* center, ScePspFVector3* up)
{
	gumLookAt(gum_current_matrix,eye,center,up);
	gum_matrix_update[gum_current_mode] = 1;
}

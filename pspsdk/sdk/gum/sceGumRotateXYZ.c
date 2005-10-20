/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

void sceGumRotateXYZ(const ScePspFVector3* v)
{
	gumRotateZ(gum_current_matrix,v->z);
	gumRotateY(gum_current_matrix,v->y);
	gumRotateX(gum_current_matrix,v->x);
	gum_matrix_update[gum_current_mode] = 1;
}

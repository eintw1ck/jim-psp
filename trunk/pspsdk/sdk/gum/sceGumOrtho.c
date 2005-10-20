/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

void sceGumOrtho(float left, float right, float bottom, float top, float near, float far)
{
	gumOrtho(gum_current_matrix,left,right,bottom,top,near,far);
	gum_matrix_update[gum_current_mode] = 1;
}

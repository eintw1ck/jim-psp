/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

#include <math.h>

void sceGumPerspective(float fovy, float aspect, float near, float far)
{
	gumPerspective(gum_current_matrix,fovy,aspect,near,far);
	gum_matrix_update[gum_current_mode] = 1;
}

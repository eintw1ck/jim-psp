/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

void sceGumTranslate(const ScePspFVector3* v)
{
	gumTranslate(gum_current_matrix,v);
	gum_matrix_update[gum_current_mode] = 1;
}

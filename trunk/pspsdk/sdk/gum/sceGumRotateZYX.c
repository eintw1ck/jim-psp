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
	sceGumRotateX(v->z);
	sceGumRotateY(v->y);
	sceGumRotateZ(v->x);
}

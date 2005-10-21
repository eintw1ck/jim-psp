/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

void gumRotateXYZ(ScePspFMatrix4* m, const ScePspFVector3* v)
{
	gumRotateX(m,v->x);
	gumRotateY(m,v->y);
	gumRotateZ(m,v->z);
}

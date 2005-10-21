/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

void gumRotateZYX(ScePspFMatrix4* m, const ScePspFVector3* v)
{
	gumRotateZ(m,v->z);
	gumRotateY(m,v->y);
	gumRotateX(m,v->x);
}

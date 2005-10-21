/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

void gumFastInverse(ScePspFMatrix4* m, const ScePspFMatrix4* a)
{
	ScePspFMatrix4 t;
	ScePspFVector3 negPos = {-a->w.x,-a->w.y,-a->w.z};

	// transpose rotation

	t.x.x = a->x.x;
	t.x.y = a->y.x;
	t.x.z = a->z.x;
	t.x.w = 0;

	t.y.x = a->x.y;
	t.y.y = a->y.y;
	t.y.z = a->z.y;
	t.y.w = 0;

	t.z.x = a->x.z;
	t.z.y = a->y.z;
	t.z.z = a->z.z;
	t.z.w = 0;

	// compute inverse position

	t.w.x = gumDotProduct(&negPos,(const ScePspFVector3*)&a->x);
	t.w.y = gumDotProduct(&negPos,(const ScePspFVector3*)&a->y);
	t.w.z = gumDotProduct(&negPos,(const ScePspFVector3*)&a->z);
	t.w.w = 1;

	gumLoadMatrix(m,&t);
}

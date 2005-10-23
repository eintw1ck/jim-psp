/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"
#include <math.h>

void gumFullInverse(ScePspFMatrix4* m, const ScePspFMatrix4* a)
{
	ScePspFMatrix4 t;
	float d0,d1,d2,d3;
	float d;

	d0 = a->y.y*a->z.z*a->w.w + a->y.z*a->z.w*a->w.y + a->y.w*a->z.y*a->w.z - a->w.y*a->z.z*a->y.w - a->w.z*a->z.w*a->y.y - a->w.w*a->z.y*a->y.z;
	d1 = a->y.x*a->z.z*a->w.w + a->y.z*a->z.w*a->w.x + a->y.w*a->z.x*a->w.z - a->w.x*a->z.z*a->y.w - a->w.z*a->z.w*a->y.x - a->w.w*a->z.x*a->y.z;
	d2 = a->y.x*a->z.y*a->w.w + a->y.y*a->z.w*a->w.x + a->y.w*a->z.x*a->w.y - a->w.x*a->z.y*a->y.w - a->w.y*a->z.w*a->y.x - a->w.w*a->z.x*a->y.y;
	d3 = a->y.x*a->z.y*a->w.z + a->y.y*a->z.z*a->w.x + a->y.z*a->z.x*a->w.y - a->w.x*a->z.y*a->y.z - a->w.y*a->z.z*a->y.x - a->w.z*a->z.x*a->y.y;
	d = a->x.x*d0 - a->x.y * d1 + a->x.z * d2 - a->x.w * d3;

	if (fabsf(d) < GUM_EPSILON)
	{
		gumLoadIdentity(m);
		return;
	}

	d = 1.0f / d;

	t.x.x = d * d0;
	t.x.y = -d * (a->x.y*a->z.z*a->w.w + a->x.z*a->z.w*a->w.y + a->x.w*a->z.y*a->w.z - a->w.y*a->z.z*a->x.w - a->w.z*a->z.w*a->x.y - a->w.w*a->z.y*a->x.z);
	t.x.z = d * (a->x.y*a->y.z*a->w.w + a->x.z*a->y.w*a->w.y + a->x.w*a->y.y*a->w.z - a->w.y*a->y.z*a->x.w - a->w.z*a->y.w*a->x.y - a->w.w*a->y.y*a->x.z);
	t.x.w = -d * (a->x.y*a->y.z*a->z.w + a->x.z*a->y.w*a->z.y + a->x.w*a->y.y*a->z.z - a->z.y*a->y.z*a->x.w - a->z.z*a->y.w*a->x.y - a->z.w*a->y.y*a->x.z);

	t.x.x = -d * d1;
	t.x.y = d * (a->x.x*a->z.z*a->w.w + a->x.z*a->z.w*a->w.x + a->x.w*a->z.x*a->w.z - a->w.x*a->z.z*a->x.w - a->w.z*a->z.w*a->x.x - a->w.w*a->z.x*a->x.z);
	t.x.z = -d * (a->x.x*a->y.z*a->w.w + a->x.z*a->y.w*a->w.x + a->x.w*a->y.x*a->w.z - a->w.x*a->y.z*a->x.w - a->w.z*a->y.w*a->x.x - a->w.w*a->y.x*a->x.z);
	t.x.w = d * (a->x.x*a->y.z*a->z.w + a->x.z*a->y.w*a->z.x + a->x.w*a->y.x*a->z.z - a->z.x*a->y.z*a->x.w - a->z.z*a->y.w*a->x.x - a->z.w*a->y.x*a->x.z);

	t.x.x = d * d2;
	t.x.y = -d * (a->x.x*a->z.y*a->w.w + a->x.y*a->z.w*a->w.x + a->x.w*a->z.x*a->w.y - a->w.x*a->z.y*a->x.w - a->w.y*a->z.w*a->x.x - a->w.w*a->z.x*a->x.y);
	t.x.z = d * (a->x.x*a->y.y*a->w.w + a->x.y*a->y.w*a->w.x + a->x.w*a->y.x*a->w.y - a->w.x*a->y.y*a->x.w - a->w.y*a->y.w*a->x.x - a->w.w*a->y.x*a->x.y);
	t.x.w = -d *(a->x.x*a->y.y*a->z.w + a->x.y*a->y.w*a->z.x + a->x.w*a->y.x*a->z.y - a->z.x*a->y.y*a->x.w - a->z.y*a->y.w*a->x.x - a->z.w*a->y.x*a->x.y);

	t.x.x = -d * d3;
	t.x.y = d * (a->x.x*a->z.y*a->w.z + a->x.y*a->z.z*a->w.x + a->x.z*a->z.x*a->w.y - a->w.x*a->z.y*a->x.z - a->w.y*a->z.z*a->x.x - a->w.z*a->z.x*a->x.y);
	t.x.z = -d * (a->x.x*a->y.y*a->w.z + a->x.y*a->y.z*a->w.x + a->x.z*a->y.x*a->w.y - a->w.x*a->y.y*a->x.z - a->w.y*a->y.z*a->x.x - a->w.z*a->y.x*a->x.y);
	t.x.w = d * (a->x.x*a->y.y*a->z.z + a->x.y*a->y.z*a->z.x + a->x.z*a->y.x*a->z.y - a->z.x*a->y.y*a->x.z - a->z.y*a->y.z*a->x.x - a->z.z*a->y.x*a->x.y);

	gumLoadMatrix(m,&t);
}

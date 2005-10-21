/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

void gumScale(ScePspFMatrix4* m, const ScePspFVector3* v)
{
	float x,y,z;

	x = v->x; y = v->y; z = v->z;
	m->x.x *= x; m->x.y *= y; m->x.z *= z;
	m->y.x *= x; m->y.y *= y; m->y.z *= z;
	m->z.x *= x; m->z.y *= y; m->z.z *= z;
}

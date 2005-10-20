/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

void gumTranslate(ScePspFMatrix4* m, const ScePspFVector3* v)
{
	ScePspFMatrix4 t;

	gumLoadIdentity(&t);
	t.w.x = v->x;
	t.w.y = v->y;
	t.w.z = v->z;

	gumMultMatrix(m,m,&t);
}

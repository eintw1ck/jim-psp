/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

#include <math.h>

void gumRotateY(ScePspFMatrix4* m, float angle)
{
	ScePspFMatrix4 t;

	float c = cosf(angle);
	float s = sinf(angle);

	gumLoadIdentity(&t);

	t.x.x = c;
	t.x.z = -s;
	t.z.x = s;
	t.z.z = c;

	gumMultMatrix(m,m,&t);
}

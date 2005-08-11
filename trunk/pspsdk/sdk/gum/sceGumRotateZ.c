/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

#include <math.h>

void sceGumRotateZ(float angle)
{
	ScePspFMatrix4 t;

	float c = cosf(angle);
	float s = sinf(angle);

	gumMakeIdentity(&t);

	t.x.x = c;
	t.x.y = s;
	t.y.x = -s;
	t.y.y = c;

	sceGumMultMatrix(&t);
}

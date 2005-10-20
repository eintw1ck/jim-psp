/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"
#include <math.h>

void gumNormalize(ScePspFVector3* v)
{
	float l = sqrtf((v->x*v->x) + (v->y*v->y) + (v->z*v->z));
	if (l > GUM_EPSILON)
	{
		float il = 1.0f / l;
		v->x *= il; v->y *= il; v->z *= il;
	}
}

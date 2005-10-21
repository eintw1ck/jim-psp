/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

float gumDotProduct(const ScePspFVector3* a, const ScePspFVector3* b)
{
	return (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
}

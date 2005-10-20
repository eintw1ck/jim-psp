/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

void sceGumTranslate(ScePspFMatrix4* m, const ScePspFVector3* v)
{
	gumMakeIdentity(&m);
	m.w.x = v->x;
	m.w.y = v->y;
	m.w.z = v->z;
}

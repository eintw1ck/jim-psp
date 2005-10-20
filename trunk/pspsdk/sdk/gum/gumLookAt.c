/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

void gumLookAt(ScePspFMatrix4* m, ScePspFVector3* eye, ScePspFVector3* center, ScePspFVector3* up)
{
	ScePspFVector3 forward, side, lup,ieye;
	ScePspFMatrix4 t;

	forward.x = center->x - eye->x;
	forward.y = center->y - eye->y;
	forward.z = center->z - eye->z;

	gumNormalize(&forward);

	gumCrossProduct(&side,&forward,up);
	gumNormalize(&side);

	gumCrossProduct(&lup,&side,&forward);
	gumLoadIdentity(&t);

	t.x.x = side.x;
	t.y.x = side.y;
	t.z.x = side.z;

	t.x.y = lup.x;
	t.y.y = lup.y;
	t.z.y = lup.z;

	t.x.z = -forward.x;
	t.y.z = -forward.y;
	t.z.z = -forward.z;

	ieye.x = -eye->x; ieye.y = -eye->y; ieye.z = -eye->z;
	gumTranslate(m,&ieye);
	gumMultMatrix(m,m,&t);
}

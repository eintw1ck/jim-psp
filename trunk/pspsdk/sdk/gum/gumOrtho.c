/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

void gumOrtho(ScePspFMatrix4* m, float left, float right, float bottom, float top, float near, float far)
{
	ScePspFMatrix4 t;
	float dx = right-left, dy = top-bottom, dz = far-near;

	gumLoadIdentity(&t);

	t.x.x = 2.0f / dx;
	t.w.x = -(right + left) / dx;
	t.y.y = 2.0f / dy;
	t.w.y = -(top + bottom) / dy;
	t.z.z = -2.0f / dz;
	t.w.z = -(far + near) / dz;

	gumMultMatrix(m,m,&t);
}

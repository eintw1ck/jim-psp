/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

#include <math.h>

void gumPerspective(ScePspFMatrix4* m, float fovy, float aspect, float near, float far)
{
	ScePspFMatrix4 t;
	float angle = (fovy / 2) * (GU_PI/180.0f);
	float cotangent = cosf(angle) / sinf(angle);
	float delta_z = near-far;

	gumLoadIdentity(&t);

	t.x.x = cotangent / aspect;
	t.y.y = cotangent;
	t.z.z = (far + near) / delta_z; // -(far + near) / delta_z
	t.w.z = 2.0f * (far * near) / delta_z; // -2 * (far * near) / delta_z
	t.z.w = -1.0f;
	t.w.w = 0.0f;

	gumMultMatrix(m,m,&t);
}

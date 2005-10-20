/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"
#include <string.h>

void gumMultMatrix(ScePspFMatrix4* result, const ScePspFMatrix4* a, const ScePspFMatrix4* b)
{
	ScePspFMatrix4 t;
	unsigned int i,j,k;
	const float* ma = (const float*)a;
	const float* mb = (const float*)b;
	float* mr = (float*)&t;

	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 4; ++j)
		{
			float v = 0.0f;
			for (k = 0; k < 4; ++k)
				v += ma[(k << 2)+j] * mb[(i << 2)+k];
			mr[(i << 2)+j] = v;
                }
        }

	memcpy(result,&t,sizeof(ScePspFMatrix4));
}

/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuBoneMatrix(unsigned int index, const float* matrix)
{
	unsigned int offset = ((index << 1)+index) << 2; // 3*4 matrix
	unsigned int i,j;

	sendCommandi(42,offset);
	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			sendCommandf(43,matrix[j+(i << 2)]);
		}
	}
}

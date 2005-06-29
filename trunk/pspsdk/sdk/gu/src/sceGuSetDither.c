/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuSetDither(int* matrix)
{
	sendCommandi(226,(matrix[0] & 0x0f)|((matrix[1] & 0x0f) << 4)|((matrix[2] & 0x0f) << 8)|((matrix[3] & 0x0f) << 12));
	sendCommandi(227,(matrix[4] & 0x0f)|((matrix[5] & 0x0f) << 4)|((matrix[6] & 0x0f) << 8)|((matrix[7] & 0x0f) << 12));
	sendCommandi(228,(matrix[8] & 0x0f)|((matrix[9] & 0x0f) << 4)|((matrix[10] & 0x0f) << 8)|((matrix[11] & 0x0f) << 12));
	sendCommandi(229,(matrix[12] & 0x0f)|((matrix[13] & 0x0f) << 4)|((matrix[14] & 0x0f) << 8)|((matrix[15] & 0x0f) << 12));
}

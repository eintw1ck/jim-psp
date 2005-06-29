/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sendCommandi(int cmd, int argument)
{
	*(gu_list->current++) = (cmd << 24) | (argument & 0xffffff);
}

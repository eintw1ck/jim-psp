/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuLightColor(int light, int type, unsigned int color)
{
	GuLightSettings* settings = &light_settings[light];

	switch (type)
	{
		case 1: sendCommandi(settings->row2[0], color & 0xffffff); break;
		case 2: sendCommandi(settings->row2[1], color & 0xffffff); break;

		case 3:
		{
			sendCommandi(settings->row2[0], color & 0xffffff); break;
			sendCommandi(settings->row2[1], color & 0xffffff); break;
		}
		break;
		
		case 4: sendCommandi(settings->row2[2], color & 0xffffff); break;
		
		case 6:
		{
			sendCommandi(settings->row2[1], color & 0xffffff); break;
			sendCommandi(settings->row2[2], color & 0xffffff); break;
		}
		break;

		default: case 0: case 5: break;
	}
}

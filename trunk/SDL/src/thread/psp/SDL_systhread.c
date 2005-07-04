/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997-2004 Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Sam Lantinga
    slouken@libsdl.org
*/

/* PSP port contributed by Marcus R. Brown <mrbrown@ocgnet.org>. */

#ifdef SAVE_RCSID
static char rcsid =
 "@(#) $Id: SDL_systhread.c,v 1.5 2004/01/04 16:49:19 slouken Exp $";
#endif

/* PSP thread management routines for SDL */

#include <stdio.h>
#include <stdlib.h>

#include "SDL_error.h"
#include "SDL_thread.h"
#include "SDL_systhread.h"


int SDL_SYS_CreateThread(SDL_Thread *thread, void *args)
{ 
	return -1;
}

void SDL_SYS_SetupThread(void)
{
	/* Do nothing. */
}

Uint32 SDL_ThreadID(void)
{
	return 0;
}

void SDL_SYS_WaitThread(SDL_Thread *thread)
{
	/* Do nothing. */
}

void SDL_SYS_KillThread(SDL_Thread *thread)
{
	/* Do nothing. */
}

/* vim: ts=4 sw=4
 */

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

/*  
    PSP port contributed by:
    Marcus R. Brown <mrbrown@ocgnet.org>
    Jim Paris <jim@jtan.com>
*/

#ifdef SAVE_RCSID
static char rcsid =
 "@(#) $Id: SDL_nullvideo.c,v 1.7 2004/01/04 16:49:24 slouken Exp $";
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SDL.h"
#include "SDL_error.h"
#include "SDL_video.h"
#include "SDL_mouse.h"
#include "SDL_sysvideo.h"
#include "SDL_pixels_c.h"
#include "SDL_events_c.h"

#include "SDL_pspvideo.h"
#include "SDL_pspevents_c.h"
#include "SDL_pspmouse_c.h"

#define PSPVID_DRIVER_NAME "psp"

/* Initialization/Query functions */
static int PSP_VideoInit(_THIS, SDL_PixelFormat *vformat);
static SDL_Rect **PSP_ListModes(_THIS, SDL_PixelFormat *format, Uint32 flags);
static SDL_Surface *PSP_SetVideoMode(_THIS, SDL_Surface *current, int width, int height, int bpp, Uint32 flags);
static int PSP_SetColors(_THIS, int firstcolor, int ncolors, SDL_Color *colors);
static void PSP_VideoQuit(_THIS);
void PSP_EventInit(_THIS);
void PSP_EventQuit(_THIS);

/* Hardware surface functions */
static int PSP_AllocHWSurface(_THIS, SDL_Surface *surface);
static int PSP_LockHWSurface(_THIS, SDL_Surface *surface);
static void PSP_UnlockHWSurface(_THIS, SDL_Surface *surface);
static void PSP_FreeHWSurface(_THIS, SDL_Surface *surface);

/* etc. */
static void PSP_UpdateRects(_THIS, int numrects, SDL_Rect *rects);

/* PSP driver bootstrap functions */

static int PSP_Available(void)
{
	return 1;
}

static void PSP_DeleteDevice(SDL_VideoDevice *device)
{
	free(device->hidden);
	free(device);
}

static SDL_VideoDevice *PSP_CreateDevice(int devindex)
{
	SDL_VideoDevice *device;

	/* Initialize all variables that we clean on shutdown */
	device = (SDL_VideoDevice *)malloc(sizeof(SDL_VideoDevice));
	if ( device ) {
		memset(device, 0, (sizeof *device));
		device->hidden = (struct SDL_PrivateVideoData *)
				malloc((sizeof *device->hidden));
	}
	if ( (device == NULL) || (device->hidden == NULL) ) {
		SDL_OutOfMemory();
		if ( device ) {
			free(device);
		}
		return(0);
	}
	memset(device->hidden, 0, (sizeof *device->hidden));

	/* Set the function pointers */
	device->VideoInit = PSP_VideoInit;
	device->ListModes = PSP_ListModes;
	device->SetVideoMode = PSP_SetVideoMode;
	device->CreateYUVOverlay = NULL;
	device->SetColors = PSP_SetColors;
	device->UpdateRects = PSP_UpdateRects;
	device->VideoQuit = PSP_VideoQuit;
	device->AllocHWSurface = PSP_AllocHWSurface;
	device->CheckHWBlit = NULL;
	device->FillHWRect = NULL;
	device->SetHWColorKey = NULL;
	device->SetHWAlpha = NULL;
	device->LockHWSurface = PSP_LockHWSurface;
	device->UnlockHWSurface = PSP_UnlockHWSurface;
	device->FlipHWSurface = NULL;
	device->FreeHWSurface = PSP_FreeHWSurface;
	device->SetCaption = NULL;
	device->SetIcon = NULL;
	device->IconifyWindow = NULL;
	device->GrabInput = NULL;
	device->GetWMInfo = NULL;
	device->InitOSKeymap = PSP_InitOSKeymap;
	device->PumpEvents = PSP_PumpEvents;

	device->free = PSP_DeleteDevice;

	return device;
}

VideoBootStrap PSP_bootstrap = {
	PSPVID_DRIVER_NAME, "PSP video driver",
	PSP_Available, PSP_CreateDevice
};

const static SDL_Rect RECT_480x272 = { .w = 480, .h = 272 };
const static SDL_Rect *modelist[] = {
	&RECT_480x272,
	NULL
};

int PSP_VideoInit(_THIS, SDL_PixelFormat *vformat)
{
	/* Default for pspsdk is 8888 ABGR */
	vformat->BitsPerPixel = 32;
	vformat->BytesPerPixel = 4;

	this->hidden->vram_base = (void *)sceGeEdramGetAddr();

	PSP_EventInit(this);
	
	return(0);
}

SDL_Rect **PSP_ListModes(_THIS, SDL_PixelFormat *format, Uint32 flags)
{
	switch(format->BitsPerPixel) {
	case 32:
		return (SDL_Rect **)modelist;
	default:
		return NULL;
	}
}

SDL_Surface *PSP_SetVideoMode(_THIS, SDL_Surface *current,
				int width, int height, int bpp, Uint32 flags)
{
	int pitch;
	Uint32 Amask, Rmask, Gmask, Bmask;

	if (width != 480 || height != 272) {
		SDL_SetError("Couldn't find requested mode");
		return NULL;
	}

	switch(bpp) {
	case 32: 
		pitch = 512 * 4;
		Amask = 0xff000000;
		Rmask = 0x000000ff;
		Gmask = 0x0000ff00;
		Bmask = 0x00ff0000;
		break;
	default:
		SDL_SetError("Couldn't find requested mode");
		return(NULL);
	}
	
	if ( ! SDL_ReallocFormat(current, bpp, Rmask, Gmask, Bmask, 0) ) {
		SDL_SetError("Couldn't allocate color format");
		return(NULL);
	}

	current->flags = (SDL_FULLSCREEN | SDL_HWSURFACE);
	current->w = width;
	current->h = height;
	current->pitch = pitch;

	sceDisplaySetMode(0, width, height);
	sceDisplaySetFrameBuf(this->hidden->vram_base, 512, 3, 1);
	current->pixels = this->hidden->vram_base;
	current->flags |= SDL_PREALLOC; /* so SDL doesn't free ->pixels */

	/* We're done */
	return(current);
}

/* We don't actually allow hardware surfaces other than the main one */
static int PSP_AllocHWSurface(_THIS, SDL_Surface *surface)
{
	return(-1);
}
static void PSP_FreeHWSurface(_THIS, SDL_Surface *surface)
{
	return;
}

/* We need to wait for vertical retrace on page flipped displays */
static int PSP_LockHWSurface(_THIS, SDL_Surface *surface)
{
	return(0);
}

static void PSP_UnlockHWSurface(_THIS, SDL_Surface *surface)
{
	/* Flush video RAM */
	sceKernelDcacheWritebackAll();

	return;
}

static void PSP_UpdateRects(_THIS, int numrects, SDL_Rect *rects)
{
	/* do nothing. */
}

int PSP_SetColors(_THIS, int firstcolor, int ncolors, SDL_Color *colors)
{
	/* do nothing of note. */
	return(1);
}

/* Note:  If we are terminated, this could be called in the middle of
   another SDL video routine -- notably UpdateRects.
*/
void PSP_VideoQuit(_THIS)
{
	PSP_EventQuit(this);

	return;
}

/* vim: ts=4 sw=4
 */

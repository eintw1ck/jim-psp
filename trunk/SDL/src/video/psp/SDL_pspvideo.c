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
    Matthew H <matthewh@webone.com.au>
*/

#ifdef SAVE_RCSID
static char rcsid =
 "@(#) $Id: SDL_nullvideo.c,v 1.7 2004/01/04 16:49:24 slouken Exp $";
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

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

#define PSP_SLICE_SIZE	(32)
#define PSP_LINE_SIZE (512)
#define SCREEN_WIDTH (480)
#define SCREEN_HEIGHT (272)

#define IS_SWSURFACE(flags) ((flags & SDL_HWSURFACE) == SDL_SWSURFACE) 
#define IS_HWSURFACE(flags) ((flags & SDL_HWSURFACE) == SDL_HWSURFACE) 

static unsigned int __attribute__((aligned(16))) list[1024];

struct Vertex
{
        unsigned short u, v;
        unsigned short color;
        short x, y, z;
};

typedef struct Texture
{
        int format;
        int mipmap;
        int width, height, stride;
        const void* data;
} Texture;


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
static int PSP_FlipHWSurface(_THIS, SDL_Surface *surface);
static void PSP_UpdateRects(_THIS, int numrects, SDL_Rect *rects);

/* etc. */
static void PSP_GuUpdateRects(_THIS, int numrects, SDL_Rect *rects);

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
	device->FlipHWSurface = PSP_FlipHWSurface;
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
	/* x dimension should be a multiple of PSP_SLICE_SIZE */
	if (IS_SWSURFACE(flags))
		return (SDL_Rect **)-1;

	switch(format->BitsPerPixel) {
	case 15:
	case 16:
	case 32:
		return (SDL_Rect **)modelist;
	default:
		return NULL;
	}
}


static void init_gu(int gu_format) {
	/* gu is used for SWSURFACE */
	sceGuInit();
	sceGuStart(GU_DIRECT, list); 
	sceGuDispBuffer(SCREEN_WIDTH, SCREEN_HEIGHT, (void*)0, PSP_LINE_SIZE);
	if (gu_format == GU_PSM_T8) {
		sceGuDrawBuffer(GU_PSM_8888, (void*)0, PSP_LINE_SIZE);
		sceGuClutMode(GU_PSM_8888, 0, 255, 0);
	} else {
		sceGuDrawBuffer(gu_format, (void*)0, PSP_LINE_SIZE);
	}
	sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);
	sceGuDepthBuffer((void*) 0x110000, PSP_LINE_SIZE);
	sceGuOffset(2048 - (SCREEN_WIDTH / 2), 2048 - (SCREEN_HEIGHT / 2));
	sceGuViewport(2048, 2048, SCREEN_WIDTH, SCREEN_HEIGHT);
	sceGuDepthRange(50000, 10000);
	sceGuScissor(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	sceGuEnable(GU_SCISSOR_TEST);
	sceGuFrontFace(GU_CW);

	sceGuFinish();
	sceGuSync(0, 0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(1);
}

SDL_Surface *PSP_SetVideoMode(_THIS, SDL_Surface *current,
				int width, int height, int bpp, Uint32 flags)
{
	int pitch = 512, pixel_format, gu_format;
	Uint32 Amask, Rmask, Gmask, Bmask;

	if (IS_HWSURFACE(flags) &&
		(width != SCREEN_WIDTH || height != SCREEN_HEIGHT)) 
	{
		SDL_SetError("Couldn't find requested mode");
		return NULL;
	}

	switch(bpp) {
	case 8:
		if (IS_HWSURFACE(flags)) {
			SDL_SetError("8-bit surfaces are only supported on software surfaces.");
			return NULL;
		}
		Amask = 0;
		Rmask = 0;
		Gmask = 0;
		Bmask = 0;
		pixel_format = PSP_DISPLAY_PIXEL_FORMAT_8888; 
		gu_format = GU_PSM_T8;
		break;
	case 15: /* 5-5-5-1 */
		pitch *= 2;
		Amask = 0x00008000;
		Rmask = 0x0000001f;
		Gmask = 0x000003e0;
		Bmask = 0x00007c00;
		pixel_format = PSP_DISPLAY_PIXEL_FORMAT_5551;
		gu_format = GU_PSM_5551;
		break;
	case 16: /* 5-6-5 */
		pitch *= 2;
		Amask = 0;
		Rmask = 0x0000001f;
		Gmask = 0x000007e0;
		Bmask = 0x0000f800;
		pixel_format = PSP_DISPLAY_PIXEL_FORMAT_565;
		gu_format = GU_PSM_5650;
		break;
	case 32: /* 8-8-8-8 */
		pitch *= 4;
		Amask = 0xff000000;
		Rmask = 0x000000ff;
		Gmask = 0x0000ff00;
		Bmask = 0x00ff0000;
		pixel_format = PSP_DISPLAY_PIXEL_FORMAT_8888;
		gu_format = GU_PSM_8888;
		break;
	default:
		SDL_SetError("Couldn't find requested mode");
		return(NULL);
	}
	
	if ( ! SDL_ReallocFormat(current, bpp, Rmask, Gmask, Bmask, 0/*Amask*/) ) {
		SDL_SetError("Couldn't allocate color format");
		return(NULL);
	}

	current->flags = flags | SDL_FULLSCREEN;
	current->w = width;
	current->h = height;

	sceDisplaySetMode(0, SCREEN_WIDTH, SCREEN_HEIGHT);
	sceDisplaySetFrameBuf(this->hidden->vram_base, 512, pixel_format, 
		PSP_DISPLAY_SETBUF_NEXTFRAME);

	if (IS_HWSURFACE(flags)) {

	    current->pixels = this->hidden->vram_base;
		current->pitch = pitch;
		current->flags |= SDL_PREALLOC; /* so SDL doesn't free ->pixels */

    } else if (IS_SWSURFACE(flags)) {

		init_gu(gu_format);

		if (width > 512)
			this->hidden->stride = width;
		else
			this->hidden->stride = 512;

		current->pitch = this->hidden->stride * (bpp/8);
        current->pixels = malloc(current->pitch * 512); 

		this->hidden->gu_format = gu_format;
		this->UpdateRects = PSP_GuUpdateRects;

		if (bpp == 8 && this->hidden->gu_palette == NULL) {
			this->hidden->gu_palette = memalign(16, 4 * 256);
		}
    }

	this->hidden->pixel_format = pixel_format;
	this->hidden->frame = 0;
	this->hidden->frame_offset = 0;

	if (IS_HWSURFACE(flags) && (flags & SDL_DOUBLEBUF)) {
		this->hidden->frame_offset = pitch * height;
		/* Set the draw buffer to the second frame. */
		this->hidden->frame = 1;
		current->pixels =
			(void *) ((Uint32) this->hidden->vram_base + this->hidden->frame_offset);
	}

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

static int PSP_FlipHWSurface(_THIS, SDL_Surface *surface)
{
	void *new_pixels;

	if (surface->flags & SDL_DOUBLEBUF) {
		/* Show the draw buffer as the display buffer, and setup the next draw buffer. */
		sceKernelDcacheWritebackAll();
		sceDisplaySetFrameBuf(surface->pixels, 512,
				this->hidden->pixel_format, PSP_DISPLAY_SETBUF_IMMEDIATE);
		this->hidden->frame ^= 1;
		new_pixels = (void *) ((Uint32) this->hidden->vram_base +
				(this->hidden->frame_offset * this->hidden->frame));
		surface->pixels = new_pixels;
	}

	return 0;
}

static void PSP_UpdateRects(_THIS, int numrects, SDL_Rect *rects)
{
	/* do nothing */
}

/**
 * Update the screen using Gu textures and sprites.  
 * Useful for scaling dimensions when using SWSURFACE.
 */
static void PSP_GuUpdateRects(_THIS, int numrects, SDL_Rect *rects)
{
	unsigned int slice;
	unsigned short old_slice = 0; /* set when we load 2nd tex */
	struct Vertex *vertices;
	SDL_Surface *screen = SDL_PublicSurface;
	void *pixels;

	if (!screen) 
		return;

	pixels = screen->pixels;

	sceKernelDcacheWritebackAll();

	sceGuStart(GU_DIRECT,list);
	sceGuEnable(GU_TEXTURE_2D);
	sceGuTexMode(this->hidden->gu_format,0,0,0);
	sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGB);
	sceGuTexFilter(GU_LINEAR, GU_LINEAR);
	sceGuTexImage(0, 512, 512, this->hidden->stride, pixels);
	sceGuTexSync();

	for (slice = 0; slice < (SCREEN_WIDTH / PSP_SLICE_SIZE); slice++) {

		vertices = (struct Vertex*)sceGuGetMemory(2 * sizeof(struct Vertex));

		vertices[0].x = slice * PSP_SLICE_SIZE;
		vertices[1].x = vertices[0].x + PSP_SLICE_SIZE;

		if ((slice * PSP_SLICE_SIZE * screen->w / SCREEN_WIDTH) >= 512) {

			/* time for the second texture (?x512) */

			if (!old_slice) {

				/* load it */
				pixels += 512 * (screen->format->BitsPerPixel / 8);
				sceGuTexImage(0, this->hidden->stride - 512, 512, this->hidden->stride, pixels);
				sceGuTexSync();
				old_slice = slice;

			}

			vertices[0].u = (slice - old_slice) * PSP_SLICE_SIZE * screen->w / SCREEN_WIDTH;
			vertices[1].u = (slice - old_slice + 1) * PSP_SLICE_SIZE * screen->w / SCREEN_WIDTH;

		} else {

			/* first 512x512 texture */
			vertices[0].u = slice * PSP_SLICE_SIZE * screen->w / SCREEN_WIDTH;
			vertices[1].u = (slice + 1) * PSP_SLICE_SIZE * screen->w / SCREEN_WIDTH;

		}

		vertices[0].v = 0;
		vertices[0].color = 0;
		vertices[0].y = 0;
		vertices[0].z = 0;

		vertices[1].v = screen->h;
		vertices[1].color = 0;
		vertices[1].y = SCREEN_HEIGHT; 
		vertices[1].z = 0;

		sceGuDrawArray(GU_SPRITES,GU_TEXTURE_16BIT|GU_COLOR_4444|GU_VERTEX_16BIT|
			GU_TRANSFORM_2D,2,0,vertices);
	}

	sceGuFinish();
	sceGuSync(0,0);

	sceGuSwapBuffers();
}

int PSP_SetColors(_THIS, int firstcolor, int ncolors, SDL_Color *colors)
{
	int i, j;
	unsigned int *palette = this->hidden->gu_palette;

	if (this->hidden->gu_format != GU_PSM_T8 || palette == NULL)
		return 0;

	for (i=firstcolor, j=0; j < ncolors; i++, j++) {
		palette[i] = (colors[j].b << 16) | (colors[j].g << 8) | (colors[j].r);
	}

	sceKernelDcacheWritebackAll();
	sceGuStart(GU_DIRECT, list);
	sceGuClutLoad(32, this->hidden->gu_palette);
	sceGuFinish();

	return 1;
}

/* Note:  If we are terminated, this could be called in the middle of
   another SDL video routine -- notably UpdateRects.
*/
void PSP_VideoQuit(_THIS)
{
	SDL_Surface *screen = SDL_PublicSurface;

	if (screen && IS_SWSURFACE(screen->flags)) {
		if (this->hidden->gu_palette != NULL) {
			free(this->hidden->gu_palette);
			this->hidden->gu_palette = NULL;
		}

		sceGuTerm();
	}

	PSP_EventQuit(this);

	return;
}

/* vim: ts=4 sw=4
 */

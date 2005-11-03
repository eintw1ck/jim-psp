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

static unsigned int __attribute__((aligned(16))) list[4096];

struct Vertex
{
        unsigned short u, v;
        unsigned short color;
        short x, y, z;
};

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
static void PSP_GuInit(_THIS);
static int PSP_CheckHWBlit(_THIS, SDL_Surface *src, SDL_Surface *dst);
static int HWAccelBlit(SDL_Surface *src, SDL_Rect *srcrect,
                       SDL_Surface *dst, SDL_Rect *dstrect);
static int PSP_GuStretchBlit(SDL_Surface *src, SDL_Rect *srcrect, SDL_Rect *dstrect);

/* Software surface function */
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
	device->CheckHWBlit = PSP_CheckHWBlit;
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

const static SDL_Rect RECT_480x272 = { .x = 0, .y = 0, .w = 480, .h = 272 };
const static SDL_Rect *modelist[] = {
	&RECT_480x272,
	NULL
};

int PSP_VideoInit(_THIS, SDL_PixelFormat *vformat)
{
	/* Default for pspsdk is 8888 ABGR */
	vformat->BitsPerPixel = 32;
	vformat->BytesPerPixel = 4;

	this->info.wm_available = 0;
	this->info.hw_available = 1;
	this->info.blit_hw = 1;
	this->info.blit_hw_CC = 1;
	this->info.blit_hw_A = 1;

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

static void PSP_GuInit(_THIS) {
	void *dispbuffer = (void*) 0;
	void *drawbuffer = (void*) this->hidden->frame_offset;

	sceGuInit();
	sceGuStart(GU_DIRECT, list); 
	sceGuDispBuffer(SCREEN_WIDTH, SCREEN_HEIGHT, dispbuffer, PSP_LINE_SIZE);
	if (this->hidden->gu_format == GU_PSM_T8) {
		sceGuDrawBuffer(GU_PSM_8888, drawbuffer, PSP_LINE_SIZE);
		sceGuClutMode(GU_PSM_8888, 0, 255, 0);
	} else {
		sceGuDrawBuffer(this->hidden->gu_format, drawbuffer, PSP_LINE_SIZE);
	}
	sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);
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

/*
vidmem handling from Holger Waechtler's pspgl
*/
struct vidmem_chunk {
	void *ptr;
	unsigned long len;
};


static struct vidmem_chunk *vidmem_map = NULL;
static unsigned long vidmem_map_len = 0;

static
void *vidmem_map_insert_new (unsigned long idx, unsigned long adr, unsigned long size)
{
	void *tmp = realloc(vidmem_map, (vidmem_map_len + 1) * sizeof(vidmem_map[0]));

	if (!tmp)
		return NULL;

//	psp_log("alloc vidmem %lu: adr 0x%08x - size 0x%08x\n", idx, (unsigned int) adr, (unsigned int) size);

	vidmem_map = tmp;
	memmove(&vidmem_map[idx+1], &vidmem_map[idx], (vidmem_map_len-idx) * sizeof(vidmem_map[0]));
	vidmem_map_len++;
	vidmem_map[idx].ptr = (void*) adr;
	vidmem_map[idx].len = size;

	return vidmem_map[idx].ptr;
}


void* vidmem_alloc (unsigned long size)
{
	unsigned long start = (unsigned long) sceGeEdramGetAddr();
	unsigned long adr = start;
	unsigned long i;

	for (i=0; i<vidmem_map_len; i++) {
		if (vidmem_map[i].ptr != NULL) {
			unsigned long new_adr = (unsigned long) vidmem_map[i].ptr;
			if (size <= new_adr - adr)
				return vidmem_map_insert_new(i, adr, size);
			adr = new_adr + vidmem_map[i].len;
		}
	}

	if (adr + size > start + sceGeEdramGetSize())
		return NULL;

	return vidmem_map_insert_new(vidmem_map_len, adr, size);
}


void  vidmem_free (void * ptr)
{
	int i;

	for (i=0; i<vidmem_map_len; i++) {
		if (vidmem_map[i].ptr == ptr) {
			void *tmp;
			
//			psp_log("free vidmem %d: adr 0x%08x - size 0x%08x\n", i,
//				(unsigned int) ptr, (unsigned int) vidmem_map[i].len);
			
			vidmem_map_len--;
			memmove(&vidmem_map[i], &vidmem_map[i+1], (vidmem_map_len-i) * sizeof(vidmem_map[0]));
			tmp = realloc(vidmem_map, vidmem_map_len * sizeof(vidmem_map[0]));
			if (tmp)
				vidmem_map = tmp;
		}
	}
}

/*
roundUpToPowerOfTwo from 
Open Dynamics Engine
Copyright (c) 2001-2004, Russell L. Smith.
All rights reserved.
 */
static inline int roundUpToPowerOfTwo (int x)
{
  int i = 1;
  while (i < x) i <<= 1;
  return i;
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

	this->hidden->gu_format = gu_format;
	this->hidden->pixel_format = pixel_format;
	this->hidden->frame = 0;
	this->hidden->frame_offset = 0;
	if (width > 512)
		this->hidden->stride = width;
	else
		this->hidden->stride = 512;

	// allocate display buffer
	this->hidden->vram_base = vidmem_alloc(pitch * SCREEN_HEIGHT); 

	sceDisplaySetMode(0, SCREEN_WIDTH, SCREEN_HEIGHT);
	sceDisplaySetFrameBuf(this->hidden->vram_base, 512, pixel_format, 
		PSP_DISPLAY_SETBUF_NEXTFRAME);

	if (IS_HWSURFACE(flags)) {

	    current->pixels = this->hidden->vram_base;
		current->pitch = pitch;
		current->flags |= SDL_PREALLOC; /* so SDL doesn't free ->pixels */

		if (flags & SDL_DOUBLEBUF) {
			this->hidden->frame_offset = pitch * height;

			/* Set the draw buffer to the second frame. */
			this->hidden->frame = 1;
			current->pixels =
				(void *) ((Uint32) this->hidden->vram_base + this->hidden->frame_offset);

			// allocate drawbuffer
			vidmem_alloc(pitch * height); 
		}

    } else if (IS_SWSURFACE(flags)) {

		current->pitch = this->hidden->stride * (bpp/8);
		current->pixels = memalign(16, current->pitch * roundUpToPowerOfTwo(height)); 

		this->UpdateRects = PSP_GuUpdateRects;

		if (bpp == 8 && this->hidden->gu_palette == NULL) {
			this->hidden->gu_palette = memalign(16, 4 * 256);
		}
    }

	PSP_GuInit(this);

	/* We're done */
	return(current);
}

static int PSP_AllocHWSurface(_THIS, SDL_Surface *surface)
{
	surface->pixels = vidmem_alloc(surface->h * surface->pitch);

	if (!surface->pixels)
		return -1;

	surface->flags |= SDL_HWSURFACE;

	return 0;
}
static void PSP_FreeHWSurface(_THIS, SDL_Surface *surface)
{
	vidmem_free(this->hidden->vram_base);
	if (this->screen->flags & SDL_DOUBLEBUF)
		vidmem_free(this->hidden->vram_base + this->hidden->frame_offset);
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

	/* Show the draw buffer as the display buffer, and setup the next draw buffer. */
	sceKernelDcacheWritebackAll();
	sceGuSync(0,0);
	sceGuSwapBuffers();
	this->hidden->frame ^= 1;
	new_pixels = (void *) ((Uint32) this->hidden->vram_base +
			(this->hidden->frame_offset * this->hidden->frame));
	surface->pixels = new_pixels;

	return 0;
}

static void PSP_UpdateRects(_THIS, int numrects, SDL_Rect *rects)
{
	sceGuSync(0, 0);
}

static int PSP_CheckHWBlit(_THIS, SDL_Surface *src, SDL_Surface *dst)
{
	src->flags |= SDL_HWACCEL;
	src->map->hw_blit = HWAccelBlit;
	return 1;
}

static int HWAccelBlit(SDL_Surface *src, SDL_Rect *srcrect,
                       SDL_Surface *dst, SDL_Rect *dstrect)
{
	sceKernelDcacheWritebackAll();

	// when rendering to the screen use GuStretchBlit without stretching
	if (dst == current_video->screen)
		return PSP_GuStretchBlit(src, srcrect, dstrect); 

	sceGuStart(GU_DIRECT,list);

	sceGuCopyImage(current_video->hidden->gu_format,
		srcrect->x, srcrect->y, srcrect->w, srcrect->h, 
		src->pitch / src->format->BytesPerPixel, src->pixels,
		dstrect->x, dstrect->y, dst->pitch / dst->format->BytesPerPixel, 
		dst->pixels);

	sceGuFinish();

	return 0;
}

/** 
 * update screen from src
 */
static int PSP_GuStretchBlit(SDL_Surface *src, SDL_Rect *srcrect, SDL_Rect *dstrect)
{
	unsigned short old_slice = 0; /* set when we load 2nd tex */
	unsigned int slice, num_slices, width, height, tbw;
	struct Vertex *vertices;
	void *pixels;

	width = roundUpToPowerOfTwo(src->w);
	height = roundUpToPowerOfTwo(src->h);
	tbw = src->pitch / src->format->BytesPerPixel;
	num_slices = (srcrect->w + (PSP_SLICE_SIZE - 1)) / PSP_SLICE_SIZE;
	pixels = src->pixels;

	// Gu doesn't appreciate textures wider than 512
	if (width > 512)
		width = 512; 

	sceGuStart(GU_DIRECT,list);
	sceGuEnable(GU_TEXTURE_2D);
	sceGuTexMode(current_video->hidden->gu_format,0,0,0);
	sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGB);
	sceGuTexFilter(GU_LINEAR, GU_LINEAR);
	sceGuTexImage(0, width, height, tbw, pixels);
	sceGuTexSync();

	for (slice = 0; slice < num_slices; slice++) {

		vertices = (struct Vertex*)sceGuGetMemory(2 * sizeof(struct Vertex));

		if ((slice * PSP_SLICE_SIZE) < width) {
			vertices[0].u = srcrect->x + slice * PSP_SLICE_SIZE;
		} else {
			if (!old_slice) {
				/* load another texture (src width > 512) */
				pixels += width * src->format->BytesPerPixel;
				sceGuTexImage(0, roundUpToPowerOfTwo(src->w - width), 
					height, tbw, pixels);
				sceGuTexSync();
				old_slice = slice;
			}
			vertices[0].u = srcrect->x + (slice - old_slice) * PSP_SLICE_SIZE;
		}
		vertices[1].u = vertices[0].u + PSP_SLICE_SIZE;
		if (vertices[1].u > (srcrect->x + srcrect->w))
			vertices[1].u = srcrect->x + srcrect->w;

		vertices[0].v = srcrect->y;
		vertices[1].v = vertices[0].v + srcrect->h;

		vertices[0].x = dstrect->x + slice * PSP_SLICE_SIZE * dstrect->w / srcrect->w;
		vertices[1].x = vertices[0].x + PSP_SLICE_SIZE * dstrect->w / srcrect->w;
		if (vertices[1].x > (dstrect->x + dstrect->w))
			vertices[1].x = dstrect->x + dstrect->w;

		vertices[0].y = dstrect->y;
		vertices[1].y = vertices[0].y + dstrect->h;

		vertices[0].color = 0;
		vertices[0].z = 0;
		vertices[1].color = 0;
		vertices[1].z = 0;

		sceGuDrawArray(GU_SPRITES,GU_TEXTURE_16BIT|GU_COLOR_4444|GU_VERTEX_16BIT|
			GU_TRANSFORM_2D,2,0,vertices);
	}

	sceGuFinish();

	return 0;
}

/**
 * Update the screen from SDL_SWSURFACE (and scale).
 */
static void PSP_GuUpdateRects(_THIS, int numrects, SDL_Rect *rects)
{
	SDL_Surface *src = SDL_VideoSurface;
	SDL_Rect srcrect;

	sceKernelDcacheWritebackAll();

	// if the screen dimensions are unusual, do a single update
	if ((src->w != 480) || (src->h != 272)) {
		srcrect.x = 0;
		srcrect.y = 0;
		srcrect.w = src->w;
		srcrect.h = src->h;
		PSP_GuStretchBlit(src, &srcrect, (SDL_Rect *)&RECT_480x272);
		sceGuSync(0, 0);
		return;
	}

	// update the specified rects 
	while(numrects--) {
		PSP_GuStretchBlit(src, rects, rects);
		rects++;
	}

	sceGuSync(0, 0);
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
	sceGuSync(0, 0);

	if (this->hidden->gu_palette != NULL) {
		free(this->hidden->gu_palette);
		this->hidden->gu_palette = NULL;
	}

	sceGuTerm();

	PSP_EventQuit(this);

	return;
}

/* vim: ts=4 sw=4
 */

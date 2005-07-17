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
 "@(#) $Id: SDL_nullevents.c,v 1.4 2004/01/04 16:49:24 slouken Exp $";
#endif

/* Being a null driver, there's no event stream. We just define stubs for
   most of the API. */

#include "SDL.h"
#include "SDL_sysevents.h"
#include "SDL_events_c.h"
#include "SDL_pspvideo.h"
#include "SDL_pspevents_c.h"
#include "SDL_thread.h"
#include <psphprm.h>

static enum PspHprmKeys hprm = 0;
static SDL_sem *event_sem = NULL;
static SDL_Thread *thread = NULL;
static int running = 0;
static struct {
	enum PspHprmKeys id;
	SDLKey sym;
} keymap[] = {
	{ PSP_HPRM_PLAYPAUSE, SDLK_F10 },
	{ PSP_HPRM_FORWARD,   SDLK_F11 },
	{ PSP_HPRM_BACK,      SDLK_F12 },
	{ PSP_HPRM_VOL_UP,    SDLK_F13 },
	{ PSP_HPRM_VOL_DOWN,  SDLK_F14 },
	{ PSP_HPRM_HOLD,      SDLK_F15 }
};

int EventUpdate(void *data)
{
	while (running) {
                SDL_SemWait(event_sem);
		sceHprmPeekCurrentKey(&hprm);
                SDL_SemPost(event_sem);
                /* Delay 1/60th of a second */
                sceKernelDelayThread(1000000 / 60);  
        }
        return 0;
}

void PSP_PumpEvents(_THIS)
{
	int i;
	enum PspHprmKeys keys;
	enum PspHprmKeys changed;
	static enum PspHprmKeys old_keys = 0;
	SDL_keysym sym;

	SDL_SemWait(event_sem);
	keys = hprm;
	SDL_SemPost(event_sem);

	/* HPRM Keyboard */
	changed = old_keys ^ keys;
	old_keys = keys;
	if(changed) {
		for(i=0; i<sizeof(keymap)/sizeof(keymap[0]); i++) {
			if(changed & keymap[i].id) {
				sym.scancode = keymap[i].id;
				sym.sym = keymap[i].sym;
				SDL_PrivateKeyboard((keys & keymap[i].id) ? 
						    SDL_PRESSED : SDL_RELEASED, 
						    &sym);
			}
		}
	}

	sceKernelDelayThread(0);

	return;
}

void PSP_InitOSKeymap(_THIS)
{
	/* do nothing. */
}

void PSP_EventInit(_THIS)
{
	/* Start thread to read data */
	if((event_sem =  SDL_CreateSemaphore(1)) == NULL) {
		SDL_SetError("Can't create input semaphore\n");
		return;
	}
	running = 1;
	if((thread = SDL_CreateThread(EventUpdate, NULL)) == NULL) {
		SDL_SetError("Can't create input thread\n");
		return;
	}
}

void PSP_EventQuit(_THIS)
{
	running = 0;
	SDL_WaitThread(thread, NULL);
	SDL_DestroySemaphore(event_sem);
}

/* end of SDL_pspevents.c ... */


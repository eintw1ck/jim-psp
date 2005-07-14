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

/* PSP input mapping by Jim Paris <jim@jtan.com> */

/* On the PSP, button input is configurable and can control the
 * joystick, mouse, and keyboard.  In SDL, kb/mouse input is tied to
 * the event subsystem, while the joystick goes to its own subsystem.
 * Since either or both subsystems can be running, we use a single
 * thread that collects data from the PSP and makes it available to
 * both subsystems.  Either one can start this thread.
 */

#include "SDL.h"
#include "SDL_pspvideo.h"
#include "SDL_pspinput.h"
#include "SDL_thread.h"
#include "SDL_mutex.h"

#include <stdlib.h>
#include <pspctrl.h>
#include <pspkernel.h>

/* Button name to ID mapping, and default button configuration */
PspButtonConfig psp_button_config[] = {
	{ "PSP_TRIANGLE", PSP_CTRL_TRIANGLE, bc_joystick, 0 },
	{ "PSP_CIRCLE",   PSP_CTRL_CIRCLE,   bc_joystick, 1 },
	{ "PSP_CROSS",    PSP_CTRL_CROSS,    bc_joystick, 2 },
	{ "PSP_SQUARE",   PSP_CTRL_SQUARE,   bc_joystick, 3 },
	{ "PSP_LTRIGGER", PSP_CTRL_LTRIGGER, bc_joystick, 4 },
	{ "PSP_RTRIGGER", PSP_CTRL_RTRIGGER, bc_joystick, 5 },
	{ "PSP_DOWN",     PSP_CTRL_DOWN,     bc_joystick, 6 },
	{ "PSP_LEFT",     PSP_CTRL_LEFT,     bc_joystick, 7 },
	{ "PSP_UP",       PSP_CTRL_UP,       bc_joystick, 8 },
	{ "PSP_RIGHT",    PSP_CTRL_RIGHT,    bc_joystick, 9 },
	{ "PSP_SELECT",   PSP_CTRL_SELECT,   bc_joystick, 10 },
	{ "PSP_START",    PSP_CTRL_START,    bc_joystick, 11 },
	{ "PSP_HOME",     PSP_CTRL_HOME,     bc_joystick, 12 },
	{ "PSP_HOLD",     PSP_CTRL_HOLD,     bc_joystick, 13 },
	{ NULL, 0, 0, 0 }
};
pdm_t psp_dpad_mode = 0;
pam_t psp_analog_mode = 0;

/* Current pad state */
SceCtrlData psp_input_pad = { 0, 0, 0, 0, "" };
SDL_sem *psp_input_sem = NULL;

static SDL_Thread *thread = NULL;
static int refcount = 0;
static void read_env_config(void);

/*
 * Function to throttle updates to once per frame.
 */
int InputUpdate(void *data)
{
	while (refcount) {
		SDL_SemWait(psp_input_sem);
		sceCtrlReadBufferPositive(&psp_input_pad, 1); 
		SDL_SemPost(psp_input_sem);
		/* Delay 1/60th of a second */
		sceKernelDelayThreadCB(1000000 / 60);  
	}
	return 0;
}

/* Initialize input */
void psp_input_init(void)
{
	refcount++;
	/* If we're the first, read the config and create thread */
	if(refcount == 1) {
		read_env_config();
		sceCtrlSetSamplingCycle(0);
		sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
		psp_input_sem =  SDL_CreateSemaphore(1);
		thread = SDL_CreateThread(InputUpdate, NULL);
	}
}

/* Stop input thread */
void psp_input_quit(void)
{
	refcount--;
	if(refcount == 0) {
		/* If we were the last, kill the thread */
		SDL_WaitThread(thread, NULL);
		SDL_DestroySemaphore(psp_input_sem);
	}
}

/* Routines to read the button configuration from the environment.
 * See README.PSP for details on the format. */

/* Like strtol, but return default value if it's not well-formed
   input, or out of bounds */
static int strtol_safe(const char *s, int defaultv, int low, int high)
{
	char *end, val;

	if(!s || !s[0])
		return defaultv; /* NULL or empty */
	val = strtol(s, &end, 0);
	if(*end)
		return defaultv; /* Not all characters parsed */
	if(val < low || val > high)
		return defaultv; /* Out of bounds */
	return val;
}

static void read_env_config(void)
{
	char *s;
	int maxval;
	PspButtonConfig *pbc;

	/* First get overall modes */
	psp_dpad_mode = strtol_safe(getenv("PSP_DPAD"), 0, 0, 1);
	psp_analog_mode = strtol_safe(getenv("PSP_ANALOG"), 0, 0, 1);

	/* If we're using dpad as axes, clear the dpad button mappings */
	if(psp_dpad_mode != pdm_buttons) {
		setenv("PSP_LEFT","",1);
		setenv("PSP_RIGHT","",1);
		setenv("PSP_UP","",1);
		setenv("PSP_DOWN","",1);
	}

	/* Now do each button assignment */
	for(pbc = psp_button_config; pbc->name != NULL; pbc++)
	{
		s = getenv(pbc->name);
		
		/* If this variable doesn't exist, keep default mapping. */
		if(!s)
			continue;

		/* Otherwise, clear default mapping, even if invalid. */
		pbc->type = bc_none;

		if(!s[0] || !s[1])
			continue;

		switch(s[0]) {
		case 'J':
		case 'j':
			pbc->type = bc_joystick;
			maxval = 13;
			break;
		case 'M':
		case 'm':
			pbc->type = bc_mouse;
			maxval = 4;
			break;
		case 'K':
		case 'k':
			pbc->type = bc_keyboard;
			maxval = SDLK_LAST - 1;
			break;
		default:
			maxval = 0;
			break;
		}

		pbc->value = strtol_safe(&s[1], -1, 0, maxval);
		if(pbc->value == -1)
			pbc->type = bc_none;
	}
}

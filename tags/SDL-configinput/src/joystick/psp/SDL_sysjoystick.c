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
    slouken@devolution.com
*/

/* PSP port contributed by Marcus R. Brown <mrbrown@ocgnet.org>. */
/* Joystick stuff by Matthew H <matthewh@webone.com.au>. */

#ifdef SAVE_RCSID
static char rcsid =
 "@(#) $Id: SDL_sysjoystick.c,v 1.3 2005/02/12 18:01:30 slouken Exp $";
#endif

/* This is the system specific header for the SDL joystick API */
#include <pspctrl.h>
#include <pspkernel.h>

#include <stdio.h>		/* For the definition of NULL */
#include <stdlib.h>

#include "SDL_error.h"
#include "SDL_joystick.h"
#include "SDL_sysjoystick.h"
#include "SDL_joystick_c.h"
#include "SDL_thread.h"
#include "SDL_mutex.h"
#include "SDL_timer.h"
#include "../../video/psp/SDL_pspinput.h"

/* Function to scan the system for joysticks.
 * This function should set SDL_numjoysticks to the number of available
 * joysticks.  Joystick 0 should be the system default joystick.
 * It should return number of joysticks, or -1 on an unrecoverable fatal error.
 */
int SDL_SYS_JoystickInit(void)
{
	SDL_numjoysticks = 1;

	/* Set up joystick config according to environment variables */
	psp_input_init();

	return 1;
}

/* Function to get the device-dependent name of a joystick */
const char *SDL_SYS_JoystickName(int index)
{
	if (index == 0)
	{
		return "PSP controller";
	}

	SDL_SetError("No joystick available with that index");
	return(NULL);
}

/* Function to open a joystick for use.
   The joystick to open is specified by the index field of the joystick.
   This should fill the nbuttons and naxes fields of the joystick structure.
   It returns 0, or -1 if there is an error.
 */
int SDL_SYS_JoystickOpen(SDL_Joystick *joystick)
{
	joystick->nbuttons = 14;

	joystick->naxes = 0;
	if(psp_dpad_mode == pdm_axes)
		joystick->naxes += 2;
	if(psp_analog_mode == pam_axes)
		joystick->naxes += 2;

	joystick->nhats = 0;

	return 0;
}

/* Function to update the state of a joystick - called as a device poll.
 * This function shouldn't update the joystick structure directly,
 * but instead should call SDL_PrivateJoystick*() to deliver events
 * and update joystick device state.
 */

void SDL_SYS_JoystickUpdate(SDL_Joystick *joystick)
{
	int i, axis_base = 0;
	SceCtrlData pad; 
	enum PspCtrlButtons changed;
	static enum PspCtrlButtons old_buttons = 0;
	static Sint16 old_dpad_x = 0, old_dpad_y = 0;
	static Sint16 old_analog_x = 0, old_analog_y = 0;
	Sint16 dpad_x, dpad_y;
	PspButtonConfig *pbc;

	SDL_SemWait(psp_input_sem);
	pad = psp_input_pad;
	SDL_SemPost(psp_input_sem);

	changed = old_buttons ^ pad.Buttons;
	old_buttons = pad.Buttons;

	/* Check dpad axes */
	if (psp_dpad_mode == pdm_axes)
	{
		/* Synthesize each dpad axis as -32767, 0, or 32727. */
		dpad_x = dpad_y = 0;	       
		if(pad.Buttons & PSP_CTRL_LEFT)  dpad_x -= 32767;
		if(pad.Buttons & PSP_CTRL_RIGHT) dpad_x += 32767;
		if(pad.Buttons & PSP_CTRL_UP)    dpad_y -= 32767;
		if(pad.Buttons & PSP_CTRL_DOWN)  dpad_y += 32767;
		
		if(dpad_x != old_dpad_x) {
			SDL_PrivateJoystickAxis(joystick, axis_base+0, dpad_x);
			old_dpad_x = dpad_x;
		}

		if(dpad_y != old_dpad_y) {
			SDL_PrivateJoystickAxis(joystick, axis_base+1, dpad_y);
			old_dpad_y = dpad_y;
		}

		axis_base += 2;
	}

	/* Check analog axes */
	if (psp_analog_mode == pam_axes)
	{
		Sint16 analog_x, analog_y;

		/* Map 0,255 to -32768,32512.  This could be
		   done more accurately via a lookup table,
		   but the analog stick is bad enough that it
		   probably doesn't matter. */
		analog_x = (((Sint16)pad.Lx) - 128) * 256;
		analog_y = (((Sint16)pad.Ly) - 128) * 256;

		if(analog_x != old_analog_x) {
			SDL_PrivateJoystickAxis(joystick, axis_base+0, analog_x);
			old_analog_x = analog_x;
		}

		if(analog_y != old_analog_y) {
			SDL_PrivateJoystickAxis(joystick, axis_base+1, analog_y);
			old_analog_y = analog_y;
		}

		axis_base += 2;
	}

	/* Check buttons */
	for(pbc = psp_button_config; pbc->name != NULL; pbc++)
	{
		if(pbc->type != bc_joystick)
			continue;

		if(changed & pbc->id) {
			SDL_PrivateJoystickButton(joystick, pbc->value,
						  (pad.Buttons & pbc->id) ? 
						  SDL_PRESSED : SDL_RELEASED);
		}
	}

	/* Process callbacks.  This is required so that the Home
	 * button can exit the game.  This also happens in the video
	 * events subsystem, but that subsystem may not have been
	 * initialized by the user. */
        sceKernelDelayThreadCB(0);
}

/* Function to close a joystick after use */
void SDL_SYS_JoystickClose(SDL_Joystick *joystick)
{
	/* Do nothing. */
}

/* Function to perform any system-specific joystick related cleanup */
void SDL_SYS_JoystickQuit(void)
{
	/* Cleanup Threads and Semaphore. */
	psp_input_quit();
}

/* vim: ts=4 sw=4
 */

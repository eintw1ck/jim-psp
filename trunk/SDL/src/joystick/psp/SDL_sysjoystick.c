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

#include <stdio.h>		/* For the definition of NULL */
#include <stdlib.h>

#include "SDL_error.h"
#include "SDL_joystick.h"
#include "SDL_sysjoystick.h"
#include "SDL_joystick_c.h"

#define JITTER 1 // value between 1 and 255. 0 to disable

static int old_pad_buttons = 0; 
static int old_axes[2] = {0,0}; 

/* Function to scan the system for joysticks.
 * This function should set SDL_numjoysticks to the number of available
 * joysticks.  Joystick 0 should be the system default joystick.
 * It should return number of joysticks, or -1 on an unrecoverable fatal error.
 */
int SDL_SYS_JoystickInit(void)
{
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
	SDL_numjoysticks = 1;
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
	joystick->naxes = 2;
	return 0;
}

/* Function to update the state of a joystick - called as a device poll.
 * This function shouldn't update the joystick structure directly,
 * but instead should call SDL_PrivateJoystick*() to deliver events
 * and update joystick device state.
 */

void SDL_SYS_JoystickUpdate(SDL_Joystick *joystick)
{
	int i, change;
	SceCtrlData pad; 
	int buttons[] = {
		PSP_CTRL_TRIANGLE, PSP_CTRL_CIRCLE, PSP_CTRL_CROSS, PSP_CTRL_SQUARE,  
		PSP_CTRL_LTRIGGER, PSP_CTRL_RTRIGGER, PSP_CTRL_DOWN, PSP_CTRL_LEFT,  
		PSP_CTRL_UP, PSP_CTRL_RIGHT, PSP_CTRL_SELECT, PSP_CTRL_START, 
		PSP_CTRL_HOME, PSP_CTRL_HOLD}; 
	unsigned char val;

	sceCtrlReadBufferPositive(&pad, 1); 

	/* joystick axes events */
	for (i = 0; i < 2; i++) {
		val = i ? pad.Ly : pad.Lx;
		change = (val - old_axes[i]);

		if ( (change > JITTER) || (change < -JITTER) ) {
			SDL_PrivateJoystickAxis(joystick, (Uint8)i, 
				(Sint16)((val - 128) * 256)); 
		}

		old_axes[i] = val;
	}

	/* joystick button events */
	if ( pad.Buttons != old_pad_buttons ) {
		for ( i = 0; i < joystick->nbuttons; i++ ) {
			if ( pad.Buttons & buttons[i] ) {  
				if ( ! joystick->buttons[i] ) {
					SDL_PrivateJoystickButton(joystick, (Uint8)i, SDL_PRESSED);
				}
			} else {
				if ( joystick->buttons[i] ) {
					SDL_PrivateJoystickButton(joystick, (Uint8)i, SDL_RELEASED);
				}
			}
		}
		old_pad_buttons = pad.Buttons;
	}
}

/* Function to close a joystick after use */
void SDL_SYS_JoystickClose(SDL_Joystick *joystick)
{
	/* Do nothing. */
}

/* Function to perform any system-specific joystick related cleanup */
void SDL_SYS_JoystickQuit(void)
{
	/* Do nothing. */
}

/* vim: ts=4 sw=4
 */

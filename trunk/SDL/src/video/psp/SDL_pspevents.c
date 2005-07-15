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
#include "SDL_pspinput.h"

void PSP_PumpEvents(_THIS)
{
	SceCtrlData pad; 
	enum PspCtrlButtons changed;
	static enum PspCtrlButtons old_buttons = 0;
	static int old_x, old_y;
	int x, y;
	PspButtonConfig *pbc;
	SDL_keysym sym;

	SDL_SemWait(psp_input_sem);
	pad = psp_input_pad;
	x = psp_rel_mouse_x;
	y = psp_rel_mouse_y;
	psp_rel_mouse_x = psp_rel_mouse_y = 0;
	SDL_SemPost(psp_input_sem);

	changed = old_buttons ^ pad.Buttons;
	old_buttons = pad.Buttons;

	/* Mouse motion */
	switch(psp_analog_mode) 
	{
	case pam_mouse:
		if(x || y) 
			SDL_PrivateMouseMotion(0, 1, x, y);
		break;
	case pam_absmouse:
		x = (int)(pad.Lx * 480) / 256;
		y = (int)(pad.Ly * 272) / 256;
		if(x != old_x || y != old_y) {
			SDL_PrivateMouseMotion(0, 0, x, y);
			old_x = x;
			old_y = y;
		}
		break;
	default:
		break;
	}

	/* Keyboard and mouse buttons */
	for(pbc = psp_button_config; pbc->name != NULL; pbc++)
	{
		if(changed & pbc->id) {
			switch(pbc->type) {
			case bc_keyboard:
				sym.scancode = pbc->id;
				sym.sym = pbc->value;
				SDL_PrivateKeyboard(
					(pad.Buttons & pbc->id) ? 
					SDL_PRESSED : SDL_RELEASED, &sym);
				break;
			case bc_mouse:
				SDL_PrivateMouseButton(
					(pad.Buttons & pbc->id) ? 
					SDL_PRESSED : SDL_RELEASED, 
					pbc->value + 1, 0, 0);
				break;
			default:
				break;
			}
		}
	}


	/* Process callbacks.  This is required so that the Home
	 * button can exit the game.  This also happens in the
	 * joystick subsystem, but that subsystem may not have been
	 * initialized by the user. */
        sceKernelDelayThreadCB(0);
}

void PSP_InitOSKeymap(_THIS)
{
	/* do nothing. */
}

/* end of SDL_pspevents.c ... */


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

#ifndef PSPINPUT_H
#define PSPINPUT_H

#include <pspctrl.h>
#include "SDL_mutex.h"

typedef struct {
	char *name;
	enum PspCtrlButtons id;
	enum { bc_none, bc_joystick, bc_mouse, bc_keyboard } type;
	int value;
} PspButtonConfig;

extern PspButtonConfig psp_button_config[];

typedef enum { pdm_buttons = 0, pdm_axes = 1 } pdm_t;
extern pdm_t psp_dpad_mode;

typedef enum { pam_axes = 0, pam_mouse = 1, pam_absmouse = 2 } pam_t;
extern pam_t psp_analog_mode;
extern int psp_rel_mouse_x, psp_rel_mouse_y;

extern SceCtrlData psp_input_pad;
extern SDL_sem *psp_input_sem;

void psp_input_init(void);
void psp_input_quit(void);

#endif

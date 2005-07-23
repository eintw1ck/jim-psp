#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <SDL/SDL.h>

#include <GL/gl.h> 
#include <GL/sdlswgl.h>
#include "ui.h"


#ifndef M_PI
#  define M_PI 3.14159265
#endif

int done = 0;

#ifdef PSP
/*
 * todo: use sdlmain instead of all this guff
 */
#include <pspkernel.h>
#include <pspdebug.h>

PSP_MODULE_INFO("SDL App", 0x1000, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

#define fprintf(x, args...) pspDebugScreenPrintf(args)
#define printf(args...) pspDebugScreenPrintf(args)

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
	done = 1;
	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();

	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", CallbackThread,
				     0x11, 0xFA0, 0, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}
#endif

void tkSwapBuffers(void)
{
	sdl_swgl_SwapBuffers();
}

int ui_loop(int argc, char **argv, const char *name)
{
	SDL_Surface *screen;
	sdl_swgl_Context *ctx=sdl_swgl_CreateContext();

	SetupCallbacks();
	SDL_Init(SDL_INIT_VIDEO);

	screen=SDL_SetVideoMode(480,272,8,SDL_HWSURFACE|SDL_DOUBLEBUF);
	sdl_swgl_MakeCurrent(screen,ctx);

	init();
	reshape(480,272);

	while(!done)
	{
		SDL_Event event;

		while(SDL_PollEvent(&event) > 0)
		{
			if (event.type == SDL_QUIT)
				done=1;
			else
				if (event.type == SDL_KEYDOWN)
				{
					SDLKey sdlkey=event.key.keysym.sym;
					int k=0;

					switch(sdlkey)
					{
						
						case SDLK_UP:
							k = KEY_UP;
							break;
						case SDLK_DOWN:
							k = KEY_DOWN;
							break;
						case SDLK_LEFT:
							k = KEY_LEFT;
							break;
						case SDLK_RIGHT:
							k = KEY_RIGHT;
							break;
						case SDLK_ESCAPE:
							k = KEY_ESCAPE;
							break;
						default:
							k = (int)sdlkey;
					}
					key(k, 0);
				}
		}
		idle();
#ifndef GP32
//		SDL_Delay(250);
#endif
	}

#ifdef PSP
        sceKernelExitGame();
#endif

	SDL_Quit();
	return 0;
}

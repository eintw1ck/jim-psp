#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "SDL_main.h"
#include "SDL_thread.h"
#include "SDL_mutex.h"

/* Tests and demonstrates use of:
     Joystick
     Mouse
     Keyboard
     Mutex
     Timer
     Video
*/

/* Maximum 480 x 272 for the PSP.  Smaller is fine. */
#define W 480
#define H 272

SDL_Surface *screen;

SDL_mutex *color_mutex;
Uint32 color = 0;
int color_draw = 0;

static Uint32 color_square(Uint32 interval, void *param)
{
	int r = 0, g = 0, b = 0;

	/* Shouldn't draw from a thread, so just pick a color and
	   signal main event loop that drawing should happen */
	if((int) param == 1)
		r = rand() & 255;
	if((int) param == 2)
		g = rand() & 255;
	if((int) param == 3)
		b = rand() & 255;

	SDL_mutexP(color_mutex);
	color = SDL_MapRGB(screen->format, r, g, b);
	color_draw = 1;
	SDL_mutexV(color_mutex);

	return interval;
}

static void draw_gradient(void)
{
	int i, j;
	Uint8 r, g, b;
	SDL_Rect rect;

	/* Draw gradient (very inefficient way to plot pixels) */
	for(i=0; i<W; i++) {
		for(j=0; j<H; j++) {
			rect.x = i; rect.y = j; rect.w = 1; rect.h = 1;
			r = (i * 255) / (W - 1);
			g = 255 - r;
			b = (j * 255) / (H - 1);
			SDL_FillRect(screen, &rect, 
				     SDL_MapRGB(screen->format, r, g, b));
		}
	}
	SDL_UpdateRect(screen, 0, 0, 0, 0);
}

int main(int argc, char *argv[])
{
	SDL_Joystick *joystick = NULL;
	SDL_Event event;
	SDL_TimerID t1, t2, t3;
	int done = 0;

	/* Initialize SDL. */
	if (SDL_Init(SDL_INIT_VIDEO |
		     SDL_INIT_JOYSTICK | 
		     SDL_INIT_TIMER) < 0) {
		fprintf(stderr, "init: '%s'\n", SDL_GetError());
		return 1;
	}

	if((color_mutex = SDL_CreateMutex()) == NULL) {
		fprintf(stderr, "mutex: '%s'\n", SDL_GetError());
		return 1;
	}

	/* Set video mode.  Any pixel format should work. */
	if((screen = SDL_SetVideoMode(W, H, 32, 0)) == NULL)
	{
		fprintf(stderr, "SetVideoMode: %s\n", SDL_GetError());
		return 1;
	}

	/* Draw background */
	draw_gradient();

	/* Wait 1 second */
	SDL_Delay(1000);

	/* Set up three callbacks to change color and signal drawing */
	t1 = SDL_AddTimer(200, color_square, (void*)1); 
	t2 = SDL_AddTimer(350, color_square, (void*)2);
	t3 = SDL_AddTimer(500, color_square, (void*)3);
	
	/* Open the joystick */
	if(SDL_NumJoysticks()) {
		joystick = SDL_JoystickOpen(0);
	} else {
		printf("No joystick detected\n");
	}

	/* Main event loop */
	done = 0;
	while (!done) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_MOUSEBUTTONDOWN:
				if(event.button.button == SDL_BUTTON_LEFT)
					draw_gradient();
				else if(event.button.button == SDL_BUTTON_RIGHT)
					done = 1;
				break;
			case SDL_JOYBUTTONDOWN:
				if(event.jbutton.button == 0)
					draw_gradient();
				else if(event.jbutton.button == 1)
					done = 1;
				break;
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_SPACE)
					draw_gradient();
				else if(event.key.keysym.sym == SDLK_ESCAPE)
					done = 1;
				break;
			case SDL_QUIT:
				done = 1;
				break;
			default:
				break;
			}
		}
		SDL_mutexP(color_mutex);
		if(color_draw) {
			SDL_Rect rect;

			color_draw = 0;			

			rect.x = rand()%(W-50);
			rect.y = rand()%(H-50);
			rect.w = 50;
			rect.h = 50;

			SDL_FillRect(screen, &rect, color);
			SDL_UpdateRect(screen, rect.x, rect.y, rect.w, rect.h);
		}
		SDL_mutexV(color_mutex);
	}

	/* Cleanup */
	SDL_RemoveTimer(t1);
	SDL_RemoveTimer(t2);
	SDL_RemoveTimer(t3);

	if(joystick)
		SDL_JoystickClose(joystick);


	SDL_DestroyMutex(color_mutex);
	SDL_Quit();

	return(0);
}



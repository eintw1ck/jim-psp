#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>

/* Maximum 480 x 272 for the PSP.  Smaller is fine. */
#define W 480
#define H 272

int main(int argc, char *argv[])
{
	SDL_Surface *screen;
	SDL_Rect rect;
	int i, j;
	Uint8 r, g, b;
  
	/* Initialize SDL. */
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "init: '%s'\n", SDL_GetError());
		return 1;
	}

	/* Set video mode.  Any pixel format should work. */
	screen = SDL_SetVideoMode(W, H, 32, SDL_HWSURFACE);
	if(screen == NULL)
	{
		fprintf(stderr,"HW surface: %s\n", SDL_GetError());
		screen = SDL_SetVideoMode(W, H, 32, SDL_SWSURFACE);
		if(screen == NULL) {
			fprintf(stderr, "SW surface: %s\n", SDL_GetError());
			return 1;
		}
	}

	SDL_ShowCursor(SDL_DISABLE);

	/* Draw gradient (not an efficient way to plot pixels) */
	for(i=0; i<W; i++) {
		for(j=0; j<H; j++) {
			rect.x = i;
			rect.y = j;
			rect.w = 1;
			rect.h = 1;
			
			r = (i * 255) / (W - 1);
			g = 255 - r;
			b = (j * 255) / (H - 1);

			SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format,
							       r, g, b));
		}
	}
	SDL_UpdateRect(screen, 0, 0, 0, 0);

	/* Wait 5 seconds */
	SDL_Delay(5000);

	/* Draw 30 random squares */
	for(i=0; i<30; i++) {
		rect.x = rand()%(W-50);
		rect.y = rand()%(H-50);
		rect.w = 50;
		rect.h = 50;
		
		r = g = b = 0;
		if(i < 10)
			r = rand() & 255;
		else if(i < 20)
			g = rand() & 255;
		else if(i < 30)
			b = rand() & 255;
		
		SDL_FillRect(screen, &rect, 
			     SDL_MapRGB(screen->format, r, g, b));
		SDL_UpdateRect(screen, rect.x, rect.y, rect.w, rect.h);
		
		SDL_Delay(100);
	}

	/* Wait 5 seconds */
	SDL_Delay(5000);

	SDL_Quit();
	return(0);
}



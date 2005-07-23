
#include <GL/sdlswgl.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/*  Prototype  */
static int sdl_swgl_resize_viewport( GLContext *c, int *xsize_ptr, int *ysize_ptr );


/*  Create context  */
sdl_swgl_Context *sdl_swgl_CreateContext(){
	sdl_swgl_Context *ctx;

	ctx = (sdl_swgl_Context*)malloc( sizeof(sdl_swgl_Context) );
	if( ctx == NULL ){
		return NULL;
	}
	ctx->gl_context = NULL;
	ctx->indexes = NULL;
	ctx->palette = NULL;
	return ctx;
}


/*!  Destroy context  */
void sdl_swgl_DestroyContext( sdl_swgl_Context *ctx ){
	if( ctx->gl_context != NULL ){
		glClose();
	}
	if ( ctx->indexes != NULL)
		free(ctx->indexes);
	if ( ctx->palette != NULL)
		free(ctx->palette);
	free( ctx );
}


/*!  Connect surface to context  */
int sdl_swgl_MakeCurrent( SDL_Surface *surface, sdl_swgl_Context *ctx ){
	int	mode;
	int	xsize;
	int	ysize;
	int	n_colors = 0;
	ZBuffer *zb;

	if( ctx->gl_context == NULL ){
		/* create the TinyGL context */

		xsize = surface->w;
		ysize = surface->h;

		switch( surface->format->BitsPerPixel ){
			case  8:
				ctx->indexes = (unsigned char *)malloc(ZB_NB_COLORS);
				if (ctx->indexes == NULL)
					return 0;
				for(mode=0;mode<ZB_NB_COLORS;mode++)
					ctx->indexes[mode]=mode;

				ctx->palette = (unsigned int *)calloc (ZB_NB_COLORS, sizeof(int));
				if (ctx->palette == NULL)
				{
					free(ctx->indexes);
					ctx->indexes = NULL;
					return 0;
				}

				ctx->pitch = surface->pitch * 2;
				n_colors = ZB_NB_COLORS;
				mode = ZB_MODE_INDEX;
//				printf("TGL  8-bit\n");
				break;
			case 16:
				ctx->pitch = surface->pitch;
				mode = ZB_MODE_5R6G5B;
//				printf("TGL 16-bit\n");
				break;
			case 24:
				ctx->pitch = ( surface->pitch * 2 ) / 3;
				mode = ZB_MODE_RGB24;
//				printf("TGL 24-bit\n");
				break;
			case 32:
				ctx->pitch = surface->pitch / 2;
				mode = ZB_MODE_RGBA;
//				printf("TGL 32-bit\n");
				break;
			default:
				return 0;
				break;
		}
		zb = ZB_open( xsize, ysize, mode, n_colors, (unsigned char*)ctx->indexes, (int *)ctx->palette, NULL);
		
		if( zb == NULL ){
//			fprintf( stderr, "Error while initializing Z buffer\n" ); 
			if (ctx->indexes != NULL )
			{
				free(ctx->indexes);
				ctx->indexes = NULL;
			}
			if (ctx->palette != NULL )
			{
				free(ctx->palette);
				ctx->palette = NULL;
			}
			return 0;
		}

		if (ctx->palette != NULL)
		{
			SDL_Color *pal=(SDL_Color *)calloc(ZB_NB_COLORS,sizeof(SDL_Color));
			if (pal!=NULL)
			{
				for (mode=0; mode<ZB_NB_COLORS; mode++)
				{
					pal[mode].r = (ctx->palette[mode]>>16) & 0xFF;
					pal[mode].g = (ctx->palette[mode]>>8) & 0xFF;
					pal[mode].b = (ctx->palette[mode]) & 0xFF;
				}

				SDL_SetColors(surface, pal, 0, ZB_NB_COLORS);
				free(pal);
			}
		}
		
		/* initialisation of the TinyGL interpreter */
		glInit( zb );
		ctx->gl_context                     = gl_get_context();
		ctx->gl_context->opaque             = (void *) ctx;
		ctx->gl_context->gl_resize_viewport = sdl_swgl_resize_viewport;

		/* set the viewport */
		/*  TIS: !!! HERE SHOULD BE -1 on both to force reshape  */
		/*  which is needed to make sure initial reshape is  */
		/*  called, otherwise it is not called..  */
		ctx->gl_context->viewport.xsize = xsize;
		ctx->gl_context->viewport.ysize = ysize;
		glViewport( 0, 0, xsize, ysize );
	}
	ctx->surface = surface;
	return 1;
}


/*!  Swap buffers  */
void sdl_swgl_SwapBuffers(){
	GLContext        *gl_context;
	sdl_swgl_Context *ctx;

    
    /* retrieve the current sdl_swgl_Context */
    gl_context = gl_get_context();
    ctx = (sdl_swgl_Context *)gl_context->opaque;

/*
	if ( (ctx->surface->flags & SDL_DOUBLEBUF) == SDL_DOUBLEBUF ) {
*/
		SDL_Flip( ctx->surface );
/*
	}else{
		SDL_UpdateRect( ctx->surface, 0, 0, ctx->surface->w, ctx->surface->h );
	}
*/
	ZB_copyFrameBuffer(ctx->gl_context->zb, ctx->surface->pixels, ctx->pitch);
}


/*!  Resize context  */
static int sdl_swgl_resize_viewport( GLContext *c, int *xsize_ptr, int *ysize_ptr ){
	sdl_swgl_Context *ctx;
	int               xsize;
	int               ysize;
  
	ctx = (sdl_swgl_Context *)c->opaque;

	xsize = *xsize_ptr;
	ysize = *ysize_ptr;

	/* we ensure that xsize and ysize are multiples of 2 for the zbuffer. 
	   TODO: find a better solution */
	xsize &= ~3;
	ysize &= ~3;

	if (xsize == 0 || ysize == 0) return -1;

	*xsize_ptr = xsize;
	*ysize_ptr = ysize;

	/* resize the Z buffer */
	ZB_resize( c->zb, ctx->surface->pixels, xsize, ysize );
	return 0;
}


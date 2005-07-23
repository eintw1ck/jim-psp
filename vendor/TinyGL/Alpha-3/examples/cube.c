/*
 * This code was created by Jeff Molofee '99 
 * (ported to Linux/SDL by Ti Leggett '01)
 * (ported to SDL-TinyGL by Chui)
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/math-sll.h>
#include "ui.h"
#include <SDL/SDL.h>
#include "mytexture.h"

/* Set up some booleans */
#define TRUE  1
#define FALSE 0

GLfloat xrot; /* X Rotation ( NEW ) */
GLfloat yrot; /* Y Rotation ( NEW ) */
GLfloat zrot; /* Z Rotation ( NEW ) */

GLuint texture[1]; /* Storage For One Texture ( NEW ) */


/* function to load in bitmap as a GL texture */
int LoadGLTextures( )
{
    /* Status indicator */
    int ret = FALSE;

    /* Create storage space for the texture */
    SDL_Surface *TextureImage[1]; 

    /* Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit */
    if ( ( TextureImage[0] = SDL_LoadBMP_RW(SDL_RWFromMem(&my_texture,MY_TEXTURE_SIZE),0) ) )
        {

	    /* Set the status to true */
	    ret = TRUE;

	    /* Create The Texture */
	    glGenTextures( 1, &texture[0] );

	    /* Typical Texture Generation Using Data From The Bitmap */
	    glBindTexture( GL_TEXTURE_2D, texture[0] );

	    /* Generate The Texture */
	    glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[0]->w,
			  TextureImage[0]->h, 0, GL_RGB /*GL_BGR */,
			  GL_UNSIGNED_BYTE, TextureImage[0]->pixels );

	    /* Linear Filtering */
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        }

    /* Free up any memory we may have used */
    if ( TextureImage[0] )
	    SDL_FreeSurface( TextureImage[0] );

    return ret;
}

/* function to reset our viewport after a window resize */
void reshape( int width, int height )
{
    /* Height / width ration */
    sll ratio;
 
    /* Protect against a divide by zero */
    if ( height == 0 )
	height = 1;

    ratio = slldiv(int2sll(width), int2sll(height));

    /* Setup our viewport. */
    glViewport( 0, 0, ( GLint )width, ( GLint )height );

    /*
     * change to the projection matrix and set
     * our viewing volume.
     */
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );

    /* Set our perspective */
    gluPerspective( int2sll(45), ratio, dbl2sll(0.1), int2sll(100) );

    /* Make sure we're chaning the model view and not the projection */
    glMatrixMode( GL_MODELVIEW );

    /* Reset The View */
    glLoadIdentity( );
}

/* function to handle key press events */
GLenum key( int k, GLenum mask )
{
    switch ( k )
	{
	case KEY_ESCAPE:
	    /* ESC key was pressed */
	    exit( 0 );
	}

    return GL_FALSE;
}

/* general OpenGL initialization function */
void init( void )
{

    /* Load in the texture */
    if ( !LoadGLTextures( ) )
	    puts("Textures no loading!!!!!");

    /* Enable Texture Mapping ( NEW ) */
    glEnable( GL_TEXTURE_2D );

    /* Enable smooth shading */
    glShadeModel( GL_SMOOTH );

    /* Set the background black */
    glClearColor( int2sll(0), int2sll(0), int2sll(0), dbl2sll(0.5) );

    /* Depth buffer setup */
    glClearDepth( int2sll(1) );

    /* Enables Depth Testing */
    glEnable( GL_DEPTH_TEST );

    /* The Type Of Depth Test To Do */
//    glDepthFunc( GL_LEQUAL );

    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

}

/* Here goes our drawing code */
void draw(void)
{
    /* Clear The Screen And The Depth Buffer */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /* Move Into The Screen 5 Units */
    glLoadIdentity( );
    glTranslatef( int2sll(0), int2sll(0), int2sll(-5) );

    glRotatef( xrot, int2sll(1), int2sll(0), int2sll(0)); /* Rotate On The X Axis */
    glRotatef( yrot, int2sll(0), int2sll(1), int2sll(0)); /* Rotate On The Y Axis */
    glRotatef( zrot, int2sll(0), int2sll(0), int2sll(1)); /* Rotate On The Z Axis */

    /* Select Our Texture */
    glBindTexture( GL_TEXTURE_2D, texture[0] );

    /* NOTE:
     *   The x coordinates of the glTexCoord2f function need to inverted
     * for SDL because of the way SDL_LoadBmp loads the data. So where
     * in the tutorial it has glTexCoord2f( int2sll(1), int2sll(0) ); it should
     * now read glTexCoord2f( int2sll(0), int2sll(0) );
     */
    glBegin(GL_QUADS);
      /* Front Face */
      /* Bottom Left Of The Texture and Quad */
      glTexCoord2f( int2sll(0), int2sll(1) ); glVertex3f( int2sll(-1),int2sll(-1), int2sll(1) );
      /* Bottom Right Of The Texture and Quad */
      glTexCoord2f( int2sll(1), int2sll(1) ); glVertex3f( int2sll(1), int2sll(-1), int2sll(1) );
      /* Top Right Of The Texture and Quad */
      glTexCoord2f( int2sll(1), int2sll(0) ); glVertex3f( int2sll(1), int2sll(1), int2sll(1) );
      /* Top Left Of The Texture and Quad */
      glTexCoord2f( int2sll(0), int2sll(0) ); glVertex3f( int2sll(-1), int2sll(1), int2sll(1) );

      /* Back Face */
      /* Bottom Right Of The Texture and Quad */
      glTexCoord2f( int2sll(0), int2sll(0) ); glVertex3f( int2sll(-1), int2sll(-1), int2sll(-1) );
      /* Top Right Of The Texture and Quad */
      glTexCoord2f( int2sll(0), int2sll(1) ); glVertex3f( int2sll(-1), int2sll(1), int2sll(-1) );
      /* Top Left Of The Texture and Quad */
      glTexCoord2f( int2sll(1), int2sll(1) ); glVertex3f( int2sll(1), int2sll(1), int2sll(-1) );
      /* Bottom Left Of The Texture and Quad */
      glTexCoord2f( int2sll(1), int2sll(0) ); glVertex3f( int2sll(1), int2sll(-1), int2sll(-1) );

      /* Top Face */
      /* Top Left Of The Texture and Quad */
      glTexCoord2f( int2sll(1), int2sll(1) ); glVertex3f( int2sll(-1),  int2sll(1), int2sll(-1) );
      /* Bottom Left Of The Texture and Quad */
      glTexCoord2f( int2sll(1), int2sll(0) ); glVertex3f( int2sll(-1),  int2sll(1),  int2sll(1) );
      /* Bottom Right Of The Texture and Quad */
      glTexCoord2f( int2sll(0), int2sll(0) ); glVertex3f(  int2sll(1),  int2sll(1),  int2sll(1) );
      /* Top Right Of The Texture and Quad */
      glTexCoord2f( int2sll(0), int2sll(1) ); glVertex3f(  int2sll(1),  int2sll(1), int2sll(-1) );

      /* Bottom Face */
      /* Top Right Of The Texture and Quad */
      glTexCoord2f( int2sll(0), int2sll(1) ); glVertex3f( int2sll(-1), int2sll(-1), int2sll(-1) );
      /* Top Left Of The Texture and Quad */
      glTexCoord2f( int2sll(1), int2sll(1) ); glVertex3f(  int2sll(1), int2sll(-1), int2sll(-1) );
      /* Bottom Left Of The Texture and Quad */
      glTexCoord2f( int2sll(1), int2sll(0) ); glVertex3f(  int2sll(1), int2sll(-1),  int2sll(1) );
      /* Bottom Right Of The Texture and Quad */
      glTexCoord2f( int2sll(0), int2sll(0) ); glVertex3f( int2sll(-1), int2sll(-1),  int2sll(1) );

      /* Right face */
      /* Bottom Right Of The Texture and Quad */
      glTexCoord2f( int2sll(0), int2sll(0) ); glVertex3f( int2sll(1), int2sll(-1), int2sll(-1) );
      /* Top Right Of The Texture and Quad */
      glTexCoord2f( int2sll(0), int2sll(1) ); glVertex3f( int2sll(1),  int2sll(1), int2sll(-1) );
      /* Top Left Of The Texture and Quad */
      glTexCoord2f( int2sll(1), int2sll(1) ); glVertex3f( int2sll(1),  int2sll(1),  int2sll(1) );
      /* Bottom Left Of The Texture and Quad */
      glTexCoord2f( int2sll(1), int2sll(0) ); glVertex3f( int2sll(1), int2sll(-1),  int2sll(1) );

      /* Left Face */
      /* Bottom Left Of The Texture and Quad */
      glTexCoord2f( int2sll(1), int2sll(0) ); glVertex3f( int2sll(-1), int2sll(-1), int2sll(-1) );
      /* Bottom Right Of The Texture and Quad */
      glTexCoord2f( int2sll(0), int2sll(0) ); glVertex3f( int2sll(-1), int2sll(-1),  int2sll(1) );
      /* Top Right Of The Texture and Quad */
      glTexCoord2f( int2sll(0), int2sll(1) ); glVertex3f( int2sll(-1),  int2sll(1),  int2sll(1) );
      /* Top Left Of The Texture and Quad */
      glTexCoord2f( int2sll(1), int2sll(1) ); glVertex3f( int2sll(-1),  int2sll(1), int2sll(-1) );
    glEnd( );

    tkSwapBuffers();
}

void idle(void)
{
    xrot = slladd(xrot, dbl2sll(1.6)); /* X Axis Rotation */
    yrot = slladd(yrot, dbl2sll(1.4)); /* Y Axis Rotation */
    zrot = slladd(zrot, dbl2sll(1.8)); /* Z Axis Rotation */

    draw();
}

int main( int argc, char **argv )
{
	return ui_loop(argc, argv, "cube");
}

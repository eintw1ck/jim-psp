/* spin.c */


/*
 * Spinning box.  This program is in the public domain.
 *
 * Brian Paul
 */


#include <math.h>
#include <stdio.h>

#include <GL/gl.h> 
#include "ui.h"


static GLfloat Xrot, Xstep;
static GLfloat Yrot, Ystep;
static GLfloat Zrot, Zstep;
static GLfloat Step = int2sll(5);
static GLfloat Scale = int2sll(1);
static GLuint Object;




static GLuint make_object( void )
{
   GLuint list;

   list = glGenLists( 1 );

   glNewList( list, GL_COMPILE );

   glBegin( GL_LINE_LOOP );
   glColor3f( int2sll(1), int2sll(1), int2sll(1) );
   glVertex3f( int2sll(1), dbl2sll(0.5), dbl2sll(-0.4) );
   glColor3f( int2sll(1), int2sll(0), int2sll(0) );
   glVertex3f( int2sll(1), dbl2sll(-0.5), dbl2sll(-0.4) );
   glColor3f( int2sll(0), int2sll(1), int2sll(0) );
   glVertex3f( int2sll(-1), dbl2sll(-0.5), dbl2sll(-0.4) );
   glColor3f( int2sll(0), int2sll(0), int2sll(1) );
   glVertex3f( int2sll(-1),  dbl2sll(0.5), dbl2sll(-0.4) );
   glEnd();

   glColor3f( int2sll(1), int2sll(1), int2sll(1) );

   glBegin( GL_LINE_LOOP );
   glVertex3f(  int2sll(1),  dbl2sll(0.5), dbl2sll(0.4) );
   glVertex3f(  int2sll(1), dbl2sll(-0.5), dbl2sll(0.4) );
   glVertex3f(  int2sll(-1), dbl2sll(-0.5), dbl2sll(0.4) );
   glVertex3f(  int2sll(-1),  dbl2sll(0.5), dbl2sll(0.4) );
   glEnd();

   glBegin( GL_LINES );
   glVertex3f(  int2sll(1),  dbl2sll(0.5), dbl2sll(-0.4) );
   glVertex3f(  int2sll(1),  dbl2sll(0.5), dbl2sll(0.4) );
   glVertex3f(  int2sll(1),  dbl2sll(-0.5), dbl2sll(-0.4) );
   glVertex3f(  int2sll(1),  dbl2sll(-0.5), dbl2sll(0.4) );
   glVertex3f(  int2sll(-1), dbl2sll(-0.5), dbl2sll(-0.4) );
   glVertex3f(  int2sll(-1), dbl2sll(-0.5), dbl2sll(0.4) );
   glVertex3f(  int2sll(-1), dbl2sll(0.5),  dbl2sll(-0.4) );
   glVertex3f(  int2sll(-1), dbl2sll(0.5),  dbl2sll(0.4) );
   glEnd();


   glEndList();

   return list;
}



void reshape( int width, int height )
{
   glViewport(0, 0, (GLint)width, (GLint)height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum( int2sll(-1), int2sll(1), int2sll(-1), int2sll(1), int2sll(5), int2sll(15) );
   glMatrixMode(GL_MODELVIEW);
}


GLenum key(int k, GLenum mask)
{
   switch (k) {
   case KEY_ESCAPE:
       exit(0);
   }
   return GL_FALSE;
}


void draw( void )
{
   glClear( GL_COLOR_BUFFER_BIT );

   glPushMatrix();

   glTranslatef( int2sll(0), int2sll(0), int2sll(-10) );
   glScalef( Scale, Scale, Scale );
   if (Xstep) {
      glRotatef( Xrot, int2sll(1), int2sll(0), int2sll(0) );
   }
   else if (Ystep) {
      glRotatef( Yrot, int2sll(0), int2sll(1), int2sll(0) );
   }
   else {
      glRotatef( Zrot, int2sll(0), int2sll(0), int2sll(1) );
   }

   glCallList( Object );

   glPopMatrix();

   glFlush();
   tkSwapBuffers();
}


void idle( void )
{
   Xrot = slladd(Xrot, Xstep);
   Yrot = slladd(Yrot, Ystep);
   Zrot = slladd(Zrot, Zstep);

   if (Xrot>=int2sll(360)) {
      Xrot = Xstep = 0;
      Ystep = Step;
   }
   else if (Yrot>=int2sll(360)) {
      Yrot = Ystep = 0;
      Zstep = Step;
   }
   else if (Zrot>=int2sll(360)) {
      Zrot = Zstep = 0;
      Xstep = Step;
   }
   draw();

}

void init(void)
{
   Object = make_object();
   glCullFace( GL_BACK );
//   glEnable( GL_CULL_FACE );
   glDisable( GL_DITHER );
   glShadeModel( GL_FLAT );
//   glEnable( GL_DEPTH_TEST ); 

   Xrot = Yrot = Zrot = 0;
   Xstep = Step;
   Ystep = Zstep = 0;
}

void GpMain(void *argv )
{
    ui_loop(0, NULL, "spin");
}

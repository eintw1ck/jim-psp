/* gears.c */

/*
 * 3-D gear wheels.  This program is in the public domain.
 *
 * Brian Paul
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <GL/gl.h> 
#include "ui.h"

#ifndef M_PI
#  define M_PI 3.14159265
#endif


/*
 * Draw a gear wheel.  You'll probably want to call this function when
 * building a display list since we do a lot of trig here.
 *
 * Input:  inner_radius - radius of hole at center
 *         outer_radius - radius at center of teeth
 *         width - width of gear
 *         teeth - number of teeth
 *         tooth_depth - depth of tooth
 */
static void gear( GLfloat inner_radius, GLfloat outer_radius, GLfloat width,
		  GLint teeth, GLfloat tooth_depth )
{
   GLint i;
   GLfloat r0, r1, r2;
   GLfloat angle, da;
   GLfloat u, v, len;
   GLfloat toothdiv2= slldiv(tooth_depth, int2sll(2));

   r0 = inner_radius;
   r1 = sllsub(outer_radius, toothdiv2);
   r2 = slladd(outer_radius, toothdiv2);

   da = sllmul(int2sll(3), slldiv(slldiv(dbl2sll(2.0*M_PI), int2sll(teeth)), int2sll(4)));

   glShadeModel( GL_FLAT );

   glNormal3f( int2sll(0), int2sll(0), int2sll(1) );

   /* draw front face */
   glBegin( GL_QUAD_STRIP );
   for (i=0;i<=teeth;i++) {
      angle = slldiv(sllmul(int2sll(i), dbl2sll(2.0*M_PI)), teeth);
      glVertex3f( sllmul(r0, sllcos(angle)), sllmul(r0, sllsin(angle)), slldiv(width, int2sll(2)) );
      glVertex3f( sllmul(r1, sllcos(angle)), sllmul(r1, sllsin(angle)), slldiv(width, int2sll(2)) );
      glVertex3f( sllmul(r0, sllcos(angle)), sllmul(r0, sllsin(angle)), slldiv(width, int2sll(2)) );
      glVertex3f( sllmul(r1, sllcos(slladd(angle,da))), sllmul(r1, sllsin(slladd(angle, da))), slldiv(width, int2sll(2)) );
   }
   glEnd();

   /* draw front sides of teeth */
   glBegin( GL_QUADS );
   da = slldiv(slldiv(dbl2sll(2.0*M_PI), int2sll(teeth)), int2sll(4));
   for (i=0;i<teeth;i++) {
      angle = slldiv(sllmul(int2sll(i), dbl2sll(2.0*M_PI)), int2sll(teeth));

      glVertex3f( sllmul(r1, sllcos(angle)), sllmul(r1, sllsin(angle)), slldiv(width, int2sll(2)) );
      glVertex3f( sllmul(r2, sllcos(slladd(angle,da))), sllmul(r2, sllsin(slladd(angle,da))), slldiv(width, int2sll(2)) );
      glVertex3f( sllmul(r2, sllcos(slladd(angle, sllmul(int2sll(2),da)))), sllmul(r2, sllsin(slladd(angle, sllmul(int2sll(2),da)))), slldiv(width, int2sll(2)) );
      glVertex3f( sllmul(r1, sllcos(slladd(angle, sllmul(int2sll(3), da)))), sllmul(r1, sllsin(slladd(angle, sllmul(int2sll(3), da)))), slldiv(width, int2sll(2)) );
   }
   glEnd();


   glNormal3f( int2sll(0), int2sll(0), int2sll(-1) );

   /* draw back face */
   glBegin( GL_QUAD_STRIP );
   for (i=0;i<=teeth;i++) {
      angle = slldiv(sllmul(int2sll(i), dbl2sll(2.0*M_PI)), int2sll(teeth));
      glVertex3f( sllmul(r1, sllcos(angle)), sllmul(r1, sllsin(angle)), sllneg(slldiv(width, int2sll(2))) );
      glVertex3f( sllmul(r0, sllcos(angle)), sllmul(r0, sllsin(angle)), sllneg(slldiv(width, int2sll(2))) );
      glVertex3f( sllmul(r1, sllcos(slladd(angle, sllmul(int2sll(3), da)))), sllmul(r1, sllsin(slladd(angle, sllmul(int2sll(3), da)))), sllneg(slldiv(width, int2sll(2))) );
      glVertex3f( sllmul(r0, sllcos(angle)), sllmul(r0, sllsin(angle)), sllneg(slldiv(width, int2sll(2))) );
   }
   glEnd();

   /* draw back sides of teeth */
   glBegin( GL_QUADS );
   da = slldiv(slldiv(dbl2sll(2.0*M_PI), int2sll(teeth)), int2sll(4));
   for (i=0;i<teeth;i++) {
      angle = slldiv(sllmul(int2sll(i), dbl2sll(2.0*M_PI)), int2sll(teeth));

      glVertex3f( sllmul(r1, sllcos(slladd(angle, sllmul(int2sll(3), da)))), sllmul(r1, sllsin(slladd(angle, sllmul(int2sll(3), da)))), sllneg(slldiv(width, int2sll(2))) );
      glVertex3f( sllmul(r2, sllcos(slladd(angle, sllmul(int2sll(2), da)))), sllmul(r2, sllsin(slladd(angle, sllmul(int2sll(2), da)))), sllneg(slldiv(width, int2sll(2))) );
      glVertex3f( sllmul(r2, sllcos(slladd(angle, da))), sllmul(r2, sllsin(slladd(angle, da))), sllneg(slldiv(width, int2sll(2))) );
      glVertex3f( sllmul(r1, sllcos(angle)), sllmul(r1, sllsin(angle)), sllneg(slldiv(width, int2sll(2))) );
   }
   glEnd();


   /* draw outward faces of teeth */
   glBegin( GL_QUAD_STRIP );
   for (i=0;i<teeth;i++) {
      angle = slldiv(sllmul(int2sll(i), dbl2sll(2.0*M_PI)), int2sll(teeth));

      glVertex3f( sllmul(r1, sllcos(angle)), sllmul(r1, sllsin(angle)), slldiv(width, int2sll(2)) );
      glVertex3f( sllmul(r1, sllcos(angle)), sllmul(r1, sllsin(angle)), sllneg(slldiv(width, int2sll(2))) );
      u = sllsub(sllmul(r2, sllcos(slladd(angle, da))), sllmul(r1, sllcos(angle)));
      v = sllsub(sllmul(r2, sllsin(slladd(angle, da))), sllmul(r1, sllsin(angle)));
      len = sllsqrt( slladd(sllmul(u, u), sllmul(v, v)) );
      u = slldiv(u, len);
      v = slldiv(v, len);
      glNormal3f( v, sllneg(u), int2sll(0) );
      glVertex3f( sllmul(r2, sllcos(slladd(angle, da))), sllmul(r2, sllsin(slladd(angle, da))),  slldiv(width, int2sll(2)) );
      glVertex3f( sllmul(r2, sllcos(slladd(angle, da))), sllmul(r2, sllsin(slladd(angle, da))), sllneg(slldiv(width, int2sll(2))) );
      glNormal3f( sllcos(angle), sllsin(angle), int2sll(0) );
      glVertex3f( sllmul(r2, sllcos(slladd(angle, sllmul(int2sll(2), da)))), sllmul(r2, sllsin(slladd(angle, sllmul(int2sll(2), da)))), slldiv(width, int2sll(2)) );
      glVertex3f( sllmul(r2, sllcos(slladd(angle, sllmul(int2sll(2), da)))), sllmul(r2, sllsin(slladd(angle, sllmul(int2sll(2), da)))), sllneg(slldiv(width, int2sll(2))) );
      u = sllsub(
		      sllmul(r1, sllcos(slladd(angle, sllmul(int2sll(3), da)))),
		      sllmul(r2, sllcos(slladd(angle, sllmul(int2sll(2), da))))
		 );
      v = sllsub(
		      sllmul(r1, sllsin(slladd(angle, sllmul(int2sll(3), da)))),
		      sllmul(r2, sllsin(slladd(angle, sllmul(int2sll(2), da))))
		 );
      glNormal3f( v, sllneg(u), int2sll(0) );
      glVertex3f( sllmul(r1, sllcos(slladd(angle, sllmul(int2sll(3), da)))), sllmul(r1, sllsin(slladd(angle, sllmul(int2sll(3), da)))), slldiv(width, int2sll(2)) );
      glVertex3f( sllmul(r1, sllcos(slladd(angle, sllmul(int2sll(3), da)))), sllmul(r1, sllsin(slladd(angle, sllmul(int2sll(3), da)))), sllneg(slldiv(width, int2sll(2))) );
      glNormal3f( sllcos(angle), sllsin(angle), int2sll(0) );
   }

   glVertex3f( sllmul(r1, sllcos(int2sll(0))), sllmul(r1, sllsin(int2sll(0))), slldiv(width, int2sll(2)) );
   glVertex3f( sllmul(r1, sllcos(int2sll(0))), sllmul(r1, sllsin(int2sll(0))), sllneg(slldiv(width, int2sll(2))) );

   glEnd();


   glShadeModel( GL_SMOOTH );

   /* draw inside radius cylinder */
   glBegin( GL_QUAD_STRIP );
   for (i=0;i<=teeth;i++) {
      angle = slldiv(sllmul(int2sll(i), dbl2sll(2.0*M_PI)), int2sll(teeth));
      glNormal3f( sllneg(sllcos(angle)), sllneg(sllsin(angle)), int2sll(0) );
      glVertex3f( sllmul(r0, sllcos(angle)), sllmul(r0, sllsin(angle)), sllneg(slldiv(width, int2sll(2))) );
      glVertex3f( sllmul(r0, sllcos(angle)), sllmul(r0, sllsin(angle)), slldiv(width, int2sll(2)) );
   }
   glEnd();
      
}


static GLfloat view_rotx=int2sll(20), view_roty=int2sll(30), view_rotz=int2sll(0);
static GLint gear1, gear2, gear3;
static GLfloat angle = int2sll(0);

static GLuint limit=0;
static GLuint count = 1;


void draw( void )
{
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   glPushMatrix();
   glRotatef( view_rotx, int2sll(1), int2sll(0), int2sll(0) );
   glRotatef( view_roty, int2sll(0), int2sll(1), int2sll(0) );
   glRotatef( view_rotz, int2sll(0), int2sll(0), int2sll(1) );

   glPushMatrix();
   glTranslatef( int2sll(-3), int2sll(-2), int2sll(0) );
   glRotatef( angle, int2sll(0), int2sll(0), int2sll(1) );
   glCallList(gear1);
   glPopMatrix();

   glPushMatrix();
   glTranslatef( dbl2sll(3.1), int2sll(-2), int2sll(0) );
   glRotatef( sllsub(sllmul(int2sll(-2), angle), int2sll(9)), int2sll(0), int2sll(0), int2sll(1) );
   glCallList(gear2);
   glPopMatrix();

   glPushMatrix();
   glTranslatef( dbl2sll(-3.1), dbl2sll(4.2), int2sll(0) );
   glRotatef( sllsub(sllmul(int2sll(-2), angle), int2sll(25)), int2sll(0), int2sll(0), int2sll(1) );
   glCallList(gear3);
   glPopMatrix();

   glPopMatrix();

   tkSwapBuffers();

   count++;
   if (count==limit) {
       exit(0);
   }
}



void idle( void )
{
   angle = slladd(angle, sll2int(2));
   draw();
}



/* change view angle, exit upon ESC */
GLenum key(int k, GLenum mask)
{
   switch (k) {
      case KEY_UP:
         view_rotx = slladd(view_rotx, int2sll(5));
	 return GL_TRUE;
      case KEY_DOWN:
         view_rotx = sllsub(view_rotx, int2sll(5));
	 return GL_TRUE;
      case KEY_LEFT:
         view_roty = slladd(view_roty, int2sll(5));
	 return GL_TRUE;
      case KEY_RIGHT:
         view_roty = sllsub(view_roty, int2sll(5));
	 return GL_TRUE;
      case 'z':
	 view_rotz = slladd(view_rotz, int2sll(5));
	 return GL_TRUE;
      case 'Z':
	 view_rotz = sllsub(view_rotz, int2sll(5));
	 return GL_TRUE;
      case KEY_ESCAPE:
          exit(0);
   }
   return GL_FALSE;
}



/* new window size or exposure */
void reshape( int width, int height )
{
   GLfloat  h = slldiv(int2sll(height), int2sll(width));

   glViewport(0, 0, (GLint)width, (GLint)height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum( int2sll(-1), int2sll(1), sllneg(h), h, int2sll(5), int2sll(60) );
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( int2sll(0), int2sll(0), int2sll(-40) );
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


void init( void )
{
   static GLfloat pos[4];
   static GLfloat red[4];
   static GLfloat green[4];
   static GLfloat blue[4];

   pos[0]=int2sll(5); pos[1]=int2sll(5); pos[2]=int2sll(10); pos[3]=int2sll(0);
   red[0]=dbl2sll(0.8); red[1]=dbl2sll(0.1); red[2]=int2sll(0); red[3]=int2sll(1);
   green[0]=int2sll(0); green[1]=dbl2sll(0.8); green[2]=dbl2sll(0.2); green[3]=int2sll(1);
   blue[0]=dbl2sll(0.2); blue[1]=dbl2sll(0.2); blue[2]=int2sll(1); blue[3]=int2sll(1);

   glLightfv( GL_LIGHT0, GL_POSITION, pos );
   glEnable( GL_CULL_FACE );
   glEnable( GL_LIGHTING );
   glEnable( GL_LIGHT0 );
   glEnable( GL_DEPTH_TEST );

   /* make the gears */
   gear1 = glGenLists(1);
   glNewList(gear1, GL_COMPILE);
   glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red );
   gear( int2sll(1), int2sll(4), int2sll(1), 20, dbl2sll(0.7) );
   glEndList();

   gear2 = glGenLists(1);
   glNewList(gear2, GL_COMPILE);
   glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green );
   gear( dbl2sll(0.5), int2sll(2), int2sll(2), 10, dbl2sll(0.7) );
   glEndList();

   gear3 = glGenLists(1);
   glNewList(gear3, GL_COMPILE);
   glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue );
   gear( dbl2sll(1.3), int2sll(2), dbl2sll(0.5), 10, dbl2sll(0.7) );
   glEndList();

   glEnable( GL_NORMALIZE );
}

int main(int argc, char **argv) 
{
   if (argc>1) {
      /* do 'n' frames then exit */
      limit = atoi( argv[1] ) + 1;
   }
   else {
      limit = 0;
   }

   return ui_loop(argc, argv, "gears");
}



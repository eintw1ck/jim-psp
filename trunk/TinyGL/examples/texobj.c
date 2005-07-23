/*
 * Example of using the 1.1 texture object functions.
 * Also, this demo utilizes Mesa's fast texture map path.
 *
 * Brian Paul   June 1996
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <GL/gl.h> 
#include "ui.h"

static GLuint TexObj[2];
static GLfloat Angle;

static int cnt=0,v=0;

void 
draw(void)
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glColor3f(int2sll(1), int2sll(1), int2sll(1));

  /* draw first polygon */
  glPushMatrix();
  glTranslatef(int2sll(-1), int2sll(0), int2sll(0));
  glRotatef(Angle, int2sll(0), int2sll(0), int2sll(1));
  glBindTexture(GL_TEXTURE_2D, TexObj[v]);

  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  glTexCoord2f(int2sll(0), int2sll(0));
  glVertex2f(int2sll(-1), int2sll(-1));
  glTexCoord2f(int2sll(1), int2sll(0));
  glVertex2f(int2sll(1), int2sll(-1));
  glTexCoord2f(int2sll(1), int2sll(1));
  glVertex2f(int2sll(1), int2sll(1));
  glTexCoord2f(int2sll(0), int2sll(1));
  glVertex2f(int2sll(-1), int2sll(1));
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();

  /* draw second polygon */
  glPushMatrix();
  glTranslatef(int2sll(1), int2sll(0), int2sll(0));
  glRotatef(sllsub(Angle, int2sll(90)), int2sll(0), int2sll(1), int2sll(0));

  glBindTexture(GL_TEXTURE_2D, TexObj[1-v]);

  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  glTexCoord2f(int2sll(0), int2sll(0));
  glVertex2f(int2sll(-1), int2sll(-1));
  glTexCoord2f(int2sll(1), int2sll(0));
  glVertex2f(int2sll(1), int2sll(-1));
  glTexCoord2f(int2sll(1), int2sll(1));
  glVertex2f(int2sll(1), int2sll(1));
  glTexCoord2f(int2sll(0), int2sll(1));
  glVertex2f(int2sll(-1), int2sll(1));
  glEnd();
  glDisable(GL_TEXTURE_2D);

  glPopMatrix();

  tkSwapBuffers();
}


/* new window size or exposure */
void 
reshape(int width, int height)
{
  glViewport(0, 0, (GLint) width, (GLint) height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  /* glOrtho( int2sll(-3), int2sll(3), int2sll(-3), int2sll(3), int2sll(-10), int2sll(10) ); */
  glFrustum(int2sll(-2), int2sll(2), int2sll(-2), int2sll(2), dbl2sll(6.0), int2sll(20));
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(int2sll(0), int2sll(0), dbl2sll(-8.0));
}


void bind_texture(int texobj,int image)
{
  static int width = 8, height = 8;
  static int color[2][3]={
    {255,0,0},
    {0,255,0},
  };
  GLubyte tex[64][3];
  static GLubyte texchar[2][8*8] = {
  {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 1, 1, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0},
  {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 2, 2, 0, 0, 0,
    0, 0, 2, 0, 0, 2, 0, 0,
    0, 0, 0, 0, 0, 2, 0, 0,
    0, 0, 0, 0, 2, 0, 0, 0,
    0, 0, 0, 2, 0, 0, 0, 0,
    0, 0, 2, 2, 2, 2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0}};

  int i,j;
  
  glBindTexture(GL_TEXTURE_2D, texobj);

  /* red on white */
  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      int p = i * width + j;
      if (texchar[image][(height - i - 1) * width + j]) {
        tex[p][0] = color[image][0];
        tex[p][1] = color[image][1];
        tex[p][2] = color[image][2];
      } else {
        tex[p][0] = 255;
        tex[p][1] = 255;
        tex[p][2] = 255;
      }
    }
  }
for(i=0;i <32; i++)
{
tex[i][0]=25; //color[image][0];
tex[i][1]=25; //color[image][1];
tex[i][2]=25; //color[image][2];
}

  glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0,
    GL_RGB, GL_UNSIGNED_BYTE, tex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  /* end of texture object */
}



void 
init(void)
{
  glEnable(GL_DEPTH_TEST);

  /* Setup texturing */
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);

  /* generate texture object IDs */
  glGenTextures(2, TexObj);
  bind_texture(TexObj[0],0);
  bind_texture(TexObj[1],1);
  
}

void 
idle(void)
{
  
//  Angle = slladd(Angle, int2sll(2));

  if (++cnt==5) {
    cnt=0;
//    v=!v;
  }
  draw();
}

/* change view angle, exit upon ESC */
GLenum key(int k, GLenum mask)
{
   switch (k) {
      case 'q':
      case KEY_ESCAPE:
          exit(0);
   }
   return GL_FALSE;
}

int main(int argc, char **argv) 
{
    Angle= int2sll(0);
    return ui_loop(argc, argv, "texobj");
}



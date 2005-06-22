/*      
# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |     ___|    ____| |    \    PSPDEV Open Source Project.
#-----------------------------------------------------------------------
# Copyright 2001-2004, ps2dev - http://www.ps2dev.org
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
#
# $Id$
# EE UGLY DEBUG ON SCREEN
*/

#include <stdio.h>
#include <psptypes.h>
#include <pspkernel.h>
#include <stdarg.h>
#include <pspdebug.h>

#define PSP_SCREEN_WIDTH 480
#define PSP_SCREEN_HEIGHT 272
#define PSP_LINE_SIZE 512
#define PSP_PIXEL_FORMAT 3

/* baseado nas libs do Duke... */

static int X = 0, Y = 0;
static int MX=60, MY=34;
static u32 bg_col = 0, fg_col = 0xFFFFFFFF;
static u32* g_vram_base = (u32 *) 0x04000000;

static void clear_screen(u32 color)
{
    int x;
    u32 *vram = g_vram_base;

    for(x = 0; x < (PSP_LINE_SIZE * PSP_SCREEN_HEIGHT); x++)
    {
		*vram++ = color; 
    }
}

void pspDebugScreenInit()
{
   X = Y = 0;
   /* Place vram in uncached memory */
   g_vram_base = (void *) (0x40000000 | sceGeEdramGetAddr());
   sceDisplaySetMode(0, PSP_SCREEN_WIDTH, PSP_SCREEN_HEIGHT);
   sceDisplaySetFrameBuf((void *) g_vram_base, PSP_LINE_SIZE, PSP_PIXEL_FORMAT, 1);
   clear_screen(bg_col);
}

void pspDebugScreenSetBackColor(u32 colour)
{
   bg_col = colour;
}

void pspDebugScreenSetTextColor(u32 colour)
{
   fg_col = colour;
}

extern u8 msx[];


void
pspDebugScreenPutChar( int x, int y, u32 color, u8 ch)
{
   int 	i,j, l;
   u8	*font;
   u32  pixel;
   u32 *vram_ptr;
   u32 *vram;

   vram = g_vram_base + x;
   vram += (y * PSP_LINE_SIZE);
   
   font = &msx[ (int)ch * 8];
   for (i=l=0; i < 8; i++, l+= 8, font++)
   {
      vram_ptr  = vram;
      for (j=0; j < 8; j++)
	{
          if ((*font & (128 >> j)))
              pixel = color;
          else
              pixel = bg_col;

          *vram_ptr++ = pixel; 
	}
      vram += PSP_LINE_SIZE;
   }
}

static void  clear_line( int Y)
{
   int i;
   for (i=0; i < MX; i++)
    pspDebugScreenPutChar( i*7 , Y * 8, bg_col, 219);


}

void pspDebugScreenPrintf(const char *format, ...)
{
   va_list	opt;
   char		buff[2048], c;
   int		i, bufsz, j;
   
   
   va_start(opt, format);
   bufsz = vsnprintf( buff, (size_t) sizeof(buff), format, opt);

   for (i = 0; i < bufsz; i++)
       {
       c = buff[i];
       switch (c)
          {
          case		'\n':
                             X = 0;
                             Y ++;
                             if (Y == MY)
                                 Y = 0;
                             clear_line(Y);
                             break;
          case      '\t':
                             for (j = 0; j < 5; j++) {
                             	pspDebugScreenPutChar( X*7 , Y * 8, fg_col, ' ');
                             	X++;
                             }
                             break;
          default:
             		     pspDebugScreenPutChar( X*7 , Y * 8, fg_col, c);
                             X++;
                             if (X == MX)
                                {
                                X = 0;
                                Y++;
                                if (Y == MY)
                                   Y = 0;
                                clear_line(Y);
                                }
          }
       }
    pspDebugScreenPutChar( X*7 , Y * 8, fg_col, 219);
}


void pspDebugScreenSetXY(int x, int y)
{
	if( x<MX && x>=0 ) X=x;
	if( y<MY && y>=0 ) Y=y;
}

int pspDebugScreenGetX()
{
	return X;
}

int pspDebugScreenGetY()
{
	return Y;
}

void pspDebugScreenClear()
{
	int y;
	for(y=0;y<MY;y++)
		clear_line(y);
	pspDebugScreenSetXY(0,0);
	clear_screen(bg_col);
}

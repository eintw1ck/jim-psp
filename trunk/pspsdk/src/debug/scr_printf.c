/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * scr_printf.c - Debug screen functions.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id$
 */
#include <stdio.h>
#include <psptypes.h>
#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspge.h>
#include <stdarg.h>
#include <pspdebug.h>

#define PSP_SCREEN_WIDTH 480
#define PSP_SCREEN_HEIGHT 272
#define PSP_LINE_SIZE 512
#define PSP_PIXEL_FORMAT 3

/* baseado nas libs do Duke... */

static int X = 0, Y = 0;
static int MX=68, MY=34;
static u32 bg_col = 0, fg_col = 0xFFFFFFFF;
static u32* g_vram_base = (u32 *) 0x04000000;
static int g_vram_offset = 0;

static int init = 0;

static void clear_screen(u32 color)
{
    int x;
    u32 *vram = g_vram_base + (g_vram_offset>>2);

    for(x = 0; x < (PSP_LINE_SIZE * PSP_SCREEN_HEIGHT); x++)
    {
		*vram++ = color; 
    }
}

void pspDebugScreenInit()
{
   X = Y = 0;
   /* Place vram in uncached memory */
   g_vram_base = (void *) (0x40000000 | (u32) sceGeEdramGetAddr());
   g_vram_offset = 0;
   sceDisplaySetMode(0, PSP_SCREEN_WIDTH, PSP_SCREEN_HEIGHT);
   sceDisplaySetFrameBuf((void *) g_vram_base, PSP_LINE_SIZE, PSP_PIXEL_FORMAT, 1);
   clear_screen(bg_col);
   init = 1;
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

   if(!init)
   {
	   return;
   }

   vram = g_vram_base + (g_vram_offset>>2) + x;
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

/* Print non-nul terminated strings */
int pspDebugScreenPrintData(const char *buff, int size)
{
	int i;
	int j;
	char c;

	for (i = 0; i < size; i++)
	{
		c = buff[i];
		switch (c)
		{
			case '\n':
						X = 0;
						Y ++;
						if (Y == MY)
							Y = 0;
						clear_line(Y);
						break;
			case '\t':
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

	return i;
}

void pspDebugScreenPrintf(const char *format, ...)
{
   va_list	opt;
   char     buff[2048];
   int		bufsz;
   
   if(!init)
   {
	   return;
   }
   
   va_start(opt, format);
   bufsz = vsnprintf( buff, (size_t) sizeof(buff), format, opt);
   (void) pspDebugScreenPrintData(buff, bufsz);
}


void pspDebugScreenSetXY(int x, int y)
{
	if( x<MX && x>=0 ) X=x;
	if( y<MY && y>=0 ) Y=y;
}

void pspDebugScreenSetOffset(int offset)
{
	g_vram_offset = offset;
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

	if(!init)
	{
		return;
	}

	for(y=0;y<MY;y++)
		clear_line(y);
	pspDebugScreenSetXY(0,0);
	clear_screen(bg_col);
}

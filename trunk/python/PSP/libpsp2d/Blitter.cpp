
/**
 * @file Blitter.cpp
 * @brief Implementation of class Blitter
 */

/**********************************************************************

  Created: 08 Nov 2005

    Copyright (C) 2005 Frank Buss, Jérôme Laheurte

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The names of the authors may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHORS ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

**********************************************************************/
// $Id$

#include <pspkernel.h>
#include <pspgu.h>

#include "Blitter.h"

using namespace PSP2D;

typedef struct
{
      unsigned short u, v;
      short x, y, z;
} Vertex;

ScreenBlitter::ScreenBlitter(Screen *scr, int sx, int sy, int w, int h, int dx, int dy, bool blend)
    : _scr(scr), _sx(sx), _sy(sy), _w(w), _h(h), _dx(dx), _dy(dy), _blend(blend)
{
}

void ScreenBlitter::visitScreen(Screen *scr)
{
    // Screen to Screen: not implemented!
}

void ScreenBlitter::visitImage(Image *img)
{
    // Image to screen

    sceKernelDcacheWritebackInvalidateAll();
    sceGuStart(GU_DIRECT, Screen::getList());

    if (_blend)
    {
       sceGuEnable(GU_TEXTURE_2D);

       sceGuTexImage(0, img->getTextureWidth(), img->getTextureHeight(), img->getTextureWidth(), (void*) img->getData());
       float u = 1.0f / ((float)img->getTextureWidth());
       float v = 1.0f / ((float)img->getTextureHeight());
       sceGuTexScale(u, v);

       int j = 0;
       while (j < _w) {
          Vertex* vertices = (Vertex*) sceGuGetMemory(2 * sizeof(Vertex));
          int sliceWidth = 64;
          if (j + sliceWidth > _w) sliceWidth = _w - j;
          vertices[0].u = _sx + j;
          vertices[0].v = _sy;
          vertices[0].x = _dx + j;
          vertices[0].y = _dy;
          vertices[0].z = 0;
          vertices[1].u = _sx + j + sliceWidth;
          vertices[1].v = _sy + _h;
          vertices[1].x = _dx + j + sliceWidth;
          vertices[1].y = _dy + _h;
          vertices[1].z = 0;
          sceGuDrawArray(GU_SPRITES, GU_TEXTURE_16BIT | GU_VERTEX_16BIT | GU_TRANSFORM_2D, 2, 0, vertices);
          j += sliceWidth;
       }

       sceGuDisable(GU_TEXTURE_2D);
    }
    else
    {
       u32* vram = Screen::getVramDrawBuffer();

       sceGuCopyImage(GU_PSM_8888, _sx, _sy, _w, _h, img->getTextureWidth(),
                      img->getData(), _dx, _dy, PSP_LINE_SIZE, vram);
    }

    sceGuFinish();
    sceGuSync(0,0);
}

ImageBlitter::ImageBlitter(Image *img, int sx, int sy, int w, int h, int dx, int dy, bool blend)
    : _img(img), _sx(sx), _sy(sy), _w(w), _h(h), _dx(dx), _dy(dy), _blend(blend)
{
}

void ImageBlitter::visitScreen(Screen *scr)
{
    // Screen to image: not implemented yet.
}

void ImageBlitter::visitImage(Image *img)
{
    // Image to image

    int j;

    u32 *srcdec;
    u32 *dstdec;

    srcdec = img->getData() + _sy * img->getTextureWidth() + _sx;
    dstdec = _img->getData() + _dy * _img->getTextureWidth() + _dx;

    for (j = 0; j < _h; ++j)
    {
       if (_blend)
       {
          int i;

          for (i = 0; i < _w; ++i)
          {
             u32 a1, a2, r1, r2, g1, g2, b1, b2;

             u32 srccol = *(srcdec + j * img->getTextureWidth() + i);
             u32 dstcol = *(dstdec + j * _img->getTextureWidth() + i);

             a1 = srccol >> 24;
             b1 = ((srccol >> 16) & 0xFF) * a1 / 255;
             g1 = ((srccol >> 8) & 0xFF) * a1 / 255;
             r1 = (srccol & 0xFF) * a1 / 255;

             a2 = dstcol >> 24;
             b2 = ((dstcol >> 16) & 0xFF) * a2 / 255;
             g2 = ((dstcol >> 8) & 0xFF) * a2 / 255;
             r2 = (dstcol & 0xFF) * a2 / 255;

             *(dstdec + j * _img->getTextureWidth() + i) = ((a1 + (255 - a1) * a2 / 255) << 24) |
                ((b1 + (255 - a1) * b2 / 255) << 16) |
                ((g1 + (255 - a1) * g2 / 255) << 8) |
                (r1 + (255 - a1) * r2 / 255);
          }
       }
       else
       {
          memcpy(dstdec + j * _img->getTextureWidth(),
                 srcdec + j * img->getTextureWidth(),
                 _w * sizeof(u32));
       }
    }
}

static const char* _rcsid_Blitter __attribute__((unused)) = "$Id$";

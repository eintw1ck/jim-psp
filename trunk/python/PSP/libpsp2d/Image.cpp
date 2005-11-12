
/**
 * @file Image.cpp
 * @brief Implementation of class Image
 */

/**********************************************************************

  Created: 08 Nov 2005

    Copyright (C) 2005 Frank Buss, J�r�me Laheurte

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

#include <malloc.h>

#include "Image.h"
#include "Blitter.h"

using namespace PSP2D;
using namespace std;

extern u8 msx[];

static int getNextPower2(int width)
{
    int b = width;
    int n;
    for (n = 0; b != 0; n++) b >>= 1;
    b = 1 << n;
    if (b == 2 * width) b >>= 1;
    return b;
}

static void user_warning_fn(png_structp png_ptr, png_const_charp warning_msg)
{
}

Image::Image(const string& filename)
{
    png_structp png_ptr;
    png_infop info_ptr;
    unsigned int sig_read = 0;
    int bit_depth, color_type, interlace_type, x, y;
    u32* line;
    FILE *fp;

    if ((fp = fopen(filename.c_str(), "rb")) == NULL)
       throw ImageIOException("Could not open file");

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL)
    {
       fclose(fp);

       throw ImagePNGException("Could not create PNG struct");
    }

    png_set_error_fn(png_ptr, (png_voidp) NULL, (png_error_ptr) NULL, user_warning_fn);

    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL)
    {
       fclose(fp);
       png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);

       throw ImagePNGException("Could not create PNG info struct");
    }

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, sig_read);
    png_read_info(png_ptr, info_ptr);
    png_get_IHDR(png_ptr, info_ptr, &_width, &_height, &bit_depth, &color_type, &interlace_type, int_p_NULL, int_p_NULL);

    _textureWidth = getNextPower2(_width);
    _textureHeight = getNextPower2(_height);

    png_set_strip_16(png_ptr);
    png_set_packing(png_ptr);

    if (color_type == PNG_COLOR_TYPE_PALETTE)
       png_set_palette_to_rgb(png_ptr);

    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
       png_set_gray_1_2_4_to_8(png_ptr);

    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
       png_set_tRNS_to_alpha(png_ptr);

    png_set_filler(png_ptr, 0xff, PNG_FILLER_AFTER);
    _data = (u32*) memalign(16, _textureWidth * _textureHeight * sizeof(u32));

    if (!_data)
    {
       fclose(fp);
       png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);

       throw ImageException("Memory error");
    }

    line = (u32*)malloc(_width * 4);
    if (!line)
    {
       free(_data);
       fclose(fp);
       png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);

       throw ImageException("Memory error");
    }

    for (y = 0; y < _height; y++)
    {
       png_read_row(png_ptr, (u8*) line, png_bytep_NULL);
       for (x = 0; x < _width; x++)
       {
          u32 color = line[x];
          _data[x + y * _textureWidth] =  color;
       }
    }

    free(line);
    png_read_end(png_ptr, info_ptr);
    png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
    fclose(fp);
}

Image::Image(png_uint_32 width, png_uint_32 height)
    : _width(width),
      _height(height),
      _data(NULL)
{
    _textureWidth = getNextPower2(_width);
    _textureHeight = getNextPower2(_height);

    _data = (u32*) memalign(16, _textureWidth * _textureHeight * sizeof(u32));

    if (!_data)
       throw ImageException("Memory error");
}

Image::Image(Image *img)
    : _width(img->_width),
      _height(img->_height),
      _textureWidth(img->_textureWidth),
      _textureHeight(img->_textureHeight)
{
    _data = (u32*)memalign(16, _textureWidth * _textureHeight * sizeof(u32));

    if (!_data)
       throw ImageException("Memory error");

    int j;
    for (j = 0; j < _height; ++j)
       memcpy(_data + j * _textureWidth,
              img->_data + j * img->_textureWidth,
              _width * sizeof(u32));
}

Image::~Image()
{
    free(_data);
}

png_uint_32 Image::getWidth()
{
    return _width;
}

png_uint_32 Image::getHeight()
{
    return _height;
}

png_uint_32 Image::getTextureWidth()
{
    return _textureWidth;
}

png_uint_32 Image::getTextureHeight()
{
    return _textureHeight;
}

u32* Image::getData()
{
    return _data;
}

void Image::accept(DrawableVisitor *v)
{
    v->visitImage(this);
}

void Image::blit(Drawable *drw, int sx, int sy, int w, int h, int dx, int dy, bool blend)
{
    ImageBlitter blt(this, sx, sy, w, h, dx, dy, blend);

    drw->accept(&blt);
}

void Image::clear(u32 color)
{
    int i, j;

    for (j = 0; j < _height; ++j)
    {
       for (i = 0; i < _width; ++i)
       {
          *(_data + j * _textureWidth + i) = color;
       }
    }
}

void Image::drawLine(int x0, int y0, int x1, int y1, u32 color)
{
    int dy = y1 - y0;
    int dx = x1 - x0;
    int stepx, stepy;

    if (dy < 0) { dy = -dy;  stepy = -_textureWidth; } else { stepy = _textureWidth; }
    if (dx < 0) { dx = -dx;  stepx = -1; } else { stepx = 1; }
    dy <<= 1;
    dx <<= 1;

    y0 *= _textureWidth;
    y1 *= _textureWidth;
    _data[x0+y0] = color;
    if (dx > dy) {
       int fraction = dy - (dx >> 1);
       while (x0 != x1) {
          if (fraction >= 0) {
             y0 += stepy;
             fraction -= dx;
          }
          x0 += stepx;
          fraction += dy;
          _data[x0+y0] = color;
       }
    } else {
       int fraction = dx - (dy >> 1);
       while (y0 != y1) {
          if (fraction >= 0) {
             x0 += stepx;
             fraction -= dy;
          }
          y0 += stepy;
          fraction += dx;
          _data[x0+y0] = color;
       }
    }
}

void Image::fillRect(u32 color, int x, int y, int w, int h)
{
    int nx, ny;
    u32 *dst = _data + x + y * _textureWidth;

    for (ny = 0; ny < h; ny++, dst += _textureWidth) {
       for (nx = 0; nx < w; nx++) *(dst + nx) = color;
    }
}

void Image::printText(int x, int y, const string& text, u32 color)
{
    int c, i, j, l;
    u8 *font;
    u32 *data_ptr;
    u32 *data;

    for (c = 0; c < text.size(); c++) {
       if (x < 0 || x + 8 > _width || y < 0 || y + 8 > _height) break;
       char ch = text[c];
       data = _data + x + y * _textureWidth;

       font = &msx[ (int)ch * 8];
       for (i = l = 0; i < 8; i++, l += 8, font++) {
          data_ptr  = data;
          for (j = 0; j < 8; j++) {
             if ((*font & (128 >> j))) *data_ptr = color;
             data_ptr++;
          }
          data += _textureWidth;
       }
       x += 8;
    }
}

void Image::saveToFile(const string& filename)
{
    png_structp png_ptr;
    png_infop info_ptr;
    FILE* fp;
    int i, x, y;
    u8* line;
	
    if ((fp = fopen(filename.c_str(), "wb")) == NULL) return;
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) return;
    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
       png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
       return;
    }
    png_init_io(png_ptr, fp);
    png_set_IHDR(png_ptr, info_ptr, _width, _height, 8,
                 PNG_COLOR_TYPE_RGBA,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png_ptr, info_ptr);
    line = (u8*) malloc(_width * 4);
    for (y = 0; y < _height; y++) {
       for (i = 0, x = 0; x < _width; x++) {
          u32 color = _data[x + y * _textureWidth];
          u8 r = color & 0xff;
          u8 g = (color >> 8) & 0xff;
          u8 b = (color >> 16) & 0xff;
          u8 a = (color >> 24) & 0xff;
          line[i++] = r;
          line[i++] = g;
          line[i++] = b;
          line[i++] = a;
       }
       png_write_row(png_ptr, line);
    }
    free(line);
    png_write_end(png_ptr, info_ptr);
    png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
    fclose(fp);
}

static const char* _rcsid_Image __attribute__((unused)) = "$Id$";

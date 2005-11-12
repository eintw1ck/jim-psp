
/**
 * @file Image.h
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

#ifndef _IMAGE_H
#define _IMAGE_H

#include <string>

#include <png.h>

#include <libpsp2d/Drawable.h>
#include <libpsp2d/Exception.h>

namespace PSP2D
{
    /**
     * Generic exception that can be throwed by the Image class.
     */

    class ImageException : public Exception
    {
      public:
       ImageException(const std::string& msg) : Exception(msg) {};
    };

    /**
     * Some I/O error
     */

    class ImageIOException : public ImageException
    {
      public:
       ImageIOException(const std::string& msg) : ImageException(msg) {};
    };

    /**
     * Error from libpng
     */

    class ImagePNGException : public ImageException
    {
      public:
       ImagePNGException(const std::string& msg) : ImageException(msg) {};
    };

    /**
     * Image class. This represents an in-memory image.
     */

    class Image : public Drawable
    {
      public:
       /**
        * Constructor. Loads the image from a PNG file.
        */

       Image(const std::string& filename);

       /**
        * Constructor. Creates an empty image.
        */

       Image(png_uint_32 width, png_uint_32 height);

       /**
        * Constructor. Copies another image.
        */

       Image(Image* img);

       virtual ~Image();

       /**
        * Returns the width of the image in pixels.
        */

       png_uint_32 getWidth();

       /**
        * Returns the height of the image in pixels.
        */

       png_uint_32 getHeight();

       /**
        * Returns the  width used to store this  image (smallest power
        * of 2 that is >= to the actual width).
        */

       png_uint_32 getTextureWidth();

       /**
        * Returns the  height used to store this  image (smallest power
        * of 2 that is >= to the actual height).
        */

       png_uint_32 getTextureHeight();

       /**
        * Returns  a  pointer  to  the  actual bytes.  Should  not  be
        * public. Will be fixed.
        */

       u32* getData();

       /**
        * Visitor pattern. See DrawableVisitor.
        */

       void accept(DrawableVisitor*);

       // These will inherit documentation from Drawable

       void blit(Drawable* drw, int sx, int sy, int w, int h, int dx, int dy, bool blend = false);
       void clear(u32 color);
       void putPixel(u32 color, int x, int y);
       u32 getPixel(int x, int y);
       void drawLine(int x0, int y0, int x1, int y1, u32 color);
       void fillRect(u32 color, int x, int y, int w, int h);
       void printText(int x, int y, const std::string& text, u32 color);

       void saveToFile(const std::string& filename);

      protected:
       png_uint_32 _width, _height, _textureWidth, _textureHeight;
       u32 *_data;
    };
};

// Inline methods
#include <libpsp2d/Image.il>

#endif /* _IMAGE_H */

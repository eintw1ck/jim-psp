
/**
 * @file image.c
 */

/**********************************************************************

  Created: 30 Oct 2005

**********************************************************************/
// $Id$

#include "image.h"
#include "color.h"

#include <png.h>
#include <malloc.h>

static u16 compute_tdim(u16 dim)
{
    if (dim == 0)
    {
       return 1;
    }
    else
    {
       u16 pwr = 1;

       while (pwr < dim)
          pwr *= 2;

       return pwr;
    }
}

static void image_dealloc(PyImage *self)
{
    if (self->data)
       free(self->data);

    self->ob_type->tp_free((PyObject*)self);
}

static PyObject* image_new(PyTypeObject *type,
                           PyObject *args,
                           PyObject *kwargs)
{
    PyImage *self;

    self = (PyImage*)type->tp_alloc(type, 0);

    if (self)
    {
       self->width = 0;
       self->height = 0;
       self->twidth = 0;
       self->theight = 0;
       self->data = NULL;
    }

    return (PyObject*)self;
}

static int image_init(PyImage *self,
                      PyObject *args,
                      PyObject *kwargs)
{
    PyObject *a, *b = NULL;

    if (!PyArg_ParseTuple(args, "O|O", &a, &b))
       return -1;

    // If only 1 argument was given, assume it is a filename.
    if (!b)
    {
       // Code mostly taken from the libpng PSP example.

       char *filename;
       FILE *fp;
       png_structp pptr;
       png_infop iptr;
       unsigned int sread = 0;
       png_uint_32 w, h, j;
       int depth, ctype, itype;

#ifdef CHECKTYPE
       if (!PyString_Check(a))
       {
          PyErr_SetString(PyExc_TypeError, "Argument must be a string");
          return -1;
       }
#endif

       filename = PyString_AsString(a);
       fp = fopen(filename, "rb");
       if (!fp)
       {
          PyErr_SetString(PyExc_IOError, "Could not open file");
          return -1;
       }

       pptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
                                     NULL, NULL, NULL);
       if (!pptr)
       {
          fclose(fp);

          PyErr_SetString(PyExc_RuntimeError, "Error creating PNG struct");
          return -1;
       }

       iptr = png_create_info_struct(pptr);
       if (!iptr)
       {
          fclose(fp);
          png_destroy_read_struct(&pptr, png_infopp_NULL, png_infopp_NULL);

          PyErr_SetString(PyExc_RuntimeError, "Error creating PNG info struct");
          return -1;
       }

       png_init_io(pptr, fp);
       png_set_sig_bytes(pptr, sread);
       png_read_info(pptr, iptr);
       png_get_IHDR(pptr, iptr, &w, &h, &depth, &ctype, &itype,
                    int_p_NULL, int_p_NULL);

       if ((w > 512) || (h > 512))
       {
          fclose(fp);
          png_destroy_read_struct(&pptr, png_infopp_NULL, png_infopp_NULL);

          PyErr_SetString(PyExc_ValueError, "Width or height is > 512");
          return -1;
       }

       png_set_strip_16(pptr);
       png_set_packing(pptr);

       if (ctype == PNG_COLOR_TYPE_PALETTE)
          png_set_palette_to_rgb(pptr);

       if (ctype == PNG_COLOR_TYPE_GRAY && depth < 8)
          png_set_gray_1_2_4_to_8(pptr);

       if (png_get_valid(pptr, iptr, PNG_INFO_tRNS))
          png_set_tRNS_to_alpha(pptr);

       png_set_filler(pptr, 0xff, PNG_FILLER_AFTER);

       self->width = w;
       self->height = h;
       self->twidth = compute_tdim(w);
       self->theight = compute_tdim(h);

       self->data = (u32*)memalign(16, sizeof(u32) * self->twidth * self->theight);
       if (!self->data)
       {
          fclose(fp);
          png_destroy_read_struct(&pptr, png_infopp_NULL, png_infopp_NULL);

          PyErr_SetString(PyExc_MemoryError, "Memory error");
          return -1;
       }

       for (j = 0; j < h; ++j)
       {
          png_read_row(pptr, (u8*)(self->data + j * self->twidth), png_bytep_NULL);
       }

       png_read_end(pptr, iptr);
       png_destroy_read_struct(&pptr, &iptr, png_infopp_NULL);
       fclose(fp);
    }
    else
    {
       // Create empty image
       int w, h;

#ifdef CHECKTYPE
       if (!PyInt_Check(a) || !PyInt_Check(b))
       {
          PyErr_SetString(PyExc_TypeError, "Arguments must be integers");
          return -1;
       }
#endif

       w = PyInt_AsLong(a);
       h = PyInt_AsLong(b);

#ifdef CHECKTYPE
       if ((w < 0) || (h < 0) || (w > 512) || (h > 512))
       {
          PyErr_SetString(PyExc_TypeError, "Width or height out of range");
          return -1;
       }
#endif

       self->width = w;
       self->height = h;
       self->twidth = compute_tdim(w);
       self->theight = compute_tdim(h);

       self->data = (u32*)memalign(16, sizeof(u32) * self->twidth * self->theight);
       if (!self->data)
       {
          PyErr_SetString(PyExc_MemoryError, "Memory error");
          return -1;
       }
    }

    return 0;
}

static PyObject* image_getwidth(PyImage *self, void *closure)
{
    return Py_BuildValue("i", self->width);
}

static PyObject* image_getheight(PyImage *self, void *closure)
{
    return Py_BuildValue("i", self->height);
}

static PyGetSetDef image_getset[] = {
   { "width", (getter)image_getwidth, NULL, "Width of the image", NULL },
   { "height", (getter)image_getheight, NULL, "Height of the image", NULL },

   { NULL }
};

static PyObject* image_clear(PyImage *self,
                             PyObject *args,
                             PyObject *kwargs)
{
    PyColor *color;
    u32 k;

    if (!PyArg_ParseTuple(args, "O:clear", &color))
       return NULL;

#ifdef CHECKTYPE
    if (((PyObject*)color)->ob_type != PPyColorType)
    {
       PyErr_SetString(PyExc_TypeError, "Argument must be a Color.");
       return NULL;
    }
#endif

    if (self->data)
    {
       for (k = 0; k < self->width * self->height; ++k)
          self->data[k] = color->color;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* image_blit(PyImage *self,
                            PyObject *args,
                            PyObject *kwargs)
{
    PyImage *src;
    int sx, sy, w, h, dx, dy;
    int blend = 0;
    int j;

    u32 *srcdec;
    u32 *dstdec;

    if (!PyArg_ParseTuple(args, "iiiiOii|i:blit", &sx, &sy,
                          &w, &h, &src, &dx, &dy, &blend))
       return NULL;

#ifdef CHECKTYPE
    if (((PyObject*)src)->ob_type != PPyImageType)
    {
       PyErr_SetString(PyExc_TypeError, "Fifth argument must be an Image");
       return NULL;
    }
#endif

    srcdec = src->data + sy * src->twidth + sx;
    dstdec = self->data + dy * self->twidth + dx;
    for (j = 0; j < h; ++j)
    {
       if (blend)
       {
          int i;

          for (i = 0; i < w; ++i)
          {
             u32 a1, a2, r1, r2, g1, g2, b1, b2;

             u32 srccol = *(srcdec + j * src->twidth + i);
             u32 dstcol = *(dstdec + j * self->twidth + i);

             a1 = srccol >> 24;
             b1 = (srccol >> 16) & 0xFF;
             g1 = (srccol >> 8) & 0xFF;
             r1 = srccol & 0xFF;

             a2 = dstcol >> 24;
             b2 = (dstcol >> 16) & 0xFF;
             g2 = (dstcol >> 8) & 0xFF;
             r2 = dstcol & 0xFF;

             *(dstdec + j * self->twidth + i) = ((a1 + (255 - a1) * a2 / 255) << 24) |
                ((b1 + (255 - a1) * b2 / 255) << 16) |
                ((g1 + (255 - a1) * g2 / 255) << 8) |
                (r1 + (255 - a1) * r2 / 255);
          }
       }
       else
       {
          memcpy(dstdec + j * self->twidth,
                 srcdec + j * src->twidth,
                 w * sizeof(u32));
       }
    }

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* image_fillRect(PyImage *self,
                                PyObject *args,
                                PyObject *kwargs)
{
    int x, y, w, h;
    PyColor *color;
    int i, j;
    u32 *dst;

    if (!PyArg_ParseTuple(args, "iiiiO:fillRect", &x, &y, &w, &h,
                          &color))
       return NULL;

#ifdef CHECKTYPE
    if (((PyObject*)color)->ob_type != PPyColorType)
    {
       PyErr_SetString(PyExc_TypeError, "Fifth argument must be a Color.");
       return NULL;
    }
#endif

    dst = self->data + y * self->twidth + x;
    for (j = 0; j < h; ++j)
    {
       for (i = 0; i < w; ++i)
       {
          *(dst + j * self->twidth + i) = color->color;
       }
    }

    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef image_methods[] = {
   { "clear", (PyCFunction)image_clear, METH_VARARGS,
     "clear(color)\n"
     "Fills the image with the given color." },

   { "blit", (PyCFunction)image_blit, METH_VARARGS,
     "blit(sx, sy, w, h, srcimg, dx, dy, blend = False)\n"
     "Copies the (sx, sy, w, h) rectangle from srcimg to this image, at\n"
     "(dx, dy) position. If blend is True, perform alpha blending." },

   { "fillRect", (PyCFunction)image_fillRect, METH_VARARGS,
     "fillRect(x, y, w, h, color)\n"
     "Fills the (x, y, w, h) rectangle with the specified color." },

   { NULL }
};

static PyTypeObject PyImageType = {
   PyObject_HEAD_INIT(NULL)
   0,
   "psp2d.Image",
   sizeof(PyImage),
   0,
   (destructor)image_dealloc,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
   "Image objects",
   0,
   0,
   0,
   0,
   0,
   0,
   image_methods,
   0,
   image_getset,
   0,
   0,
   0,
   0,
   0,
   (initproc)image_init,
   0,
   image_new,
};

PyTypeObject* PPyImageType = &PyImageType;

#ifdef _GNUC
static const char* _rcsid_image __attribute__((unused)) = "$Id$";
#endif

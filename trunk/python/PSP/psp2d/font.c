
/**
 * @file font.c
 */

/**********************************************************************

  Created: 05 Nov 2005

**********************************************************************/
// $Id$

#include <png.h>
#include <malloc.h>

#include "font.h"

static void font_dealloc(PyFont *self)
{
    if (self->data)
       free(self->data);

    self->ob_type->tp_free((PyObject*)self);
}

static PyObject* font_new(PyTypeObject *type,
                          PyObject *args,
                          PyObject *kwargs)
{
    PyFont *self;

    self = (PyFont*)type->tp_alloc(type, 0);

    if (self)
    {
       memset(self->positions, 0, sizeof(u16) * 512);
       self->maxpos = 0;
       self->width = 0;
       self->height = 0;
       self->data = NULL;
    }

    return (PyObject*)self;
}

static int font_init(PyFont *self,
                      PyObject *args,
                      PyObject *kwargs)
{
    char *filename;
    FILE *fp;
    png_structp pptr;
    png_infop iptr;
    unsigned int sread = 0;
    png_uint_32 w, h, i, j, x;
    int depth, ctype, itype;

    if (!PyArg_ParseTuple(args, "s", &filename))
       return -1;

    // Code mostly taken from the libpng PSP example.

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

    self->data = (u32*)memalign(16, sizeof(u32) * self->width * self->height);
    if (!self->data)
    {
       fclose(fp);
       png_destroy_read_struct(&pptr, png_infopp_NULL, png_infopp_NULL);

       PyErr_SetString(PyExc_MemoryError, "Memory error");
       return -1;
    }

    for (j = 0; j < h; ++j)
    {
       png_read_row(pptr, (u8*)(self->data + j * self->width), png_bytep_NULL);
    }

    png_read_end(pptr, iptr);
    png_destroy_read_struct(&pptr, &iptr, png_infopp_NULL);
    fclose(fp);

    i = 0;
    x = 0;
    while (x < self->width)
    {
       if ((self->data[x] & 0x00FFFFFFU) == 0x00FF00FFU)
       {
          self->positions[i++] = x;
          while ((x < self->width) && ((self->data[x] & 0x00FFFFFFU) == 0x00FF00FFU))
             ++x;
          self->positions[i++] = x;
       }
       ++x;
    }

    self->maxpos = x - 1;

    return 0;
}

static PyObject* font_textWidth(PyFont *self,
                                PyObject *args,
                                PyObject *kwargs)
{
    char *text, *c;
    int offset, w;

    if (!PyArg_ParseTuple(args, "s:textWidth", &text))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    offset = 0;
    w = 0;

    for (c = text; *c != 0; ++c)
    {
       offset = (int)(*c - 33) * 2 + 1;

       if ((*c == ' ') || (offset < 0) || (offset > self->maxpos))
       {
          w += self->positions[2] - self->positions[1];
       }
       else
       {
          w += self->positions[offset + 1] - self->positions[offset];
       }
    }

    return Py_BuildValue("i", w);
}

static PyObject* font_textHeight(PyFont *self,
                                 PyObject *args,
                                 PyObject *kwargs)
{
    char *text;

    if (!PyArg_ParseTuple(args, "s:textHeight", &text))
       return NULL;

    return Py_BuildValue("i", (int)self->height);
}

static PyMethodDef font_methods[] = {
   { "textWidth", (PyCFunction)font_textWidth, METH_VARARGS, "" },
   { "textHeight", (PyCFunction)font_textHeight, METH_VARARGS, "" },

   { NULL }
};

static PyTypeObject PyFontType = {
   PyObject_HEAD_INIT(NULL)
   0,
   "psp2d.Font",
   sizeof(PyFont),
   0,
   (destructor)font_dealloc,
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
   "Font objects",
   0,
   0,
   0,
   0,
   0,
   0,
   font_methods,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   (initproc)font_init,
   0,
   font_new,
};

PyTypeObject* PPyFontType = &PyFontType;

#ifdef _GNUC
static const char* _rcsid_font __attribute__((unused)) = "$Id$";
#endif

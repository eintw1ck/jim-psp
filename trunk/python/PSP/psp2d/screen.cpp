
/**
 * @file screen.c
 */

/**********************************************************************

  Created: 30 Oct 2005

**********************************************************************/
// $Id$

#include "screen.h"
#include "image.h"
#include "color.h"
#include "font.h"

using namespace PSP2D;

#define MIN(x, y) ((x) < (y) ? (x) : (y))

static void screen_dealloc(PyScreen *self)
{
    self->ob_type->tp_free((PyObject*)self);
}

static PyObject* screen_new(PyTypeObject *type,
                            PyObject *args,
                            PyObject *kwargs)
{
    PyScreen *self;

    self = (PyScreen*)type->tp_alloc(type, 0);

    if (self)
       self->scr = NULL;

    return (PyObject*)self;
}

static int screen_init(PyScreen *self,
                      PyObject *args,
                      PyObject *kwargs)
{
    if (!PyArg_ParseTuple(args, ""))
       return -1;

    self->scr = Screen::getInstance();

    return 0;
}

static PyObject* screen_blit(PyScreen *self,
                             PyObject *args,
                             PyObject *kwargs)
{
    int sx = 0, sy = 0, w = -1, h = -1, dx = 0, dy = 0, blend = 0;
    PyImage *img;

    static char* kwids[] = { "src", "sx", "sy", "w", "h", "dx", "dy", "blend", NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     "O|iiiiiii", kwids,
                                     &img,
                                     &sx, &sy, &w, &h,
                                     &dx, &dy,
                                     &blend))
       return NULL;

#ifdef CHECKTYPE
    if (((PyObject*)img)->ob_type != PPyImageType)
    {
       PyErr_SetString(PyExc_TypeError, "Fifth argument must be an Image");
       return NULL;
    }
#endif

    if (PyErr_CheckSignals())
       return NULL;

    if (w == -1)
       w = (int)img->img->getWidth();

    if (h == -1)
       h = (int)img->img->getHeight();

    // Sanity checks

    if ((dx >= SCREEN_WIDTH) || (dy >= SCREEN_HEIGHT))
    {
       Py_INCREF(Py_None);
       return Py_None;
    }

    w = MIN(w, SCREEN_WIDTH - dx);
    w = MIN(w, (int)img->img->getWidth() - sx);

    h = MIN(h, SCREEN_HEIGHT - dy);
    h = MIN(h, (int)img->img->getHeight() - sy);

    if ((w <= 0) || (h <= 0))
    {
       Py_INCREF(Py_None);
       return Py_None;
    }

    // OK

    self->scr->blit(img->img, sx, sy, w, h, dx, dy, blend);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* screen_clear(PyScreen *self,
                              PyObject *args,
                              PyObject *kwargs)
{
    PyColor *color;

    if (!PyArg_ParseTuple(args, "O:clear", &color))
       return NULL;

#ifdef CHECKTYPE
    if (((PyObject*)color)->ob_type != PPyColorType)
    {
       PyErr_SetString(PyExc_TypeError, "Argument must be a Color.");
       return NULL;
    }
#endif

    if (PyErr_CheckSignals())
       return NULL;

    self->scr->clear(color->color);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* screen_fillRect(PyScreen *self,
                                 PyObject *args,
                                 PyObject *kwargs)
{
    PyColor *color;
    int x, y, w, h;

    if (!PyArg_ParseTuple(args, "iiiiO:fillRect", &x, &y,
                          &w, &h, &color))
       return NULL;

#ifdef CHECKTYPE
    if (((PyObject*)color)->ob_type != PPyColorType)
    {
       PyErr_SetString(PyExc_TypeError, "Fifth argument must be a Color.");
       return NULL;
    }
#endif

    if (PyErr_CheckSignals())
       return NULL;

    self->scr->fillRect(color->color, x, y, w, h);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* screen_swap(PyScreen *self,
                             PyObject *args,
                             PyObject *kwargs)
{
    if (!PyArg_ParseTuple(args, ":swap"))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    self->scr->flip();

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* screen_saveToFile(PyScreen *self,
                                   PyObject *args,
                                   PyObject *kwargs)
{
    char *filename;

    if (!PyArg_ParseTuple(args, "s", &filename))
       return NULL;

    self->scr->saveToFile(filename);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* screen_putPixel(PyScreen *self,
                                 PyObject *args,
                                 PyObject *kwargs)
{
    int x, y;
    PyColor *color;

    if (!PyArg_ParseTuple(args, "iiO", &x, &y, &color))
       return NULL;

#ifdef CHECKTYPE
    if (((PyObject*)color)->ob_type != PPyColorType)
    {
       PyErr_SetString(PyExc_TypeError, "Third argument must be a Color.");
       return NULL;
    }
#endif

    self->scr->putPixel(color->color, x, y);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* screen_getPixel(PyScreen *self,
                                 PyObject *args,
                                 PyObject *kwargs)
{
    int x, y;
    PyColor *color;
    PyObject *nargs;
    u32 c;

    if (!PyArg_ParseTuple(args, "ii", &x, &y))
       return NULL;

    c = self->scr->getPixel(x, y);
    nargs = Py_BuildValue("iii", (int)(c & 0xFF), (int)((c >> 8) & 0xFF),
                          (int)((c >> 16) & 0xFF), (int)((c >> 24) & 0xFF));

    color = (PyColor*)PyType_GenericNew(PPyColorType, nargs, NULL);
    Py_DECREF(nargs);

    color->color = c;
    return (PyObject*)color;
}

static PyMethodDef screen_methods[] = {
   { "blit", (PyCFunction)screen_blit, METH_VARARGS|METH_KEYWORDS, "" },
   { "clear", (PyCFunction)screen_clear, METH_VARARGS, "" },
   { "fillRect", (PyCFunction)screen_fillRect, METH_VARARGS, "" },
   { "swap", (PyCFunction)screen_swap, METH_VARARGS, "" },
   { "saveToFile", (PyCFunction)screen_saveToFile, METH_VARARGS, "" },
   { "putPixel", (PyCFunction)screen_putPixel, METH_VARARGS, "" },
   { "getPixel", (PyCFunction)screen_getPixel, METH_VARARGS, "" },

   { NULL }
};

static PyTypeObject PyScreenType = {
   PyObject_HEAD_INIT(NULL)
   0,
   "psp2d.Screen",
   sizeof(PyScreen),
   0,
   (destructor)screen_dealloc,
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
   "Screen objects",
   0,
   0,
   0,
   0,
   0,
   0,
   screen_methods,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   (initproc)screen_init,
   0,
   screen_new,
};

PyTypeObject* PPyScreenType = &PyScreenType;

#ifdef _GNUC
static const char* _rcsid_screen __attribute__((unused)) = "$Id$";
#endif

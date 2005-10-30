
/**
 * @file image.c
 */

/**********************************************************************

  Created: 30 Oct 2005

**********************************************************************/
// $Id$

#include "image.h"
#include "color.h"

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
#ifdef CHECKTYPE
       if (!PyString_Check(a))
       {
          PyErr_SetString(PyExc_TypeError, "Argument must be a string");
          return -1;
       }
#endif

       // TODO: load image from file...
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

       self->data = (u32*)malloc(sizeof(u32) * w * h);
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

static PyMethodDef image_methods[] = {
   { "clear", (PyCFunction)image_clear, METH_VARARGS,
     "clear(color)\n"
     "Fills the image with the given color." },

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

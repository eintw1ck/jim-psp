
/**
 * @file mask.c
 */

/**********************************************************************

  Created: 01 Nov 2005

**********************************************************************/
// $Id$

#include <malloc.h>
#include <math.h>

#include "mask.h"
#include "image.h"

#define ISSET(o, x, y) (((*((o)->data + (y) * (o)->wcap + ((x) / 32))) & (1U << ((x) & 31))) != 0)
#define SET(o, x, y) *((o)->data + (y) * (o)->wcap + ((x) / 32)) |= (1U << ((x) & 31))
#define CLEAR(o, x, y) *((o)->data + (y) * (o)->wcap + ((x) / 32)) &= ~(1U << ((x) & 31))

static void mask_dealloc(PyMask *self)
{
    if (self->data)
       free(self->data);

    self->ob_type->tp_free((PyObject*)self);
}

static PyObject* mask_new(PyTypeObject *type,
                          PyObject *args,
                          PyObject *kwargs)
{
    PyMask *self;

    self = (PyMask*)type->tp_alloc(type, 0);

    if (self)
    {
       self->width = 0;
       self->height = 0;
       self->wcap = 0;
       self->data = NULL;
    }

    return (PyObject*)self;
}

static int mask_init(PyMask *self,
                      PyObject *args,
                      PyObject *kwargs)
{
    PyImage *img;
    int x, y, w, h, t = 128, i, j;

    if (!PyArg_ParseTuple(args, "Oiiii|i", &img, &x, &y, &w, &h, &t))
       return -1;

#ifdef CHEKTYPE
    if (((PyObject*)img)->ob_type != PPyImageType)
    {
       PyErr_SetString(PyExc_TypeError, "First argument must be a Image.");
       return -1;
    }
#endif

    self->width = w;
    self->height = h;

    self->wcap = (u16)ceil(1.0 * self->width / 32);
    self->data = (u32*)memalign(16, self->wcap * sizeof(u32) * self->height);

    if (!self->data)
    {
       PyErr_SetString(PyExc_MemoryError, "Memory error");
       return -1;
    }

    memset(self->data, 0, self->wcap * sizeof(u32) * self->height);

    for (j = 0; j < self->height; ++j)
    {
       for (i = 0; i < self->width; ++i)
       {
          if (((*(img->data + (j + y) * img->twidth + i + x)) >> 24) >= t)
             SET(self, i, j);
          else
             CLEAR(self, i, j);
       }
    }

    return 0;
}

static PyObject* mask_collide(PyMask *self,
                              PyObject *args,
                              PyObject *kwargs)
{
    PyMask *other;
    int i, j, k, count = 0;

    if (!PyArg_ParseTuple(args, "O", &other))
       return NULL;

#ifdef CHECKTYPE
    if (((PyObject*)other)->ob_type != PPyMaskType)
    {
       PyErr_SetString(PyExc_TypeError, "Argument must be a Mask.");
       return NULL;
    }

    if ((self->width != other->width) || (self->height != other->height))
    {
       PyErr_SetString(PyExc_ValueError, "Masks must have the same size");
       return NULL;
    }
#endif

    for (j = 0; j < self->height; ++j)
    {
       for (i = 0; i < self->wcap; ++i)
       {
          u32 m;

          m = (*(self->data + j * self->wcap + i)) & (*(other->data + j * other->wcap + i));

          if (m)
          {
             for (k = 0; k<32; ++k)
                count += ((m >> k) & 1);
          }
       }
    }

    return Py_BuildValue("i", count);
}

static PyObject* mask_union(PyMask *self,
                            PyObject *args,
                            PyObject *kwargs)
{
    PyMask *other;
    int k;

    if (!PyArg_ParseTuple(args, "O", &other))
       return NULL;

#ifdef CHECKTYPE
    if (((PyObject*)other)->ob_type != PPyMaskType)
    {
       PyErr_SetString(PyExc_TypeError, "Argument must be a Mask.");
       return NULL;
    }

    if ((self->width != other->width) || (self->height != other->height))
    {
       PyErr_SetString(PyExc_ValueError, "Masks must have the same size");
       return NULL;
    }
#endif

    for (k = 0; k < self->wcap * self->height; ++k)
       *(self->data + k) |= *(other->data + k);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* mask_isIn(PyMask *self,
                           PyObject *args,
                           PyObject *kwargs)
{
    int x, y;

    if (!PyArg_ParseTuple(args, "ii", &x, &y))
       return NULL;

    if (ISSET(self, x, y))
    {
       Py_INCREF(Py_True);
       return Py_True;
    }

    Py_INCREF(Py_False);
    return Py_False;
}

static PyMethodDef mask_methods[] = {
   { "collide", (PyCFunction)mask_collide, METH_VARARGS, "" },
   { "union", (PyCFunction)mask_union, METH_VARARGS, "" },
   { "isIn", (PyCFunction)mask_isIn, METH_VARARGS, "" },

   { NULL }
};

static PyTypeObject PyMaskType = {
   PyObject_HEAD_INIT(NULL)
   0,
   "psp2d.Mask",
   sizeof(PyMask),
   0,
   (destructor)mask_dealloc,
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
   "Mask objects",
   0,
   0,
   0,
   0,
   0,
   0,
   mask_methods,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   (initproc)mask_init,
   0,
   mask_new,
};

PyTypeObject* PPyMaskType = &PyMaskType;

#ifdef _GNUC
static const char* _rcsid_mask __attribute__((unused)) = "$Id$";
#endif

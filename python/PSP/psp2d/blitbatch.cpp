
/**
 * @file blitbatch.cpp
 * @brief Implementation of class blitbatch
 */

/**********************************************************************

  Created: 20 Nov 2005

**********************************************************************/
// $Id$

#include "blitbatch.h"
#include "image.h"

using namespace PSP2D;

class PyBatched : public BatchedDrawable
{
   public:
      PyBatched(PyObject*);
      ~PyBatched();

      bool getData(Image*&, u16&, u16&, u16&, u16&, u16&, u16&);

   protected:
      PyObject *_self;
};

PyBatched::PyBatched(PyObject *self)
    : _self(self)
{
    Py_INCREF(_self);
}

PyBatched::~PyBatched()
{
    Py_DECREF(_self);
}

bool PyBatched::getData(Image*& img, u16& sx, u16& sy, u16& w, u16& h, u16& dx, u16& dy)
{
    PyObject *tuple = PyObject_GetAttrString(_self, "data");

    if (!tuple)
    {
       PyErr_Print();
       return false;
    }

    PyImage *pyimg;
    int x, y;

    if (!PyArg_ParseTuple(tuple, "Oii", &pyimg, &x, &y))
    {
       PyErr_Print();
       Py_DECREF(tuple);
       return false;
    }

#ifdef CHECKTYPE
    if (((PyObject*)pyimg)->ob_type != PPyImageType)
    {
       Py_DECREF(tuple);

       return false;
    }
#endif

    img = pyimg->img;
    sx = 0;
    sy = 0;
    w = img->getWidth();
    h = img->getHeight();
    dx = (u16)x;
    dy = (u16)y;

    return true;
}

static void blitbatch_dealloc(PyBlitBatch *self)
{
    delete self->batch;

    self->ob_type->tp_free((PyObject*)self);
}

static PyObject* blitbatch_new(PyTypeObject *type,
                               PyObject *args,
                               PyObject *kwargs)
{
    PyBlitBatch *self;

    self = (PyBlitBatch*)type->tp_alloc(type, 0);

    if (self)
       self->batch = NULL;

    return (PyObject*)self;
}

static int blitbatch_init(PyBlitBatch *self,
                          PyObject *args,
                          PyObject *kwargs)
{
    if (!PyArg_ParseTuple(args, ""))
       return -1;

    self->batch = new BlitBatch();

    return 0;
}

static PyObject* blitbatch_add(PyBlitBatch *self,
                               PyObject *args,
                               PyObject *kwargs)
{
    PyObject *other;

    if (!PyArg_ParseTuple(args, "O", &other))
       return NULL;

    self->batch->add(new PyBatched(other));

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* blitbatch_blit(PyBlitBatch *self,
                                PyObject *args,
                                PyObject *kwargs)
{
    if (!PyArg_ParseTuple(args, ""))
       return NULL;

    self->batch->blit();

    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef blitbatch_methods[] = {
   { "add", (PyCFunction)blitbatch_add, METH_VARARGS, "" },
   { "blit", (PyCFunction)blitbatch_blit, METH_VARARGS, "" },

   { NULL }
};

static PyTypeObject PyBlitBatchType = {
   PyObject_HEAD_INIT(NULL)
   0,
   "psp2d.BlitBatch",
   sizeof(PyBlitBatch),
   0,
   (destructor)blitbatch_dealloc,
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
   "BlitBatch objects",
   0,
   0,
   0,
   0,
   0,
   0,
   blitbatch_methods,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   (initproc)blitbatch_init,
   0,
   blitbatch_new,
};

PyTypeObject* PPyBlitBatchType = &PyBlitBatchType;

static const char* _rcsid_blitbatch __attribute__((unused)) = "$Id$";

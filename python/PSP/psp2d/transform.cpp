
/**
 * @file transform.c
 */

/**********************************************************************

  Created: 06 Nov 2005

**********************************************************************/
// $Id$

#include "transform.h"
#include "image.h"
#include "color.h"

static void transform_dealloc(PyTransform *self)
{
    Py_XDECREF(self->cb);

    self->ob_type->tp_free((PyObject*)self);
}

static PyObject* transform_new(PyTypeObject *type,
                               PyObject *args,
                               PyObject *kwargs)
{
    PyTransform *self;

    self = (PyTransform*)type->tp_alloc(type, 0);
    if (self)
    {
       self->type = 0;
       self->param = 0;
       self->cb = NULL;
    }

    return (PyObject*)self;
}

static int transform_init(PyTransform *self,
                          PyObject *args,
                          PyObject *kwargs)
{
    PyObject *p;
    float param = 0.0;

    if (!PyArg_ParseTuple(args, "O|f", &p, &param))
       return -1;

    if (PyInt_Check(p))
    {
       self->type = PyInt_AsLong(p);
       self->param = param;
    }
    else if (PyCallable_Check(p))
    {
       self->type = 0;
       self->cb = p;
       Py_INCREF(p);
    }
    else
    {
       PyErr_SetString(PyExc_TypeError, "Argument must be either an integer or a callable");
       return -1;
    }

    return 0;
}

static PyObject* transform_apply(PyTransform *self,
                                 PyObject *args,
                                 PyObject *kwargs)
{
    PyImage *img;
    u32 x, y, k;
    u8 * rgba;

    if (!PyArg_ParseTuple(args, "O", &img))
       return NULL;

#ifdef CHECKTYPE
    if (((PyObject*)img)->ob_type != PPyImageType)
    {
       PyErr_SetString(PyExc_TypeError, "Argument must be an Image.");
       return NULL;
    }
#endif

    if (PyErr_CheckSignals())
       return NULL;

    if (self->type == TR_USER)
    {
       for (y = 0; y < img->img->getHeight(); ++y)
       {
          for (x = 0; x < img->img->getWidth(); ++x)
          {
             PyObject *nargs, *ret;
             PyColor *color;

             rgba = (u8*)(img->img->getData() + y * img->img->getTextureWidth() + x);
             color = (PyColor*)PyType_GenericNew(PPyColorType, NULL, NULL);
             ret = PyObject_CallMethod((PyObject*)color, "__init__", "iiii",
                                       (int)rgba[3], (int)rgba[2],
                                       (int)rgba[1], (int)rgba[0]);
             Py_XDECREF(ret);

             nargs = Py_BuildValue("iiO", x, y, color);

             ret = PyObject_Call(self->cb, nargs, NULL);

             Py_DECREF(nargs);

             if (!ret)
                PyErr_Print();

             if (!PyObject_IsTrue(ret))
             {
                Py_DECREF(ret);
                Py_DECREF(color);

                Py_INCREF(Py_None);
                return Py_None;
             }

             Py_DECREF(ret);

             *(img->img->getData() + y * img->img->getTextureWidth() + x) = color->color;
             Py_DECREF(color);
          }
       }
    }
    else
    {
       Py_BEGIN_ALLOW_THREADS

       for (y = 0; y < img->img->getHeight(); ++y)
       {
          for (x = 0; x < img->img->getWidth(); ++x)
          {
             rgba = (u8*)(img->img->getData() + y * img->img->getTextureWidth() + x);
             switch (self->type)
             {
                case TR_PLUS:
                   for (k = 1; k < 4; ++k)
                   {
                      int r = (int)rgba[k] + (int)self->param;

                      if (r < 0) r = 0;
                      if (r > 255) r = 255;
                      rgba[k] = (u8)r;
                   }
                   break;

                case TR_MULT:
                   for (k = 1; k < 4; ++k)
                   {
                      int r = (int)rgba[k] * (int)self->param;

                      if (r < 0) r = 0;
                      if (r > 255) r = 255;
                      rgba[k] = (u8)r;
                   }
                   break;
             }
          }
       }

       Py_END_ALLOW_THREADS
    }

    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef transform_methods[] = {
   { "apply", (PyCFunction)transform_apply, METH_VARARGS, "" },

   { NULL }
};

static PyTypeObject PyTransformType = {
   PyObject_HEAD_INIT(NULL)
   0,
   "psp2d.Transform",
   sizeof(PyTransform),
   0,
   (destructor)transform_dealloc,
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
   "Transform objects",
   0,
   0,
   0,
   0,
   0,
   0,
   transform_methods,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   (initproc)transform_init,
   0,
   transform_new,
};

PyTypeObject* PPyTransformType = &PyTransformType;

#ifdef _GNUC
static const char* _rcsid_transform __attribute__((unused)) = "$Id$";
#endif

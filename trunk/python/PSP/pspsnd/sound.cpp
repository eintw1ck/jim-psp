
/**
 * @file sound.c
 */

/**********************************************************************

  Created: 30 Oct 2005

**********************************************************************/
// $Id$

#include "sound.h"

using namespace PSPSND;

static void sound_dealloc(PySound *self)
{
    delete self->sound;

    self->ob_type->tp_free((PyObject*)self);
}

static PyObject* sound_new(PyTypeObject *type,
                           PyObject *args,
                           PyObject *kwargs)
{
    PySound *self;

    self = (PySound*)type->tp_alloc(type, 0);
    if (self)
       self->sound = NULL;

    return (PyObject*)self;
}

static int sound_init(PySound *self,
                      PyObject *args,
                      PyObject *kwargs)
{
    char *filename;

    if (!PyArg_ParseTuple(args, "s", &filename))
       return -1;

    self->sound = new Sound(filename);

    return 0;
}

static PyObject* sound_start(PySound *self,
                             PyObject *args,
                             PyObject *kwargs)
{
    if (!PyArg_ParseTuple(args, ":start"))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    self->sound->start();

    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef sound_methods[] = {
   { "start", (PyCFunction)sound_start, METH_VARARGS,
     "start()\n"
     "Starts playing the sound." },

   { NULL }
};

static PyTypeObject PySoundType = {
   PyObject_HEAD_INIT(NULL)
   0,
   "pspsnd.Sound",
   sizeof(PySound),
   0,
   (destructor)sound_dealloc,
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
   "Sound objects",
   0,
   0,
   0,
   0,
   0,
   0,
   sound_methods,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   (initproc)sound_init,
   0,
   sound_new,
};

PyTypeObject* PPySoundType = &PySoundType;

#ifdef _GNUC
static const char* _rcsid_sound __attribute__((unused)) = "$Id$";
#endif


/**
 * @file music.c
 */

/**********************************************************************

  Created: 30 Oct 2005

**********************************************************************/
// $Id$

#include "music.h"

static void music_dealloc(PyMusic *self)
{
    if (self->mf)
       MikMod_FreeSong(self->mf);

    self->ob_type->tp_free((PyObject*)self);
}

static PyObject* music_new(PyTypeObject *type,
                           PyObject *args,
                           PyObject *kwargs)
{
    PyMusic *self;

    self = (PyMusic*)type->tp_alloc(type, 0);
    if (self)
       self->mf = NULL;

    return (PyObject*)self;
}

static int music_init(PyMusic *self,
                      PyObject *args,
                      PyObject *kwargs)
{
    char *filename;
    int maxchan = 128;

    if (!PyArg_ParseTuple(args, "s|i", &filename, &maxchan))
       return -1;

    self->mf = MikMod_LoadSong(filename, maxchan);
    if (!self->mf)
    {
       PyErr_SetString(PyExc_IOError, "Could not load song file.");
       return -1;
    }

    return 0;
}

static PyObject* music_start(PyMusic *self,
                             PyObject *args,
                             PyObject *kwargs)
{
    if (!PyArg_ParseTuple(args, ":start"))
       return NULL;

#ifdef CHECKTYPE
    if (!self->mf)
    {
       PyErr_SetString(PyExc_RuntimeError, "No music was loaded!");
       return NULL;
    }
#endif

    Player_Start(self->mf);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* music_stop(PyMusic *self,
                            PyObject *args,
                            PyObject *kwargs)
{
    if (!PyArg_ParseTuple(args, ":stop"))
       return NULL;

#ifdef CHECKTYPE
    if (!self->mf)
    {
       PyErr_SetString(PyExc_RuntimeError, "No music was loaded!");
       return NULL;
    }
#endif

    Player_Stop();

    MikMod_FreeSong(self->mf);
    self->mf = NULL;

    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef music_methods[] = {
   { "start", (PyCFunction)music_start, METH_VARARGS,
     "start()\n"
     "Starts playing the music." },
   { "stop", (PyCFunction)music_stop, METH_VARARGS,
     "stop()\n"
     "Stops playing the music." },

   { NULL }
};

static PyTypeObject PyMusicType = {
   PyObject_HEAD_INIT(NULL)
   0,
   "psp2d.Music",
   sizeof(PyMusic),
   0,
   (destructor)music_dealloc,
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
   "Music objects",
   0,
   0,
   0,
   0,
   0,
   0,
   music_methods,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   (initproc)music_init,
   0,
   music_new,
};

PyTypeObject* PPyMusicType = &PyMusicType;

#ifdef _GNUC
static const char* _rcsid_music __attribute__((unused)) = "$Id$";
#endif

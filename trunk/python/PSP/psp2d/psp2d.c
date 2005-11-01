
/**
 * @file psp2d.c
 */

/**********************************************************************

  Created: 30 Oct 2005

**********************************************************************/
// $Id$

#include <Python.h>

#include "color.h"
#include "image.h"
#include "controller.h"
#include "music.h"
#include "sound.h"
#include "screen.h"
#include "mask.h"

#ifndef PyMODINIT_FUNC
#define PyMODINIT_FUNC void
#endif

static PyObject* psp2d_setMusicVolume(PyObject *self,
                                      PyObject *args,
                                      PyObject *kwargs)
{
    int volume;

    if (!PyArg_ParseTuple(args, "i:setMusicVolume", &volume))
       return NULL;

#ifdef CHECKTYPE
    if ((volume < 0) || (volume > 255))
    {
       PyErr_SetString(PyExc_ValueError, "Bad volume value");
       return NULL;
    }
#endif

    md_musicvolume = (UBYTE)volume;

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* psp2d_setSndFxVolume(PyObject *self,
                                      PyObject *args,
                                      PyObject *kwargs)
{
    int volume;

    if (!PyArg_ParseTuple(args, "i:setSndFxVolume", &volume))
       return NULL;

#ifdef CHECKTYPE
    if ((volume < 0) || (volume > 255))
    {
       PyErr_SetString(PyExc_ValueError, "Bad volume value");
       return NULL;
    }
#endif

    md_sndfxvolume = (UBYTE)volume;

    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef psp2d_functions[] = {
   { "setMusicVolume", (PyCFunction)psp2d_setMusicVolume, METH_VARARGS, "" },
   { "setSndFxVolume", (PyCFunction)psp2d_setSndFxVolume, METH_VARARGS, "" },

   { NULL }
};

PyMODINIT_FUNC initpsp2d(void)
{
    PyObject *mdl;

    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    if (PyType_Ready(PPyColorType) < 0)
       return;

    if (PyType_Ready(PPyImageType) < 0)
       return;

    if (PyType_Ready(PPyControllerType) < 0)
       return;

    if (PyType_Ready(PPyMusicType) < 0)
       return;

    if (PyType_Ready(PPySoundType) < 0)
       return;

    if (PyType_Ready(PPyScreenType) < 0)
       return;

    if (PyType_Ready(PPyMaskType) < 0)
       return;

    mdl = Py_InitModule3("psp2d", psp2d_functions, "2D programming for the PSP");
    if (!mdl)
       return;

    Py_INCREF(PPyColorType);
    PyModule_AddObject(mdl, "Color", (PyObject*)PPyColorType);

    Py_INCREF(PPyImageType);
    PyModule_AddObject(mdl, "Image", (PyObject*)PPyImageType);

    Py_INCREF(PPyControllerType);
    PyModule_AddObject(mdl, "Controller", (PyObject*)PPyControllerType);

    Py_INCREF(PPyMusicType);
    PyModule_AddObject(mdl, "Music", (PyObject*)PPyMusicType);

    Py_INCREF(PPySoundType);
    PyModule_AddObject(mdl, "Sound", (PyObject*)PPySoundType);

    Py_INCREF(PPyScreenType);
    PyModule_AddObject(mdl, "Screen", (PyObject*)PPyScreenType);

    Py_INCREF(PPyMaskType);
    PyModule_AddObject(mdl, "Mask", (PyObject*)PPyMaskType);
}

#ifdef _GNUC
static const char* _rcsid_psp2d __attribute__((unused)) = "$Id$";
#endif

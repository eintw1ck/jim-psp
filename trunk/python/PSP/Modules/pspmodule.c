
/**
 * @file pspmodule.c
 */

/**********************************************************************

  Created: 02 Oct 2005

**********************************************************************/
// $Id$

#include "Python.h"

//#include <pspdebug.h>
#include <pspctrl.h>
#include <pspaudiolib.h>
#include <pspkernel.h>
#include <pspdisplay.h>


/**************************************************************************/
// Debugging

// XXX FIXME: when  building WITH_GU the PSP hangs  if these functions
// are defined,  even if they're not  used. Bug in  PSP-toolchain ? In
// KXploit ? Size problem ? don't know yet.

#ifndef WITH_GU

static PyObject* PyPSP_debugScreenInit(PyObject *self,
                                       PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":debugScreenInit"))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    pspDebugScreenInit();

    pspDebugScreenPrintf("Debug screen initialized.\n");

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* PyPSP_debugScreenSetXY(PyObject *self,
                                        PyObject *args)
{
    int x, y;

    if (!PyArg_ParseTuple(args, "ii:debugScreenSetXY", &x, &y))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    pspDebugScreenSetXY(x, y);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* PyPSP_debug(PyObject *self,
                             PyObject *args)
{
    char *s;

    if (!PyArg_ParseTuple(args, "s:debug", &s))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    pspDebugScreenPrintf("%s", s);

    Py_INCREF(Py_None);
    return Py_None;
}

#endif


/**************************************************************************/
// Controller

static PyObject* PyPSP_ctrlSetSamplingCycle(PyObject *self,
                                            PyObject *args)
{
    int i;

    if (!PyArg_ParseTuple(args, "i:ctrlSetSamplingCycle", &i))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceCtrlSetSamplingCycle(i);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* PyPSP_ctrlSetSamplingMode(PyObject *self,
                                           PyObject *args)
{
    int i;

    if (!PyArg_ParseTuple(args, "i:ctrlSetSamplingMode", &i))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceCtrlSetSamplingMode(i);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* PyPSP_ctrlReadBufferPositive(PyObject *self,
                                              PyObject *args)
{
    SceCtrlData pad;

    if (!PyArg_ParseTuple(args, ":ctrlReadBufferPositive"))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceCtrlReadBufferPositive(&pad, 1);

    return Py_BuildValue("iiii", (int)pad.TimeStamp, (int)pad.Buttons,
                         (int)pad.Lx, (int)pad.Ly);
}

/**************************************************************************/
// Audio

/* WARNING: due to threading issues, the audio does not work. I really
 * need to implement threading... */

/*
static PyObject* currentAudioCallbacks[2] = { NULL, NULL };

static PyObject* PyPSP_audioInit(PyObject *self,
                                 PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":audioInit"))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    pspAudioInit();

    Py_INCREF(Py_None);
    return Py_None;
}

static void audioCallback0(void *buffer, unsigned int length)
{
    if (currentAudioCallbacks[0])
    {
       PyObject *args, *ret;

       args = Py_BuildValue("i", length);
       ret = PyObject_CallObject(currentAudioCallbacks[0], args);

       Py_DECREF(args);

       if (ret)
       {
          if (PyString_Check(ret))
          {
             char *bf;
             int sz;

             PyString_AsStringAndSize(ret, &bf, &sz);

             if (sz <= length)
             {
                memcpy(buffer, bf, sz);
             }
          }

          Py_DECREF(ret);
       }
    }
}

static void audioCallback1(void *buffer, unsigned int length)
{
    if (currentAudioCallbacks[0])
    {
       PyObject *args, *ret;

       args = Py_BuildValue("i", length);
       ret = PyObject_CallObject(currentAudioCallbacks[1], args);

       Py_DECREF(args);

       if (ret)
       {
          if (PyString_Check(ret))
          {
             char *bf;
             int sz;

             PyString_AsStringAndSize(ret, &bf, &sz);

             if (sz > length)
                sz = length;

             memcpy(buffer, bf, sz);
          }

          Py_DECREF(ret);
       }
    }
}

static PyObject* PyPSP_audioSetChannelCallback(PyObject *self,
                                               PyObject *args)
{
    int channel;
    PyObject *cb;

    if (!PyArg_ParseTuple(args, "iO:audioSetChannelCallback", &channel, &cb))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    if (!PyCallable_Check(cb))
    {
       PyErr_SetString(PyExc_TypeError, "Argument must be callable");
       return NULL;
    }

    if ((channel < 0) || (channel > 1))
    {
       PyErr_SetString(PyExc_ValueError, "Channel must be 0 or 1");
       return NULL;
    }

    Py_INCREF(cb);
    Py_XDECREF(currentAudioCallbacks[channel]);
    currentAudioCallbacks[channel] = cb;

    switch (channel)
    {
       case 0:
          pspAudioSetChannelCallback(channel, audioCallback0);
          break;
       case 1:
          pspAudioSetChannelCallback(channel, audioCallback1);
          break;
    }

    Py_INCREF(Py_None);
    return Py_None;
}
*/

/**************************************************************************/
// Others

static PyObject* PyPSP_kernelDcacheWritebackAll(PyObject *self,
                                                PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":kernelDcacheWritebackAll"))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceKernelDcacheWritebackAll();

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* PyPSP_displayWaitVblankStart(PyObject *self,
                                              PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":displayWaitVblankStart"))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceDisplayWaitVblankStart();

    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef psp_functions[] = {
#ifndef WITH_GU
   { "debugScreenInit", PyPSP_debugScreenInit, METH_VARARGS,
     "Initializes the debug screen" },
   { "debugScreenSetXY", PyPSP_debugScreenSetXY, METH_VARARGS,
     "Sets the debug screen's cursor position" },
   { "debug", PyPSP_debug, METH_VARARGS,
     "Outputs a string to debug screen" },
#endif

   { "ctrlSetSamplingCycle", PyPSP_ctrlSetSamplingCycle, METH_VARARGS,
     "Sets the controller sampling cycle" },
   { "ctrlSetSamplingMode", PyPSP_ctrlSetSamplingMode, METH_VARARGS,
     "Sets the controller sampling mode" },
   { "ctrlReadBufferPositive", PyPSP_ctrlReadBufferPositive, METH_VARARGS,
     "Reads the controller buffer. Returns a 4-tuple (timestamp, buttons, "
     "analog_x, analog_y). See the PSP_CTRL_* constants for the bits that "
     "make up the buttons." },

   /*
   { "audioInit", PyPSP_audioInit, METH_VARARGS,
     "Initializes the audio library" },
   { "audioSetChannelCallback", PyPSP_audioSetChannelCallback, METH_VARARGS,
     "Sets a channel audio callback" },
   */

   { "kernelDcacheWritebackAll", PyPSP_kernelDcacheWritebackAll, METH_VARARGS, "" },
   { "displayWaitVblankStart", PyPSP_displayWaitVblankStart, METH_VARARGS, "" },

   { NULL }
};

#ifndef PyMODINIT_FUNC	/* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif

PyMODINIT_FUNC initpsp(void)
{
    PyObject *mdl;

    mdl = Py_InitModule3("psp", psp_functions, "Wrapper for the PSP native APIs");

    if (!mdl)
       return;

    /* Controller constants */
    PyModule_AddIntConstant(mdl, "CTRL_SELECT", PSP_CTRL_SELECT);
    PyModule_AddIntConstant(mdl, "CTRL_START", PSP_CTRL_START);
    PyModule_AddIntConstant(mdl, "CTRL_UP", PSP_CTRL_UP);
    PyModule_AddIntConstant(mdl, "CTRL_RIGHT", PSP_CTRL_RIGHT);
    PyModule_AddIntConstant(mdl, "CTRL_DOWN", PSP_CTRL_DOWN);
    PyModule_AddIntConstant(mdl, "CTRL_LEFT", PSP_CTRL_LEFT);
    PyModule_AddIntConstant(mdl, "CTRL_LTRIGGER", PSP_CTRL_LTRIGGER);
    PyModule_AddIntConstant(mdl, "CTRL_RTRIGGER", PSP_CTRL_RTRIGGER);
    PyModule_AddIntConstant(mdl, "CTRL_TRIANGLE", PSP_CTRL_TRIANGLE);
    PyModule_AddIntConstant(mdl, "CTRL_CIRCLE", PSP_CTRL_CIRCLE);
    PyModule_AddIntConstant(mdl, "CTRL_CROSS", PSP_CTRL_CROSS);
    PyModule_AddIntConstant(mdl, "CTRL_SQUARE", PSP_CTRL_SQUARE);
    PyModule_AddIntConstant(mdl, "CTRL_HOME", PSP_CTRL_HOME);
    PyModule_AddIntConstant(mdl, "CTRL_HOLD", PSP_CTRL_HOLD);
    PyModule_AddIntConstant(mdl, "CTRL_NOTE", PSP_CTRL_NOTE);
}

#ifdef _GNUC
static const char* _rcsid_pspmodule __attribute__((unused)) = "$Id$";
#endif

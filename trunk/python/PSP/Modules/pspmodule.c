
/**
 * @file pspmodule.c
 */

/**********************************************************************

  Created: 02 Oct 2005

**********************************************************************/
// $Id$

#include "Python.h"

#include <pspdebug.h>
#include <pspctrl.h>
#include <pspaudiolib.h>
#include <pspkernel.h>
#include <pspdisplay.h>


/**************************************************************************/
// Debugging

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

static PyObject* PyPSP_debugScreenPrint(PyObject *self,
                                        PyObject *args)
{
    char *s;

    if (!PyArg_ParseTuple(args, "s:debugScreenPrint", &s))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    pspDebugScreenPrintf("%s", s);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* PyPSP_debugScreenSetBackColor(PyObject *self,
                                               PyObject *args)
{
    int r, g, b, a = 0;
    u32 color;

    if (!PyArg_ParseTuple(args, "iii|i:debugScreenSetBackColor", &r, &g, &b, &a))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    color = (a << 24) | (b << 16) | (g << 8) | r;

    pspDebugScreenSetBackColor(color);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* PyPSP_debugScreenSetTextColor(PyObject *self,
                                               PyObject *args)
{
    int r, g, b, a = 0;
    u32 color;

    if (!PyArg_ParseTuple(args, "iii|i:debugScreenSetTextColor", &r, &g, &b, &a))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    color = (a << 24) | (b << 16) | (g << 8) | r;

    pspDebugScreenSetTextColor(color);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* PyPSP_debugScreenPutChar(PyObject *self,
                                          PyObject *args)
{
    int x, y, c, r, g, b, a = 0;
    u32 color;

    if (!PyArg_ParseTuple(args, "iiiiii|i:debugScreenPutChar", &x, &y, &c, &r, &g, &b, &a))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    color = (a << 24) | (b << 16) | (g << 8) | r;

    pspDebugScreenPutChar(x, y, color, (u8)c);

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

static PyObject* PyPSP_debugScreenGetX(PyObject *self,
                                       PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":debugScreenGetX"))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    return Py_BuildValue("i", pspDebugScreenGetX());
}

static PyObject* PyPSP_debugScreenGetY(PyObject *self,
                                       PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":debugScreenGetY"))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    return Py_BuildValue("i", pspDebugScreenGetY());
}

static PyObject* PyPSP_debugScreenClear(PyObject *self,
                                        PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":debugScreenClear"))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    pspDebugScreenClear();

    Py_INCREF(Py_None);
    return Py_None;
}


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

static PyObject* PyPSP_ctrlGetSamplingCycle(PyObject *self,
                                            PyObject *args)
{
    int sc;

    if (!PyArg_ParseTuple(args, ""))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceCtrlGetSamplingCycle(&sc);

    return Py_BuildValue("i", sc);
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

static PyObject* PyPSP_ctrlGetSamplingMode(PyObject *self,
                                           PyObject *args)
{
    int sm;

    if (!PyArg_ParseTuple(args, ""))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceCtrlGetSamplingMode(&sm);

    return Py_BuildValue("i", sm);
}

static PyObject* PyPSP_ctrlPeekBufferPositive(PyObject *self,
                                              PyObject *args)
{
    SceCtrlData *pdata;
    PyObject *ret;
    int n, k, err;

    if (!PyArg_ParseTuple(args, "i", &n))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    pdata = (SceCtrlData*)malloc(sizeof(SceCtrlData) * n);

    err = sceCtrlPeekBufferPositive(pdata, n);
    if (err < 0)
    {
       free(pdata);
       PyErr_SetString(PyExc_RuntimeError, "FIXME"); // FIXME
       return NULL;
    }

    ret = PyList_New(n);
    for (k = 0; k < n; ++k)
    {
       // FIXME: does PyList_Append steal a reference ?

       PyList_Append(ret, Py_BuildValue("iiii",
                                        (int)pdata[k].TimeStamp,
                                        (int)pdata[k].Buttons,
                                        (int)pdata[k].Lx,
                                        (int)pdata[k].Ly));
    }

    free(pdata);
    return ret;
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
#ifdef CHECKTYPE
          if (PyString_Check(ret))
#endif
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
#ifdef CHECKTYPE
          if (PyString_Check(ret))
#endif
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

#ifdef CHECKTYPE
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
#endif

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
// Display

static PyObject* PyPSP_displaySetMode(PyObject *self,
                                      PyObject *args)
{
    int mode, w, h;

    if (!PyArg_ParseTuple(args, "iii", &mode, &w, &h))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    if (sceDisplaySetMode(mode, w, h))
    {
       PyErr_SetString(PyExc_RuntimeError, "FIXME");
       return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* PyPSP_displayGetMode(PyObject *self,
                                      PyObject *args)
{
    int mode, w, h;

    if (!PyArg_ParseTuple(args, ""))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    if (sceDisplayGetMode(&mode, &w, &h))
    {
       PyErr_SetString(PyExc_RuntimeError, "FIXME");
       return NULL;
    }

    return Py_BuildValue("iii", mode, w, h);
}

static PyObject* PyPSP_displayGetVcount(PyObject *self,
                                        PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    return Py_BuildValue("i", sceDisplayGetVcount());
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

/**************************************************************************/
// Kernel

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

static PyMethodDef psp_functions[] = {
   { "debugScreenInit", PyPSP_debugScreenInit, METH_VARARGS, "" },
   { "debugScreenPrint", PyPSP_debugScreenPrint, METH_VARARGS, "" },
   { "debugScreenSetBackColor", PyPSP_debugScreenSetBackColor, METH_VARARGS, "" },
   { "debugScreenSetTextColor", PyPSP_debugScreenSetTextColor, METH_VARARGS, "" },
   { "debugScreenPutChar", PyPSP_debugScreenPutChar, METH_VARARGS, "" },
   { "debugScreenSetXY", PyPSP_debugScreenSetXY, METH_VARARGS, "" },
   { "debugScreenGetX", PyPSP_debugScreenGetX, METH_VARARGS, "" },
   { "debugScreenGetY", PyPSP_debugScreenGetY, METH_VARARGS, "" },
   { "debugScreenClear", PyPSP_debugScreenClear, METH_VARARGS, "" },

   { "ctrlSetSamplingCycle", PyPSP_ctrlSetSamplingCycle, METH_VARARGS, "" },
   { "ctrlGetSamplingCycle", PyPSP_ctrlGetSamplingCycle, METH_VARARGS, "" },
   { "ctrlSetSamplingMode", PyPSP_ctrlSetSamplingMode, METH_VARARGS, "" },
   { "ctrlGetSamplingMode", PyPSP_ctrlGetSamplingMode, METH_VARARGS, "" },
   { "ctrlPeekBufferPositive", PyPSP_ctrlPeekBufferPositive, METH_VARARGS, "" },
   { "ctrlReadBufferPositive", PyPSP_ctrlReadBufferPositive, METH_VARARGS, "" },

   /*
   { "audioInit", PyPSP_audioInit, METH_VARARGS,
     "Initializes the audio library" },
   { "audioSetChannelCallback", PyPSP_audioSetChannelCallback, METH_VARARGS,
     "Sets a channel audio callback" },
   */


   { "kernelDcacheWritebackAll", PyPSP_kernelDcacheWritebackAll, METH_VARARGS, "" },

   { "displaySetMode", PyPSP_displaySetMode, METH_VARARGS, "" },
   { "displayGetMode", PyPSP_displayGetMode, METH_VARARGS, "" },
   //{ "displaySetFrameBuf", PyPSP_displaySetFrameBuf, METH_VARARGS, "" },
   //{ "displayGetFrameBuf", PyPSP_displayGetFrameBuf, METH_VARARGS, "" },
   { "displayGetVcount", PyPSP_displayGetVcount, METH_VARARGS, "" },
   { "displayWaitVblankStart", PyPSP_displayWaitVblankStart, METH_VARARGS, "" },


   { NULL }
};

#ifndef PyMODINIT_FUNC	/* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif

PyMODINIT_FUNC init_psp(void)
{
    PyObject *mdl;

    mdl = Py_InitModule3("_psp", psp_functions, "Wrapper for the PSP native APIs");

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

    PyModule_AddIntConstant(mdl, "DISPLAY_PIXEL_FORMAT_565", PSP_DISPLAY_PIXEL_FORMAT_565);
    PyModule_AddIntConstant(mdl, "DISPLAY_PIXEL_FORMAT_5551", PSP_DISPLAY_PIXEL_FORMAT_5551);
    PyModule_AddIntConstant(mdl, "DISPLAY_PIXEL_FORMAT_4444", PSP_DISPLAY_PIXEL_FORMAT_4444);
    PyModule_AddIntConstant(mdl, "DISPLAY_PIXEL_FORMAT_8888", PSP_DISPLAY_PIXEL_FORMAT_8888);

    PyModule_AddIntConstant(mdl, "DISPLAY_SETBUF_IMMEDIATE", PSP_DISPLAY_SETBUF_IMMEDIATE);
    PyModule_AddIntConstant(mdl, "DISPLAY_SETBUF_NEXTFRAME", PSP_DISPLAY_SETBUF_NEXTFRAME);
}

#ifdef _GNUC
static const char* _rcsid_pspmodule __attribute__((unused)) = "$Id$";
#endif

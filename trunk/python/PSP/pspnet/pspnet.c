
#include <Python.h>

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspsdk.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pspnet.h>
#include <pspnet_inet.h>
#include <pspnet_apctl.h>
#include <pspnet_resolver.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <errno.h>

static PyObject* connect_to_apctl(PyObject *self, PyObject *args)
{
    int err, config = 1;
    int stateLast = -1;
    PyObject *callback = NULL, *ret;

    /* TODO: timeout */

    if (!PyArg_ParseTuple(args, "|iO", &config, &callback))
       return NULL;

    if (callback)
    {
       if (!PyCallable_Check(callback))
       {
          PyErr_SetString(PyExc_TypeError, "callback must be callable");
          return NULL;
       }
    }

    err = sceNetApctlConnect(config);
    if (err != 0)
    {
       PyErr_Format(PyExc_RuntimeError, "sceNetApctlConnect returns %08x\n", err);
       return NULL;
    }

    while (1)
    {
       int state;
       err = sceNetApctlGetState(&state);

       if (err != 0)
       {
          PyErr_Format(PyExc_RuntimeError, "sceNetApctlGetState returns %08x\n", err);
          return NULL;
       }

       if (state > stateLast)
       {
          if (callback)
          {
             ret = PyObject_CallFunction(callback, "i", state);
             if (!ret)
                return NULL;
             Py_XDECREF(ret);
          }

          stateLast = state;
       }

       if (state == 4)
          break;  // connected with static IP

       // wait a little before polling again
       sceKernelDelayThread(50 * 1000); // 50ms
    }

    if (callback)
    {
       ret = PyObject_CallFunction(callback, "i", -1);
       if (!ret)
          return NULL;
       Py_XDECREF(ret);
    }

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* disconnect_apctl(PyObject *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
       return NULL;

    sceNetApctlDisconnect();

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* get_ip(PyObject *self, PyObject *args)
{
    char ipaddr[32];

    if (!PyArg_ParseTuple(args, ""))
       return NULL;

    if (sceNetApctlGetInfo(8, ipaddr) != 0)
    {
       PyErr_SetString(PyExc_RuntimeError, "Could not get IP");
       return NULL;
    }

    return Py_BuildValue("s", ipaddr);
}

static PyMethodDef methods[] = {
   { "connectToAPCTL", (PyCFunction)connect_to_apctl, METH_VARARGS, "" },
   { "disconnectAPCTL", (PyCFunction)disconnect_apctl, METH_VARARGS, "" },
   { "getIP", (PyCFunction)get_ip, METH_VARARGS, "" },

   { NULL }
};

PyMODINIT_FUNC initpspnet(void)
{
    PyObject *mdl;

    mdl = Py_InitModule3("pspnet", methods, "PSP-specific net functions");
    if (!mdl)
       return;
}

#ifdef GNUC
static const char* _rcsid_pspnet __attribute__((unused)) = "$Id$";
#endif

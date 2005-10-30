
/**
 * @file controller.c
 */

/**********************************************************************

  Created: 30 Oct 2005

**********************************************************************/
// $Id$

#include "controller.h"

static void controller_dealloc(PyController *self)
{
    self->ob_type->tp_free((PyObject*)self);
}

static PyObject* controller_new(PyTypeObject *type,
                                PyObject *args,
                                PyObject *kwargs)
{
    PyController *self;

    self = (PyController*)type->tp_alloc(type, 0);

    if (self)
       memset(&self->data, 0, sizeof(self->data));

    return (PyObject*)self;
}

static int controller_init(PyController *self,
                           PyObject *args,
                           PyObject *kwargs)
{
    if (!PyArg_ParseTuple(args, ""))
       return -1;

    sceCtrlReadBufferPositive(&self->data, 1);

    return 0;
}

static PyObject* controller_getanalogx(PyController *self, void *closure)
{
    return Py_BuildValue("i", (int)self->data.Lx - 127);
}

static PyObject* controller_getanalogy(PyController *self, void *closure)
{
    return Py_BuildValue("i", (int)self->data.Ly - 127);
}

static PyObject* controller_getsquare(PyController *self, void *closure)
{
    PyObject* ret = (self->data.Buttons & PSP_CTRL_SQUARE) ? Py_True : Py_False;

    Py_INCREF(ret);
    return ret;
}

static PyObject* controller_gettriangle(PyController *self, void *closure)
{
    PyObject* ret = (self->data.Buttons & PSP_CTRL_TRIANGLE) ? Py_True : Py_False;

    Py_INCREF(ret);
    return ret;
}

static PyObject* controller_getcircle(PyController *self, void *closure)
{
    PyObject* ret = (self->data.Buttons & PSP_CTRL_CIRCLE) ? Py_True : Py_False;

    Py_INCREF(ret);
    return ret;
}

static PyObject* controller_getcross(PyController *self, void *closure)
{
    PyObject* ret = (self->data.Buttons & PSP_CTRL_CROSS) ? Py_True : Py_False;

    Py_INCREF(ret);
    return ret;
}

static PyObject* controller_getup(PyController *self, void *closure)
{
    PyObject* ret = (self->data.Buttons & PSP_CTRL_UP) ? Py_True : Py_False;

    Py_INCREF(ret);
    return ret;
}

static PyObject* controller_getdown(PyController *self, void *closure)
{
    PyObject* ret = (self->data.Buttons & PSP_CTRL_DOWN) ? Py_True : Py_False;

    Py_INCREF(ret);
    return ret;
}

static PyObject* controller_getleft(PyController *self, void *closure)
{
    PyObject* ret = (self->data.Buttons & PSP_CTRL_LEFT) ? Py_True : Py_False;

    Py_INCREF(ret);
    return ret;
}

static PyObject* controller_getright(PyController *self, void *closure)
{
    PyObject* ret = (self->data.Buttons & PSP_CTRL_RIGHT) ? Py_True : Py_False;

    Py_INCREF(ret);
    return ret;
}

static PyObject* controller_getstart(PyController *self, void *closure)
{
    PyObject* ret = (self->data.Buttons & PSP_CTRL_START) ? Py_True : Py_False;

    Py_INCREF(ret);
    return ret;
}

static PyObject* controller_getselect(PyController *self, void *closure)
{
    PyObject* ret = (self->data.Buttons & PSP_CTRL_SELECT) ? Py_True : Py_False;

    Py_INCREF(ret);
    return ret;
}

static PyObject* controller_getl(PyController *self, void *closure)
{
    PyObject* ret = (self->data.Buttons & PSP_CTRL_LTRIGGER) ? Py_True : Py_False;

    Py_INCREF(ret);
    return ret;
}

static PyObject* controller_getr(PyController *self, void *closure)
{
    PyObject* ret = (self->data.Buttons & PSP_CTRL_RTRIGGER) ? Py_True : Py_False;

    Py_INCREF(ret);
    return ret;
}

static PyGetSetDef controller_getset[] = {
   { "analogX", (getter)controller_getanalogx, NULL, "Analog pad X", NULL },
   { "analogY", (getter)controller_getanalogy, NULL, "Analog pad Y", NULL },
   { "square", (getter)controller_getsquare, NULL, "Square button.", NULL },
   { "triangle", (getter)controller_gettriangle, NULL, "Triangle button.", NULL },
   { "circle", (getter)controller_getcircle, NULL, "Circle button.", NULL },
   { "cross", (getter)controller_getcross, NULL, "Cross button.", NULL },
   { "up", (getter)controller_getup, NULL, "Up button.", NULL },
   { "down", (getter)controller_getdown, NULL, "Down button.", NULL },
   { "left", (getter)controller_getleft, NULL, "Left button.", NULL },
   { "right", (getter)controller_getright, NULL, "Right button.", NULL },
   { "start", (getter)controller_getstart, NULL, "Start button.", NULL },
   { "select", (getter)controller_getselect, NULL, "Select button.", NULL },
   { "l", (getter)controller_getl, NULL, "Left trigger.", NULL },
   { "r", (getter)controller_getr, NULL, "Right trigger.", NULL },

   { NULL }
};

static PyMethodDef controller_methods[] = {
   { NULL }
};

static PyTypeObject PyControllerType = {
   PyObject_HEAD_INIT(NULL)
   0,
   "psp2d.Controller",
   sizeof(PyController),
   0,
   (destructor)controller_dealloc,
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
   "Controller objects",
   0,
   0,
   0,
   0,
   0,
   0,
   controller_methods,
   0,
   controller_getset,
   0,
   0,
   0,
   0,
   0,
   (initproc)controller_init,
   0,
   controller_new,
};

PyTypeObject* PPyControllerType = &PyControllerType;

#ifdef _GNUC
static const char* _rcsid_controller __attribute__((unused)) = "$Id$";
#endif

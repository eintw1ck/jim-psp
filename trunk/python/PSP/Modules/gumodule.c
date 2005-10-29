
/**
 * @file gumodule.c
 */

/**********************************************************************

  Created: 02 Oct 2005

**********************************************************************/
// $Id$

#include "Python.h"
#include "matrix.h"

#include <pspgu.h>


/**************************************************************************/
// Matrix wrappers

static PyTypeObject* pMatrixType;

typedef struct
{
      PyObject_HEAD

      float *data;
} matrixObject;

static void matrix_dealloc(matrixObject *self)
{
    free(self->data);

    self->ob_type->tp_free((PyObject*)self);
}

static PyObject* matrix_new(PyTypeObject *type,
                            PyObject *args,
                            PyObject *kwargs)
{
    matrixObject *self;

    self = (matrixObject*)type->tp_alloc(type, 0);
    if (self)
    {
       self->data = (float*)malloc(sizeof(float) * 16);
    }

    return (PyObject*)self;
}

static int matrix_init(matrixObject *self,
                       PyObject *args,
                       PyObject *kwargs)
{
    float f[16];

    if (!PyArg_ParseTuple(args, "|ffffffffffffffff", f, f+1, f+2,
                          f+3, f+4, f+5, f+6, f+7, f+8, f+9, f+10,
                          f+11, f+12, f+13, f+14, f+15))
       return -1;

    memcpy(self->data, f, sizeof(f));

    return 0;
}

static PyObject* Py_matrix_identity(matrixObject *self,
                                    PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":identity"))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    matrix_identity(self->data);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Py_matrix_multiply(matrixObject *self,
                                    PyObject *args)
{
    matrixObject *other;

    if (!PyArg_ParseTuple(args, "O:multiply", &other))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    if (other->ob_type != pMatrixType)
    {
       PyErr_SetString(PyExc_TypeError, "Argument must be a Matrix");
       return NULL;
    }

    matrix_multiply(self->data, self->data, other->data);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Py_matrix_projection(matrixObject *self,
                                      PyObject *args)
{
    float fovy, aspect, near, far;

    if (!PyArg_ParseTuple(args, "ffff:projection", &fovy, &aspect, &near, &far))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    matrix_projection(self->data, fovy, aspect, near, far);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Py_matrix_translate(matrixObject *self,
                                     PyObject *args)
{
    float x, y, z;

    if (!PyArg_ParseTuple(args, "fff:translate", &x, &y, &z))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    matrix_translate(self->data, x, y, z);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Py_matrix_setrotatex(matrixObject *self,
                                      PyObject *args)
{
    float v;

    if (!PyArg_ParseTuple(args, "f:setrotatex", &v))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    matrix_setrotatex(self->data, v);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Py_matrix_setrotatey(matrixObject *self,
                                      PyObject *args)
{
    float v;

    if (!PyArg_ParseTuple(args, "f:setrotatey", &v))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    matrix_setrotatey(self->data, v);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Py_matrix_setrotatez(matrixObject *self,
                                      PyObject *args)
{
    float v;

    if (!PyArg_ParseTuple(args, "f:setrotatez", &v))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    matrix_setrotatez(self->data, v);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Py_matrix_rotate(matrixObject *self,
                                  PyObject *args)
{
    float x, y, z;

    if (!PyArg_ParseTuple(args, "fff:rotate", &x, &y, &z))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    matrix_rotate(self->data, x, y, z);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef matrix_methods[] = {
   { "identity", (PyCFunction)Py_matrix_identity, METH_VARARGS, "" },
   { "projection", (PyCFunction)Py_matrix_projection, METH_VARARGS, "" },
   { "multiply", (PyCFunction)Py_matrix_multiply, METH_VARARGS, "" },
   { "translate", (PyCFunction)Py_matrix_translate, METH_VARARGS, "" },
   { "setrotatex", (PyCFunction)Py_matrix_setrotatex, METH_VARARGS, "" },
   { "setrotatey", (PyCFunction)Py_matrix_setrotatey, METH_VARARGS, "" },
   { "setrotatez", (PyCFunction)Py_matrix_setrotatez, METH_VARARGS, "" },
   { "rotate", (PyCFunction)Py_matrix_rotate, METH_VARARGS, "" },

   { NULL }
};

static PyTypeObject matrixType = {
   PyObject_HEAD_INIT(NULL)
   0,
   "gu.Matrix",
   sizeof(matrixObject),
   0,
   (destructor)matrix_dealloc,
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
   "Matrix helper objects",
   0,
   0,
   0,
   0,
   0,
   0,
   matrix_methods,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   (initproc)matrix_init,
   0,
   matrix_new,
};

/**************************************************************************/
// Display context wrapper

typedef struct
{
      PyObject_HEAD

      unsigned int __attribute__((aligned(16))) list[262144];
} contextObject;

static void context_dealloc(contextObject *self)
{
    self->ob_type->tp_free((PyObject*)self);
}

static PyObject* context_new(PyTypeObject *type,
                             PyObject *args,
                             PyObject *kwargs)
{
    contextObject *self;

    self = (contextObject*)type->tp_alloc(type, 0);

    return (PyObject*)self;
}

static int context_init(contextObject *self,
                        PyObject *args,
                        PyObject *kwargs)
{
    if (!PyArg_ParseTuple(args, ""))
       return -1;

    return 0;
}

static PyMethodDef context_methods[] = {
   { NULL }
};

static PyTypeObject contextType = {
   PyObject_HEAD_INIT(NULL)
   0,
   "gu.Context",
   sizeof(contextObject),
   0,
   (destructor)context_dealloc,
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
   "Display context objects",
   0,
   0,
   0,
   0,
   0,
   0,
   context_methods,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   (initproc)context_init,
   0,
   context_new,
};

/**************************************************************************/

static PyObject* Pygu_init(PyObject *self,
                           PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":init"))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuInit();

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_term(PyObject *self,
                           PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":term"))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuTerm();

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_start(PyObject *self,
                            PyObject *args)
{
    contextObject *context;
    int kind;

    if (!PyArg_ParseTuple(args, "Oi:start", &context, &kind))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    if (context->ob_type != &contextType)
    {
       PyErr_SetString(PyExc_TypeError, "Argument must be a Context");
       return NULL;
    }

    sceGuStart(kind, context->list);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_drawBuffer(PyObject *self,
                                 PyObject *args)
{
    int psm, fbp, fbw;

    if (!PyArg_ParseTuple(args, "iii:drawBuffer", &psm, &fbp, &fbw))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuDrawBuffer(psm, (void*)fbp, fbw);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_dispBuffer(PyObject *self,
                                 PyObject *args)
{
    int width, height, dispbp, dispbw;

    if (!PyArg_ParseTuple(args, "iiii:dispBuffer", &width, &height, &dispbp, &dispbw))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuDispBuffer(width, height, (void*)dispbp, dispbw);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_depthBuffer(PyObject *self,
                                  PyObject *args)
{
    int zbp, zbw;

    if (!PyArg_ParseTuple(args, "ii:depthBuffer", &zbp, &zbw))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuDepthBuffer((void*)zbp, zbw);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_offset(PyObject *self,
                             PyObject *args)
{
    int x, y;

    if (!PyArg_ParseTuple(args, "ii:offset", &x, &y))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuOffset(x, y);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_viewport(PyObject *self,
                               PyObject *args)
{
    int x, y, w, h;

    if (!PyArg_ParseTuple(args, "iiii:viewport", &x, &y, &w, &h))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuViewport(x, y, w, h);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_depthRange(PyObject *self,
                                 PyObject *args)
{
    int near, far;

    if (!PyArg_ParseTuple(args, "ii:depthRange", &near, &far))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuDepthRange(near, far);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_scissor(PyObject *self,
                              PyObject *args)
{
    int x, y, w, h;

    if (!PyArg_ParseTuple(args, "iiii:scissor", &x, &y, &w, &h))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuScissor(x, y, w, h);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_enable(PyObject *self,
                             PyObject *args)
{
    int state;

    if (!PyArg_ParseTuple(args, "i:enable", &state))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuEnable(state);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_depthFunc(PyObject *self,
                                PyObject *args)
{
    int func;

    if (!PyArg_ParseTuple(args, "i:depthFunc", &func))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuDepthFunc(func);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_frontFace(PyObject *self,
                                PyObject *args)
{
    int order;

    if (!PyArg_ParseTuple(args, "i:frontFace", &order))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuFrontFace(order);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_shadeModel(PyObject *self,
                                 PyObject *args)
{
    int mode;

    if (!PyArg_ParseTuple(args, "i:shadeModel", &mode))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuShadeModel(mode);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_finish(PyObject *self,
                             PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":finish"))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuFinish();

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_sync(PyObject *self,
                           PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":sync"))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuSync(0, 0);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_display(PyObject *self,
                              PyObject *args)
{
    int state;

    if (!PyArg_ParseTuple(args, "i:display", &state))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuDisplay(state);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_clearColor(PyObject *self,
                                 PyObject *args)
{
    unsigned long color;

    if (!PyArg_ParseTuple(args, "k:clearColor", &color))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuClearColor((unsigned int)(color & 0xFFFFFFFF));

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_clearDepth(PyObject *self,
                                 PyObject *args)
{
    int depth;

    if (!PyArg_ParseTuple(args, "i:clearDepth", &depth))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuClearDepth(depth);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_light(PyObject *self,
                            PyObject *args)
{
    int light, type, components;
    ScePspFVector3 v;

    if (!PyArg_ParseTuple(args, "iii(fff):light", &light, &type, &components,
                          &v.x, &v.y, &v.z))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuLight(light, type, components, &v);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_lightColor(PyObject *self,
                                 PyObject *args)
{
    int light, component;
    unsigned long color;

    if (!PyArg_ParseTuple(args, "iik:lightColor", &light, &component, &color))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuLightColor(light, component, (unsigned int)(color & 0xFFFFFFFF));

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_clear(PyObject *self,
                            PyObject *args)
{
    int flags;

    if (!PyArg_ParseTuple(args, "i:clear", &flags))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuClear(flags);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_specular(PyObject *self,
                               PyObject *args)
{
    float power;

    if (!PyArg_ParseTuple(args, "f:specular", &power))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuSpecular(power);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_setMatrix(PyObject *self,
                                PyObject *args)
{
    matrixObject *matrix;
    int type;

    if (!PyArg_ParseTuple(args, "iO:setMatrix", &type, &matrix))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    if (matrix->ob_type != &matrixType)
    {
       PyErr_SetString(PyExc_TypeError, "Argument 2 must be a Matrix");
       return NULL;
    }

    sceGuSetMatrix(type, (ScePspFMatrix4*)matrix->data);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_ambientColor(PyObject *self,
                                   PyObject *args)
{
    unsigned long color;

    if (!PyArg_ParseTuple(args, "k:ambientColor", &color))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuAmbientColor((unsigned int)(color & 0xFFFFFFFF));

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_morphWeight(PyObject *self,
                                  PyObject *args)
{
    int index;
    float weight;

    if (!PyArg_ParseTuple(args, "if:morphWeight", &index, &weight))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuMorphWeight(index, weight);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_drawArray(PyObject *self,
                                PyObject *args)
{
    // TODO: use lists of indices/vertex instead of buffer
    void *bf_ind, *bf_ver;
    int sz_ind, sz_ver;

    int prim, vtype, count;

    if (!PyArg_ParseTuple(args, "iiis#s#:drawArray", &prim, &vtype, &count, &bf_ind, &sz_ind, &bf_ver, &sz_ver))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuDrawArray(prim, vtype, count, (void*)bf_ind, (void*)bf_ver);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_swapBuffers(PyObject *self,
                                  PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":swapBuffers"))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuSwapBuffers();

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_WEIGHTS(PyObject *self,
                              PyObject *args)
{
    int p;

    if (!PyArg_ParseTuple(args, "i:WEIGHTS", &p))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    return Py_BuildValue("i", GU_WEIGHTS(p));
}

static PyObject* Pygu_VERTICES(PyObject *self,
                               PyObject *args)
{
    int p;

    if (!PyArg_ParseTuple(args, "i:VERTICES", &p))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    return Py_BuildValue("i", GU_VERTICES(p));
}

/**************************************************************************/

static PyMethodDef gu_functions[] = {
   { "init", Pygu_init, METH_VARARGS, "" },
   { "term", Pygu_term, METH_VARARGS, "" },
   { "start", Pygu_start, METH_VARARGS, "" },
   { "drawBuffer", Pygu_drawBuffer, METH_VARARGS, "" },
   { "dispBuffer", Pygu_dispBuffer, METH_VARARGS, "" },
   { "depthBuffer", Pygu_depthBuffer, METH_VARARGS, "" },
   { "offset", Pygu_offset, METH_VARARGS, "" },
   { "viewport", Pygu_viewport, METH_VARARGS, "" },
   { "depthRange", Pygu_depthRange, METH_VARARGS, "" },
   { "scissor", Pygu_scissor, METH_VARARGS, "" },
   { "enable", Pygu_enable, METH_VARARGS, "" },
   { "depthFunc", Pygu_depthFunc, METH_VARARGS, "" },
   { "frontFace", Pygu_frontFace, METH_VARARGS, "" },
   { "shadeModel", Pygu_shadeModel, METH_VARARGS, "" },
   { "finish", Pygu_finish, METH_VARARGS, "" },
   { "sync", Pygu_sync, METH_VARARGS, "" },
   { "display", Pygu_display, METH_VARARGS, "" },
   { "clearColor", Pygu_clearColor, METH_VARARGS, "" },
   { "clearDepth", Pygu_clearDepth, METH_VARARGS, "" },
   { "light", Pygu_light, METH_VARARGS, "" },
   { "lightColor", Pygu_lightColor, METH_VARARGS, "" },
   { "clear", Pygu_clear, METH_VARARGS, "" },
   { "specular", Pygu_specular, METH_VARARGS, "" },
   { "setMatrix", Pygu_setMatrix, METH_VARARGS, "" },
   { "ambientColor", Pygu_ambientColor, METH_VARARGS, "" },
   { "morphWeight", Pygu_morphWeight, METH_VARARGS, "" },
   { "drawArray", Pygu_drawArray, METH_VARARGS, "" },
   { "swapBuffers", Pygu_swapBuffers, METH_VARARGS, "" },

   { "WEIGHTS", Pygu_WEIGHTS, METH_VARARGS, "" },
   { "VERTICES", Pygu_VERTICES, METH_VARARGS, "" },

   { NULL }
};

#ifndef PyMODINIT_FUNC	/* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif

PyMODINIT_FUNC initgu(void)
{
    PyObject *mdl;

    if (PyType_Ready(&matrixType) < 0)
       return;

    if (PyType_Ready(&contextType) < 0)
       return;

    mdl = Py_InitModule3("gu", gu_functions, "Graphics library");

    if (!mdl)
       return;

    pMatrixType = &matrixType;

    Py_INCREF(&matrixType);
    PyModule_AddObject(mdl, "Matrix", (PyObject*)&matrixType);

    Py_INCREF(&contextType);
    PyModule_AddObject(mdl, "Context", (PyObject*)&contextType);

    PyModule_AddIntConstant(mdl, "DIRECT", GU_DIRECT);
    PyModule_AddIntConstant(mdl, "CALL", GU_CALL);
    PyModule_AddIntConstant(mdl, "SEND", GU_SEND);

    PyModule_AddIntConstant(mdl, "ALPHA_TEST", GU_ALPHA_TEST);
    PyModule_AddIntConstant(mdl, "DEPTH_TEST", GU_DEPTH_TEST);
    PyModule_AddIntConstant(mdl, "SCISSOR_TEST", GU_SCISSOR_TEST);
    PyModule_AddIntConstant(mdl, "BLEND", GU_BLEND);
    PyModule_AddIntConstant(mdl, "CULL_FACE", GU_CULL_FACE);
    PyModule_AddIntConstant(mdl, "DITHER", GU_DITHER);
    PyModule_AddIntConstant(mdl, "CLIP_PLANES", GU_CLIP_PLANES);
    PyModule_AddIntConstant(mdl, "TEXTURE_2D", GU_TEXTURE_2D);
    PyModule_AddIntConstant(mdl, "LIGHTING", GU_LIGHTING);
    PyModule_AddIntConstant(mdl, "LIGHT0", GU_LIGHT0);
    PyModule_AddIntConstant(mdl, "LIGHT1", GU_LIGHT1);
    PyModule_AddIntConstant(mdl, "LIGHT2", GU_LIGHT2);
    PyModule_AddIntConstant(mdl, "LIGHT3", GU_LIGHT3);
    PyModule_AddIntConstant(mdl, "COLOR_LOGIC_OP", GU_COLOR_LOGIC_OP);

    PyModule_AddIntConstant(mdl, "NEVER", GU_NEVER);
    PyModule_AddIntConstant(mdl, "ALWAYS", GU_ALWAYS);
    PyModule_AddIntConstant(mdl, "EQUAL", GU_EQUAL);
    PyModule_AddIntConstant(mdl, "NOTEQUAL", GU_NOTEQUAL);
    PyModule_AddIntConstant(mdl, "LESS", GU_LESS);
    PyModule_AddIntConstant(mdl, "LEQUAL", GU_LEQUAL);
    PyModule_AddIntConstant(mdl, "GREATER", GU_GREATER);
    PyModule_AddIntConstant(mdl, "GEQUAL", GU_GEQUAL);

    PyModule_AddIntConstant(mdl, "CW", GU_CW);
    PyModule_AddIntConstant(mdl, "CCW", GU_CCW);

    PyModule_AddIntConstant(mdl, "FLAT", GU_FLAT);
    PyModule_AddIntConstant(mdl, "SMOOTH", GU_SMOOTH);

    PyModule_AddIntConstant(mdl, "DIRECTIONAL", GU_DIRECTIONAL);
    PyModule_AddIntConstant(mdl, "POINTLIGHT", GU_POINTLIGHT);
    PyModule_AddIntConstant(mdl, "SPOTLIGHT", GU_SPOTLIGHT);

    PyModule_AddIntConstant(mdl, "AMBIENT", GU_AMBIENT);
    PyModule_AddIntConstant(mdl, "DIFFUSE", GU_DIFFUSE);
    PyModule_AddIntConstant(mdl, "SPECULAR", GU_SPECULAR);
    PyModule_AddIntConstant(mdl, "AMBIENT_AND_DIFFUSE", GU_AMBIENT_AND_DIFFUSE);
    PyModule_AddIntConstant(mdl, "DIFFUSE_AND_SPECULAR", GU_DIFFUSE_AND_SPECULAR);
    PyModule_AddIntConstant(mdl, "UNKNOWN_LIGHT_COMPONENT", GU_UNKNOWN_LIGHT_COMPONENT);

    PyModule_AddIntConstant(mdl, "COLOR_BUFFER_BIT", GU_COLOR_BUFFER_BIT);
    PyModule_AddIntConstant(mdl, "DEPTH_BUFFER_BIT", GU_DEPTH_BUFFER_BIT);

    PyModule_AddIntConstant(mdl, "COLOR_BUFFER_BIT", GU_COLOR_BUFFER_BIT);
    PyModule_AddIntConstant(mdl, "DEPTH_BUFFER_BIT", GU_DEPTH_BUFFER_BIT);

    PyModule_AddIntConstant(mdl, "PROJECTION", GU_PROJECTION);
    PyModule_AddIntConstant(mdl, "VIEW", GU_VIEW);
    PyModule_AddIntConstant(mdl, "MODEL", GU_MODEL);
    PyModule_AddIntConstant(mdl, "TEXTURE", GU_TEXTURE);

    PyModule_AddIntConstant(mdl, "POINTS", GU_POINTS);
    PyModule_AddIntConstant(mdl, "LINES", GU_LINES);
    PyModule_AddIntConstant(mdl, "LINE_STRIP", GU_LINE_STRIP);
    PyModule_AddIntConstant(mdl, "TRIANGLES", GU_TRIANGLES);
    PyModule_AddIntConstant(mdl, "TRIANGLE_STRIP", GU_TRIANGLE_STRIP);
    PyModule_AddIntConstant(mdl, "TRIANGLE_FAN", GU_TRIANGLE_FAN);
    PyModule_AddIntConstant(mdl, "SPRITES", GU_SPRITES);

    PyModule_AddIntConstant(mdl, "TEXTURE_8BIT", GU_TEXTURE_8BIT);
    PyModule_AddIntConstant(mdl, "TEXTURE_16BIT", GU_TEXTURE_16BIT);
    PyModule_AddIntConstant(mdl, "TEXTURE_32BITF", GU_TEXTURE_32BITF);

    PyModule_AddIntConstant(mdl, "COLOR_5650", GU_COLOR_5650);
    PyModule_AddIntConstant(mdl, "COLOR_5551", GU_COLOR_5551);
    PyModule_AddIntConstant(mdl, "COLOR_4444", GU_COLOR_4444);
    PyModule_AddIntConstant(mdl, "COLOR_8888", GU_COLOR_8888);

    PyModule_AddIntConstant(mdl, "NORMAL_8BIT", GU_NORMAL_8BIT);
    PyModule_AddIntConstant(mdl, "NORMAL_16BIT", GU_NORMAL_16BIT);
    PyModule_AddIntConstant(mdl, "NORMAL_32BITF", GU_NORMAL_32BITF);

    PyModule_AddIntConstant(mdl, "VERTEX_8BIT", GU_VERTEX_8BIT);
    PyModule_AddIntConstant(mdl, "VERTEX_16BIT", GU_VERTEX_16BIT);
    PyModule_AddIntConstant(mdl, "VERTEX_32BITF", GU_VERTEX_32BITF);

    PyModule_AddIntConstant(mdl, "WEIGHT_8BIT", GU_WEIGHT_8BIT);
    PyModule_AddIntConstant(mdl, "WEIGHT_16BIT", GU_WEIGHT_16BIT);
    PyModule_AddIntConstant(mdl, "WEIGHT_32BITF", GU_WEIGHT_32BITF);

    PyModule_AddIntConstant(mdl, "INDEX_8BIT", GU_INDEX_8BIT);
    PyModule_AddIntConstant(mdl, "INDEX_16BIT", GU_INDEX_16BIT);

    PyModule_AddIntConstant(mdl, "TRANSFORM_2D", GU_TRANSFORM_2D);
    PyModule_AddIntConstant(mdl, "TRANSFORM_3D", GU_TRANSFORM_3D);

    PyModule_AddIntConstant(mdl, "PSM_8888", GU_PSM_8888);
}

#ifdef _GNUC
static const char* _rcsid_gumodule __attribute__((unused)) = "$Id$";
#endif

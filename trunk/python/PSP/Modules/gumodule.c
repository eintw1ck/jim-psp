
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

// TODO:

// sceGuBreak
// sceGuContinue
// sceGuSetCallback
// sceGuSignal
// sceGuGetMemory
// sceGuSendList
// sceGuBeginObject
// sceGuEndObject
// sceGuLightMode
// sceGuLightSpot
// sceGuAmbient
// sceGuAmbientColor
// sceGuMaterial
// sceGuModelColor
// sceGuSetDither
// sceGuCopyImage
// sceGuTexImage
// sceGuTexLevelMode
// sceGuTexScale
// sceGuTexClose
// sceGuTexSync
// sceGuClutLoad
// sceGuClutMode
// sceGuDrawBezier
// sceGuPatchDivide
// sceGuPatchFrontFace
// sceGuPatchPrim
// sceGuSpriteMode


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

#ifdef CHECKTYPE
    if (other->ob_type != pMatrixType)
    {
       PyErr_SetString(PyExc_TypeError, "Argument must be a Matrix");
       return NULL;
    }
#endif

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

#ifdef CHECKTYPE
    if (context->ob_type != &contextType)
    {
       PyErr_SetString(PyExc_TypeError, "Argument must be a Context");
       return NULL;
    }
#endif

    sceGuStart(kind, context->list);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_callList(PyObject *self,
                               PyObject *args)
{
    contextObject *context;

    if (!PyArg_ParseTuple(args, "O:callList", &context))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

#ifdef CHECKTYPE
    if (context->ob_type != &contextType)
    {
       PyErr_SetString(PyExc_TypeError, "Argument must be a Context");
       return NULL;
    }
#endif

    sceGuCallList(context->list);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_checkList(PyObject *self,
                                PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":checkList"))
       return NULL;

    return Py_BuildValue("i", sceGuCheckList());
}

static PyObject* Pygu_callMode(PyObject *self,
                               PyObject *args)
{
    int mode;

    if (!PyArg_ParseTuple(args, "i:callMode", &mode))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuCallMode(mode);

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

static PyObject* Pygu_drawBufferList(PyObject *self,
                                     PyObject *args)
{
    int psm, fbp, fbw;

    if (!PyArg_ParseTuple(args, "iii:drawBufferList", &psm, &fbp, &fbw))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuDrawBufferList(psm, (void*)fbp, fbw);

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

static PyObject* Pygu_fog(PyObject *self,
                          PyObject *args)
{
    int near, far, r, g, b, a = 0;
    u32 color;

    if (!PyArg_ParseTuple(args, "iiiii|i:fog", &near, &far, &r, &g, &b, &a))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    color = (a << 24) | (b << 16) | (g << 8) | r;

    sceGuFog(near, far, color);

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

static PyObject* Pygu_disable(PyObject *self,
                              PyObject *args)
{
    int state;

    if (!PyArg_ParseTuple(args, "i:disable", &state))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuDisable(state);

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

static PyObject* Pygu_depthMask(PyObject *self,
                                PyObject *args)
{
    int mask;

    if (!PyArg_ParseTuple(args, "i:depthMask", &mask))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuDepthMask(mask);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_depthOffset(PyObject *self,
                                  PyObject *args)
{
    int offset;

    if (!PyArg_ParseTuple(args, "i:depthOffset", &offset))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuDepthOffset(offset);

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

    return Py_BuildValue("i", sceGuDisplay(state ? GU_TRUE : GU_FALSE));
}

static PyObject* Pygu_clearColor(PyObject *self,
                                 PyObject *args)
{
    int r, g, b, a = 0;
    u32 color;

    if (!PyArg_ParseTuple(args, "iii|i:clearColor", &r, &g, &b, &a))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    color = (a << 24) | (b << 16) | (g << 8) | r;

    sceGuClearColor(color);

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

static PyObject* Pygu_clearStencil(PyObject *self,
                                   PyObject *args)
{
    int stencil;

    if (!PyArg_ParseTuple(args, "i:clearStencil", &stencil))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuClearStencil(stencil);

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

static PyObject* Pygu_lightAtt(PyObject *self,
                               PyObject *args)
{
    int light;
    float atten0, atten1, atten2;

    if (!PyArg_ParseTuple(args, "ifff:lightAtt", &light, &atten0,
                          &atten1, &atten2))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuLightAtt(light, atten0, atten1, atten2);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_lightColor(PyObject *self,
                                 PyObject *args)
{
    int light, component, r, g, b, a = 0;
    u32 color;

    if (!PyArg_ParseTuple(args, "iiiii|i:lightColor", &light, &component, &r, &g, &b, &a))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    color = (a << 24) | (b << 16) | (g << 8) | r;

    sceGuLightColor(light, component, color);

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

#ifdef CHECKTYPE
    if (matrix->ob_type != &matrixType)
    {
       PyErr_SetString(PyExc_TypeError, "Argument 2 must be a Matrix");
       return NULL;
    }
#endif

    sceGuSetMatrix(type, (ScePspFMatrix4*)matrix->data);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_boneMatrix(PyObject *self,
                                 PyObject *args)
{
    matrixObject *matrix;
    int index;

    if (!PyArg_ParseTuple(args, "iO:boneMatrix", &index, &matrix))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

#ifdef CHECKTYPE
    if (matrix->ob_type != &matrixType)
    {
       PyErr_SetString(PyExc_TypeError, "Argument 2 must be a Matrix");
       return NULL;
    }
#endif

    sceGuBoneMatrix(index, (ScePspFMatrix4*)matrix->data);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_ambientColor(PyObject *self,
                                   PyObject *args)
{
    int r, g, b, a = 0;
    u32 color;

    if (!PyArg_ParseTuple(args, "iii|i:ambientColor", &r, &g, &b, &a))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    color = (a << 24) | (b << 16) | (g << 8) | r;

    sceGuAmbientColor(color);

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

static PyObject* Pygu_sendCommandf(PyObject *self,
                                   PyObject *args)
{
    int cmd;
    float arg;

    if (!PyArg_ParseTuple(args, "if:sendCommandf", &cmd, &arg))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuSendCommandf(cmd, arg);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_sendCommandi(PyObject *self,
                                   PyObject *args)
{
    int cmd, arg;

    if (!PyArg_ParseTuple(args, "ii:sendCommandi", &cmd, &arg))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuSendCommandi(cmd, arg);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_setStatus(PyObject *self,
                                PyObject *args)
{
    int state, status;

    if (!PyArg_ParseTuple(args, "ii:setStatus", &state, &status))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuSetStatus(state, status);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_getStatus(PyObject *self,
                                PyObject *args)
{
    int state;

    if (!PyArg_ParseTuple(args, "i:getStatus", &state))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    return Py_BuildValue("i", sceGuGetStatus(state));
}

static PyObject* Pygu_setAllStatus(PyObject *self,
                                   PyObject *args)
{
    int status;

    if (!PyArg_ParseTuple(args, "i:setAllStatus", &status))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuSetAllStatus(status);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_getAllStatus(PyObject *self,
                                   PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":getAllStatus"))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    return Py_BuildValue("i", sceGuGetAllStatus());
}

static PyObject* Pygu_pixelMask(PyObject *self,
                                PyObject *args)
{
    unsigned int mask;

    if (!PyArg_ParseTuple(args, "i:pixelMask", &mask))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuPixelMask(mask);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_color(PyObject *self,
                            PyObject *args)
{
    int r, g, b, a = 0;
    u32 color;

    if (!PyArg_ParseTuple(args, "iii|i:color", &r, &g, &b, &a))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    color = (a << 24) | (b << 16) | (g << 8) | r;

    sceGuColor(color);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_colorFunc(PyObject *self,
                                PyObject *args)
{
    int r, g, b, a = 0;
    int func;
    u32 mask, color;

    if (!PyArg_ParseTuple(args, "iiiii|i:colorFunc", &func, &mask, &r, &g, &b, &a))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    color = (a << 24) | (b << 16) | (g << 8) | r;

    sceGuColorFunc(func, color, mask);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_colorMaterial(PyObject *self,
                                    PyObject *args)
{
    int comp;

    if (!PyArg_ParseTuple(args, "i:colorMaterial", &comp))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuColorMaterial(comp);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_alphaFunc(PyObject *self,
                                PyObject *args)
{
    int func, value, mask;

    if (!PyArg_ParseTuple(args, "iii:alphaFunc", &func, &value, &mask))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuAlphaFunc(func, value, mask);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_blendFunc(PyObject *self,
                                PyObject *args)
{
    int op, src, dest;
    u32 srcfix, destfix;

    if (!PyArg_ParseTuple(args, "iiiii:blendFunc", &op, &src, &dest, &srcfix, &destfix))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuBlendFunc(op, src, dest, srcfix, destfix);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_stencilFunc(PyObject *self,
                                  PyObject *args)
{
    int func, ref, mask;

    if (!PyArg_ParseTuple(args, "iii:stencilFunc", &func, &ref, &mask))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuStencilFunc(func, ref, mask);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_stencilOp(PyObject *self,
                                PyObject *args)
{
    int fail, zfail, zpass;

    if (!PyArg_ParseTuple(args, "iii:stencilOp", &fail, &zfail, &zpass))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuStencilOp(fail, zfail, zpass);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_logicalOp(PyObject *self,
                                PyObject *args)
{
    int op;

    if (!PyArg_ParseTuple(args, "i:logicalOp", &op))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuLogicalOp(op);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_texEnvColor(PyObject *self,
                                  PyObject *args)
{
    int r, g, b, a = 0;
    u32 color;

    if (!PyArg_ParseTuple(args, "iii|i:texEnvColor", &r, &g, &b, &a))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    color = (a << 24) | (b << 16) | (g << 8) | r;

    sceGuTexEnvColor(color);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_texFilter(PyObject *self,
                                PyObject *args)
{
    int min, mag;

    if (!PyArg_ParseTuple(args, "ii:texFilter", &min, &mag))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuTexFilter(min, mag);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_texFlush(PyObject *self,
                               PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":texFlush"))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuTexFlush();

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_texFunc(PyObject *self,
                              PyObject *args)
{
    int tfx, tcc;

    if (!PyArg_ParseTuple(args, "ii:texFunc", &tfx, &tcc))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuTexFunc(tfx, tcc);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_texMapMode(PyObject *self,
                                 PyObject *args)
{
    int mode;

    if (!PyArg_ParseTuple(args, "i:texMapMode", &mode))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuTexMapMode(mode, 0, 0);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_texMode(PyObject *self,
                              PyObject *args)
{
    int tpsm, maxmips, swizzle;

    if (!PyArg_ParseTuple(args, "iii:texMode", &tpsm, &maxmips, &swizzle))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuTexMode(tpsm, maxmips, 0, swizzle);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_texOffset(PyObject *self,
                                PyObject *args)
{
    float u, v;

    if (!PyArg_ParseTuple(args, "ff:texOffset", &u, &v))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuTexOffset(u, v);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_texProjMapMode(PyObject *self,
                                     PyObject *args)
{
    int mode;

    if (!PyArg_ParseTuple(args, "i:texProjMapMode", &mode))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuTexProjMapMode(mode);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* Pygu_texWrap(PyObject *self,
                              PyObject *args)
{
    float u, v;

    if (!PyArg_ParseTuple(args, "ff:texWrap", &u, &v))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceGuTexWrap(u, v);

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

static PyObject* Pygu_TEXTURE_SHIFT(PyObject *self,
                                    PyObject *args)
{
    int n;

    if (!PyArg_ParseTuple(args, "i", &n))
       return NULL;

    return Py_BuildValue("i", GU_TEXTURE_SHIFT(n));
}

static PyObject* Pygu_COLOR_SHIFT(PyObject *self,
                                  PyObject *args)
{
    int n;

    if (!PyArg_ParseTuple(args, "i", &n))
       return NULL;

    return Py_BuildValue("i", GU_COLOR_SHIFT(n));
}

static PyObject* Pygu_NORMAL_SHIFT(PyObject *self,
                                   PyObject *args)
{
    int n;

    if (!PyArg_ParseTuple(args, "i", &n))
       return NULL;

    return Py_BuildValue("i", GU_NORMAL_SHIFT(n));
}

static PyObject* Pygu_VERTEX_SHIFT(PyObject *self,
                                   PyObject *args)
{
    int n;

    if (!PyArg_ParseTuple(args, "i", &n))
       return NULL;

    return Py_BuildValue("i", GU_VERTEX_SHIFT(n));
}

static PyObject* Pygu_WEIGHT_SHIFT(PyObject *self,
                                   PyObject *args)
{
    int n;

    if (!PyArg_ParseTuple(args, "i", &n))
       return NULL;

    return Py_BuildValue("i", GU_WEIGHT_SHIFT(n));
}

static PyObject* Pygu_INDEX_SHIFT(PyObject *self,
                                  PyObject *args)
{
    int n;

    if (!PyArg_ParseTuple(args, "i", &n))
       return NULL;

    return Py_BuildValue("i", GU_INDEX_SHIFT(n));
}

static PyObject* Pygu_TRANSFORM_SHIFT(PyObject *self,
                                      PyObject *args)
{
    int n;

    if (!PyArg_ParseTuple(args, "i", &n))
       return NULL;

    return Py_BuildValue("i", GU_TRANSFORM_SHIFT(n));
}

/**************************************************************************/

static PyMethodDef gu_functions[] = {
   { "init", Pygu_init, METH_VARARGS, "" },
   { "term", Pygu_term, METH_VARARGS, "" },
   { "start", Pygu_start, METH_VARARGS, "" },
   { "callList", Pygu_callList, METH_VARARGS, "" },
   { "checkList", Pygu_checkList, METH_VARARGS, "" },
   { "callMode", Pygu_callMode, METH_VARARGS, "" },
   { "drawBuffer", Pygu_drawBuffer, METH_VARARGS, "" },
   { "drawBufferList", Pygu_drawBufferList, METH_VARARGS, "" },
   { "dispBuffer", Pygu_dispBuffer, METH_VARARGS, "" },
   { "depthBuffer", Pygu_depthBuffer, METH_VARARGS, "" },
   { "offset", Pygu_offset, METH_VARARGS, "" },
   { "viewport", Pygu_viewport, METH_VARARGS, "" },
   { "scissor", Pygu_scissor, METH_VARARGS, "" },
   { "enable", Pygu_enable, METH_VARARGS, "" },
   { "disable", Pygu_disable, METH_VARARGS, "" },
   { "depthFunc", Pygu_depthFunc, METH_VARARGS, "" },
   { "depthMask", Pygu_depthMask, METH_VARARGS, "" },
   { "depthOffset", Pygu_depthOffset, METH_VARARGS, "" },
   { "depthRange", Pygu_depthRange, METH_VARARGS, "" },
   { "fog", Pygu_fog, METH_VARARGS, "" },
   { "frontFace", Pygu_frontFace, METH_VARARGS, "" },
   { "shadeModel", Pygu_shadeModel, METH_VARARGS, "" },
   { "finish", Pygu_finish, METH_VARARGS, "" },
   { "sync", Pygu_sync, METH_VARARGS, "" },
   { "display", Pygu_display, METH_VARARGS, "" },
   { "clearColor", Pygu_clearColor, METH_VARARGS, "" },
   { "clearDepth", Pygu_clearDepth, METH_VARARGS, "" },
   { "clearStencill", Pygu_clearStencil, METH_VARARGS, "" },
   { "light", Pygu_light, METH_VARARGS, "" },
   { "lightAtt", Pygu_lightAtt, METH_VARARGS, "" },
   { "lightColor", Pygu_lightColor, METH_VARARGS, "" },
   { "clear", Pygu_clear, METH_VARARGS, "" },
   { "setMatrix", Pygu_setMatrix, METH_VARARGS, "" },
   { "boneMatrix", Pygu_boneMatrix, METH_VARARGS, "" },
   { "ambientColor", Pygu_ambientColor, METH_VARARGS, "" },
   { "morphWeight", Pygu_morphWeight, METH_VARARGS, "" },
   { "drawArray", Pygu_drawArray, METH_VARARGS, "" },
   { "swapBuffers", Pygu_swapBuffers, METH_VARARGS, "" },
   { "sendCommandf", Pygu_sendCommandf, METH_VARARGS, "" },
   { "sendCommandi", Pygu_sendCommandi, METH_VARARGS, "" },
   { "setStatus", Pygu_setStatus, METH_VARARGS, "" },
   { "getStatus", Pygu_getStatus, METH_VARARGS, "" },
   { "setAllStatus", Pygu_setAllStatus, METH_VARARGS, "" },
   { "getAllStatus", Pygu_getAllStatus, METH_VARARGS, "" },
   { "pixelMask", Pygu_pixelMask, METH_VARARGS, "" },
   { "color", Pygu_color, METH_VARARGS, "" },
   { "colorFunc", Pygu_colorFunc, METH_VARARGS, "" },
   { "colorMaterial", Pygu_colorMaterial, METH_VARARGS, "" },
   { "alphaFunc", Pygu_alphaFunc, METH_VARARGS, "" },
   { "blendFunc", Pygu_blendFunc, METH_VARARGS, "" },
   { "stencilFunc", Pygu_stencilFunc, METH_VARARGS, "" },
   { "stencilOp", Pygu_stencilOp, METH_VARARGS, "" },
   { "logicalOp", Pygu_logicalOp, METH_VARARGS, "" },
   { "specular", Pygu_specular, METH_VARARGS, "" },
   { "texEnvColor", Pygu_texEnvColor, METH_VARARGS, "" },
   { "texFilter", Pygu_texFilter, METH_VARARGS, "" },
   { "texFlush", Pygu_texFlush, METH_VARARGS, "" },
   { "texFunc", Pygu_texFunc, METH_VARARGS, "" },
   { "texMapMode", Pygu_texMapMode, METH_VARARGS, "" },
   { "texMode", Pygu_texMode, METH_VARARGS, "" },
   { "texOffset", Pygu_texOffset, METH_VARARGS, "" },
   { "texProjMapMode", Pygu_texProjMapMode, METH_VARARGS, "" },
   { "texWrap", Pygu_texWrap, METH_VARARGS, "" },

   { "WEIGHTS", Pygu_WEIGHTS, METH_VARARGS, "" },
   { "VERTICES", Pygu_VERTICES, METH_VARARGS, "" },
   { "TEXTURE_SHIFT", Pygu_TEXTURE_SHIFT, METH_VARARGS, "" },
   { "COLOR_SHIFT", Pygu_COLOR_SHIFT, METH_VARARGS, "" },
   { "NORMAL_SHIFT", Pygu_NORMAL_SHIFT, METH_VARARGS, "" },
   { "VERTEX_SHIFT", Pygu_VERTEX_SHIFT, METH_VARARGS, "" },
   { "WEIGHT_SHIFT", Pygu_WEIGHT_SHIFT, METH_VARARGS, "" },
   { "INDEX_SHIFT", Pygu_INDEX_SHIFT, METH_VARARGS, "" },
   { "TRANSFORM_SHIFT", Pygu_TRANSFORM_SHIFT, METH_VARARGS, "" },

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
    PyModule_AddIntConstant(mdl, "FOG", GU_FOG);
    PyModule_AddIntConstant(mdl, "CLIP_PLANES", GU_CLIP_PLANES);
    PyModule_AddIntConstant(mdl, "TEXTURE_2D", GU_TEXTURE_2D);
    PyModule_AddIntConstant(mdl, "LIGHTING", GU_LIGHTING);
    PyModule_AddIntConstant(mdl, "LIGHT0", GU_LIGHT0);
    PyModule_AddIntConstant(mdl, "LIGHT1", GU_LIGHT1);
    PyModule_AddIntConstant(mdl, "LIGHT2", GU_LIGHT2);
    PyModule_AddIntConstant(mdl, "LIGHT3", GU_LIGHT3);
    PyModule_AddIntConstant(mdl, "COLOR_TEST", GU_COLOR_LOGIC_OP);
    PyModule_AddIntConstant(mdl, "COLOR_LOGIC_OP", GU_COLOR_LOGIC_OP);
    PyModule_AddIntConstant(mdl, "FACE_NORMAL_REVERSE", GU_FACE_NORMAL_REVERSE);
    PyModule_AddIntConstant(mdl, "PATCH_FACE", GU_PATCH_FACE);
    PyModule_AddIntConstant(mdl, "FRAGMENT_2X", GU_FRAGMENT_2X);

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
    PyModule_AddIntConstant(mdl, "STENCIL_BUFFER_BIT", GU_STENCIL_BUFFER_BIT);
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
    PyModule_AddIntConstant(mdl, "TEXTURE_BITS", GU_TEXTURE_BITS);

    PyModule_AddIntConstant(mdl, "WEIGHTS_BITS", GU_WEIGHTS_BITS);
    PyModule_AddIntConstant(mdl, "VERTICES_BITS", GU_VERTICES_BITS);

    PyModule_AddIntConstant(mdl, "COLOR_RES1", GU_COLOR_RES1);
    PyModule_AddIntConstant(mdl, "COLOR_RES2", GU_COLOR_RES2);
    PyModule_AddIntConstant(mdl, "COLOR_RES3", GU_COLOR_RES3);
    PyModule_AddIntConstant(mdl, "COLOR_5650", GU_COLOR_5650);
    PyModule_AddIntConstant(mdl, "COLOR_5551", GU_COLOR_5551);
    PyModule_AddIntConstant(mdl, "COLOR_4444", GU_COLOR_4444);
    PyModule_AddIntConstant(mdl, "COLOR_8888", GU_COLOR_8888);
    PyModule_AddIntConstant(mdl, "COLOR_BITS", GU_COLOR_BITS);

    PyModule_AddIntConstant(mdl, "NORMAL_8BIT", GU_NORMAL_8BIT);
    PyModule_AddIntConstant(mdl, "NORMAL_16BIT", GU_NORMAL_16BIT);
    PyModule_AddIntConstant(mdl, "NORMAL_32BITF", GU_NORMAL_32BITF);
    PyModule_AddIntConstant(mdl, "NORMAL_BITS", GU_NORMAL_BITS);

    PyModule_AddIntConstant(mdl, "VERTEX_8BIT", GU_VERTEX_8BIT);
    PyModule_AddIntConstant(mdl, "VERTEX_16BIT", GU_VERTEX_16BIT);
    PyModule_AddIntConstant(mdl, "VERTEX_32BITF", GU_VERTEX_32BITF);
    PyModule_AddIntConstant(mdl, "VERTEX_BITS", GU_VERTEX_BITS);

    PyModule_AddIntConstant(mdl, "WEIGHT_8BIT", GU_WEIGHT_8BIT);
    PyModule_AddIntConstant(mdl, "WEIGHT_16BIT", GU_WEIGHT_16BIT);
    PyModule_AddIntConstant(mdl, "WEIGHT_32BITF", GU_WEIGHT_32BITF);
    PyModule_AddIntConstant(mdl, "WEIGHT_BITS", GU_WEIGHT_BITS);

    PyModule_AddIntConstant(mdl, "INDEX_8BIT", GU_INDEX_8BIT);
    PyModule_AddIntConstant(mdl, "INDEX_16BIT", GU_INDEX_16BIT);
    PyModule_AddIntConstant(mdl, "INDEX_BITS", GU_INDEX_BITS);

    PyModule_AddIntConstant(mdl, "TRANSFORM_2D", GU_TRANSFORM_2D);
    PyModule_AddIntConstant(mdl, "TRANSFORM_3D", GU_TRANSFORM_3D);
    PyModule_AddIntConstant(mdl, "TRANSFORM_BITS", GU_TRANSFORM_BITS);

    PyModule_AddIntConstant(mdl, "PSM_5650", GU_PSM_5650);
    PyModule_AddIntConstant(mdl, "PSM_5551", GU_PSM_5551);
    PyModule_AddIntConstant(mdl, "PSM_4444", GU_PSM_4444);
    PyModule_AddIntConstant(mdl, "PSM_8888", GU_PSM_8888);
    PyModule_AddIntConstant(mdl, "PSM_T4", GU_PSM_T4);
    PyModule_AddIntConstant(mdl, "PSM_T8", GU_PSM_T8);
    PyModule_AddIntConstant(mdl, "PSM_T16", GU_PSM_T16);
    PyModule_AddIntConstant(mdl, "PSM_T32", GU_PSM_T32);

    PyModule_AddIntConstant(mdl, "CLEAR", GU_CLEAR);
    PyModule_AddIntConstant(mdl, "AND", GU_AND);
    PyModule_AddIntConstant(mdl, "AND_REVERSE", GU_AND_REVERSE);
    PyModule_AddIntConstant(mdl, "COPY", GU_COPY);
    PyModule_AddIntConstant(mdl, "AND_INVERTED", GU_AND_INVERTED);
    PyModule_AddIntConstant(mdl, "NOOP", GU_NOOP);
    PyModule_AddIntConstant(mdl, "XOR", GU_XOR);
    PyModule_AddIntConstant(mdl, "OR", GU_OR);
    PyModule_AddIntConstant(mdl, "NOR", GU_NOR);
    PyModule_AddIntConstant(mdl, "EQUIV", GU_EQUIV);
    PyModule_AddIntConstant(mdl, "INVERTED", GU_INVERTED);
    PyModule_AddIntConstant(mdl, "OR_REVERSE", GU_OR_REVERSE);
    PyModule_AddIntConstant(mdl, "COPY_INVERTED", GU_COPY_INVERTED);
    PyModule_AddIntConstant(mdl, "OR_INVERTED", GU_OR_INVERTED);
    PyModule_AddIntConstant(mdl, "NAND", GU_NAND);
    PyModule_AddIntConstant(mdl, "SET", GU_SET);

    PyModule_AddIntConstant(mdl, "NEAREST", GU_NEAREST);
    PyModule_AddIntConstant(mdl, "LINEAR", GU_LINEAR);
    PyModule_AddIntConstant(mdl, "NEAREST_MIPMAP_NEAREST", GU_NEAREST_MIPMAP_NEAREST);
    PyModule_AddIntConstant(mdl, "LINEAR_MIPMAP_NEAREST", GU_LINEAR_MIPMAP_NEAREST);
    PyModule_AddIntConstant(mdl, "NEAREST_MIPMAP_LINEAR", GU_NEAREST_MIPMAP_LINEAR);
    PyModule_AddIntConstant(mdl, "LINEAR_MIPMAP_LINEAR", GU_LINEAR_MIPMAP_LINEAR);

    PyModule_AddIntConstant(mdl, "TEXTURE_COORDS", GU_TEXTURE_COORDS);
    PyModule_AddIntConstant(mdl, "TEXTURE_MATRIX", GU_TEXTURE_MATRIX);
    PyModule_AddIntConstant(mdl, "ENVIRONMENT_MAP", GU_ENVIRONMENT_MAP);

    PyModule_AddIntConstant(mdl, "POSITION", GU_POSITION);
    PyModule_AddIntConstant(mdl, "UV", GU_UV);
    PyModule_AddIntConstant(mdl, "NORMALIZED_NORMAL", GU_NORMALIZED_NORMAL);
    PyModule_AddIntConstant(mdl, "NORMAL", GU_NORMAL);

    PyModule_AddIntConstant(mdl, "REPEAT", GU_REPEAT);
    PyModule_AddIntConstant(mdl, "CLAMP", GU_CLAMP);

    PyModule_AddIntConstant(mdl, "TFX_MODULATE", GU_TFX_MODULATE);
    PyModule_AddIntConstant(mdl, "TFX_DECAL", GU_TFX_DECAL);
    PyModule_AddIntConstant(mdl, "TFX_BLEND", GU_TFX_BLEND);
    PyModule_AddIntConstant(mdl, "TFX_REPLACE", GU_TFX_REPLACE);
    PyModule_AddIntConstant(mdl, "TFX_ADD", GU_TFX_ADD);

    PyModule_AddIntConstant(mdl, "TCC_RGB", GU_TCC_RGB);
    PyModule_AddIntConstant(mdl, "TCC_RGBA", GU_TCC_RGBA);

    PyModule_AddIntConstant(mdl, "ADD", GU_ADD);
    PyModule_AddIntConstant(mdl, "SUBTRACT", GU_SUBTRACT);
    PyModule_AddIntConstant(mdl, "REVERSE_SUBTRACT", GU_REVERSE_SUBTRACT);
    PyModule_AddIntConstant(mdl, "MIN", GU_MIN);
    PyModule_AddIntConstant(mdl, "MAX", GU_MAX);
    PyModule_AddIntConstant(mdl, "ABS", GU_ABS);

    PyModule_AddIntConstant(mdl, "SRC_COLOR", GU_SRC_COLOR);
    PyModule_AddIntConstant(mdl, "ONE_MINUS_SRC_COLOR", GU_ONE_MINUS_SRC_COLOR);
    PyModule_AddIntConstant(mdl, "SRC_ALPHA", GU_SRC_ALPHA);
    PyModule_AddIntConstant(mdl, "ONE_MINUS_SRC_ALPHA", GU_ONE_MINUS_SRC_ALPHA);
    PyModule_AddIntConstant(mdl, "DST_COLOR", GU_DST_COLOR);
    PyModule_AddIntConstant(mdl, "ONE_MINUS_DST_COLOR", GU_ONE_MINUS_DST_COLOR);
    PyModule_AddIntConstant(mdl, "DST_ALPHA", GU_DST_ALPHA);
    PyModule_AddIntConstant(mdl, "ONE_MINUS_DST_ALPHA", GU_ONE_MINUS_DST_ALPHA);
    PyModule_AddIntConstant(mdl, "FIX", GU_FIX);

    PyModule_AddIntConstant(mdl, "KEEP", GU_KEEP);
    PyModule_AddIntConstant(mdl, "ZERO", GU_ZERO);
    PyModule_AddIntConstant(mdl, "REPLACE", GU_REPLACE);
    PyModule_AddIntConstant(mdl, "INVERT", GU_INVERT);
    PyModule_AddIntConstant(mdl, "INCR", GU_INCR);
    PyModule_AddIntConstant(mdl, "DECR", GU_DECR);

    PyModule_AddIntConstant(mdl, "TAIL", GU_TAIL);
    PyModule_AddIntConstant(mdl, "HEAD", GU_HEAD);
}

#ifdef _GNUC
static const char* _rcsid_gumodule __attribute__((unused)) = "$Id$";
#endif


/**
 * @file screen.c
 */

/**********************************************************************

  Created: 30 Oct 2005

**********************************************************************/
// $Id$

#include "screen.h"
#include "image.h"
#include "color.h"

#include <pspdisplay.h>
#include <pspkernel.h>

#define PSP_LINE_SIZE 512
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

#define FRAMEBUFFER_SIZE (PSP_LINE_SIZE*SCREEN_HEIGHT*4)

#define VRAM_BASE ((u32*)(0x40000000 | 0x04000000))

typedef struct
{
      unsigned short u, v;
      short x, y, z;
} Vertex;

static u32* getDrawBase(PyScreen *self)
{
    u32* ret = VRAM_BASE;

    if (!self->current)
       ret += FRAMEBUFFER_SIZE / sizeof(u32);

    return ret;
}

static void screen_dealloc(PyScreen *self)
{
    self->ob_type->tp_free((PyObject*)self);
}

static PyObject* screen_new(PyTypeObject *type,
                            PyObject *args,
                            PyObject *kwargs)
{
    PyScreen *self;

    self = (PyScreen*)type->tp_alloc(type, 0);

    if (self)
       self->current = 0;

    return (PyObject*)self;
}

static int screen_init(PyScreen *self,
                      PyObject *args,
                      PyObject *kwargs)
{
    if (!PyArg_ParseTuple(args, ""))
       return -1;

    // TODO: ensure this gets instantiated only ONCE!!!

    sceGuStart(GU_DIRECT, self->list);

    sceGuDrawBuffer(GU_PSM_8888, (void*)FRAMEBUFFER_SIZE, PSP_LINE_SIZE);
    sceGuDispBuffer(SCREEN_WIDTH, SCREEN_HEIGHT, (void*)0, PSP_LINE_SIZE);

    sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);
    sceGuDepthBuffer((void*) (FRAMEBUFFER_SIZE*2), PSP_LINE_SIZE);
    sceGuOffset(2048 - (SCREEN_WIDTH / 2), 2048 - (SCREEN_HEIGHT / 2));
    sceGuViewport(2048, 2048, SCREEN_WIDTH, SCREEN_HEIGHT);
    sceGuDepthRange(0xc350, 0x2710);

    sceGuScissor(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);

    sceGuAlphaFunc(GU_GREATER, 0, 0xff);
    sceGuEnable(GU_ALPHA_TEST);

    sceGuDepthFunc(GU_GEQUAL);
    sceGuEnable(GU_DEPTH_TEST);

    sceGuFrontFace(GU_CW);
    sceGuShadeModel(GU_SMOOTH);
    sceGuEnable(GU_CULL_FACE);
    sceGuEnable(GU_TEXTURE_2D);
    sceGuEnable(GU_CLIP_PLANES);
    sceGuTexMode(GU_PSM_8888, 0, 0, 0);
    sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGBA);
    sceGuTexFilter(GU_NEAREST, GU_NEAREST);
    sceGuAmbientColor(0xffffffff);
    sceGuEnable(GU_BLEND);
    sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);

    sceGuFinish();
    sceGuSync(0, 0);

    sceDisplayWaitVblankStart();
    sceGuDisplay(GU_TRUE);

    return 0;
}

static PyObject* screen_blit(PyScreen *self,
                             PyObject *args,
                             PyObject *kwargs)
{
    int sx, sy, w, h, dx, dy, blend = 0;
    PyImage *img;

    if (!PyArg_ParseTuple(args, "iiiiOii|i:blit", &sx, &sy, &w, &h,
                          &img, &dx, &dy, &blend))
       return NULL;

#ifdef CHECKTYPE
    if (((PyObject*)img)->ob_type != PPyImageType)
    {
       PyErr_SetString(PyExc_TypeError, "Fifth argument must be an Image");
       return NULL;
    }
#endif

    if (PyErr_CheckSignals())
       return NULL;

    if (blend)
    {
       int j = 0;

       sceKernelDcacheWritebackInvalidateAll();
       sceGuStart(GU_DIRECT, self->list);
       sceGuTexImage(0, img->twidth, img->theight, img->twidth, (void*)img->data);
       sceGuTexScale(1.0f / (float)img->twidth,
                     1.0f / (float)img->theight);

       while (j < w) {
          Vertex* vertices = (Vertex*) sceGuGetMemory(2 * sizeof(Vertex));
          int sliceWidth = 64;

          if (j + sliceWidth > w)
             sliceWidth = w - j;

          vertices[0].u = sx + j;
          vertices[0].v = sy;
          vertices[0].x = dx + j;
          vertices[0].y = dy;
          vertices[0].z = 0;
          vertices[1].u = sx + j + sliceWidth;
          vertices[1].v = sy + h;
          vertices[1].x = dx + j + sliceWidth;
          vertices[1].y = dy + h;
          vertices[1].z = 0;

          sceGuDrawArray(GU_SPRITES, GU_TEXTURE_16BIT | GU_VERTEX_16BIT | GU_TRANSFORM_2D, 2, 0, vertices);
          j += sliceWidth;
       }

       sceGuFinish();
       sceGuSync(0, 0);
    }
    else
    {
       u32 *vram;

       vram = getDrawBase(self);

       sceKernelDcacheWritebackInvalidateAll();
       sceGuStart(GU_DIRECT, self->list);
       sceGuCopyImage(GU_PSM_8888,
                      sx, sy, w, h,
                      img->twidth,
                      img->data,
                      dx, dy,
                      PSP_LINE_SIZE,
                      vram);
       sceGuFinish();
       sceGuSync(0, 0);
    }

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* screen_clear(PyScreen *self,
                              PyObject *args,
                              PyObject *kwargs)
{
    PyColor *color;

    if (!PyArg_ParseTuple(args, "O:clear", &color))
       return NULL;

#ifdef CHECKTYPE
    if (((PyObject*)color)->ob_type != PPyColorType)
    {
       PyErr_SetString(PyExc_TypeError, "Argument must be a Color.");
       return NULL;
    }
#endif

    if (PyErr_CheckSignals())
       return NULL;

    sceGuStart(GU_DIRECT, self->list);
    sceGuClearColor(color->color);
    sceGuClearDepth(0);
    sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);
    sceGuFinish();
    sceGuSync(0, 0);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* screen_fillRect(PyScreen *self,
                                 PyObject *args,
                                 PyObject *kwargs)
{
    PyColor *color;
    int x, y, w, h;
    u32 *dst;
    int i, j;

    if (!PyArg_ParseTuple(args, "iiiiO:fillRect", &x, &y,
                          &w, &h, &color))
       return NULL;

#ifdef CHECKTYPE
    if (((PyObject*)color)->ob_type != PPyColorType)
    {
       PyErr_SetString(PyExc_TypeError, "Fifth argument must be a Color.");
       return NULL;
    }
#endif

    if (PyErr_CheckSignals())
       return NULL;

    dst = getDrawBase(self) + y * PSP_LINE_SIZE + x;
    for (j = 0; j < h; ++j)
    {
       for (i = 0; i < w; ++i)
       {
          *(dst + j * PSP_LINE_SIZE + i) = color->color;
       }
    }

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* screen_swap(PyScreen *self,
                             PyObject *args,
                             PyObject *kwargs)
{
    if (!PyArg_ParseTuple(args, ":swap"))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    sceDisplayWaitVblankStart();
    sceGuSwapBuffers();

    self->current ^= 1;

    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef screen_methods[] = {
   { "blit", (PyCFunction)screen_blit, METH_VARARGS,
     "blit(sx, sy, w, h, img, dx, dy, blend = False)\n"
     "Copies the (sx, sy, w, h) rectangle from img to (dx, dy).\n"
     "If blend is True, perform blending." },

   { "clear", (PyCFunction)screen_clear, METH_VARARGS,
     "clear()\n"
     "Clears the screen." },

   { "fillRect", (PyCFunction)screen_fillRect, METH_VARARGS,
     "fillRect(x, y, w, h, color)\n"
     "Fills a rectangle." },

   { "swap", (PyCFunction)screen_swap, METH_VARARGS,
     "swap()\n"
     "Swaps the draw buffer and the display buffer." },

   { NULL }
};

static PyTypeObject PyScreenType = {
   PyObject_HEAD_INIT(NULL)
   0,
   "psp2d.Screen",
   sizeof(PyScreen),
   0,
   (destructor)screen_dealloc,
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
   "Screen objects",
   0,
   0,
   0,
   0,
   0,
   0,
   screen_methods,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   (initproc)screen_init,
   0,
   screen_new,
};

PyTypeObject* PPyScreenType = &PyScreenType;

#ifdef _GNUC
static const char* _rcsid_screen __attribute__((unused)) = "$Id$";
#endif

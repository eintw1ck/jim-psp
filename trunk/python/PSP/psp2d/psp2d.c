
/**
 * @file psp2d.c
 */

/**********************************************************************

  Created: 30 Oct 2005

**********************************************************************/
// $Id$

#include <Python.h>
#include <png.h>
#include <pspdisplay.h>

#include "color.h"
#include "image.h"
#include "controller.h"
#include "music.h"
#include "sound.h"
#include "screen.h"
#include "mask.h"
#include "font.h"
#include "transform.h"

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

    if (PyErr_CheckSignals())
       return NULL;

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

    if (PyErr_CheckSignals())
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

static PyObject* psp2d_screenshot(PyObject *self,
                                  PyObject *args,
                                  PyObject *kwargs)
{
    u32* vram32;
    u16* vram16;
    int bufferwidth;
    int pixelformat;
    int unknown;
    int i, x, y;
    png_structp png_ptr;
    png_infop info_ptr;
    FILE* fp;
    u8* line;
    char *filename;

    if (!PyArg_ParseTuple(args, "s", &filename))
       return NULL;

    fp = fopen(filename, "wb");
    if (!fp)
    {
       PyErr_SetString(PyExc_IOError, "Could not open file");
       return NULL;
    }

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr)
    {
       fclose(fp);

       PyErr_SetString(PyExc_RuntimeError, "PNG struct creation error");
       return NULL;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
       png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
       fclose(fp);

       PyErr_SetString(PyExc_RuntimeError, "PNG infostruct creation error");
       return NULL;
    }

    png_init_io(png_ptr, fp);
    png_set_IHDR(png_ptr, info_ptr, SCREEN_WIDTH, SCREEN_HEIGHT,
                 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png_ptr, info_ptr);
    line = (u8*) malloc(SCREEN_WIDTH * 3);
    sceDisplayWaitVblankStart();  // if framebuf was set with PSP_DISPLAY_SETBUF_NEXTFRAME, wait until it is changed
    sceDisplayGetFrameBuf((void**)&vram32, &bufferwidth, &pixelformat, &unknown);
    vram16 = (u16*) vram32;
    for (y = 0; y < SCREEN_HEIGHT; y++) {
       for (i = 0, x = 0; x < SCREEN_WIDTH; x++) {
          u32 color = 0;
          u8 r = 0, g = 0, b = 0;
          switch (pixelformat) {
             case PSP_DISPLAY_PIXEL_FORMAT_565:
                color = vram16[x + y * bufferwidth];
                r = (color & 0x1f) << 3;
                g = ((color >> 5) & 0x3f) << 2 ;
                b = ((color >> 11) & 0x1f) << 3 ;
                break;
             case PSP_DISPLAY_PIXEL_FORMAT_5551:
                color = vram16[x + y * bufferwidth];
                r = (color & 0x1f) << 3;
                g = ((color >> 5) & 0x1f) << 3 ;
                b = ((color >> 10) & 0x1f) << 3 ;
                break;
             case PSP_DISPLAY_PIXEL_FORMAT_4444:
                color = vram16[x + y * bufferwidth];
                r = (color & 0xf) << 4;
                g = ((color >> 4) & 0xf) << 4 ;
                b = ((color >> 8) & 0xf) << 4 ;
                break;
             case PSP_DISPLAY_PIXEL_FORMAT_8888:
                color = vram32[x + y * bufferwidth];
                r = color & 0xff;
                g = (color >> 8) & 0xff;
                b = (color >> 16) & 0xff;
                break;
          }
          line[i++] = r;
          line[i++] = g;
          line[i++] = b;
       }
       png_write_row(png_ptr, line);
    }
    free(line);
    png_write_end(png_ptr, info_ptr);
    png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
    fclose(fp);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef psp2d_functions[] = {
   { "setMusicVolume", (PyCFunction)psp2d_setMusicVolume, METH_VARARGS, "" },
   { "setSndFxVolume", (PyCFunction)psp2d_setSndFxVolume, METH_VARARGS, "" },
   { "screenshot", (PyCFunction)psp2d_screenshot, METH_VARARGS, "" },

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

    if (PyType_Ready(PPyFontType) < 0)
       return;

    if (PyType_Ready(PPyTransformType) < 0)
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

    Py_INCREF(PPyFontType);
    PyModule_AddObject(mdl, "Font", (PyObject*)PPyFontType);

    Py_INCREF(PPyTransformType);
    PyModule_AddObject(mdl, "Transform", (PyObject*)PPyTransformType);

    PyModule_AddIntConstant(mdl, "TR_PLUS", TR_PLUS);
    PyModule_AddIntConstant(mdl, "TR_MULT", TR_MULT);
}

#ifdef _GNUC
static const char* _rcsid_psp2d __attribute__((unused)) = "$Id$";
#endif

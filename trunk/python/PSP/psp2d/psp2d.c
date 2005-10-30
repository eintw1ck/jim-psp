
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

#ifndef PyMODINIT_FUNC
#define PyMODINIT_FUNC void
#endif

static PyMethodDef psp2d_functions[] = {
   { NULL }
};

// MikMod globals

extern UWORD md_mode;
extern UBYTE md_reverb;
extern UBYTE md_pansep;

PyMODINIT_FUNC initpsp2d(void)
{
    PyObject *mdl;

    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    MikMod_RegisterAllLoaders();
    MikMod_RegisterAllDrivers();
    md_mode = DMODE_16BITS|DMODE_STEREO|DMODE_SOFT_SNDFX|DMODE_SOFT_MUSIC;
    md_reverb = 0;
    md_pansep = 128;
    MikMod_Init();
    MikMod_SetNumVoices(-1, 8);

    MikMod_EnableOutput();

    // TODO: MikMod_Exit => in main() ?

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
}

#ifdef _GNUC
static const char* _rcsid_psp2d __attribute__((unused)) = "$Id$";
#endif


/**
 * @file sound.h
 */

/**********************************************************************

  Created: 30 Oct 2005

**********************************************************************/
// $Id$

#ifndef _SOUND_H
#define _SOUND_H

#include <Python.h>
#include <mikmod.h>

typedef struct
{
      PyObject_HEAD

      SAMPLE *sf;
} PySound;

extern PyTypeObject* PPySoundType;

#endif /* _SOUND_H */


/**
 * @file sound.h
 */

/**********************************************************************

  Created: 30 Oct 2005

**********************************************************************/
// $Id$

#ifndef _PYSOUND_H
#define _PYSOUND_H

#include <Python.h>
#include <libpspsnd/Sound.h>

typedef struct
{
      PyObject_HEAD

      PSPSND::Sound *sound;
} PySound;

extern PyTypeObject* PPySoundType;

#endif /* _PYSOUND_H */

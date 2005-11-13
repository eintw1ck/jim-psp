
/**
 * @file music.h
 */

/**********************************************************************

  Created: 30 Oct 2005

**********************************************************************/
// $Id$

#ifndef _PYMUSIC_H
#define _PYMUSIC_H

#include <Python.h>
#include <libpspsnd/Music.h>

typedef struct
{
      PyObject_HEAD

      PSPSND::Music *music;
} PyMusic;

extern PyTypeObject* PPyMusicType;

#endif /* _PYMUSIC_H */

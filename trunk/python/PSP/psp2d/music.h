
/**
 * @file music.h
 */

/**********************************************************************

  Created: 30 Oct 2005

**********************************************************************/
// $Id$

#ifndef _MUSIC_H
#define _MUSIC_H

#include <Python.h>
#include <mikmod.h>

typedef struct
{
      PyObject_HEAD

      UNIMOD *mf;
} PyMusic;

extern PyTypeObject* PPyMusicType;

#endif /* _MUSIC_H */

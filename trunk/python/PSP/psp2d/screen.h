
/**
 * @file screen.h
 */

/**********************************************************************

  Created: 30 Oct 2005

**********************************************************************/
// $Id$

#ifndef _PYSCREEN_H
#define _PYSCREEN_H

#include <Python.h>
#include <lib2d/Screen.h>

typedef struct
{
      PyObject_HEAD

      PSP2D::Screen *scr;
} PyScreen;

extern PyTypeObject* PPyScreenType;

#endif /* _PYSCREEN_H */


/**
 * @file color.h
 */

/**********************************************************************

  Created: 30 Oct 2005

**********************************************************************/
// $Id$

#ifndef _COLOR_H
#define _COLOR_H

#include <Python.h>
#include <psptypes.h>

typedef struct
{
      PyObject_HEAD

      u32 color;
} PyColor;

extern PyTypeObject* PPyColorType;

#endif /* _COLOR_H */


/**
 * @file mask.h
 */

/**********************************************************************

  Created: 01 Nov 2005

**********************************************************************/
// $Id$

#ifndef _MASK_H
#define _MASK_H

#include <Python.h>
#include <psptypes.h>

typedef struct
{
      PyObject_HEAD

      u32* data;
      u16 width;
      u16 height;
      u16 wcap;
} PyMask;

extern PyTypeObject* PPyMaskType;

#endif /* _MASK_H */

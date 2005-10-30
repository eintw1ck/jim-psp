
/**
 * @file image.h
 */

/**********************************************************************

  Created: 30 Oct 2005

**********************************************************************/
// $Id$

#ifndef _IMAGE_H
#define _IMAGE_H

#include <Python.h>
#include <psptypes.h>

typedef struct
{
      PyObject_HEAD

      u16 width;
      u16 height;

      u32 *data;
} PyImage;

extern PyTypeObject* PPyImageType;

#endif /* _IMAGE_H */


/**
 * @file image.h
 */

/**********************************************************************

  Created: 30 Oct 2005

**********************************************************************/
// $Id$

#ifndef _PYIMAGE_H
#define _PYIMAGE_H

#include <Python.h>
#include <lib2d/Image.h>

typedef struct
{
      PyObject_HEAD

      PSP2D::Image *img;
} PyImage;

extern PyTypeObject* PPyImageType;

#endif /* _PYIMAGE_H */

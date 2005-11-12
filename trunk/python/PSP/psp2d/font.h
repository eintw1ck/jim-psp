
/**
 * @file font.h
 */

/**********************************************************************

  Created: 05 Nov 2005

**********************************************************************/
// $Id$

#ifndef _PYFONT_H
#define _PYFONT_H

#include <Python.h>
#include <libpsp2d/Font.h>

typedef struct
{
      PyObject_HEAD

      PSP2D::Font *fnt;
} PyFont;

extern PyTypeObject* PPyFontType;

#endif /* _PYFONT_H */

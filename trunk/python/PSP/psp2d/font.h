
/**
 * @file font.h
 */

/**********************************************************************

  Created: 05 Nov 2005

**********************************************************************/
// $Id$

#ifndef _FONT_H
#define _FONT_H

#include <Python.h>
#include <psptypes.h>

typedef struct
{
      PyObject_HEAD

      u32* data;
      u16 width;
      u16 height;
      u16 positions[512];
      u16 maxpos;
} PyFont;

extern PyTypeObject* PPyFontType;

#endif /* _FONT_H */

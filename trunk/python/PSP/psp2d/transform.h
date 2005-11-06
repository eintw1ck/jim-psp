
/**
 * @file transform.h
 */

/**********************************************************************

  Created: 06 Nov 2005

**********************************************************************/
// $Id$

#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include <Python.h>
#include <psptypes.h>

#define TR_USER                 0
#define TR_PLUS                 1
#define TR_MULT                 2

typedef struct
{
      PyObject_HEAD

      u32 type;           // 0 == user-defined Python callback
      float param;
      PyObject *cb;
} PyTransform;

extern PyTypeObject* PPyTransformType;

#endif /* _TRANSFORM_H */

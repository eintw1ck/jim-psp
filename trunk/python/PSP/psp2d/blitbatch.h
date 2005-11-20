
/**
 * @file blitbatch.h
 */

/**********************************************************************

  Created: 20 Nov 2005

**********************************************************************/
// $Id$

#ifndef _PYBLITBATCH_H
#define _PYBLITBATCH_H

#include <Python.h>
#include <libpsp2d/BlitBatch.h>

typedef struct
{
      PyObject_HEAD

      PSP2D::BlitBatch *batch;
} PyBlitBatch;

extern PyTypeObject* PPyBlitBatchType;

#endif /* _PYBLITBATCH_H */


/**
 * @file controller.h
 */

/**********************************************************************

  Created: 30 Oct 2005

**********************************************************************/
// $Id$

#ifndef _PYCONTROLLER_H
#define _PYCONTROLLER_H

#include <Python.h>
#include <libpsp2d/Controller.h>

typedef struct
{
      PyObject_HEAD

      PSP2D::Controller *ctrl;
} PyController;

extern PyTypeObject* PPyControllerType;

#endif /* _PYCONTROLLER_H */

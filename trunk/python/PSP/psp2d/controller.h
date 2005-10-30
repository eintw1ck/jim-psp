
/**
 * @file controller.h
 */

/**********************************************************************

  Created: 30 Oct 2005

**********************************************************************/
// $Id$

#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <Python.h>
#include <pspctrl.h>

typedef struct
{
      PyObject_HEAD

      SceCtrlData data;
} PyController;

extern PyTypeObject* PPyControllerType;

#endif /* _CONTROLLER_H */

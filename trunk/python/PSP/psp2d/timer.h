
/**
 * @file timer.h
 */

/**********************************************************************

  Created: 20 Nov 2005

**********************************************************************/
// $Id$

#ifndef _PYTIMER_H
#define _PYTIMER_H

#include <Python.h>
#include <libpsp2d/Timer.h>

typedef struct
{
      PyObject_HEAD

      PSP2D::Timer *tmr;
} PyTimer;

extern PyTypeObject* PPyTimerType;

#endif /* _PYTIMER_H */

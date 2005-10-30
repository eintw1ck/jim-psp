
/**
 * @file screen.h
 */

/**********************************************************************

  Created: 30 Oct 2005

**********************************************************************/
// $Id$

#ifndef _SCREEN_H
#define _SCREEN_H

#include <Python.h>
#include <pspgu.h>

typedef struct
{
      PyObject_HEAD

      unsigned int __attribute__((aligned(16))) list[262144];
      int current;
} PyScreen;

extern PyTypeObject* PPyScreenType;

#endif /* _SCREEN_H */

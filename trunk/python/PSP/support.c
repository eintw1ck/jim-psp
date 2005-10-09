
/**
 * @file support.c
 */

/**********************************************************************

  Created: 02 Oct 2005

**********************************************************************/
// $Id$

#include <pspkernel.h>

unsigned int sleep(unsigned int seconds)
{
    sceKernelDelayThreadCB(seconds * 1e6);
    return 0;
}

#ifdef _GNUC
static const char* _rcsid_support __attribute__((unused)) = "$Id$";
#endif

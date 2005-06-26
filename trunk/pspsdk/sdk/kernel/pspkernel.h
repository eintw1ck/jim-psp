/* kernel.h */

#ifndef __KERNEL_H__
#define __KERNEL_H__

#include <psptypes.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <pspiofilemgr.h>
#include <psploadexec.h>
#include <pspmoduleinfo.h>
#include <pspmodulemgr.h>
#include <pspthreadman.h>
#include <psputils.h>
#include <pspumd.h>
#include <pspge.h>

/** @defgroup Kernel PSP Kernel Import Library */

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Kernel */
/*@{*/

/** Define the elf name variable, contains a pointer to the boot elf path */
extern const char* g_elf_name;

/** Define the elf name size variable */
extern int g_elf_namesize;

/*@}*/

#ifdef __cplusplus
}
#endif

#endif

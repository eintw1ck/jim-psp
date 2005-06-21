/* kernel.h */

#ifndef __KERNEL_H__
#define __KERNEL_H__

/** Define the module info macro. This must be specified in one file of a project */
#define MODULE_INFO(name, flags) asm ( \
		".section \".rodata.sceModuleInfo\", \"a\", @progbits\r\n" 	\
		".global  module_info\r\n" 						  	\
		"module_info:\r\n"										\
		".word " #flags "\r\n" 								  	\
		".ascii \"" name "\"\r\n" 							  	\
		".align 5\r\n"											\
		".word _gp\r\n" 										\
		".word __lib_ent_top\r\n"								\
		".word __lib_ent_bottom\r\n"							\
		".word __lib_stub_top\r\n"								\
		".word __lib_stub_bottom\r\n"							\
		);

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

#include <stddef.h>
#include <stdarg.h>

#include <psptypes.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <pspiofilemgr.h>
#include <psploadexec.h>
#include <pspmodulemgr.h>
#include <pspthreadman.h>
#include <psputils.h>
#include <pspumd.h>
#include <pspge.h>

#ifdef __cplusplus
}
#endif

#endif

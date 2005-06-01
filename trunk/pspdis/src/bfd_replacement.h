/*                          ____  _     
#         ____  _________  / __ \(_)____
#        / __ \/ ___/ __ \/ / / / / ___/
#       / /_/ (__  ) /_/ / /_/ / (__  ) 
#      / .___/____/ .___/_____/_/____/  
#     /_/        /_/
#     
# Copyright 2005, pspdev - http://www.pspdev.org
# Author:       John Kelley
# Date:         June 1 2005
# File:         bfd_replacement.c
# Description:  Code taken from bfd.h and libbfd.c in binutils-2.16-psp
#               to satisfy libopcodes.
#
*/
#ifndef _BFD_REPLACEMENT_H_
#define _BFD_REPLACEMENT_H_

#include "dis-asm.h"

#define _bfd_int64_low(x) ((unsigned long) (((x) & 0xffffffff)))
#define _bfd_int64_high(x) ((unsigned long) (((x) >> 32) & 0xffffffff))

bfd_vma bfd_getl32 (const void *p);
bfd_vma bfd_getb32 (const void *p);
bfd_vma bfd_getl16 (const void *p);
bfd_vma bfd_getb16 (const void *p);
enum bfd_architecture bfd_get_arch (bfd *abfd);

#endif

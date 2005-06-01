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
# File:         libopcode_helper.h
# Description:  Helper functions for libopcode as per dis-asm.h
#
*/
#ifndef _LIBOPCODE_HELPER_H_
#define _LIBOPCODE_HELPER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "dis-asm.h"

int libopcodes_read_mem(bfd_vma memaddr, bfd_byte *myaddr, unsigned int length, struct disassemble_info *info);
void libopcodes_print_addr(bfd_vma addr, struct disassemble_info *info);
void libopcodes_mem_error(int status, bfd_vma memaddr, struct disassemble_info *info);
int libopcodes_symbol_at_addr(bfd_vma addr, struct disassemble_info * info);
bfd_boolean libopcodes_symbol_is_valid(asymbol *symbol, struct disassemble_info * info);

#ifdef __cplusplus
}
#endif

#endif

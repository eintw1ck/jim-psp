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
# File:         libopcode_helper.c
# Description:  Helper functions for libopcode as per dis-asm.h
#
*/
#include <string.h>
#include "libopcodes_helper.h"
#include "bfd_replacement.h"
#include "util.h"

/* Function used to get bytes to disassemble.  MEMADDR is the
     address of the stuff to be disassembled, MYADDR is the address to
     put the bytes in, and LENGTH is the number of bytes to read.
     INFO is a pointer to this struct.
     Returns an errno value or 0 for success.  */
int libopcodes_read_mem(bfd_vma memaddr, bfd_byte *myaddr, unsigned int length, struct disassemble_info *info) {
	void * result;
	printf("disasm is trying to read %d bytes from 0x%08lX (dest contains 0x%08X)\n", length, memaddr, *(int *)&myaddr[0]);
	result = memcpy(myaddr, (void *)(u32)memaddr, length);
	//printf("src: 0x%08X dest: 0x%08X\n",*(int *)&((u8 *)(u32)memaddr)[0], *(int *)&myaddr[0]);
	if (result == myaddr)
		return 0;
	return -1;
}

  /* Function called to print ADDR.  */
void libopcodes_print_addr(bfd_vma addr, struct disassemble_info *info) {
	if ( _bfd_int64_high (addr) == 0)
		printf("0x%08lx", _bfd_int64_low (addr));
	else
		printf("0x%08lx%08lx", _bfd_int64_high (addr), _bfd_int64_low (addr));
}
  
  /* Function which should be called if we get an error that we can't
     recover from.  STATUS is the errno value from read_memory_func and
     MEMADDR is the address that we were trying to read.  INFO is a
     pointer to this struct.  */
void libopcodes_mem_error(int status, bfd_vma memaddr, struct disassemble_info *info) {
	printf("mem error called with status %d @", status);
	libopcodes_print_addr(memaddr, info);
	printf("\n");
}

  /* Function called to determine if there is a symbol at the given ADDR.
     If there is, the function returns 1, otherwise it returns 0.
     This is used by ports which support an overlay manager where
     the overlay number is held in the top part of an address.  In
     some circumstances we want to include the overlay number in the
     address, (normally because there is a symbol associated with
     that address), but sometimes we want to mask out the overlay bits.  */
int libopcodes_symbol_at_addr(bfd_vma addr, struct disassemble_info * info) {
	return 0;
}

  /* Function called to check if a SYMBOL is can be displayed to the user.
     This is used by some ports that want to hide special symbols when
     displaying debugging outout.  */
bfd_boolean libopcodes_symbol_is_valid(asymbol *symbol, struct disassemble_info * info) {
	return 0;
}

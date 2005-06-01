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
#include "bfd_replacement.h"

bfd_vma
bfd_getl32 (const void *p)
{
  const bfd_byte *addr = p;
  unsigned long v;

  v = (unsigned long) addr[0];
  v |= (unsigned long) addr[1] << 8;
  v |= (unsigned long) addr[2] << 16;
  v |= (unsigned long) addr[3] << 24;
  return v;
}
bfd_vma
bfd_getb32 (const void *p)
{
  const bfd_byte *addr = p;
  unsigned long v;

  v = (unsigned long) addr[0] << 24;
  v |= (unsigned long) addr[1] << 16;
  v |= (unsigned long) addr[2] << 8;
  v |= (unsigned long) addr[3];
  return v;
}
bfd_vma
bfd_getl16 (const void *p)
{
  const bfd_byte *addr = p;
  return (addr[1] << 8) | addr[0];
}
bfd_vma
bfd_getb16 (const void *p)
{
  const bfd_byte *addr = p;
  return (addr[0] << 8) | addr[1];
}

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
# File:         util.c
# Description:  Utility functions.
#
*/
#ifndef _UTIL_H_
#define _UTIL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdio.h>
#include <ctype.h>

#define makehexchar(i) (i<=9) ? '0'+(i) : 'A'+((i)-10)

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

void hexdump(const u8* data, size_t length);

#ifdef __cplusplus
}
#endif

#endif

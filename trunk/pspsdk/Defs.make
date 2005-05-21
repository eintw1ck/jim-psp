# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# Copyright 2001-2004, ps2dev - http://www.ps2dev.org
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
#
# $Id$

 
# You can override the following options on the make command line, or manually
# edit them below.  Please see the file INSTALL for details on building
# ps2sdk.

#
# Definitions for the PSP toolchain.
#

#PSP_TOOL_PREFIX = ee-
PSP_TOOL_PREFIX = psp-
PSP_CC = $(PSP_TOOL_PREFIX)gcc
PSP_CXX = $(PSP_TOOL_PREFIX)g++
PSP_AS = $(PSP_TOOL_PREFIX)as
PSP_LD = $(PSP_TOOL_PREFIX)ld
PSP_AR = $(PSP_TOOL_PREFIX)ar
PSP_OBJCOPY = $(PSP_TOOL_PREFIX)objcopy
PSP_STRIP = $(PSP_TOOL_PREFIX)strip


#
# Definitions for the local toolchain
#

CC = gcc
AS = as
LD = ld
AR = ar
OBJCOPY = objcopy
STRIP = strip

#
# Definitions for local shell operations
#

MKDIR = mkdir
RMDIR = rmdir
ECHO  = echo
GNUMAKE = make

SYSTEM = $(shell uname)

ifeq ($(findstring Windows, $(SYSTEM)), Windows)
  # these versions are used for the cygwin toolchain in a dos environment
  # since they need to overwrite the standard dos versions of each command
  MKDIR = cyg-mkdir
  RMDIR = cyg-rmdir
  ECHO  = cyg-echo
  GNUMAKE = make
endif

ifeq ($(findstring BSD, $(SYSTEM)), BSD)
  # *BSD needs gnu make
  GNUMAKE = gmake
endif

ifeq ($(SYSTEM), Darwin)
  # OSX needs gnu make
  GNUMAKE = gmake
endif

MAKEREC = $(GNUMAKE) -C

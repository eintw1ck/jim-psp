# _____     ___ ____     ___ ____ 
#  ____|   |    ____|   |        | |____|    
# |     ___|   |     ___|    ____| |    \    PSPDEV Open Source Project. 
#-----------------------------------------------------------------------
# Copyright 2001-2004, ps2dev - http://www.ps2dev.org
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details. 
#
# $Id$

.SUFFIXES:.c
VPATH = src:obj

LIBDEBUG_LIB  = lib/libdebug.a

PSP_OBJS_DIR = obj/
PSP_LIB_DIR = lib/
PSP_SRC_DIR = src/
PSP_INC_DIR = include/

PSP_LIB = $(LIBDEBUG_LIB)

PSP_OBJS = scr_printf.o  font.o callstack.o callstackget.o
PSP_OBJS := $(PSP_OBJS:%=$(PSP_OBJS_DIR)%)

all: $(PSP_OBJS_DIR) $(PSP_LIB_DIR) $(LIBDEBUG_LIB) 


.c.o :
	$(PSP_CC) $(PSP_CFLAGS) $(PSP_INC) -c $< -o obj/$@

clean:
	rm -f -r $(PSP_OBJS_DIR) $(PSP_LIB_DIR)


include $(PSPSDKSRC)/Defs.make
include $(PSPSDKSRC)/psp/Rules.make
include $(PSPSDKSRC)/psp/Rules.release

# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# Copyright 2001-2004, ps2dev - http://www.ps2dev.org
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
#
# $Id$


LIBKERNEL_LIB = lib/libkernel.a

PSP_OBJS_DIR = obj/
PSP_LIB_DIR = lib/
PSP_SRC_DIR = src/
PSP_INC_DIR = include/

LIBKERNEL_OBJS = kernel.o ctrl.o fileio.o threadman.o display.o modload.o \
				 utility.o ge.o umd.o loadexec.o power.o utils.o suspend.o \
				 sysmem.o stdio.o 
LIBKERNEL_OBJS := $(LIBKERNEL_OBJS:%=$(PSP_OBJS_DIR)%)

all: $(PSP_OBJS_DIR) $(PSP_LIB_DIR) $(LIBKERNEL_LIB)

$(LIBKERNEL_LIB): $(LIBKERNEL_OBJS) 
	$(PSP_AR) cru $(LIBKERNEL_LIB) $(LIBKERNEL_OBJS) 

clean:
	rm -f -r $(PSP_OBJS_DIR) $(PSP_LIB_DIR)


include $(PSPSDKSRC)/Defs.make
include $(PSPSDKSRC)/psp/Rules.make
include $(PSPSDKSRC)/psp/Rules.release

release: release-dirs release-include
	cp -f $(LIBKERNEL_LIB) $(PSPSDK)/lib


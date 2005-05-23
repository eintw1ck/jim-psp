# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# Copyright 2001-2004, ps2dev - http://www.ps2dev.org
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
#
# $Id$

PSP_INCS := $(PSP_INCS) -I$(PSPSDKSRC)/psp/include -I$(PSPSDKSRC)/psp/libc/include -Iinclude

# C compiler flags
PSP_CFLAGS :=  -O2 -G0 -Wall -mdivide-breaks -march=r4000 -mgp32 -mlong32 -fshort-double $(PSP_CFLAGS)

# C++ compiler flags
PSP_CXXFLAGS :=  -O2 -G0 -Wall -mdivide-breaks -march=r4000 -mgp32 -mlong32 -fshort-double -fno-exceptions $(PSP_CXXFLAGS)

# Linker flags
#PSP_LDFLAGS := $(PSP_LDFLAGS)

# Assembler flags
PSP_ASFLAGS := -G0 --break -march=r4000 -mgp32 $(PSP_ASFLAGS)

# Externally defined variables: PSP_BIN, PSP_OBJS, PSP_LIB

# These macros can be used to simplify certain build rules.
PSP_C_COMPILE = $(PSP_CC) $(PSP_CFLAGS) $(PSP_INCS)
PSP_CXX_COMPILE = $(PSP_CC) $(PSP_CXXFLAGS) $(PSP_INCS)


$(PSP_OBJS_DIR)%.o : $(PSP_SRC_DIR)%.c
	$(PSP_CC) $(PSP_CFLAGS) $(PSP_INCS) -c $< -o $@

$(PSP_OBJS_DIR)%.o : $(PSP_SRC_DIR)%.cpp
	$(PSP_CXX) $(PSP_CXXFLAGS) $(PSP_INCS) -c $< -o $@

$(PSP_OBJS_DIR)%.o : $(PSP_SRC_DIR)%.S
	$(PSP_CC) $(PSP_CFLAGS) $(PSP_INCS) -c $< -o $@

$(PSP_OBJS_DIR)%.o : $(PSP_SRC_DIR)%.s
	$(PSP_AS) $(PSP_ASFLAGS) $< -o $@

$(PSP_LIB_DIR):
	$(MKDIR) -p $(PSP_LIB_DIR)

$(PSP_BIN_DIR):
	$(MKDIR) -p $(PSP_BIN_DIR)

$(PSP_OBJS_DIR):
	$(MKDIR) -p $(PSP_OBJS_DIR)

$(PSP_BIN) : $(PSP_OBJS) $(PSPSDKSRC)/psp/startup/obj/crt0.o
	$(PSP_CC) -mno-crt0 -T$(PSPSDKSRC)/psp/startup/src/linkfile $(PSP_LDFLAGS) \
		-o $(PSP_BIN) $(PSPSDKSRC)/psp/startup/obj/crt0.o $(PSP_OBJS) $(PSP_LIBS)

$(PSP_LIB) : $(PSP_OBJS)
	$(PSP_AR) cru $(PSP_LIB) $(PSP_OBJS)

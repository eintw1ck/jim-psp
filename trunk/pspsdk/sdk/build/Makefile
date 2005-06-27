# PSP Software Development Kit - http://www.pspdev.org
# -----------------------------------------------------------------------
# Licensed under the BSD license, see LICENSE in PSPSDK root for details.
#
# Makefile - Base makefile for projects using PSPSDK.
#
# Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
# Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
# Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
#
# $Id$

# program defs
PSP_CC = psp-gcc
PSP_CXX = psp-g++
PSP_LD = psp-gcc
PSP_AR = psp-ar

# Include directories
PSP_INCS := -I$(PSPSDK)/include -I. $(PSP_INCS)

# C compiler flags
PSP_CFLAGS := -O2 -G0 -Wall $(PSP_CFLAGS)

# C++ compiler flags
PSP_CXXFLAGS := -O2 -G0 -Wall $(PSP_CXXFLAGS)

# Linker flags
PSP_LDFLAGS := -O0 -G0 -L$(PSPSDK)/lib $(PSP_LDFLAGS)

# Assembler flags
PSP_ASFLAGS := -G0 $(PSP_ASFLAGS)

# Link with following libraries.  This is a special case, and instead of
# allowing the user to override the library order, we always make sure
# libkernel is the last library to be linked.
PSP_LIBS += -lgcc -lkernel

# Define the overridable parameters for the EBOOT

ifndef PSP_EBOOT_TITLE
PSP_EBOOT_TITLE = PSPSDK
endif

ifndef PSP_EBOOT_SFO
PSP_EBOOT_SFO = PARAM.SFO
endif

ifndef PSP_EBOOT_ICON
PSP_EBOOT_ICON = $(PSPSDK)/build/res/ICON0.PNG
endif

ifndef PSP_EBOOT_ICON1
PSP_EBOOT_ICON1 = NULL
endif

ifndef PSP_EBOOT_UNKPNG
PSP_EBOOT_UNKPNG = NULL
endif

ifndef PSP_EBOOT_PIC1
PSP_EBOOT_PIC1 = NULL
endif

ifndef PSP_EBOOT_SND0
PSP_EBOOT_SND0 = NULL
endif

ifndef PSP_EBOOT_PSAR
PSP_EBOOT_PSAR = NULL
endif

# Externally defined variables: PSP_BIN, PSP_OBJS, PSP_LIB

# These macros can be used to simplify certain build rules.
PSP_C_COMPILE = $(PSP_CC) $(PSP_CFLAGS) $(PSP_INCS)
PSP_CXX_COMPILE = $(PSP_CXX) $(PSP_CXXFLAGS) $(PSP_INCS)

%.o : %.c
	$(PSP_CC) $(PSP_CFLAGS) $(PSP_INCS) -c $< -o $@

%.o : %.cpp
	$(PSP_CXX) $(PSP_CXXFLAGS) $(PSP_INCS) -c $< -o $@

%.o : %.S
	$(PSP_CC) $(PSP_CFLAGS) $(PSP_INCS) -c $< -o $@

%.o : %.s
	$(PSP_AS) $(PSP_ASFLAGS) $< -o $@

%.SFO : 
	$(PSPSDK)/bin/mksfo '$(PSP_EBOOT_TITLE)' $(PSP_EBOOT_SFO)

$(PSP_BIN) : $(PSP_OBJS) 
	$(PSP_LD) $(PSP_LDFLAGS) -o $(PSP_BIN).fix $(PSP_OBJS) $(PSP_LIBS)
	$(PSPSDK)/bin/prxtool -p -o $(PSP_BIN) $(PSP_BIN).fix 
	rm -f $(PSP_BIN).fix

$(PSP_LIB) : $(PSP_OBJS)
	$(PSP_AR) cru $(PSP_LIB) $(PSP_OBJS)

$(PSP_EBOOT) : $(PSP_BIN) $(PSP_EBOOT_SFO)
	$(PSPSDK)/bin/pack-pbp EBOOT.PBP $(PSP_EBOOT_SFO) $(PSP_EBOOT_ICON)  \
		     $(PSP_EBOOT_ICON1) $(PSP_EBOOT_UNKPNG) $(PSP_EBOOT_PIC1)  \
			 $(PSP_EBOOT_SND0)  $(PSP_BIN) $(PSP_EBOOT_PSAR)

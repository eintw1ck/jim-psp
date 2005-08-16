TARGET = psppacker
OBJS = main.o payload.o

INCDIR =
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
#USE_PSPSDK_LIBC = 1

LIBDIR =
LDFLAGS =

LIBS = -lpspdebug -lpspsdk -lpsplibc -lpspdisplay -lpspge
# 
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Module loader

PSPSDK=$(shell psp-config --pspsdk-path)
#include $(PSPSDK)/lib/build.mak

CC       = psp-gcc
CXX      = psp-g++
AS       = psp-gcc
LD       = psp-gcc
AR       = psp-ar
RANLIB   = psp-ranlib
STRIP    = psp-strip
MKSFO    = mksfo
PACK_PBP = pack-pbp

# Add in PSPSDK includes and libraries.
INCDIR   := $(INCDIR) . $(PSPSDK)/include
LIBDIR   := $(LIBDIR) . $(PSPSDK)/lib

CFLAGS   := $(addprefix -I,$(INCDIR)) $(CFLAGS)
CXXFLAGS := $(CFLAGS) $(CXXFLAGS)
ASFLAGS  := $(CFLAGS) $(ASFLAGS)

LDFLAGS  := $(addprefix -L,$(LIBDIR)) $(LDFLAGS) -mno-crt0 -nostartfiles
LIBS     := $(LIBS) $(PSPSDK_LIBS) -lpspuser -lpspkernel
FINAL_TARGET = $(TARGET).elf

# Define the overridable parameters for EBOOT.PBP
ifndef PSP_EBOOT_TITLE
PSP_EBOOT_TITLE = $(TARGET)
endif

ifndef PSP_EBOOT_SFO
PSP_EBOOT_SFO = PARAM.SFO
endif

ifndef PSP_EBOOT_ICON
PSP_EBOOT_ICON = NULL
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

ifndef PSP_EBOOT
PSP_EBOOT = EBOOT.PBP
endif

all: $(FINAL_TARGET)
clean: $(EXTRA_CLEAN)
	-rm -f $(FINAL_TARGET) $(OBJS) $(PSP_EBOOT_SFO) $(PSP_EBOOT) $(EXTRA_TARGETS)
	
$(TARGET).elf: $(OBJS)
	$(LINK.c) $^ $(LIBS) -o $@
	psp-strip $(TARGET).elf
$(PSP_EBOOT_SFO): 
	$(MKSFO) '$(PSP_EBOOT_TITLE)' $@

$(PSP_EBOOT): $(TARGET).elf $(PSP_EBOOT_SFO)
	$(STRIP) $(TARGET).elf -o $(TARGET)_strip.elf
	$(PACK_PBP) EBOOT.PBP $(PSP_EBOOT_SFO) $(PSP_EBOOT_ICON)  \
		$(PSP_EBOOT_ICON1) $(PSP_EBOOT_UNKPNG) $(PSP_EBOOT_PIC1)  \
		$(PSP_EBOOT_SND0)  $(TARGET)_strip.elf $(PSP_EBOOT_PSAR)
	-rm -f $(TARGET)_strip.elf
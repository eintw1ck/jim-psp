TARGET = pspstub
OBJS = main.o

INCDIR = 
CFLAGS = -Os -G0 -Wall -DNDEBUG
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS = -mno-crt0 -nostartfiles -Tpacklink

LIBS = 

EXTRA_TARGETS = stripfile

stripfile: $(TARGET).elf
	psp-strip $^
	psp-strip -R .reginfo -R .comment -R .mdebug.eabi32 -R .gcc_compiled_long32 $^
	touch stripfile

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

TARGET = cube
OBJS = cube.o

INCDIR = ../../include
CFLAGS = -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS= -lpspgu

PSP_DIR_NAME=CUBE
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = SceGu Cube

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

TARGET = asciidemo
OBJS = main.o

INCDIR = ../libpspirkeyb/include
CFLAGS = -O2 -G0 -Wall -g
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR = ../libpspirkeyb
LDFLAGS =

LIBS = -lpspirkeyb -lpsppower

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = IR Keyb ASCii Test

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

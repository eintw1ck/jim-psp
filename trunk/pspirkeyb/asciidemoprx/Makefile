TARGET = asciidemo
OBJS = main.o

INCDIR = ../libpspirkeyb/include ../libpspirkeybprx/include
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR = ../libpspirkeybprx
LDFLAGS =

LIBS = -lpspirkeybprx -lpsppower

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = IR Keyb ASCii Test Prx

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

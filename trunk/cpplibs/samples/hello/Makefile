TARGET = hello
OBJS = main.o menu.o

INCDIR =
CFLAGS = -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS = -lpspsnd -lpsp2d -lmikmod -lmmio -lpspaudiolib -lpspaudio -lpspgu -lpng -lz -lm -lstdc++ -ljpeg

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Hello World

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

TARGET = sdltest
OBJS = sdltest.o

INCDIR = 
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP kxploit
EXTRA_CLEAN = my-clean

PSP_EBOOT_TITLE = SDL Test v1.1
PSP_DIR_NAME = SDLTEST

PSPSDK=$(shell psp-config --pspsdk-path)
PSPBIN = $(PSPSDK)/../bin
CFLAGS += `$(PSPBIN)/sdl-config --cflags`
LIBS += `$(PSPBIN)/sdl-config --libs`
include $(PSPSDK)/lib/build.mak

# Use "make pc" to build a copy of sdltest that runs on your PC.
pc:
	gcc -o sdltest-pc sdltest.c `sdl-config --cflags` `sdl-config --libs`

my-clean:
	rm -rf $(TARGET) $(TARGET)% sdltest-pc
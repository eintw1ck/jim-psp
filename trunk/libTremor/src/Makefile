PSPSDK = $(shell psp-config --pspsdk-path)
PSPDIR = $(shell psp-config --psp-prefix)

TARGET_LIB = ../lib/libvorbisidec.a
OBJS = mdct.o block.o window.o synthesis.o info.o floor1.o floor0.o vorbisfile.o res012.o mapping0.o registry.o codebook.o sharedbook.o framing.o bitwise.o
CFLAGS = -O2 -G0 -Wall -I../include $(PSP_CFLAGS) -DSTDC_HEADERS=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1 -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 -DHAVE_DLFCN_H=1 -DHAVE_ALLOCA_H=1 -DHAVE_ALLOCA=1 -fsigned-char -D_REENTRANT
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
USE_PSPSDK_LIBC = 1
include $(PSPSDK)/lib/build.mak

install: $(PSP_LIB)
	@echo "Installing Tremor into $(PSPDIR)"
	@mkdir  -p $(PSPDIR)/include $(PSPDIR)/lib
	@cp ../include/ogg.h $(PSPDIR)/include
	@cp ../include/os_types.h $(PSPDIR)/include
	@cp ../include/config_types.h $(PSPDIR)/include
	@cp ../include/ivorbisfile.h $(PSPDIR)/include
	@cp ../include/ivorbiscodec.h $(PSPDIR)/include
	@cp ../lib/libvorbisidec.a $(PSPDIR)/lib
	@echo "Done."


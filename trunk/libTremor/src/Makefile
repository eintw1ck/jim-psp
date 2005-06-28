PSPSDK=$(shell psp-config --pspsdk-path)
PSPLIBSDIR = $(PSPSDK)/..

TARGET_LIB = ../lib/libvorbisidec.a
OBJS = mdct.o block.o window.o synthesis.o info.o floor1.o floor0.o vorbisfile.o res012.o mapping0.o registry.o codebook.o sharedbook.o framing.o bitwise.o
CFLAGS = -O2 -G0 -Wall -I../include $(PSP_CFLAGS) -DSTDC_HEADERS=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1 -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 -DHAVE_DLFCN_H=1 -DHAVE_ALLOCA_H=1 -DHAVE_ALLOCA=1 -fsigned-char  -D_REENTRANT
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

include $(PSPSDK)/lib/build.mak

install: $(PSP_LIB)
	@echo "Installing Tremor into $(PSPLIBSDIR)/libTremor"
	@mkdir  -p $(PSPLIBSDIR)/libTremor/include $(PSPLIBSDIR)/libTremor/lib
	@cp ../include/ogg.h $(PSPLIBSDIR)/libTremor/include
	@cp ../include/os_types.h $(PSPLIBSDIR)/libTremor/include
	@cp ../include/config_types.h $(PSPLIBSDIR)/libTremor/include
	@cp ../include/ivorbisfile.h $(PSPLIBSDIR)/libTremor/include
	@cp ../include/ivorbiscodec.h $(PSPLIBSDIR)/libTremor/include
	@cp ../lib/libvorbisidec.a $(PSPLIBSDIR)/libTremor/lib
	@echo "Done."


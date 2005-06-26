PSPDEV = $(shell psp-config --pspsdk-path)/..
PSPSDK = $(shell psp-config --pspsdk-path)
PSP_LIB = ../lib/libvorbisidec.a
PSP_OBJS = mdct.o block.o window.o synthesis.o info.o floor1.o floor0.o vorbisfile.o res012.o mapping0.o registry.o codebook.o sharedbook.o framing.o bitwise.o
PSP_CFLAGS := -I../include $(PSP_CFLAGS) -DSTDC_HEADERS=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1 -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 -DHAVE_DLFCN_H=1 -DHAVE_ALLOCA_H=1 -DHAVE_ALLOCA=1 -fsigned-char  -D_REENTRANT
PSP_LDFLAGS :=  -v $(PSP_LDFLAGS)

all: $(PSP_LIB)

install: $(PSP_LIB)
	@echo "Installing Tremor into $(PSPDEV)/include/libTremor"
	@mkdir  -p $(PSPDEV)/libraries/libTremor/include $(PSPDEV)/libraries/libTremor/lib
	@cp ../include/ogg.h $(PSPDEV)/libraries/libTremor/include
	@cp ../include/os_types.h $(PSPDEV)/libraries/libTremor/include
	@cp ../include/config_types.h $(PSPDEV)/libraries/libTremor/include
	@cp ../include/ivorbisfile.h $(PSPDEV)/libraries/libTremor/include
	@cp ../include/ivorbiscodec.h $(PSPDEV)/libraries/libTremor/include
	@cp ../lib/libvorbisidec.a $(PSPDEV)/libraries/libTremor/lib
	@echo "Done."
	
clean:
	rm -f *.o $(PSP_LIB)

include $(PSPSDK)/lib/Makefile


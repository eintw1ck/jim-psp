PSP_LIB = ../lib/libmad.a
PSP_OBJS = bit.o decoder.o fixed.o frame.o huffman.o layer12.o layer3.o \
	stream.o synth.o timer.o version.o

install: $(PSP_LIB)


PSP_CFLAGS += -DHAVE_CONFIG_H -DHAVE_SYS_TYPES_H -DHAVE_ERRNO_H -DHAVE_UNISTD_H \
	-DHAVE_FCNTL_H -I$(PSPSDK)/include/sys/  -I../include

all: $(PSP_LIB)

clean:
	rm -f *.o $(PSP_LIB)
	
include $(PSPSDK)/build/Makefile.pref
include $(PSPSDK)/build/Makefile.global


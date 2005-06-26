PSPSDK=$(shell psp-config --pspsdk-path)
PSPDEV=$(shell psp-config --pspsdk-path)/../
PSP_LIB = ../lib/libmad.a
PSP_OBJS = bit.o decoder.o fixed.o frame.o huffman.o layer12.o layer3.o \
	stream.o synth.o timer.o version.o

PSP_CFLAGS += -DHAVE_CONFIG_H -DHAVE_SYS_TYPES_H -DHAVE_ERRNO_H -DHAVE_UNISTD_H \
	-DHAVE_FCNTL_H -I$(PSPSDK)/include/sys/  -I../include

all: $(PSP_LIB)

install: $(PSP_LIB)
	@echo "Installing libmad into $(PSPDEV)/libraries/libmad"
	@mkdir -p $(PSPDEV)/libraries/libmad/include $(PSPDEV)/libraries/libmad/lib
	@cp ../include/mad.h $(PSPDEV)/libraries/libmad/includ
	@cp ../lib/libmad.a  $(PSPDEV)/libraries/libmad/lib
	@echo "Done"
clean:
	rm -f *.o $(PSP_LIB)
	
include $(PSPSDK)/lib/Makefile


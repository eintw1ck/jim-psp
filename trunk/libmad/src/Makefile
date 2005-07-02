PSPSDK=$(shell psp-config --pspsdk-path)
PSPLIBSDIR=$(PSPSDK)/..
TARGET_LIB = ../lib/libmad.a
OBJS = bit.o decoder.o fixed.o frame.o huffman.o layer12.o layer3.o \
	stream.o synth.o timer.o version.o

CFLAGS += -DHAVE_CONFIG_H -DHAVE_SYS_TYPES_H -DHAVE_ERRNO_H -DHAVE_UNISTD_H \
	-DHAVE_FCNTL_H -I$(PSPSDK)/include/sys/  -I../include


install: $(TARGET_LIB)
	@echo "Installing libmad into $(PSPLIBSDIR)/libmad"
	@mkdir -p $(PSPLIBSDIR)/libmad/include $(PSPLIBSDIR)/libmad/lib
	@cp ../include/mad.h $(PSPLIBSDIR)/libmad/include
	@cp ../lib/libmad.a  $(PSPLIBSDIR)/libmad/lib
	@echo "Done"
	
include $(PSPSDK)/lib/build.mak


PSPSDK=$(shell psp-config --pspsdk-path)
PSPLIBSDIR=$(PSPSDK)/..
TARGET_LIB = libz.a
OBJS = 	adler32.o compress.o crc32.o gzio.o uncompr.o deflate.o trees.o \
	zutil.o inflate.o infback.o inftrees.o inffast.o

CFLAGS = -O2 -G0

include $(PSPSDK)/lib/build.mak

install: $(TARGET_LIB)
	@echo "Installing libz into $(PSPLIBSDIR)"
	@mkdir -p $(PSPLIBSDIR)/include $(PSPLIBSDIR)/lib
	@cp zlib.h zconf.h $(PSPLIBSDIR)/include
	@cp libz.a  $(PSPLIBSDIR)/lib
	@echo "Done"

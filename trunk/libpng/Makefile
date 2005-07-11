PSPSDK=$(shell psp-config --pspsdk-path)
PSPLIBSDIR=$(PSPSDK)/..
TARGET_LIB = libpng.a
OBJS = png.o pngerror.o pngget.o pngmem.o pngpread.o \
	pngread.o pngrio.o pngrtran.o pngrutil.o pngset.o \
	pngtrans.o pngwio.o pngwrite.o pngwtran.o pngwutil.o

CFLAGS = -O2 -G0

include $(PSPSDK)/lib/build.mak

install: $(TARGET_LIB)
	@echo "Installing libpng into $(PSPLIBSDIR)"
	@mkdir -p $(PSPLIBSDIR)/include $(PSPLIBSDIR)/lib
	@cp png.h pngconf.h $(PSPLIBSDIR)/include
	@cp libpng.a  $(PSPLIBSDIR)/lib
	@echo "Done"

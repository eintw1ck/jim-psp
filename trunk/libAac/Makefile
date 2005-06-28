PSPSDK = $(shell psp-config --pspsdk-path)
PSPLIBSDIR = $(PSPSDK)/..

TARGET_LIB = lib/libAac.a
OBJS = src/aactabs.o src/aacdec.o src/bitstream.o src/fft.o src/noiseless.o src/sbrhfadj.o src/sbrqmf.o src/trigtabs.o src/buffers.o src/filefmt.o src/pns.o src/sbrhfgen.o src/sbrside.o src/trigtabs_fltgen.o src/dct4.o src/huffman.o src/sbr.o src/sbrhuff.o src/sbrtabs.o src/decelmnt.o src/hufftabs.o src/sbrfft.o src/sbrimdct.o src/stproc.o src/dequant.o src/imdct.o src/sbrfreq.o src/sbrmath.o src/tns.o
INCDIR = include src
EXTRA_CLEAN = extra-clean

CFLAGS = -O2 -G0 -Wall -D__ALLEGREX__ -DUSE_DEFAULT_STDLIB
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

include $(PSPSDK)/lib/build.mak

extra-clean:
	rm -f src/*.o
install: 
	@echo "Installing libAac into $(PSPLIBSDIR)/libAac"
	@mkdir -p $(PSPLIBSDIR)/libAac/include $(PSPLIBSDIR)/libAac/lib
	@cp include/aaccommon.h $(PSPLIBSDIR)/libAac/include
	@cp include/aacdec.h $(PSPLIBSDIR)/libAac/include
	@cp include/statname.h $(PSPLIBSDIR)/libAac/include
	@cp lib/libAac.a  $(PSPLIBSDIR)/libAac/lib
	@echo "Done"

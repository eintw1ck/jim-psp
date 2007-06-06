# MikMod Library Makefile for PSP
# Divine Entertainment Game Programming Pack

PSPSDK=$(shell psp-config --pspsdk-path)
PSPDIR=$(shell psp-config --psp-prefix)

####################
### User Options ###
####################

# Use the C or C++ compiler
CC                = psp-gcc 
CFLAGS  = -G0 -O2 -I. -I../include -I$(PSPSDK)/include -g -DPSP

Lib_file          = ../lib/libmikmod.a

LoaderObjs        = mloader.o mlreg.o npertab.o sloader.o load_uni.o mwav.o \
    load_mod.o load_m15.o load_mtm.o load_s3m.o load_stm.o load_669.o \
    load_far.o load_dsm.o load_med.o load_xm.o load_ult.o load_it.o \
    s3m_it.o load_wav.o

DriverObjs        = mdriver.o mdreg.o drv_nos.o drv_raw.o drv_wav.o drv_psp.o

PlayerObjs        = mplayer.o

####################
## Makefile rules ##
####################

all: $(Lib_file)

$(Lib_file): stream.o virtch.o munitrk.o \
	$(LoaderObjs) $(DriverObjs) $(PlayerObjs)
	psp-ar r $(Lib_file) stream.o virtch.o munitrk.o \
        $(LoaderObjs) $(PlayerObjs) $(DriverObjs)

clean:
	rm -f *.o
	rm -f unix_drv/*.o
	rm -f $(Lib_file)

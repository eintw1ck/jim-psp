
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel

CHNNLSV_OBJS = sceChnnlsv_0000.o sceChnnlsv_0001.o sceChnnlsv_0002.o sceChnnlsv_0003.o sceChnnlsv_0004.o sceChnnlsv_0005.o sceChnnlsv_0006.o

libpspchnnlsvincludedir = @PSPSDK_INCLUDEDIR@
libpspchnnlsvinclude_HEADERS = pspchnnlsv.h 

lib_LIBRARIES = libpspchnnlsv.a
libpspchnnlsv_a_SOURCES = sceChnnlsv.S
libpspchnnlsv_a_LIBADD = $(CHNNLSV_OBJS)

$(CHNNLSV_OBJS): sceChnnlsv.S
	$(COMPILE) -DF_$* $< -c -o $@

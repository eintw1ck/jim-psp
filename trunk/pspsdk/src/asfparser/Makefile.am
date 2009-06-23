
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel

ASF_OBJS = sceAsfParser_0000.o sceAsfParser_0001.o sceAsfParser_0002.o sceAsfParser_0003.o sceAsfParser_0004.o sceAsfParser_0005.o sceAsfParser_0006.o sceAsfParser_0007.o sceAsfParser_0008.o sceAsfParser_0009.o sceAsfParser_0010.o sceAsfParser_0011.o sceAsfParser_0012.o sceAsfParser_0013.o

libpspasfparserincludedir = @PSPSDK_INCLUDEDIR@
libpspasfparserinclude_HEADERS = pspasfparser.h

lib_LIBRARIES = libpspasfparser.a


libpspasfparser_a_SOURCES = sceAsfParser.S
libpspasfparser_a_LIBADD = $(ASF_OBJS)

$(ASF_OBJS): sceAsfParser.S
	$(COMPILE) -DF_$* $< -c -o $@


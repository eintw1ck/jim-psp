
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/user -I$(top_srcdir)/src/debug
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES)

AUDIO_OBJS = sceAudio_0000.o sceAudio_0001.o sceAudio_0002.o sceAudio_0003.o sceAudio_0004.o sceAudio_0005.o sceAudio_0006.o sceAudio_0007.o sceAudio_0008.o sceAudio_0009.o sceAudio_0010.o sceAudio_0011.o sceAudio_0012.o sceAudio_0013.o sceAudio_0014.o sceAudio_0015.o sceAudio_0016.o sceAudio_0017.o sceAudio_0018.o sceAudio_0019.o

libpspaudioincludedir = @PSPSDK_INCLUDEDIR@
libpspaudioinclude_HEADERS = pspaudio.h

libpspaudiolibincludedir = @PSPSDK_INCLUDEDIR@
libpspaudiolibinclude_HEADERS = pspaudiolib.h

lib_LIBRARIES = libpspaudio.a libpspaudiolib.a

libpspaudio_a_SOURCES = sceAudio.S
libpspaudio_a_LIBADD = $(AUDIO_OBJS)

libpspaudiolib_a_SOURCES = pspaudiolib.c

$(AUDIO_OBJS): sceAudio.S
	$(COMPILE) -DF_$* $< -c -o $@

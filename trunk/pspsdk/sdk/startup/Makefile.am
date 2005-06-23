
CC = @PSP_CC@
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base

## Borrow this trick from newlib - create a dummy library to generate build rules.
noinst_LIBRARIES = lib.a
lib_a_SOURCES = dummy.c dummyasm.S

startupdir = @PSPDEV_LIBDIR@
startup_DATA = crt0.o

all: crt0.o

CLEANFILES = crt0.o

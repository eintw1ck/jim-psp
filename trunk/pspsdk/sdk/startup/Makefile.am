
CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel -I$(top_srcdir)/sdk/user
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES)

## Borrow this trick from newlib - create a dummy library to generate build rules.
noinst_LIBRARIES = lib.a
lib_a_SOURCES = dummy.c

startupdir = @PSPDEV_LIBDIR@
startup_DATA = crt0.o

all: crt0.o

CLEANFILES = crt0.o

## How else do I add a dependency for this?
EXTRA_DIST = crt0.c

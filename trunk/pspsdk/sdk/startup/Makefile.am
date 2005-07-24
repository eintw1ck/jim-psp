
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

all: crt0.o

startupdir = @PSPDEV_LIBDIR@
install-exec-hook:
	$(mkinstalldirs) $(DESTDIR)$(startupdir)
	$(INSTALL_DATA) crt0.o $(DESTDIR)$(startupdir)/crt0.o

uninstall-hook:
	rm -f $(DESTDIR)$(startupdir)/crt0.o

CLEANFILES = crt0.o

## How else do I add a dependency for this?
EXTRA_DIST = crt0.c

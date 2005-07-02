
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel

libpsphprmincludedir = @PSPSDK_INCLUDEDIR@
libpsphprminclude_HEADERS = psphprm.h

lib_LIBRARIES = libpsphprm.a
libpsphprm_a_SOURCES = hprm.S


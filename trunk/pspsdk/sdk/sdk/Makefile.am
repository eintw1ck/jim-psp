
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base \
	   -I$(top_srcdir)/sdk/kernel \
	   -I$(top_srcdir)/sdk/user
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES)

libpspsdkincludedir = @PSPSDK_INCLUDEDIR@
libpspsdkinclude_HEADERS = pspsdk.h

lib_LIBRARIES = libpspsdk.a

libpspsdk_a_SOURCES =		\
	query_mod.c

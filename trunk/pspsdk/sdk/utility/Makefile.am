
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel

libpsputilityincludedir = @PSPSDK_INCLUDEDIR@
libpsputilityinclude_HEADERS = psputility.h \
                               psputility_sysparam.h \
                               psputility_netconf.h \
                               psputility_netparam.h \
                               psputility_msgdialog.h

lib_LIBRARIES = libpsputility.a
libpsputility_a_SOURCES = utility.S


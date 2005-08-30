
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel

HPRM_OBJS = sceHprm_0000.o sceHprm_0001.o sceHprm_0002.o sceHprm_0003.o sceHprm_0004.o sceHprm_0005.o sceHprm_0006.o sceHprm_0007.o sceHprm_0008.o 

libpsphprmincludedir = @PSPSDK_INCLUDEDIR@
libpsphprminclude_HEADERS = psphprm.h

lib_LIBRARIES = libpsphprm.a
libpsphprm_a_SOURCES = sceHprm.S
libpsphprm_a_LIBADD  = $(HPRM_OBJS)

$(HPRM_OBJS): sceHprm.S
	$(COMPILE) -DF_$* $< -c -o $@


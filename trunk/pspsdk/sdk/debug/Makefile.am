
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base

libpspdebugincludedir = @PSPSDK_INCLUDEDIR@
libpspdebuginclude_HEADERS =	\
	pspdebug.h

lib_LIBRARIES = libpspdebug.a

libpspdebug_a_SOURCES =		\
	callstack.c		\
	callstackget.S		\
	font.c			\
	scr_printf.c	\
	exception.c	\
	exception_asm.S \
	modmgr.c	\
	kprintf.c	

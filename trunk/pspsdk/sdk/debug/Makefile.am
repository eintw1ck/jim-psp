
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel -I$(top_srcdir)/sdk/display -I$(top_srcdir)/sdk/ge
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
	kprintf.c	\
	stacktrace.c	

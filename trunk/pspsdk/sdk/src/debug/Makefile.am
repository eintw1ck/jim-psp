
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(srcdir) -I$(top_srcdir)/sdk/include

libpspdebugincludedir = @PSPSDK_INCLUDEDIR@
libpspdebuginclude_HEADERS =	\
	pspdebug.h

lib_LIBRARIES = libpspdebug.a

libpspdebug_a_SOURCES =		\
	callstack.c		\
	callstackget.S		\
	font.c			\
	scr_printf.c

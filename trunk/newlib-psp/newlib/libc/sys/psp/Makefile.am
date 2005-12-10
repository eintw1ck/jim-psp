## Process this file with automake to generate Makefile.in

AUTOMAKE_OPTIONS = cygnus

INCLUDES = $(NEWLIB_CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS)

noinst_LIBRARIES = lib.a

LIBCGLUE_MULT_OBJS = _close.o _exit.o _fork.o _fstat.o _getpid.o	\
                     _gettimeofday.o _kill.o _lseek.o _open.o _read.o	\
                     _sbrk.o _wait.o _write.o clock.o isatty.o time.o	\
                     _link.o _unlink.o sleep.o opendir.o readdir.o	\
                     closedir.o getcwd.o chdir.o mkdir.o rmdir.o	\
                     realpath.o _stat.o truncate.o access.o tzset.o	\
                     __psp_set_errno.o	

SOCKET_MULT_OBJS = socket.o accept.o bind.o connect.o getsockopt.o \
				   listen.o recv.o recvfrom.o send.o sendto.o \
				   setsockopt.o shutdown.o __psp_socket_map.o \
				   getsockname.o getpeername.o

XPRINTF_MULT_OBJS = vxprintf.o _xprintf.o __sout.o vsnprintf.o snprintf.o vsprintf.o sprintf.o __mout.o mprintf.o vmprintf.o asprintf.o vasprintf.o __fout.o fprintf.o vfprintf.o printf.o vprintf.o _sprintf_r.o

lib_a_SOURCES = libcglue.c socket.c pspcwd.c xprintf.c
lib_a_LIBADD  = $(LIBCGLUE_MULT_OBJS) $(SOCKET_MULT_OBJS) $(XPRINTF_MULT_OBJS)

all: crt0.o

$(LIBCGLUE_MULT_OBJS): libcglue.c
	$(COMPILE) -DF_$* $< -c -o $@

$(SOCKET_MULT_OBJS): socket.c
	$(COMPILE) -DF_$* $< -c -o $@

$(XPRINTF_MULT_OBJS): xprintf.c
	$(COMPILE) -DF_$* $< -c -o $@

ACLOCAL_AMFLAGS = -I ../../..
CONFIG_STATUS_DEPENDENCIES = $(newlib_basedir)/configure.host

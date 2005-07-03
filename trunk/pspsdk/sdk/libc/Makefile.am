
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CXX = @PSP_CXX@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CXXFLAGS = @PSPSDK_CXXFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base

EXTRA_DIST = LIB.status

lib_LIBRARIES = libpsplibc.a libpspglue.a

## libpsplibc.a sources.
CORE_SOURCES = terminate.c setjmp.S qsort.c init.c cxx.cpp
MULT_SOURCES = xprintf.c alloc.c string.c stdio.c stdlib.c

ALLOC_OBJS = malloc.o realloc.o calloc.o memalign.o free.o __builtin_alloc.o __alloc_internals.o __mem_walk.o

STRING_C_OBJS = strdup.o strcasecmp.o strncasecmp.o strtok.o strrchr.o strstr.o \
	strupr.o strlwr.o _sjis_internals.o strcpy_ascii.o strcpy_sjis.o \
	strpbrk.o strspn.o strcspn.o memchr.o memcmp.o memcpy.o memmove.o \
	memset.o strcat.o strchr.o strcmp.o strcpy.o strlen.o strncat.o strncmp.o strncpy.o \
	tolower.o toupper.o isupper.o islower.o isalpha.o isdigit.o isalnum.o iscntrl.o \
	isgraph.o isprint.o ispunct.o isspace.o isxdigit.o

XPRINTF_OBJS = vxprintf.o _xprintf.o __sout.o vsnprintf.o snprintf.o vsprintf.o sprintf.o \
	__mout.o mprintf.o vmprintf.o __fout.o fprintf.o vfprintf.o printf.o vprintf.o putchar.o \
	asprintf.o vasprintf.o 

STDIO_OBJS = clearerr.o fclose.o fcloseall.o feof.o ferror.o fflush.o fflushall.o fgetc.o \
	fgetpos.o fgets.o fopen.o fputc.o fputs.o fread.o fseek.o fsetpos.o ftell.o fwrite.o fileno.o \
	getc.o getchar.o getfdtype.o gets.o perror.o putc.o puts.o remove.o rename.o fdopen.o \
	rewind.o skipatoi.o sscanf.o _stdio.o tmpfile.o tmpnam.o ungetc.o updatestdoutxy.o strerror.o \
	__stdio_internals.o 

STDLIB_OBJS = abs.o atexit.o atof.o bsearch.o div.o getenv.o _itoa.o labs.o \
	ldiv.o llabs.o lldiv.o _lltoa.o _ltoa.o rand.o setenv.o srand.o \
	strtod.o strtol.o strtoul.o __assert_fail.o \
	__stdlib_internals.o 

## Use a few functions from libpspglue.a.
GLUE_OBJS = glue__exit.o glue__sbrk.o glue___errno.o glue_clock.o glue_gettimeofday.o glue_time.o

MULT_OBJS = $(XPRINTF_OBJS) $(ALLOC_OBJS) $(STRING_C_OBJS) $(STDIO_OBJS) $(STDLIB_OBJS) $(GLUE_OBJS)

libpsplibc_a_SOURCES = $(CORE_SOURCES) $(MULT_SOURCES)
libpsplibc_a_LIBADD  = $(MULT_OBJS)

$(XPRINTF_OBJS): xprintf.c
	$(COMPILE) -DF_$* $< -c -o $@

$(ALLOC_OBJS): alloc.c
	$(COMPILE) -DF_$* $< -c -o $@

$(STRING_C_OBJS): string.c
	$(COMPILE) -DF_$* $< -c -o $@

$(STDIO_OBJS): stdio.c
	$(COMPILE) -DF_$* $< -c -o $@

$(STDLIB_OBJS): stdlib.c
	$(COMPILE) -DF_$* $< -c -o $@

$(GLUE_OBJS): libcglue.c
	$(COMPILE) -DF_$* $< -c -o $@

## libpspglue.a sources.
LIBCGLUE_MULT_OBJS = _close.o _exit.o _fork.o _fstat.o _getpid.o _gettimeofday.o _kill.o _lseek.o \
	_open.o _read.o _sbrk.o _wait.o _write.o clock.o isatty.o time.o

libpspglue_a_SOURCES = libcglue.c
libpspglue_a_LIBADD  = $(LIBCGLUE_MULT_OBJS)

$(LIBCGLUE_MULT_OBJS): libcglue.c
	$(COMPILE) -DF_$* $< -c -o $@

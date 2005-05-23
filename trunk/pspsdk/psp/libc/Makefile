# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# Copyright 2001-2004, ps2dev - http://www.ps2dev.org
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
#
# $Id$

.SUFFIXES:.c
VPATH = src:obj

LIBC_LIB  = lib/libc.a

PSP_OBJS_DIR = obj/
PSP_LIB_DIR = lib/
PSP_SRC_DIR = src/
PSP_INC_DIR = include/

PSP_LIB = $(LIBC_LIB)


CORE_OBJS = sbrk.o terminate.o setjmp.o qsort.o init.o cxx.o
CORE_OBJS := $(CORE_OBJS:%=$(PSP_OBJS_DIR)%)

ALLOC_OBJS = malloc.o realloc.o calloc.o memalign.o free.o __builtin_alloc.o __alloc_internals.o __mem_walk.o
ALLOC_OBJS := $(ALLOC_OBJS:%=$(PSP_OBJS_DIR)%)

STRING_C_OBJS = strdup.o strcasecmp.o strncasecmp.o strtok.o strrchr.o strstr.o \
    strupr.o strlwr.o _sjis_internals.o strcpy_ascii.o strcpy_sjis.o \
    strpbrk.o strspn.o strcspn.o memchr.o memcmp.o memcpy.o memmove.o \
    memset.o strcat.o strchr.o strcmp.o strcpy.o strlen.o strncat.o strncmp.o strncpy.o \
    tolower.o toupper.o isupper.o islower.o isalpha.o isdigit.o isalnum.o iscntrl.o \
    isgraph.o isprint.o ispunct.o isspace.o isxdigit.o
STRING_C_OBJS := $(STRING_C_OBJS:%=$(PSP_OBJS_DIR)%)

XPRINTF_OBJS = vxprintf.o xprintf.o __sout.o vsnprintf.o snprintf.o vsprintf.o sprintf.o \
	__mout.o mprintf.o vmprintf.o __fout.o fprintf.o vfprintf.o printf.o vprintf.o putchar.o \
	asprintf.o vasprintf.o 
XPRINTF_OBJS := $(XPRINTF_OBJS:%=$(PSP_OBJS_DIR)%)

STDIO_OBJS = clearerr.o fclose.o fcloseall.o feof.o ferror.o fflush.o fflushall.o fgetc.o \
	fgetpos.o fgets.o fopen.o fputc.o fputs.o fread.o fseek.o fsetpos.o ftell.o fwrite.o fileno.o \
	getc.o getchar.o getfdtype.o gets.o perror.o putc.o puts.o remove.o rename.o fdopen.o \
	rewind.o skipatoi.o sscanf.o stdio.o tmpfile.o tmpnam.o ungetc.o updatestdoutxy.o strerror.o \
	__stdio_internals.o 
STDIO_OBJS := $(STDIO_OBJS:%=$(PSP_OBJS_DIR)%)

STDLIB_OBJS = abs.o atexit.o atof.o bsearch.o div.o getenv.o _itoa.o labs.o \
	ldiv.o llabs.o lldiv.o _lltoa.o _ltoa.o rand.o setenv.o srand.o \
	strtod.o strtol.o strtoul.o __assert_fail.o \
	__stdlib_internals.o 
# multibytes hell... do we want it ? is it stable ??
# mblen.o mbstowcs.o mbtowc.o wcstombs.o wctomb.o
STDLIB_OBJS := $(STDLIB_OBJS:%=$(PSP_OBJS_DIR)%)

TIME_OBJS = clock.o
TIME_OBJS := $(TIME_OBJS:%=$(PSP_OBJS_DIR)%)

MULT_OBJS = $(XPRINTF_OBJS) $(ALLOC_OBJS) $(STRING_C_OBJS) $(STDIO_OBJS) $(STDLIB_OBJS) $(TIME_OBJS)

PSP_OBJS = $(CORE_OBJS) $(MULT_OBJS)

all: $(PSP_OBJS_DIR) $(PSP_LIB_DIR) $(LIBC_LIB) 


.c.o :
	$(PSP_CC) $(PSP_CFLAGS) $(PSP_INC) -c $< -o obj/$@

$(XPRINTF_OBJS): src/xprintf.c
	$(PSP_C_COMPILE) -DF_$(*:$(PSP_OBJS_DIR)%=%) $< -c -o $@

$(ALLOC_OBJS): src/alloc.c
	$(PSP_C_COMPILE) -DF_$(*:$(PSP_OBJS_DIR)%=%) $< -c -o $@

$(STRING_C_OBJS): src/string.c
	$(PSP_C_COMPILE) -DF_$(*:$(PSP_OBJS_DIR)%=%) $< -c -o $@

$(STDIO_OBJS): src/stdio.c
	$(PSP_C_COMPILE) -DF_$(*:$(PSP_OBJS_DIR)%=%) $< -c -o $@

$(STDLIB_OBJS): src/stdlib.c
	$(PSP_C_COMPILE) -DF_$(*:$(PSP_OBJS_DIR)%=%) $< -c -o $@

$(TIME_OBJS): src/time.c
	$(PSP_C_COMPILE) -DF_$(*:$(PSP_OBJS_DIR)%=%) $< -c -o $@


clean:
	rm -f -r $(PSP_OBJS_DIR) $(PSP_LIB_DIR)


include $(PSPSDKSRC)/Defs.make
include $(PSPSDKSRC)/psp/Rules.make
include $(PSPSDKSRC)/psp/Rules.release

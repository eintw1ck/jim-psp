
CC = @PSP_CC@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@

EXTRA_DIST = $(srcdir)/testfiles/dummy

noinst_PROGRAMS = psplibctests.elf

psplibctests_elf_SOURCES =	\
	runner.c		\
	testsuite.c		\
	stdio_tests.c

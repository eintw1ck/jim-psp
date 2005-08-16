
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/user
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES)

libpspkernelincludedir = @PSPSDK_INCLUDEDIR@

libpspkernelinclude_HEADERS =	\
	pspiofilemgr_kernel.h	\
	pspkernel.h		\
	psploadcore.h		\
	pspstdio_kernel.h	\
	pspsysreg.h		\
	psputilsforkernel.h
	
lib_LIBRARIES = libpspkernel.a

libpspkernel_a_SOURCES =	\
	ExceptionManagerForKernel.S \
	KDebugForKernel.S	\
	LoadCoreForKernel.S	\
	iofilemgr_kernel.S	\
	StdioForKernel.S	\
	sceSysreg_driver.S	\
	utils.S
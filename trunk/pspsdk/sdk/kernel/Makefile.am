
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/user
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES)

EXCEPTION_OBJS = ExceptionManagerForKernel_0000.o ExceptionManagerForKernel_0001.o ExceptionManagerForKernel_0002.o ExceptionManagerForKernel_0003.o ExceptionManagerForKernel_0004.o ExceptionManagerForKernel_0005.o ExceptionManagerForKernel_0006.o ExceptionManagerForKernel_0007.o ExceptionManagerForKernel_0008.o 

KDEBUG_OBJS = KDebugForKernel_0000.o KDebugForKernel_0001.o KDebugForKernel_0002.o KDebugForKernel_0003.o KDebugForKernel_0004.o KDebugForKernel_0005.o KDebugForKernel_0006.o KDebugForKernel_0007.o KDebugForKernel_0008.o KDebugForKernel_0009.o KDebugForKernel_0010.o KDebugForKernel_0011.o KDebugForKernel_0012.o KDebugForKernel_0013.o KDebugForKernel_0014.o KDebugForKernel_0015.o KDebugForKernel_0016.o KDebugForKernel_0017.o KDebugForKernel_0018.o KDebugForKernel_0019.o KDebugForKernel_0020.o 

LOADCORE_OBJS = LoadCoreForKernel_0000.o LoadCoreForKernel_0001.o LoadCoreForKernel_0002.o LoadCoreForKernel_0003.o LoadCoreForKernel_0004.o LoadCoreForKernel_0005.o LoadCoreForKernel_0006.o LoadCoreForKernel_0007.o LoadCoreForKernel_0008.o LoadCoreForKernel_0009.o LoadCoreForKernel_0010.o LoadCoreForKernel_0011.o LoadCoreForKernel_0012.o LoadCoreForKernel_0013.o LoadCoreForKernel_0014.o LoadCoreForKernel_0015.o LoadCoreForKernel_0016.o LoadCoreForKernel_0017.o LoadCoreForKernel_0018.o LoadCoreForKernel_0019.o LoadCoreForKernel_0020.o LoadCoreForKernel_0021.o LoadCoreForKernel_0022.o LoadCoreForKernel_0023.o LoadCoreForKernel_0024.o LoadCoreForKernel_0025.o LoadCoreForKernel_0026.o LoadCoreForKernel_0027.o LoadCoreForKernel_0028.o LoadCoreForKernel_0029.o LoadCoreForKernel_0030.o 

IO_OBJS = IoFileMgrForKernel_0000.o IoFileMgrForKernel_0001.o IoFileMgrForKernel_0002.o IoFileMgrForKernel_0003.o IoFileMgrForKernel_0004.o IoFileMgrForKernel_0005.o IoFileMgrForKernel_0006.o IoFileMgrForKernel_0007.o IoFileMgrForKernel_0008.o IoFileMgrForKernel_0009.o IoFileMgrForKernel_0010.o IoFileMgrForKernel_0011.o IoFileMgrForKernel_0012.o IoFileMgrForKernel_0013.o IoFileMgrForKernel_0014.o IoFileMgrForKernel_0015.o IoFileMgrForKernel_0016.o IoFileMgrForKernel_0017.o IoFileMgrForKernel_0018.o IoFileMgrForKernel_0019.o IoFileMgrForKernel_0020.o IoFileMgrForKernel_0021.o IoFileMgrForKernel_0022.o IoFileMgrForKernel_0023.o IoFileMgrForKernel_0024.o IoFileMgrForKernel_0025.o IoFileMgrForKernel_0026.o IoFileMgrForKernel_0027.o IoFileMgrForKernel_0028.o IoFileMgrForKernel_0029.o IoFileMgrForKernel_0030.o IoFileMgrForKernel_0031.o IoFileMgrForKernel_0032.o IoFileMgrForKernel_0033.o IoFileMgrForKernel_0034.o IoFileMgrForKernel_0035.o IoFileMgrForKernel_0036.o IoFileMgrForKernel_0037.o IoFileMgrForKernel_0038.o IoFileMgrForKernel_0039.o IoFileMgrForKernel_0040.o IoFileMgrForKernel_0041.o IoFileMgrForKernel_0042.o 

STDIO_OBJS = StdioForKernel_0000.o StdioForKernel_0001.o StdioForKernel_0002.o StdioForKernel_0003.o StdioForKernel_0004.o StdioForKernel_0005.o StdioForKernel_0006.o StdioForKernel_0007.o StdioForKernel_0008.o StdioForKernel_0009.o StdioForKernel_0010.o StdioForKernel_0011.o StdioForKernel_0012.o StdioForKernel_0013.o StdioForKernel_0014.o StdioForKernel_0015.o 

SYSREG_OBJS = sceSysreg_driver_0000.o sceSysreg_driver_0001.o sceSysreg_driver_0002.o sceSysreg_driver_0003.o sceSysreg_driver_0004.o sceSysreg_driver_0005.o sceSysreg_driver_0006.o sceSysreg_driver_0007.o sceSysreg_driver_0008.o sceSysreg_driver_0009.o sceSysreg_driver_0010.o sceSysreg_driver_0011.o sceSysreg_driver_0012.o sceSysreg_driver_0013.o sceSysreg_driver_0014.o sceSysreg_driver_0015.o sceSysreg_driver_0016.o sceSysreg_driver_0017.o sceSysreg_driver_0018.o sceSysreg_driver_0019.o sceSysreg_driver_0020.o sceSysreg_driver_0021.o sceSysreg_driver_0022.o sceSysreg_driver_0023.o sceSysreg_driver_0024.o sceSysreg_driver_0025.o sceSysreg_driver_0026.o sceSysreg_driver_0027.o sceSysreg_driver_0028.o sceSysreg_driver_0029.o sceSysreg_driver_0030.o sceSysreg_driver_0031.o sceSysreg_driver_0032.o sceSysreg_driver_0033.o sceSysreg_driver_0034.o sceSysreg_driver_0035.o sceSysreg_driver_0036.o sceSysreg_driver_0037.o sceSysreg_driver_0038.o sceSysreg_driver_0039.o sceSysreg_driver_0040.o sceSysreg_driver_0041.o sceSysreg_driver_0042.o sceSysreg_driver_0043.o sceSysreg_driver_0044.o sceSysreg_driver_0045.o sceSysreg_driver_0046.o sceSysreg_driver_0047.o sceSysreg_driver_0048.o sceSysreg_driver_0049.o sceSysreg_driver_0050.o sceSysreg_driver_0051.o sceSysreg_driver_0052.o sceSysreg_driver_0053.o sceSysreg_driver_0054.o sceSysreg_driver_0055.o sceSysreg_driver_0056.o sceSysreg_driver_0057.o sceSysreg_driver_0058.o sceSysreg_driver_0059.o sceSysreg_driver_0060.o sceSysreg_driver_0061.o sceSysreg_driver_0062.o sceSysreg_driver_0063.o sceSysreg_driver_0064.o sceSysreg_driver_0065.o sceSysreg_driver_0066.o sceSysreg_driver_0067.o sceSysreg_driver_0068.o sceSysreg_driver_0069.o sceSysreg_driver_0070.o sceSysreg_driver_0071.o sceSysreg_driver_0072.o sceSysreg_driver_0073.o sceSysreg_driver_0074.o sceSysreg_driver_0075.o sceSysreg_driver_0076.o sceSysreg_driver_0077.o sceSysreg_driver_0078.o sceSysreg_driver_0079.o sceSysreg_driver_0080.o sceSysreg_driver_0081.o sceSysreg_driver_0082.o sceSysreg_driver_0083.o sceSysreg_driver_0084.o sceSysreg_driver_0085.o sceSysreg_driver_0086.o sceSysreg_driver_0087.o sceSysreg_driver_0088.o sceSysreg_driver_0089.o sceSysreg_driver_0090.o sceSysreg_driver_0091.o sceSysreg_driver_0092.o sceSysreg_driver_0093.o sceSysreg_driver_0094.o sceSysreg_driver_0095.o sceSysreg_driver_0096.o sceSysreg_driver_0097.o sceSysreg_driver_0098.o sceSysreg_driver_0099.o sceSysreg_driver_0100.o sceSysreg_driver_0101.o sceSysreg_driver_0102.o sceSysreg_driver_0103.o sceSysreg_driver_0104.o sceSysreg_driver_0105.o sceSysreg_driver_0106.o sceSysreg_driver_0107.o sceSysreg_driver_0108.o sceSysreg_driver_0109.o sceSysreg_driver_0110.o sceSysreg_driver_0111.o sceSysreg_driver_0112.o sceSysreg_driver_0113.o sceSysreg_driver_0114.o sceSysreg_driver_0115.o sceSysreg_driver_0116.o sceSysreg_driver_0117.o sceSysreg_driver_0118.o sceSysreg_driver_0119.o sceSysreg_driver_0120.o sceSysreg_driver_0121.o sceSysreg_driver_0122.o sceSysreg_driver_0123.o sceSysreg_driver_0124.o sceSysreg_driver_0125.o sceSysreg_driver_0126.o sceSysreg_driver_0127.o sceSysreg_driver_0128.o sceSysreg_driver_0129.o sceSysreg_driver_0130.o sceSysreg_driver_0131.o sceSysreg_driver_0132.o sceSysreg_driver_0133.o sceSysreg_driver_0134.o sceSysreg_driver_0135.o sceSysreg_driver_0136.o sceSysreg_driver_0137.o sceSysreg_driver_0138.o sceSysreg_driver_0139.o sceSysreg_driver_0140.o sceSysreg_driver_0141.o sceSysreg_driver_0142.o sceSysreg_driver_0143.o sceSysreg_driver_0144.o sceSysreg_driver_0145.o sceSysreg_driver_0146.o sceSysreg_driver_0147.o sceSysreg_driver_0148.o sceSysreg_driver_0149.o sceSysreg_driver_0150.o sceSysreg_driver_0151.o 

UTILS_OBJS = UtilsForKernel_0000.o UtilsForKernel_0001.o UtilsForKernel_0002.o UtilsForKernel_0003.o UtilsForKernel_0004.o UtilsForKernel_0005.o UtilsForKernel_0006.o UtilsForKernel_0007.o UtilsForKernel_0008.o UtilsForKernel_0009.o UtilsForKernel_0010.o UtilsForKernel_0011.o UtilsForKernel_0012.o UtilsForKernel_0013.o UtilsForKernel_0014.o UtilsForKernel_0015.o UtilsForKernel_0016.o UtilsForKernel_0017.o UtilsForKernel_0018.o UtilsForKernel_0019.o UtilsForKernel_0020.o UtilsForKernel_0021.o UtilsForKernel_0022.o UtilsForKernel_0023.o UtilsForKernel_0024.o UtilsForKernel_0025.o UtilsForKernel_0026.o UtilsForKernel_0027.o UtilsForKernel_0028.o UtilsForKernel_0029.o UtilsForKernel_0030.o UtilsForKernel_0031.o UtilsForKernel_0032.o UtilsForKernel_0033.o UtilsForKernel_0034.o UtilsForKernel_0035.o UtilsForKernel_0036.o UtilsForKernel_0037.o UtilsForKernel_0038.o UtilsForKernel_0039.o 

SYSCON_OBJS = sceSyscon_driver_0000.o sceSyscon_driver_0001.o sceSyscon_driver_0002.o sceSyscon_driver_0003.o sceSyscon_driver_0004.o sceSyscon_driver_0005.o sceSyscon_driver_0006.o sceSyscon_driver_0007.o sceSyscon_driver_0008.o sceSyscon_driver_0009.o sceSyscon_driver_0010.o sceSyscon_driver_0011.o sceSyscon_driver_0012.o sceSyscon_driver_0013.o sceSyscon_driver_0014.o sceSyscon_driver_0015.o sceSyscon_driver_0016.o sceSyscon_driver_0017.o sceSyscon_driver_0018.o sceSyscon_driver_0019.o sceSyscon_driver_0020.o sceSyscon_driver_0021.o sceSyscon_driver_0022.o sceSyscon_driver_0023.o sceSyscon_driver_0024.o sceSyscon_driver_0025.o sceSyscon_driver_0026.o sceSyscon_driver_0027.o sceSyscon_driver_0028.o sceSyscon_driver_0029.o sceSyscon_driver_0030.o sceSyscon_driver_0031.o sceSyscon_driver_0032.o sceSyscon_driver_0033.o sceSyscon_driver_0034.o sceSyscon_driver_0035.o sceSyscon_driver_0036.o sceSyscon_driver_0037.o sceSyscon_driver_0038.o sceSyscon_driver_0039.o sceSyscon_driver_0040.o sceSyscon_driver_0041.o sceSyscon_driver_0042.o sceSyscon_driver_0043.o sceSyscon_driver_0044.o sceSyscon_driver_0045.o sceSyscon_driver_0046.o sceSyscon_driver_0047.o sceSyscon_driver_0048.o sceSyscon_driver_0049.o sceSyscon_driver_0050.o sceSyscon_driver_0051.o sceSyscon_driver_0052.o sceSyscon_driver_0053.o sceSyscon_driver_0054.o sceSyscon_driver_0055.o sceSyscon_driver_0056.o sceSyscon_driver_0057.o sceSyscon_driver_0058.o sceSyscon_driver_0059.o sceSyscon_driver_0060.o sceSyscon_driver_0061.o sceSyscon_driver_0062.o sceSyscon_driver_0063.o sceSyscon_driver_0064.o sceSyscon_driver_0065.o sceSyscon_driver_0066.o sceSyscon_driver_0067.o sceSyscon_driver_0068.o sceSyscon_driver_0069.o sceSyscon_driver_0070.o sceSyscon_driver_0071.o sceSyscon_driver_0072.o sceSyscon_driver_0073.o sceSyscon_driver_0074.o sceSyscon_driver_0075.o sceSyscon_driver_0076.o sceSyscon_driver_0077.o sceSyscon_driver_0078.o sceSyscon_driver_0079.o sceSyscon_driver_0080.o sceSyscon_driver_0081.o sceSyscon_driver_0082.o sceSyscon_driver_0083.o sceSyscon_driver_0084.o sceSyscon_driver_0085.o sceSyscon_driver_0086.o sceSyscon_driver_0087.o sceSyscon_driver_0088.o sceSyscon_driver_0089.o sceSyscon_driver_0090.o sceSyscon_driver_0091.o sceSyscon_driver_0092.o sceSyscon_driver_0093.o sceSyscon_driver_0094.o sceSyscon_driver_0095.o sceSyscon_driver_0096.o sceSyscon_driver_0097.o sceSyscon_driver_0098.o sceSyscon_driver_0099.o sceSyscon_driver_0100.o sceSyscon_driver_0101.o sceSyscon_driver_0102.o sceSyscon_driver_0103.o sceSyscon_driver_0104.o sceSyscon_driver_0105.o sceSyscon_driver_0106.o sceSyscon_driver_0107.o sceSyscon_driver_0108.o sceSyscon_driver_0109.o sceSyscon_driver_0110.o sceSyscon_driver_0111.o sceSyscon_driver_0112.o sceSyscon_driver_0113.o 

libpspkernelincludedir = @PSPSDK_INCLUDEDIR@

libpspkernelinclude_HEADERS =	\
	pspiofilemgr_kernel.h	\
	pspkernel.h		\
	psploadcore.h		\
	pspstdio_kernel.h	\
	pspsysreg.h		\
	psputilsforkernel.h \
	pspkdebug.h
	
lib_LIBRARIES = libpspkernel.a

libpspkernel_a_SOURCES =	\
	ExceptionManagerForKernel.S \
	KDebugForKernel.S	\
	LoadCoreForKernel.S	\
	IoFileMgrForKernel.S	\
	StdioForKernel.S	\
	sceSyscon_driver.S	\
	sceSysreg_driver.S	\
	UtilsForKernel.S
libpspkernel_a_LIBADD = $(EXCEPTION_OBJS) $(KDEBUG_OBJS) $(LOADCORE_OBJS) $(IO_OBJS) \
						$(STDIO_OBJS) $(SYSREG_OBJS) $(UTILS_OBJS) $(SYSCON_OBJS)

$(EXCEPTION_OBJS): ExceptionManagerForKernel.S
	$(COMPILE) -DF_$* $< -c -o $@

$(KDEBUG_OBJS): KDebugForKernel.S
	$(COMPILE) -DF_$* $< -c -o $@

$(LOADCORE_OBJS): LoadCoreForKernel.S
	$(COMPILE) -DF_$* $< -c -o $@

$(IO_OBJS): IoFileMgrForKernel.S
	$(COMPILE) -DF_$* $< -c -o $@

$(STDIO_OBJS): StdioForKernel.S
	$(COMPILE) -DF_$* $< -c -o $@

$(SYSREG_OBJS): sceSysreg_driver.S
	$(COMPILE) -DF_$* $< -c -o $@

$(UTILS_OBJS): UtilsForKernel.S
	$(COMPILE) -DF_$* $< -c -o $@

$(SYSCON_OBJS): sceSyscon_driver.S
	$(COMPILE) -DF_$* $< -c -o $@

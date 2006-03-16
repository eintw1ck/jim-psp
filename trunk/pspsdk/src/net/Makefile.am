
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES)

NET_OBJS = sceNet_0000.o sceNet_0001.o sceNet_0002.o sceNet_0003.o sceNet_0004.o sceNet_0005.o sceNet_0006.o sceNet_0007.o sceNet_0008.o 

NETLIB_OBJS = sceNet_lib_0000.o sceNet_lib_0001.o sceNet_lib_0002.o sceNet_lib_0003.o sceNet_lib_0004.o sceNet_lib_0005.o sceNet_lib_0006.o sceNet_lib_0007.o sceNet_lib_0008.o sceNet_lib_0009.o sceNet_lib_0010.o sceNet_lib_0011.o sceNet_lib_0012.o sceNet_lib_0013.o sceNet_lib_0014.o sceNet_lib_0015.o sceNet_lib_0016.o sceNet_lib_0017.o sceNet_lib_0018.o sceNet_lib_0019.o sceNet_lib_0020.o sceNet_lib_0021.o sceNet_lib_0022.o sceNet_lib_0023.o sceNet_lib_0024.o sceNet_lib_0025.o sceNet_lib_0026.o sceNet_lib_0027.o sceNet_lib_0028.o sceNet_lib_0029.o sceNet_lib_0030.o sceNet_lib_0031.o sceNet_lib_0032.o sceNet_lib_0033.o sceNet_lib_0034.o sceNet_lib_0035.o sceNet_lib_0036.o sceNet_lib_0037.o sceNet_lib_0038.o sceNet_lib_0039.o sceNet_lib_0040.o sceNet_lib_0041.o sceNet_lib_0042.o sceNet_lib_0043.o sceNet_lib_0044.o sceNet_lib_0045.o sceNet_lib_0046.o sceNet_lib_0047.o sceNet_lib_0048.o sceNet_lib_0049.o sceNet_lib_0050.o sceNet_lib_0051.o sceNet_lib_0052.o sceNet_lib_0053.o sceNet_lib_0054.o sceNet_lib_0055.o sceNet_lib_0056.o sceNet_lib_0057.o sceNet_lib_0058.o sceNet_lib_0059.o sceNet_lib_0060.o sceNet_lib_0061.o sceNet_lib_0062.o sceNet_lib_0063.o sceNet_lib_0064.o sceNet_lib_0065.o sceNet_lib_0066.o sceNet_lib_0067.o sceNet_lib_0068.o sceNet_lib_0069.o sceNet_lib_0070.o sceNet_lib_0071.o sceNet_lib_0072.o sceNet_lib_0073.o sceNet_lib_0074.o sceNet_lib_0075.o sceNet_lib_0076.o sceNet_lib_0077.o sceNet_lib_0078.o sceNet_lib_0079.o sceNet_lib_0080.o sceNet_lib_0081.o sceNet_lib_0082.o sceNet_lib_0083.o sceNet_lib_0084.o sceNet_lib_0085.o sceNet_lib_0086.o sceNet_lib_0087.o sceNet_lib_0088.o sceNet_lib_0089.o sceNet_lib_0090.o sceNet_lib_0091.o sceNet_lib_0092.o sceNet_lib_0093.o sceNet_lib_0094.o sceNet_lib_0095.o sceNet_lib_0096.o 

NET_APCTL_OBJS = sceNetApctl_0000.o sceNetApctl_0001.o sceNetApctl_0002.o sceNetApctl_0003.o sceNetApctl_0004.o sceNetApctl_0005.o sceNetApctl_0006.o sceNetApctl_0007.o sceNetApctl_0008.o 

NET_INET_OBJS = sceNetInet_0000.o sceNetInet_0001.o sceNetInet_0002.o sceNetInet_0003.o sceNetInet_0004.o sceNetInet_0005.o sceNetInet_0006.o sceNetInet_0007.o sceNetInet_0008.o sceNetInet_0009.o sceNetInet_0010.o sceNetInet_0011.o sceNetInet_0012.o sceNetInet_0013.o sceNetInet_0014.o sceNetInet_0015.o sceNetInet_0016.o sceNetInet_0017.o sceNetInet_0018.o sceNetInet_0019.o sceNetInet_0020.o sceNetInet_0021.o sceNetInet_0022.o sceNetInet_0023.o sceNetInet_0024.o sceNetInet_0025.o sceNetInet_0026.o sceNetInet_0027.o sceNetInet_0028.o sceNetInet_0029.o sceNetInet_0030.o 

NET_RESOLVER_OBJS = sceNetResolver_0000.o sceNetResolver_0001.o sceNetResolver_0002.o sceNetResolver_0003.o sceNetResolver_0004.o sceNetResolver_0005.o sceNetResolver_0006.o sceNetResolver_0007.o 

NET_ADHOC_OBJS = sceNetAdhoc_0000.o sceNetAdhoc_0001.o sceNetAdhoc_0002.o sceNetAdhoc_0003.o sceNetAdhoc_0004.o sceNetAdhoc_0005.o sceNetAdhoc_0006.o sceNetAdhoc_0007.o sceNetAdhoc_0008.o sceNetAdhoc_0009.o sceNetAdhoc_0010.o sceNetAdhoc_0011.o sceNetAdhoc_0012.o sceNetAdhoc_0013.o sceNetAdhoc_0014.o sceNetAdhoc_0015.o sceNetAdhoc_0016.o sceNetAdhoc_0017.o sceNetAdhoc_0018.o sceNetAdhoc_0019.o sceNetAdhoc_0020.o sceNetAdhoc_0021.o sceNetAdhoc_0022.o sceNetAdhoc_0023.o sceNetAdhoc_0024.o sceNetAdhoc_0025.o 

NET_ADHOCCTL_OBJS = sceNetAdhocctl_0000.o sceNetAdhocctl_0001.o sceNetAdhocctl_0002.o sceNetAdhocctl_0003.o sceNetAdhocctl_0004.o sceNetAdhocctl_0005.o sceNetAdhocctl_0006.o sceNetAdhocctl_0007.o sceNetAdhocctl_0008.o sceNetAdhocctl_0009.o sceNetAdhocctl_0010.o sceNetAdhocctl_0011.o sceNetAdhocctl_0012.o sceNetAdhocctl_0013.o sceNetAdhocctl_0014.o sceNetAdhocctl_0015.o sceNetAdhocctl_0016.o sceNetAdhocctl_0017.o sceNetAdhocctl_0018.o sceNetAdhocctl_0019.o sceNetAdhocctl_0020.o 

NET_ADHOCMATCHING_OBJS = sceNetAdhocMatching_0000.o sceNetAdhocMatching_0001.o sceNetAdhocMatching_0002.o sceNetAdhocMatching_0003.o sceNetAdhocMatching_0004.o sceNetAdhocMatching_0005.o sceNetAdhocMatching_0006.o sceNetAdhocMatching_0007.o sceNetAdhocMatching_0008.o sceNetAdhocMatching_0009.o sceNetAdhocMatching_0010.o sceNetAdhocMatching_0011.o sceNetAdhocMatching_0012.o 

libpspnetincludedir = @PSPSDK_INCLUDEDIR@
libpspnetinclude_HEADERS = pspnet.h			\
			   pspnet_apctl.h		\
			   pspnet_inet.h		\
			   pspnet_resolver.h	\
			   pspnet_adhoc.h		\
			   pspnet_adhocctl.h	\
			   pspnet_adhocmatching.h

lib_LIBRARIES = libpspnet.a			\
		libpspnet_apctl.a		\
		libpspnet_inet.a		\
		libpspnet_resolver.a	\
		libpspnet_adhoc.a		\
		libpspnet_adhocctl.a	\
		libpspnet_adhocmatching.a	

libpspnet_a_SOURCES = sceNet.S sceNet_lib.S
libpspnet_a_LIBADD  = $(NET_OBJS) $(NETLIB_OBJS)
libpspnet_apctl_a_SOURCES = sceNetApctl.S
libpspnet_apctl_a_LIBADD  = $(NET_APCTL_OBJS)
libpspnet_inet_a_SOURCES = sceNetInet.S
libpspnet_inet_a_LIBADD  = $(NET_INET_OBJS)
libpspnet_resolver_a_SOURCES = sceNetResolver.S
libpspnet_resolver_a_LIBADD  = $(NET_RESOLVER_OBJS)
libpspnet_adhoc_a_SOURCES = sceNetAdhoc.S
libpspnet_adhoc_a_LIBADD = $(NET_ADHOC_OBJS)
libpspnet_adhocctl_a_SOURCES = sceNetAdhocctl.S
libpspnet_adhocctl_a_LIBADD = $(NET_ADHOCCTL_OBJS)
libpspnet_adhocmatching_a_SOURCES = sceNetAdhocMatching.S
libpspnet_adhocmatching_a_LIBADD = $(NET_ADHOCMATCHING_OBJS)

$(NET_OBJS): sceNet.S
	$(COMPILE) -DF_$* $< -c -o $@

$(NETLIB_OBJS): sceNet_lib.S
	$(COMPILE) -DF_$* $< -c -o $@

$(NET_APCTL_OBJS): sceNetApctl.S
	$(COMPILE) -DF_$* $< -c -o $@

$(NET_INET_OBJS): sceNetInet.S
	$(COMPILE) -DF_$* $< -c -o $@

$(NET_RESOLVER_OBJS): sceNetResolver.S
	$(COMPILE) -DF_$* $< -c -o $@

$(NET_ADHOC_OBJS): sceNetAdhoc.S
	$(COMPILE) -DF_$* $< -c -o $@

$(NET_ADHOCCTL_OBJS): sceNetAdhocctl.S
	$(COMPILE) -DF_$* $< -c -o $@

$(NET_ADHOCMATCHING_OBJS): sceNetAdhocMatching.S
	$(COMPILE) -DF_$* $< -c -o $@

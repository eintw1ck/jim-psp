
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES)

NET_OBJS = sceNet_0000.o sceNet_0001.o sceNet_0002.o sceNet_0003.o sceNet_0004.o sceNet_0005.o sceNet_0006.o sceNet_0007.o sceNet_0008.o 

NET_APCTL_OBJS = sceNetApctl_0000.o sceNetApctl_0001.o sceNetApctl_0002.o sceNetApctl_0003.o sceNetApctl_0004.o sceNetApctl_0005.o sceNetApctl_0006.o sceNetApctl_0007.o sceNetApctl_0008.o 

NET_INET_OBJS = sceNetInet_0000.o sceNetInet_0001.o sceNetInet_0002.o sceNetInet_0003.o sceNetInet_0004.o sceNetInet_0005.o sceNetInet_0006.o sceNetInet_0007.o sceNetInet_0008.o sceNetInet_0009.o sceNetInet_0010.o sceNetInet_0011.o sceNetInet_0012.o sceNetInet_0013.o sceNetInet_0014.o sceNetInet_0015.o sceNetInet_0016.o sceNetInet_0017.o sceNetInet_0018.o sceNetInet_0019.o sceNetInet_0020.o sceNetInet_0021.o sceNetInet_0022.o sceNetInet_0023.o sceNetInet_0024.o sceNetInet_0025.o sceNetInet_0026.o sceNetInet_0027.o sceNetInet_0028.o sceNetInet_0029.o sceNetInet_0030.o 

NET_RESOLVER_OBJS = sceNetResolver_0000.o sceNetResolver_0001.o sceNetResolver_0002.o sceNetResolver_0003.o sceNetResolver_0004.o sceNetResolver_0005.o sceNetResolver_0006.o sceNetResolver_0007.o 

libpspnetincludedir = @PSPSDK_INCLUDEDIR@
libpspnetinclude_HEADERS = pspnet.h			\
			   pspnet_apctl.h		\
			   pspnet_inet.h		\
			   pspnet_resolver.h

lib_LIBRARIES = libpspnet.a			\
		libpspnet_apctl.a		\
		libpspnet_inet.a		\
		libpspnet_resolver.a

libpspnet_a_SOURCES = sceNet.S 
libpspnet_a_LIBADD  = $(NET_OBJS)
libpspnet_apctl_a_SOURCES = sceNetApctl.S
libpspnet_apctl_a_LIBADD  = $(NET_APCTL_OBJS)
libpspnet_inet_a_SOURCES = sceNetInet.S
libpspnet_inet_a_LIBADD  = $(NET_INET_OBJS)
libpspnet_resolver_a_SOURCES = sceNetResolver.S
libpspnet_resolver_a_LIBADD  = $(NET_RESOLVER_OBJS)

$(NET_OBJS): sceNet.S
	$(COMPILE) -DF_$* $< -c -o $@

$(NET_APCTL_OBJS): sceNetApctl.S
	$(COMPILE) -DF_$* $< -c -o $@

$(NET_INET_OBJS): sceNetInet.S
	$(COMPILE) -DF_$* $< -c -o $@

$(NET_RESOLVER_OBJS): sceNetResolver.S
	$(COMPILE) -DF_$* $< -c -o $@

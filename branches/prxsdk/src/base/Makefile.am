
pspsdkincludedir = @PSPSDK_INCLUDEDIR@

pspsdkinclude_HEADERS =		\
	as_reg_compat.h		\
	psptypes.h		\
	pspstub.s		\
	pspimport.s

## Install the build.mak fragment to $PSPSDK/lib.
buildmakdir = @PSPSDK_LIBDIR@
buildmak_DATA = build.mak

buildmakprxdir = @PSPSDK_LIBDIR@
buildmakprx_DATA = build_prx.mak linkfile.prx

EXTRA_DIST = build.mak build_prx.mak linkfile.prx

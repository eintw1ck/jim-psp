
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel -I$(top_srcdir)/sdk/display -I$(top_srcdir)/sdk/ge -I$(top_srcdir)/sdk/user
CFLAGS =  @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES)

libpspgumincludedir = @PSPSDK_INCLUDEDIR@
libpspguminclude_HEADERS = pspgum.h

lib_LIBRARIES = libpspgum.a

noinst_HEADERS = gumInternal.h

libpspgum_a_SOURCES = gumInternal.c sceGumLoadIdentity.c sceGumLoadMatrix.c sceGumMatrixMode.c \
                      sceGumMultMatrix.c sceGumOrtho.c sceGumPerspective.c sceGumPopMatrix.c \
                      sceGumPushMatrix.c sceGumScale.c sceGumTranslate.c sceGumUpdateMatrix.c \
                      sceGumStoreMatrix.c sceGumLookAt.c sceGumDrawArray.c sceGumDrawArrayN.c \
                      sceGumDrawBezier.c sceGumDrawSpline.c sceGumRotateX.c sceGumRotateY.c \
                      sceGumRotateZ.c sceGumRotateXYZ.c sceGumRotateZYX.c \
                      gumMultMatrix.c gumMakeIdentity.c gumCrossProduct.c gumNormalize.c

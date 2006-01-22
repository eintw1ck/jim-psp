
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel -I$(top_srcdir)/src/display -I$(top_srcdir)/src/ge -I$(top_srcdir)/src/user
CFLAGS =  @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES)

libpspgumincludedir = @PSPSDK_INCLUDEDIR@
libpspguminclude_HEADERS = pspgum.h

lib_LIBRARIES = libpspgum.a libpspgum_vfpu.a

noinst_HEADERS = gumInternal.h

PSPGUM_SHARED_OBJS =  gumLoadIdentity.o gumLoadMatrix.o gumOrtho.o gumPerspective.o \
                      gumScale.o gumTranslate.o gumLookAt.o gumRotateX.o gumRotateY.o \
                      gumRotateZ.o gumRotateXYZ.o gumRotateZYX.o gumFullInverse.o \
                      gumCrossProduct.o gumDotProduct.o gumNormalize.o \
                      sceGumDrawArray.o sceGumDrawArrayN.o sceGumDrawBezier.o sceGumDrawSpline.o \
                      sceGumRotateXYZ.o sceGumRotateZYX.o

PSPGUM_FPU_OBJS =     sceGumLoadIdentity.o sceGumLoadMatrix.o sceGumMatrixMode.o \
                      sceGumMultMatrix.o sceGumOrtho.o sceGumPerspective.o sceGumPopMatrix.o \
                      sceGumPushMatrix.o sceGumScale.o sceGumTranslate.o sceGumUpdateMatrix.o \
                      sceGumStoreMatrix.o sceGumLookAt.o sceGumRotateX.o sceGumRotateY.o \
                      sceGumRotateZ.o sceGumFullInverse.o sceGumFastInverse.o \
                      gumFastInverse.o gumMultMatrix.o

PSPGUM_VFPU_OBJS =    sceGumLoadIdentity_vfpu.o sceGumLoadMatrix_vfpu.o sceGumMatrixMode_vfpu.o \
                      sceGumMultMatrix_vfpu.o sceGumOrtho_vfpu.o sceGumPerspective_vfpu.o \
                      sceGumPopMatrix_vfpu.o sceGumPushMatrix_vfpu.o sceGumScale_vfpu.o \
                      sceGumTranslate_vfpu.o sceGumUpdateMatrix_vfpu.o sceGumStoreMatrix_vfpu.o \
                      sceGumLookAt_vfpu.o sceGumRotateX_vfpu.o sceGumRotateY_vfpu.o \
                      sceGumRotateZ_vfpu.o sceGumFullInverse_vfpu.o sceGumFastInverse_vfpu.o \
                      gumFastInverse_vfpu.o gumMultMatrix_vfpu.o

libpspgum_a_SOURCES = gumInternal.c pspgum.c
libpspgum_a_LIBADD = $(PSPGUM_FPU_OBJS) $(PSPGUM_SHARED_OBJS)

libpspgum_vfpu_a_SOURCES = gumInternal.c pspgum.c pspgum_vfpu.c
libpspgum_vfpu_a_LIBADD = $(PSPGUM_VFPU_OBJS) $(PSPGUM_SHARED_OBJS)

$(PSPGUM_SHARED_OBJS): pspgum.c
	$(COMPILE) -DF_$* $< -c -o $@

$(PSPGUM_FPU_OBJS): pspgum.c
	$(COMPILE) -DF_$* $< -c -o $@

$(PSPGUM_VFPU_OBJS): pspgum_vfpu.c
	$(COMPILE) -DF_$* $< -c -o $@

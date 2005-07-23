include ../config.mk

OBJS= api.o list.o vertex.o init.o matrix.o texture.o \
      misc.o clear.o light.o clip.o select.o get.o error.o \
      zbuffer.o zline.o zdither.o ztriangle.o \
      zmath.o image_util.o oscontext.o msghandling.o \
      arrays.o specbuf.o memory.o
ifdef TINYGL_USE_GLX
OBJS += glx.o
endif
ifdef TINYGL_USE_NANOX
OBJS += nglx.o
endif
ifdef TINYGL_USE_SDL
OBJS += sdlswgl.o
endif

INCLUDES = -I../include
LIB = libTinyGL.a

all: $(LIB)

$(LIB): $(OBJS)
	rm -f $(LIB)
	$(AR) rcs $(LIB) $(OBJS)
	cp $(LIB) ../lib

clean:
	rm -f *~ *.o *.a

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $*.c

clip.o: ../include/GL/zgl.h ../include/GL/zfeatures.h
vertex.o: ../include/GL/zgl.h ../include/GL/zfeatures.h
light.o: ../include/GL/zgl.h ../include/GL/zfeatures.h
matrix.o: ../include/GL/zgl.h ../include/GL/zfeatures.h
list.o: ../include/GL/zgl.h ../include/GL/opinfo.h ../include/GL/zfeatures.h
arrays.c: ../include/GL/zgl.h ../include/GL/zfeatures.h
specbuf.o: ../include/GL/zgl.h ../include/GL/zfeatures.h
glx.o: ../include/GL/zgl.h ../include/GL/zfeatures.h
nglx.o: ../include/GL/zgl.h ../include/GL/zfeatures.h
zline.o: ../include/GL/zgl.h ../include/GL/zfeatures.h ../include/GL/zline.h

ztriangle.o: ztriangle.c ../include/GL/ztriangle.h ../include/GL/zgl.h ../include/GL/zfeatures.h
	$(CC) $(CFLAGS) -Wno-uninitialized $(INCLUDES) -c $*.c

include ../../config.mk

OBJS= glu.o glu_sphere.o glu_disk.o glu_perspective.o \
      glu_cylinder.o glu_torus.o 

INCLUDES = -I../../include
LIB = libTinyGLU.a

all: $(LIB)

$(LIB): $(OBJS)
	rm -f $(LIB)
	$(AR) rcs $(LIB) $(OBJS)
	cp $(LIB) ../../lib

clean:
	rm -f *~ *.o *.a

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $*.c

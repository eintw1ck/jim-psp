include ../config.mk

LFLAGS += -L../lib

PROGS = mech texobj gears spin cube

all: $(PROGS)

clean:
	rm -f core *.o *~ $(PROGS)

cube: cube.o $(UI_OBJS) $(GL_DEPS)
	$(CC) $(LFLAGS) $^ -o $@ $(GL_LIBS) $(GLU_LIBS) $(UI_LIBS) -lm

mech: mech.o $(UI_OBJS) $(GL_DEPS)
	$(CC) $(LFLAGS) $^ -o $@ $(GL_LIBS) $(GLU_LIBS) $(UI_LIBS) -lm

texobj: texobj.o $(UI_OBJS) $(GL_DEPS)
	$(CC) $(LFLAGS) $^ -o $@ $(GL_LIBS) $(UI_LIBS) -lm

gears: gears.o $(UI_OBJS) $(GL_DEPS)
	$(CC) $(LFLAGS) $^ -o $@ $(GL_LIBS) $(UI_LIBS) -lm

spin: spin.o $(UI_OBJS) $(GL_DEPS)
	$(CC) $(LFLAGS) $^ -o $@ $(GL_LIBS) $(UI_LIBS) -lm

.c.o:
	$(CC)	$(CFLAGS) $(GL_INCLUDES) $(UI_INCLUDES) -c $*.c

ui.o: ui.h

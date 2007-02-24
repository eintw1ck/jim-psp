OUTPUT=remotejoy
OBJS=remotejoy.o font.o

CFLAGS=-O2 -Wall -g $(shell sdl-config --cflags)

all: remotejoy

$(OUTPUT): $(OBJS)
	$(CC) -o $@ $^ $(shell sdl-config --libs)

clean:
	rm -f $(OUTPUT) *.o

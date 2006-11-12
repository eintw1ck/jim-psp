OUTPUT=pspsh
OBJS=pspsh.o parse_args.o pspkerror.o

CFLAGS=-Wall -g -D_PCTERM -I../psplink
LIBS=-lreadline -lcurses

all: pspsh

$(OUTPUT): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

clean:
	rm -f $(OUTPUT) *.o

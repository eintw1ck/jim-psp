OUTPUT=pcterm
OBJS=pcterm.o

CFLAGS=-Wall -g -D_PCTERM -I../psplink
LIBS=-lreadline -lcurses

all: pcterm

$(OUTPUT): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

clean:
	rm -f $(OUTPUT) *.o

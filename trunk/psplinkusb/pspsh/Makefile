OUTPUT=pspsh
OBJS=pspsh.o parse_args.o pspkerror.o asm.o disasm.o

CXXFLAGS=-Wall -g -D_PCTERM -I../psplink
LIBS=-lreadline -lcurses

all: pspsh

$(OUTPUT): $(OBJS)
	$(CXX) -o $@ $^ $(LIBS)

clean:
	rm -f $(OUTPUT) *.o

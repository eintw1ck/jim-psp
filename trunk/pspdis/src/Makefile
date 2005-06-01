# Makefile for Dimunes
.SUFFIXES: # Delete the default suffixes 
.SUFFIXES: .c .o .s .exe

BIN  = ../pspdis.exe
OBJS = util.o bfd_replacement.o libopcodes_helper.o pspdis.o 
INCS = -I. -I../libopcodes
LIBS =  -lopcodes -lintl
LDFLAGS = -L../libopcodes
CFLAGS = -O2 -g -c -Wall $(INCS)

$(BIN) : $(OBJS)
	g++ $(LDFLAGS) -o $(BIN) $(OBJS) $(LIBS)

$(OBJS_DIR)%.o : %.cc
	g++ $(CFLAGS) $< -o $@
		
$(OBJS_DIR)%.o : %.c
	gcc $(CFLAGS) $< -o $@

$(OBJS_DIR)%.o : %.s
	as $(ASFLAGS) $< -o $@

$(OBJS_DIR)%.o : %.S
	gcc $(CFLAGS) $< -o $@
	
all: $(BIN)
	
clean:
	rm -f -r $(BIN) $(OBJS)

# Makefile for PSPDis
.SILENT:

.SUFFIXES: # Delete the default suffixes 
.SUFFIXES: .c .o .s .exe

# location of CONFIGURED binutils including the pspsdk patches
PSPBINUTILSSRC=/home/groepaz/Desktop/pspstuff/compiler/newtoolchain/binutils-2.16.1

# name and location of the final binary
BIN  = ../pspdis
#BIN  = ../pspdis.exe

# pspdis objects
OBJS = util.o bfd_replacement.o libopcodes_helper.o pspdis.o nidDb.o
# tinyxml objects 
OBJS+=../tinyxml/tinyxml.o ../tinyxml/tinystr.o ../tinyxml/tinyxmlparser.o ../tinyxml/tinyxmlerror.o
# libopcodes objects (from binutils)
OBJS+=$(PSPBINUTILSSRC)/opcodes/mips-dis.o $(PSPBINUTILSSRC)/opcodes/mips-opc.o 
OBJS+=$(PSPBINUTILSSRC)/opcodes/mips16-opc.o $(PSPBINUTILSSRC)/opcodes/dis-init.o
OBJS+=$(PSPBINUTILSSRC)/opcodes/dis-buf.o $(PSPBINUTILSSRC)/opcodes/disassemble.o 

INCS = -I. -I$(PSPBINUTILSSRC)/include -I$(PSPBINUTILSSRC)/opcodes -I$(PSPBINUTILSSRC)/bfd -I$(PSPBINUTILSSRC)/build-psp/opcodes/ -I../
LIBS=-lc 

LDFLAGS = -L$(PSPBINUTILSSRC)/opcodes
CFLAGS = -O2 -g -c -Wall $(INCS) 

# mmmh ?! doesnt work without, but nothing from libopcodes includes any header that defines it
CFLAGS+=-Dbfd_mach_mips_allegrex=10111431

$(BIN) : $(OBJS)
	g++ $(LDFLAGS) -o $(BIN) $(OBJS) $(LIBS)

$(OBJS_DIR)%.o : %.cpp
	g++ $(CFLAGS) $< -o $@
	
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
	rm -rf $(BIN) $(OBJS)

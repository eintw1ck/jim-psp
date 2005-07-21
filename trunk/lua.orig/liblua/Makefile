LUA= .
include $(LUA)/config
EXTRA_DEFS= $(POPEN) $(TMPNAM) $(DEGREES) $(LOADLIB)

PSPSDK=$(shell psp-config --pspsdk-path)
PSPLIBSDIR=$(PSPSDK)/..
TARGET_LIB = liblua.a
OBJS = src/lapi.o src/lcode.o src/ldebug.o src/ldo.o src/ldump.o src/lfunc.o \
	src/lgc.o src/llex.o src/lmem.o src/lobject.o src/lopcodes.o \
	src/lparser.o src/lstate.o src/lstring.o src/ltable.o src/ltests.o \
	src/ltm.o src/lundump.o src/lvm.o src/lzio.o \
	src/lib/lauxlib.o src/lib/lbaselib.o src/lib/ldblib.o \
	src/lib/liolib.o src/lib/lmathlib.o src/lib/ltablib.o \
	src/lib/lstrlib.o src/lib/loadlib.o

CFLAGS = -O2 -G0 -I./include

include $(PSPSDK)/lib/build.mak

install: $(TARGET_LIB)
	@echo "Installing Lua into $(PSPLIBSDIR)"
	@mkdir -p $(PSPLIBSDIR)/include $(PSPLIBSDIR)/lib
	@cp include/lua.h include/lualib.h include/lauxlib.h $(PSPLIBSDIR)/include
	@cp liblua.a  $(PSPLIBSDIR)/lib
	@echo "Done"


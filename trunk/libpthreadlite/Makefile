TARGET_LIB = libpthreadlite.a
OBJS = pthreadlite.o

INCDIR = 
CFLAGS = $(GLOBAL_CFLAGS) -O2 -Wall -g
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LDFLAGS = 
LIBS = 

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

install: $(TARGET_LIB)
	@cp -v $(TARGET_LIB) `psp-config --psp-prefix`/lib
	@cp -v *.h `psp-config --psp-prefix`/include
	@echo "Done."


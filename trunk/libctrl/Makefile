TARGET_LIB = libctrl.a
OBJS = libctrl.o

INCDIR = 
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =

PSPSDK=$(shell psp-config --pspsdk-path)
PSP_PREF=$(shell psp-config --psp-prefix)

include $(PSPSDK)/lib/build.mak


myclean:
	rm -f *~

install: all
	install -m644 $(TARGET_LIB) $(PSP_PREF)/lib
	install -m644 $(patsubst %.a,%.h,$(TARGET_LIB)) $(PSP_PREF)/include

uninstall:
	rm -f $(PSP_PREF)/lib/$(TARGET_LIB)
	rm -f $(PSP_PREF)/include/$(patsubst %.a,%.h,$(TARGET_LIB))

tags:
	etags --members --typedefs $(patsubst %.o,%.c,$(OBJS))

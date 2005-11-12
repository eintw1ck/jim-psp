
PSPSDK=$(shell psp-config --pspsdk-path)
PSPDIR=$(shell psp-config --psp-prefix)

TARGET_LIB = libpsp2d.a

OBJS = framebuffer.o Exception.o Drawable.o Screen.o Image.o Blitter.o Controller.o Font.o

CXXFLAGS = -O2 -G0
CPPFLAGS = -I..

include $(PSPSDK)/lib/build.mak

install: $(TARGET_LIB)
	@echo "Installing lib2d into $(PSPDIR)"
	@mkdir -p $(PSPDIR)/include $(PSPDIR)/lib
	@cp *.h $(PSPDIR)/include
	@cp *.il $(PSPDIR)/include
	@cp libpsp2d.a  $(PSPDIR)/lib
	@echo "Done"

doc:
	doxygen


PSPSDK=$(shell psp-config --pspsdk-path)
PSPDIR=$(shell psp-config --psp-prefix)

TARGET_LIB = libpspsnd.a

OBJS = Sound.o Music.o

CXXFLAGS = -O2 -G0 -Wall
CPPFLAGS = -I..

include $(PSPSDK)/lib/build.mak

install: $(TARGET_LIB)
	@echo "Installing libpspsnd into $(PSPDIR)"
	@mkdir -p $(PSPDIR)/include $(PSPDIR)/lib
	@cp *.h $(PSPDIR)/include
	@cp *.il $(PSPDIR)/include
	@cp libpspsnd.a  $(PSPDIR)/lib
	@echo "Done"

doc:
	doxygen

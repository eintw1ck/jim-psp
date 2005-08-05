PSPSDK=$(shell psp-config --pspsdk-path)
PSPDIR=$(shell psp-config --psp-prefix)

OBJS = example.o

LIBS = $(PSPDIR)/lib/libmikmod.a $(PSPDIR)/lib/libmmio.a -lpspaudiolib -lpspaudio

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = mikmodtest

include $(PSPSDK)/lib/build.mak

.PHONY: libs
libs: mmio playercode
	$(MAKE) -C mmio 
	$(MAKE) -C playercode


install: libs
	@echo "Installing mikmodlib into $(PSPDIR)"
	@mkdir -p $(PSPDIR)/include $(PSPDIR)/lib
	@cp include/* $(PSPDIR)/include
	@cp lib/*  $(PSPDIR)/lib
	@echo "Done"

	

.PHONY: clean
clean:
	$(MAKE) -C mmio clean
	$(MAKE) -C playercode clean
	rm -f *.o PARAM.SFO EBOOT.PBP libmikmod.a


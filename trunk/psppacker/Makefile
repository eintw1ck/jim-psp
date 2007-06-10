PSPSDK=$(shell psp-config --pspsdk-path)
PSPDIR=$(shell psp-config --psp-prefix)

all:
	$(MAKE) -C bin2c
	$(MAKE) -C pspstub
	$(MAKE) -C pc

install: all
	@echo "Installing psp-packer into $(PSPDIR)/bin"
	@cp pc/psp-packer $(PSPDIR)/bin

clean:
	$(MAKE) -C bin2c clean
	$(MAKE) -C pspstub clean
	$(MAKE) -C pc clean

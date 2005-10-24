# pspaalib
# aalib psp port by brice rouanet
# tmator@gmail.com
# See COPYING For licence info
PSPDIR=$(shell psp-config --psp-prefix)

all :
	$(MAKE) -C src all
	$(MAKE) -C test all

install:
	@mkdir -p $(PSPDIR)/include $(PSPDIR)/lib
	@cp include/aalib.h $(PSPDIR)/include
	@cp lib/*  $(PSPDIR)/lib

clean :
	$(MAKE) -C src clean
	$(MAKE) -C test clean

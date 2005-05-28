# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# Copyright 2001-2004, ps2dev - http://www.ps2dev.org
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
#
# $Id$

ifeq (x$(PSPSDKSRC), x)
  export PSPSDKSRC=$(shell pwd)
endif

SUBDIRS = psp tools

all: build 
	@$(ECHO) .;
	@$(ECHO) .PSPSDK Built.;
	@$(ECHO) .;

# Common rules shared by all build targets.

.PHONY: dummy

# Use SUBDIRS to descend into subdirectories.
subdir_list  = $(patsubst %,all-%,$(SUBDIRS))
subdir_clean = $(patsubst %,clean-%,$(SUBDIRS))
subdir_release = $(patsubst %,release-%,$(SUBDIRS))
subdirs: dummy $(subdir_list)

$(subdir_list): dummy
	$(MAKEREC) $(patsubst all-%,%,$@)
$(subdir_clean): dummy
	$(MAKEREC) $(patsubst clean-%,%,$@) clean
$(subdir_release): dummy
	$(MAKEREC) $(patsubst release-%,%,$@) release


build: env_build_check $(subdir_list)

clean: env_build_check $(subdir_clean)

rebuild: env_build_check $(subdir_clean) $(subdir_list)

$(PSPSDK)/include:
	$(MKDIR) -p $(PSPSDK)/include

$(PSPSDK)/build:
	$(MKDIR) -p $(PSPSDK)/build

install: release

release: build release_base $(PSPSDK)/include $(PSPSDK)/build $(subdir_release) 
	cp -rf $(PSPSDKSRC)/psp/include/* $(PSPSDK)/include/
	cp -rf $(PSPSDKSRC)/psp/build/* $(PSPSDK)/build/


release_base: env_release_check
	@if test ! -d $(PSPSDK) ; then \
	  $(MKDIR) -p $(PSPSDK) ; \
	fi
#	cp -f README $(PSPSDK)
#	cp -f CHANGELOG $(PSPSDK)
#	cp -f AUTHORS $(PSPSDK)
#	cp -f LICENSE $(PSPSDK)
#	cp -f ID $(PSPSDK)
	cp -f Defs.make $(PSPSDK)

env_build_check: 
	@if test -z $(PSPSDKSRC) ; \
	then \
	  $(ECHO) PSPSDKSRC environment variable should be defined. ; \
	fi

env_release_check:
	@if test -z $(PSPSDK) ; \
	then \
	  $(ECHO) PSPSDK environment variable must be defined. ; \
	  exit 1; \
	fi

docs:
	doxygen doxy.conf

include Defs.make

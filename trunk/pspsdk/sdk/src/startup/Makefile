# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# Copyright 2001-2004, ps2dev - http://www.ps2dev.org
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
#
# $Id$


PSP_OBJS_DIR = obj/
PSP_SRC_DIR = src/

all:  $(PSP_OBJS_DIR) obj/crt0.o

clean:
	rm -f -r $(PSP_OBJS_DIR)

release:
	cp -f src/linkfile $(PSPSDK)/startup
	cp -f obj/crt0.o $(PSPSDK)/startup

include $(PSPSDKSRC)/Defs.make
include $(PSPSDKSRC)/psp/Rules.make


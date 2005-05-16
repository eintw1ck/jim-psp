# _____     ___ _____     ___ ____
#  ____|   |     ____|   |        | |____|
# |     ___|    |     ___|    ____| |    \    PSPDEV Open Source Project.
#-----------------------------------------------------------------------
# Copyright 2005, PS2DEV - http://www.ps2dev.org
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
#
# $Id$

PSP_CC = ee-gcc
PSP_LD = ee-ld

PSP_SRC_DIR = src
PSP_INC_DIR = include
PSP_OBJS_DIR = obj
PSP_BIN_DIR = bin

PSP_BIN = sdktest.bin
PSP_PATCHEDBIN = sdktestp.bin
PSP_OUTPUT = EBOOT.PBP

PSP_OBJS = main.o
PSP_OBJS := $(PSP_OBJS:%=$(PSP_OBJS_DIR)/%)

PSP_MAP = sdktest.map
PSP_CFLAGS = -Wall -march=r4000 -g -G0 -mgp32 -mlong32
PSP_INCS = -I. -I./include -I$(PSPSDK)/include

all: $(PSP_BIN_DIR)/$(PSP_OUTPUT)

clean:
	rm -f $(PSP_OBJS) $(PSP_MAP) $(PSP_BIN_DIR)/$(PSP_BIN) $(PSP_BIN_DIR)/$(PSP_PATCHEDBIN) $(PSP_BIN_DIR)/$(PSP_OUTPUT)

$(PSP_BIN_DIR)/$(PSP_OUTPUT) : $(PSP_BIN_DIR)/$(PSP_PATCHEDBIN)
	$(PSPSDK)/bin/elf2pbp.exe $(PSP_BIN_DIR)/$(PSP_PATCHEDBIN) "SDK Test"
#	cp	EBOOT.PBP /cygdrive/f/PSP/GAME/test

$(PSP_BIN_DIR)/$(PSP_PATCHEDBIN) : $(PSP_OBJS)
	$(PSP_LD) -O0 -G0 $(PSPSDK)/startup/crt0.o $(PSP_OBJS) -L$(PSPSDK)/lib -lkernel -M -Ttext 8900000 -q -o $(PSP_BIN_DIR)/$(PSP_BIN) > $(PSP_MAP)
	$(PSPSDK)/bin/outpatch $(PSP_BIN_DIR)/$(PSP_BIN) $(PSP_BIN_DIR)/$(PSP_PATCHEDBIN)

$(PSP_OBJS_DIR)/%.o : $(PSP_SRC_DIR)/%.c
	$(PSP_CC) $(PSP_CFLAGS) $(PSP_INCS) -c $< -o $@

$(PSP_OBJS_DIR)/%.o : $(PSP_SRC_DIR)/%.s
	$(PSP_CC) $(PSP_CFLAGS) $(PSP_INCS) -c -xassembler -O -o $@ $<

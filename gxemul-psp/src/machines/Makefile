#
#  DO NOT EDIT THIS FILE! It is automagically created by
#  the configure script, based on Makefile.skel.
#

XINCLUDE=-I/usr/X11R6/include
XLIB=-L/usr/X11R6/lib -lX11
CWARNINGS=-Wall 
COPTIM=-O3 -g -pg -Wall
INCLUDE=-Iinclude/
DINCLUDE=-I../include/
CC=cc
OTHERLIBS=-lm 
CPU_ARCHS=
CPU_BACKENDS=
CPU_TOOLS=

#
#  $Id: Makefile.skel,v 1.21 2006/02/17 20:27:21 debug Exp $
#
#  Makefile for GXemul machines
#

CFLAGS=$(CWARNINGS) $(COPTIM) $(XINCLUDE) $(DINCLUDE)
OBJS=machine_psp.o interrupts_psp.o

all:
	$(MAKE) objs
	$(MAKE) automachine.o

automachine.c: $(OBJS) automachine_head.c automachine_middle.c automachine_tail.c makeautomachine.sh
	./makeautomachine.sh

objs: $(OBJS)

$(OBJS): Makefile


clean:
	rm -f $(OBJS) *core
	rm -f automachine.[co]
	rm -f *~

clean_all: clean
	rm -f Makefile


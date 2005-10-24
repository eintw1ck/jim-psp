PSPDIR=$(shell psp-config --psp-prefix)

TARGET = Bb/bb

OBJS =  autopilo.o 	\
	backconv.o 	\
	bb.o  		\
	credits2.o	\
	credits.o	\
	ctrl87.o	\
	fk1.o		\
	fk2.o		\
	fk3.o		\
	fk4.o		\
	formulas.o	\
	hh1.o		\
	hh2.o		\
	hh3.o		\
	hh4.o		\
	image.o		\
	julia.o		\
	kt1.o		\
	kt2.o		\
	kt3.o		\
	kt4.o		\
	main.o		\
	messager.o	\
	minilzo.o	\
	ms1.o		\
	ms2.o		\
	ms3.o		\
	ms4.o		\
	print.o		\
	scene1.o	\
	scene2.o	\
	scene3.o	\
	scene4.o	\
	scene5.o	\
	scene7.o	\
	scene8.o	\
	scene9.o	\
	tex.o		\
	textform.o	\
	timers.o	\
	uncompfn.o	\
	zeb.o		\
	zoom.o		\


INCDIR = $(PSPDIR)/include
CFLAGS = -G0 -g -O2 -DHAVE_CONFIG_H -DSOUNDDIR=\"ms0:/PSP/GAME/Bb/\" 
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR = $(PSPDIR)/lib
LIBS = -laa -lm -lmikmod -lpspdebug -lpspaudiolib -lpspaudio
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Test aalib

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak


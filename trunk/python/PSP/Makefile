TARGET = python

BUILD_GU = 0
BUILD_PSP = 0
BUILD_PSP2D = 1

MODULES_STATIC = \
	Modules/config.o \
	Modules/pspos.o \
	../Modules/main.o \
	../Modules/getbuildinfo.o \
	../Modules/gcmodule.o \
	../Modules/getpath.o \
	../Modules/timemodule.o \
	../Modules/mathmodule.o \
	../Modules/structmodule.o \
	../Modules/binascii.o \
	../Modules/_randommodule.o \
	../Modules/_sre.o \
	../Modules/cStringIO.o \
	../Modules/errnomodule.o \
	../Modules/threadmodule.o \
	../Modules/collectionsmodule.o

OBJECTS_PYTHON = \
	../Python/traceback.o \
	../Python/sysmodule.o \
	../Python/structmember.o \
	../Python/strdup.o \
	../Python/sigcheck.o \
	../Python/pythonrun.o \
	../Python/pystate.o \
	../Python/pyfpe.o \
	../Python/mystrtoul.o \
	../Python/mysnprintf.o \
	../Python/modsupport.o \
	../Python/marshal.o \
	../Python/importdl.o \
	../Python/import.o \
	../Python/graminit.o \
	../Python/getversion.o \
	../Python/getplatform.o \
	../Python/getopt.o \
	../Python/getcopyright.o \
	../Python/getcompiler.o \
	../Python/getargs.o \
	../Python/frozenmain.o \
	../Python/frozen.o \
	../Python/errors.o \
	../Python/compile.o \
	../Python/ceval.o \
	../Python/bltinmodule.o \
	../Python/exceptions.o \
	../Python/codecs.o \
	../Python/symtable.o \
	../Python/future.o \
	../Python/dynload_stub.o \
	../Python/pystrtod.o \
	../Python/thread.o

OBJECTS_OBJECTS = \
	../Objects/typeobject.o \
	../Objects/tupleobject.o \
	../Objects/stringobject.o \
	../Objects/sliceobject.o \
	../Objects/rangeobject.o \
	../Objects/object.o \
	../Objects/obmalloc.o \
	../Objects/moduleobject.o \
	../Objects/methodobject.o \
	../Objects/longobject.o \
	../Objects/listobject.o \
	../Objects/intobject.o \
	../Objects/boolobject.o \
	../Objects/iterobject.o \
	../Objects/funcobject.o \
	../Objects/frameobject.o \
	../Objects/floatobject.o \
	../Objects/fileobject.o \
	../Objects/enumobject.o \
	../Objects/dictobject.o \
	../Objects/complexobject.o \
	../Objects/cobject.o \
	../Objects/classobject.o \
	../Objects/cellobject.o \
	../Objects/bufferobject.o \
	../Objects/abstract.o \
	../Objects/unicodectype.o \
	../Objects/unicodeobject.o \
	../Objects/descrobject.o \
	../Objects/weakrefobject.o \
	../Objects/structseq.o \
	../Objects/setobject.o \
	../Objects/genobject.o

OBJECTS_PARSER = \
	../Parser/tokenizer.o \
	../Parser/printgrammar.o \
	../Parser/parsetok.o \
	../Parser/parser.o \
	../Parser/node.o \
	../Parser/myreadline.o \
	../Parser/metagrammar.o \
	../Parser/listnode.o \
	../Parser/intrcheck.o \
	../Parser/grammar1.o \
	../Parser/grammar.o \
	../Parser/firstsets.o \
	../Parser/bitset.o \
	../Parser/acceler.o

OBJS = main.o psperror.o support.o getmtime.o Modules/matrix.o \
	$(MODULES_STATIC) $(OBJECTS_PYTHON) $(OBJECTS_OBJECTS) $(OBJECTS_PARSER)

CPPFLAGS=
LIBS=

ifeq ($(BUILD_GU),1)
CPPFLAGS += -DWITH_GU
OBJS += Modules/gumodule.o
LIBS += -lpspgu
endif

ifeq ($(BUILD_PSP),1)
CPPFLAGS += -DWITH_PSP
OBJS += Modules/pspmodule.o
endif

ifeq ($(BUILD_PSP2D),1)
CPPFLAGS += -DWITH_PSP2D
OBJS += psp2d/psp2d.o \
	psp2d/color.o \
	psp2d/image.o \
	psp2d/controller.o \
	psp2d/screen.o \
	psp2d/mask.o \
	psp2d/font.o \
	psp2d/transform.o \
	psp2d/blitbatch.o \
	pspsnd/pspsnd.o \
	pspsnd/sound.o \
	pspsnd/music.o

LIBS += -Llibpsp2d -lpsp2d -Llibpspsnd -lpspsnd -lmikmod -lmmio -lpspaudiolib -lpspaudio -lpng -lz -lpspgu -lstdc++
endif

CPPFLAGS += -DHAVE_CONFIG_H -DPSP -I../Include -DCHECKTYPE
LIBS += -lc -lm

CFLAGS = -O2 -G0 -Wall -Wno-strict-aliasing
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Python for PSP

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

psperror.c:
	python generr.py

#####################################################################
# C compiler


# linux
CC= psp-gcc
AR= psp-ar
RANLIB= psp-ranlib
#CC= g++-3.2
CFLAGS= -g -Wall -O0 -G0
LFLAGS= -L`psp-config --pspsdk-path`/lib 

# for BeOS PPC
#CC= mwcc
#CFLAGS= -I. -i-
#LFLAGS=


#####################################################################
# Fixed Point 

#####################################################################
CFLAGS += -Wall
#CFLAGS += -DSLL_DEBUG -Wall

#####################################################################
# TinyGL configuration 

#####################################################################
# Select window API for TinyGL: 

# standard X11 GLX like API 
#TINYGL_USE_GLX=y

# BEOS API
#TINYGL_USE_BEOS=y

# Micro Windows NanoX API
#TINYGL_USE_NANOX=y

# SDL
TINYGL_USE_SDL=y

#####################################################################
# X11 configuration (for the examples only)

ifdef TINYGL_USE_GLX
# Linux
UI_LIBS= -L/usr/X11R6/lib -lX11 -lXext
UI_INCLUDES= 
# Solaris
#UI_LIBS= -L/usr/X11/lib -lX11 -lXext -lsocket -lnsl
#UI_INCLUDES= 

UI_OBJS=x11.o
endif

#####################################################################
# Micro windowX11 configuration (for the examples only)

ifdef TINYGL_USE_NANOX
UI_LIBS= -lnano-X -lmwengine -lmwdrivers -lmwfonts
UI_INCLUDES=

# X11 target for nanoX
UI_LIBS+= -L/usr/X11R6/lib -lX11 -lXext

UI_OBJS=nanox.o
endif

#####################################################################
# SDL configuration (for the examples only)

ifdef TINYGL_USE_SDL
#UI_LIBS= -lSDL -lpthread
UI_LIBS= -lSDL 
UI_INCLUDES=

PSPSDK_LIBC_LIB = -lm -lc -lpspglue -lc
PSPSDK_LIBS = -lpsphprm -lpspdebug -lpspdisplay -lpspge -lpspaudio -lpspctrl -lpspsdk
UI_LIBS += $(LIBS) $(PSPSDK_LIBS) $(PSPSDK_LIBC_LIB) -lpspuser -lpspkernel
UI_INCLUDES += -I`psp-config --pspsdk-path`/include -I`psp-config --pspsdk-path`/../include

UI_OBJS=sdl.o
endif

#####################################################################
# OpenGL configuration (for the examples only)

# use TinyGL 
GL_LIBS= -lTinyGL
GLU_LIBS= -lTinyGLU
GL_INCLUDES= -I../include
#GL_DEPS= ../lib/libTinyGL.a

# use Mesa
#GL_LIBS= -lMesaGL 
#GL_INCLUDES= 
#GL_DEPS=

# use OpenGL
#GL_LIBS= -lGL 
#GL_INCLUDES= 
#GL_DEPS=

####################################################################
# Compile and link control

# UNIX systems
DIRS= src src/glu examples

# BeOS
# DIRS= src BeOS


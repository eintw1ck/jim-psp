#!/bin/sh
# SDL.sh by Dan Peori (danpeori@oopo.net)

 ## Exit on errors
 set -e

 ## Download the latest source code.
 if test ! -d "SDL"; then
  svn checkout svn://svn.ps2dev.org/psp/trunk/SDL
 else
  svn update SDL
 fi

 ## Enter the source directory.
 cd SDL

 ## Bootstrap the source.
 sh autogen.sh

 ## Configure the build.
 LDFLAGS="-L$(psp-config --pspsdk-path)/lib" LIBS="-lc -lpspuser" ./configure --host psp --prefix=$(psp-config --psp-prefix) --enable-pspirkeyb

 ## Compile and install.
 make clean
 make -j2
 make install
 make clean

#!/bin/sh
# SDL_ttf.sh by Dan Peori (danpeori@oopo.net)

 ## Exit on errors
 set -e

 ## Download the latest source code.
 if test ! -d "SDL_ttf"; then
  svn checkout svn://svn.ps2dev.org/psp/trunk/SDL_ttf
 else
  svn update SDL_ttf
 fi

 ## Enter the source directory.
 cd SDL_ttf

 ## Bootstrap the source.
 sh autogen.sh

 ## Configure the build.
 LDFLAGS="-L$(psp-config --pspsdk-path)/lib" LIBS="-lpspirkeyb -lc -lpspuser" ./configure --host psp --with-sdl-prefix=$(psp-config --psp-prefix) --with-freetype-prefix=$(psp-config --psp-prefix) --without-x --prefix=$(psp-config --psp-prefix)

 ## Compile and install.
 make clean
 make -j2
 make install
 make clean

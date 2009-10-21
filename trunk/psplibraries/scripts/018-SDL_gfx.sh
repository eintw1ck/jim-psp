#!/bin/sh
# SDL_gfx.sh by Dan Peori (danpeori@oopo.net)

 ## Exit on errors
 set -e

 ## Download the latest source code.
 if test ! -d "SDL_gfx"; then
  svn checkout svn://svn.ps2dev.org/psp/trunk/SDL_gfx
 else
  svn update SDL_gfx
 fi

 ## Enter the source directory.
 cd SDL_gfx

 ## Bootstrap the source.
 sh autogen.sh

 ## Configure the build.
 AR=psp-ar LDFLAGS="-L$(psp-config --pspsdk-path)/lib" LIBS="-lc -lpspuser" ./configure --host psp --with-sdl-prefix=$(psp-config --psp-prefix) --prefix=$(psp-config --psp-prefix) --disable-mmx --disable-shared

 ## Compile and install.
 make clean
 make -j2
 make install
 make clean

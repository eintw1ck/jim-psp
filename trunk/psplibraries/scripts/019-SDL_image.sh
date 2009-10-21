#!/bin/sh
# SDL_image.sh by Dan Peori (danpeori@oopo.net)

 ## Exit on errors
 set -e

 ## Download the latest source code.
 if test ! -d "SDL_image"; then
  svn checkout svn://svn.ps2dev.org/psp/trunk/SDL_image
 else
  svn update SDL_image
 fi

 ## Enter the source directory.
 cd SDL_image

 ## Bootstrap the source.
 sh autogen.sh

 ## Configure the build.
 LDFLAGS="-L$(psp-config --pspsdk-path)/lib" LIBS="-lpspirkeyb -lc -lpspuser" ./configure --host psp --with-sdl-prefix=$(psp-config --psp-prefix) --prefix=$(psp-config --psp-prefix)

 ## Compile and install.
 make clean
 make -j2
 make install
 make clean

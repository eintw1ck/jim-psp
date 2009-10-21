#!/bin/sh
# SDL_mixer.sh by Dan Peori (danpeori@oopo.net)

 ## Exit on errors
 set -e

 ## Download the latest source code.
 if test ! -d "SDL_mixer"; then
  svn checkout svn://svn.ps2dev.org/psp/trunk/SDL_mixer
 else
  svn update SDL_mixer
 fi

 ## Enter the source directory.
 cd SDL_mixer

 ## Bootstrap the source.
 sh autogen.sh

 ## Configure the build.
 LDFLAGS="-L$(psp-config --pspsdk-path)/lib" LIBS="-lc -lpspuser" ./configure --host psp --with-sdl-prefix=$(psp-config --psp-prefix) --prefix=$(psp-config --psp-prefix) --enable-music-mod

 ## Compile and install.
 make clean
 make -j2
 make install
 make clean

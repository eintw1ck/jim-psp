#!/bin/sh
# freetype.sh by Dan Peori (danpeori@oopo.net)

 ## Exit on errors
 set -e

 ## Download the latest source code.
 if test ! -d "freetype"; then
  svn checkout svn://svn.ps2dev.org/psp/trunk/freetype
 else
  svn update freetype
 fi

 ## Enter the source directory.
 cd freetype

 ## Bootstrap the source.
 sh autogen.sh

 ## Configure the build.
 LDFLAGS="-L$(psp-config --pspsdk-path)/lib" LIBS="-lc -lpspuser" ./configure --host psp --prefix=$(psp-config --psp-prefix)

 ## Compile and install.
 make clean
 make -j2
 make install
 make clean

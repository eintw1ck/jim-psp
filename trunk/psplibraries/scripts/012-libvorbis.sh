#!/bin/sh
# libvorbis.sh by Dan Peori (danpeori@oopo.net)

 ## Exit on errors
 set -e

 ## Download the latest source code.
 if test ! -d "libvorbis"; then
  svn checkout svn://svn.ps2dev.org/psp/trunk/libvorbis
 else
  svn update libvorbis
 fi

 ## Enter the source directory.
 cd libvorbis

 ## Bootstrap the source.
 LDFLAGS="-L$(psp-config --pspsdk-path)/lib" LIBS="-lc -lpspuser" ./autogen.sh --host psp --prefix=$(psp-config --psp-prefix)

 ## Compile and install.
 make clean
 make -j2
 make install
 make clean

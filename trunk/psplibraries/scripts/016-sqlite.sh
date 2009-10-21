#!/bin/sh
# sqlite.sh by Dan Peori (danpeori@oopo.net)

 ## Exit on errors
 set -e

 ## Download the latest source code.
 if test ! -d "sqlite"; then
  svn checkout svn://svn.ps2dev.org/psp/trunk/sqlite
 else
  svn update sqlite
 fi

 ## Enter the source directory.
 cd sqlite

 ## Configure the build.
 LDFLAGS="-L$(psp-config --pspsdk-path)/lib" LIBS="-lc -lpspuser" ./configure --host=psp --disable-readline --disable-tcl --prefix=$(psp-config --psp-prefix)

 ## Compile and install.
 make clean
 make -j2
 make install
 make clean

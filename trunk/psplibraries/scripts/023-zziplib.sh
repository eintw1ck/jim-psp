#!/bin/sh
# zziplib.sh by Dan Peori (danpeori@oopo.net)

 ## Exit on errors
 set -e

 ## Download the latest source code.
 if test ! -d "zziplib"; then
  svn checkout svn://svn.ps2dev.org/psp/trunk/zziplib
 else
  svn update zziplib
 fi

 ## Enter the source directory.
 cd zziplib

 ## Configure the build.
 LDFLAGS="-L$(psp-config --pspsdk-path)/lib" LIBS="-lc -lpspuser" ./configure --host=psp --prefix=$(psp-config --psp-prefix)

 ## Compile and install.
 make clean
 make -j2
 make install
 make clean

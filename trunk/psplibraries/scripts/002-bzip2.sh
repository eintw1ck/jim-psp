#!/bin/sh
# bzip2.sh by Dan Peori (danpeori@oopo.net)

 ## Exit on errors
 set -e

 ## Download the latest source code.
 if test ! -d "bzip2"; then
  svn checkout svn://svn.ps2dev.org/psp/trunk/bzip2
 else
  svn update bzip2
 fi

 ## Enter the source directory.
 cd bzip2

 ## Compile and install.
 make clean
 make -j2
 make install
 make clean

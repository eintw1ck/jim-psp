#!/bin/sh
# smpeg-psp.sh by Dan Peori (danpeori@oopo.net)

 ## Exit on errors
 set -e

 ## Download the latest source code.
 if test ! -d "smpeg-psp"; then
  svn checkout http://smpeg-psp.googlecode.com/svn/trunk smpeg-psp
 else
  svn update smpeg-psp
 fi

 ## Enter the source directory.
 cd smpeg-psp

 ## Compile and install.
 make clean
 make -j2
 make install
 make clean

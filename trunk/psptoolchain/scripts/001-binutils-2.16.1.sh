#!/bin/sh
# binutils-2.16.1.sh by Dan Peori (danpeori@oopo.net)

 ## Download the source code.
 wget --continue ftp://ftp.gnu.org/pub/gnu/binutils/binutils-2.16.1.tar.bz2 || { exit 1; }

 ## Unpack the source code.
 rm -Rf binutils-2.16.1 && tar xfvj binutils-2.16.1.tar.bz2 || { exit 1; }

 ## Enter the source directory and patch the source code.
 cd binutils-2.16.1 || { exit 1; }
 patch -p 1 < ../../patches/binutils-2.16.1-PSP.patch || { exit 1; }
 patch -p 0 < ../../patches/binutils-2.16.1-fix-ar.patch || { exit 1; }

 ## Create and enter the build directory.
 mkdir build-psp && cd build-psp || { exit 1; }

 ## Configure the build.
 ../configure --prefix="$PSPDEV" --target="psp" --enable-install-libbfd || { exit 1; }

 ## Compile and install. ( -r is required for building under osx )
 make clean && make -r -j 2 && make install && make clean || { exit 1; }

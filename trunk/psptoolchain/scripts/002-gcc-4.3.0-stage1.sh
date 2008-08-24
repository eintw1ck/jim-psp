#!/bin/sh
# gcc-4.3.0-stage1.sh by Dan Peori (danpeori@oopo.net)

 ## Download the source code.
 wget --continue ftp://ftp.gnu.org/pub/gnu/gcc/gcc-4.3.0/gcc-4.3.0.tar.bz2 || { exit 1; }

 ## Unpack the source code.
 rm -Rf gcc-4.3.0 && tar xfvj gcc-4.3.0.tar.bz2 || { exit 1; }

 ## Enter the source directory and patch the source code.
 cd gcc-4.3.0 && cat ../../patches/gcc-4.3.0-PSP.patch | patch -p1 || { exit 1; }

 ## Create and enter the build directory.
 mkdir build-psp && cd build-psp || { exit 1; }

 ## Configure the build.
 ../configure --prefix="$PSPDEV" --target="psp" --enable-languages="c" --with-newlib --with-gmp --with-mpfr --without-headers --disable-libssp  || { exit 1; }

 ## Compile and install.
 make clean && make -j 2 && make install && make clean || { exit 1; }

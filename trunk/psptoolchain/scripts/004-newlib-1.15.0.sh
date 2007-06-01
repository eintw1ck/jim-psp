#!/bin/sh
# newlib-1.15.0.sh by Dan Peori (danpeori@oopo.net)

 ## Download the source code.
 wget --continue ftp://sources.redhat.com/pub/newlib/newlib-1.15.0.tar.gz || { exit 1; }

 ## Unpack the source code.
 rm -Rf newlib-1.15.0 && tar xfvz newlib-1.15.0.tar.gz || { exit 1; }

 ## Enter the source directory and patch the source code.
 cd newlib-1.15.0 && cat ../../patches/newlib-1.15.0-PSP.patch | patch -p1 || { exit 1; }

 ## Create and enter the build directory.
 mkdir build-psp && cd build-psp || { exit 1; }

 ## Configure the build.
 ../configure --prefix="$PSPDEV" --target="psp" || { exit 1; }

 ## Compile and install.
 make clean && make -j 2 && make install && make clean || { exit 1; }

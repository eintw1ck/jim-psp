#!/bin/sh
LDFLAGS="-L$(psp-config --psp-prefix)/lib -L$(psp-config --pspsdk-path)/lib" \
LIBS="-lc -lpsplibc -lpspuser" \
./configure --host=psp --disable-shared --prefix=$(psp-config --psp-prefix)

#!/bin/sh
LDFLAGS="-L/usr/local/pspdev/psp/lib -L/usr/local/pspdev/psp/sdk/lib" \
LIBS="-lc -lpsplibc -lpspuser" \
./configure --host=psp --disable-shared --prefix=/usr/local/pspdev/psp

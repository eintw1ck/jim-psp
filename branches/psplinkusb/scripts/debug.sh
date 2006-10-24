#!/usr/local/pspdev/bin/pspsh

# Script to load a prx and its symbols, set a breakpoint on its main
# function and start it.
modload $1.elf
set UID=$?
echo "UID $UID"
symload $1.sym
bpset '?$!:main?'
#modstart '@$!' $1.prx

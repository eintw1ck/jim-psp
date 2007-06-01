#!/bin/sh
# toolchain-sudo.sh by Dan Peori (danpeori@oopo.net)

 ## Enter the script directory.
 cd "`dirname $0`" || { echo "ERROR: Could not enter the script directory."; exit 1; }

 ## Set up the environment.
 export PSPDEV=/usr/local/pspdev
 export PATH=$PATH:$PSPDEV/bin

 ## Run the toolchain script.
 ./toolchain.sh || { echo "ERROR: Could not run the toolchain script."; exit 1; }

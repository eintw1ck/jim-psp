#!/bin/sh
# check-ncurses.sh by Dan Peori (danpeori@oopo.net)

 ## Check for a ncurses library.
 ls /usr/lib/libncurses.a 1> /dev/null || ls /usr/lib/libncurses.dll.a || { echo "ERROR: Install ncurses before continuing."; exit 1; }

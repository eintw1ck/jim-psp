
  ==================
   HOW DO I USE IT?
  ==================

   Basically, you run the toolchain script:

    ## Make the script executable.
    chmod a+x ./toolchain.sh

    ## Run the script.
    ./toolchain.sh

   First, this script will attempt to make sure you have all the programs
   you need to build the toolchain. Then it will download the source from
   various places on the internet. Finally, it will compile and build the
   source. This may take a long time.

   Once finished, you need to add the following to your login settings:

    ## PSPDEV SETTINGS
    export PSPDEV="/usr/local/pspdev"
    export PSPSDK="$PSPDEV/pspsdk"
    export CVSROOT=":pserver:anonymous@cvs.ps2dev.org:/home/pspcvs"
    export PATH="$PATH:$PSPDEV/bin:$PSPDEV/psp/bin:$PSPSDK/bin"

   Then you're done!

  ======================
   HOW DO I CONTRIBUTE?
  ======================

   If you're interested in hacking on any part of the PSP toolchain,
   please read devel/README.TXT before getting started.

  =============
   THE CREDITS
  =============

   Add yourself here, or be anonymous:

   Dan Peori (peori@oopo.net) - Created the script, patch maintenance.
   Marcus R. Brown (mrbrown@0xd6.org) - Drop-in tree, toolchain.

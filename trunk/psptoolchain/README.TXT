
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
    export PATH="$PATH:$PSPDEV/bin"

   Then you're done!

  =====================
   WHAT ELSE CAN I DO?
  =====================

   Thanks to Rinco, you can now select which parts of the process to
   perform. No longer will you have to rerun the whole script:

    -d		- Download the required files.
    -b		- Build and install binutils.
    -g		- Build and install gcc. (both c and c++)
    -n		- Build and install newlib.
    -p		- Download, build and install pspsdk.

   For example, say you wanted to update only pspsdk:

    ./toolchain.sh -p

   The script grabs the latest version of pspsdk from the svn repository.

  ============================
   HOW CAN I STAY UP TO DATE?
  ============================

   The psp toolchain itself isn't updated nearly as often as pspsdk itself
   so you can usually stay up to date by just running:

    ./toolchain.sh -p

   However, you can update the entire psp toolchain script, patches and sdk
   by grabbing the latest version direct from the svn server:

    svn update
    ./toolchain.sh

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
   Rinco (matthewh@webone.com.au) - Options to build specific targets.

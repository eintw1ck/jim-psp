
 ===================
  Toolchain Hacking
 ===================
 
  The pspdev toolchain consists of a port of the popular GNU toolchain in a
  configuration typically used for embedded systems.  The GNU toolchain
  consists of GNU binutils (the linker and assembler), GCC (the C and C++
  compilers, and Standard C++ Library), and newlib (the Standard C Library).
  For more information on this software please visit:

   binutils: http://sources.redhat.com/binutils/
   newlib: http://sources.redhat.com/newlib/
   GCC: http://gcc.gnu.org/
  
  Maintaing patches against huge software projects such as GCC can be a
  daunting task.  Keeping track of any local changes typically entails
  importing the entire GCC tree into a CVS (or Subversion) respository.
  Upgrading the modified tree consists of applying the upgrade patch against
  all modified files, and keeping track of which files were modified outside of
  your own.  The maintained tree can become unweildy because of all of the
  unimportant files that must be maintained on top of the small subset that
  make the toolchain work.

  One solution I've used on previous projects is called a "drop-in tree".  A
  drop-in tree consists of only the files required to get a toolchain port
  working.  Only these files are ever checked into the source repository.  When
  making changes to the drop-in tree that require the full toolchain source,
  the drop-in tree is symlinked on top of the full source tree.  The full
  source tree then behaves as if it had been patched normally, except that any
  edits made to files contained in the drop-in tree will be tracked by CVS (or
  Subversion).  Although a drop-in is a bit more work to maintain than a full
  source tree imported into a source repository, it can be extremely helpful
  to work with only the files you care about.

  The pspdev toolchain currently uses drop-in trees against binutils, newlib,
  and GCC.  The rest of this document provides developers and patch
  maintainers instructions on using these drop-in trees with pspdev CVS.

 ========================
  How to Get Things Done
 ========================

  The following examples assume you are working with a drop-in tree in CVS
  called gcc-psp, and that the full source of GCC 4.0.0 is extracted into
  a directory called gcc-4.0.0.

  Editing and building the toolchain:

  1. Use the treelink script to symlink the drop-in tree on top of the full
     source tree:

      treelink.sh gcc-psp gcc-4.0.0

     You can now edit files contained in the drop-in tree from within the full
     source tree, and build that tree as if it were patched.

  Generating a patch:

  1. Use the difftree script to create a patch showing only the differences in
     the files contained in the drop-in tree:

      difftree.sh gcc-psp gcc-4.0.0

     The patch will be called patch-gcc-psp-gcc-4.0.0-<timestamp>.diff, where
     <timestamp> is a numeric date string produced by `date +%s'.

  2. Replace the old PSP toolchain patch and check it into CVS:

      cp patch-gcc-psp-gcc-4.0.0-<timestamp>.diff psptoolchain/gcc-4.0.0.patch
      cd psptoolchain ; cvs commit gcc-4.0.0.patch

  Adding new source files to the drop-in tree:

  1. Copy the original source file from an unmodified copy of the full source
     tree into the drop-in tree, and add the file to CVS.  For example, if I
     wanted to start tracking gcc/config.gcc from GCC 4.0.0:

      mkdir gcc-psp/gcc
      cp gcc-4.0.0/gcc/config.gcc gcc-psp/gcc
      cd gcc-psp ; cvs add gcc/config.gcc
      cd .. ; treelink.sh gcc-psp gcc-4.0.0

     Note that if I didn't relink the drop-in tree on top of the full source
     tree, any changes I make to config.gcc wouldn't be tracked by the drop-in
     tree.  Relinking the drop-in tree after adding new files is one of the
     drawbacks to using this system.  Please don't forget to do it!

   Restoring a full source tree after it's been treelinked:

   1. Use the treeunlink script to undo the changes made by treelink:

       treeunlink.sh gcc-4.0.0

      The treelink script creates a directory called .orig in every directory
      that contains a copy of drop-in tree files within the full source tree.
      The treeunlink script will remove the symlinks created by treelink and
      restore the original files from the .orig directory.
   
 ====================
  Toolchain Upgrades
 ====================

  The following instructions can be used for upgrading the toolchain and
  integrating those changes into the drop-in tree.  In the instructions, a
  drop-in tree against GCC 4.0.0 will be upgraded to GCC 4.1.  The instructions
  are meant to be followed in order, from the directory that the drop-in tree
  and the psptoolchain patches reside in.  The full, pristine GCC 4.0.0 source
  is in a directory called gcc.

  Make sure that your drop-in tree is current with what's in CVS.  

  1. Tag the version of the drop-in tree you are upgrading from.  Note that we
     always tag the drop-in tree BEFORE upgrading, so that we can query CVS for
     the final state of the drop-in tree against the current toolchain version:

      cd gcc-psp ; cvs tag gcc-psp-4.0.0
  
  2. Link your drop-in tree on top of the pristine source of the tools you are
     upgrading from:

      cd .. ; treelink.sh gcc-psp gcc     # gcc currently contains GCC 4.0.0

  3. Apply the upstream patches to the treelinked tree to upgrade it:

      cd gcc ; patch -s -p1 < ../gcc-4.1.diff

  4. Clean up after any .orig files patch may have left around using the
     treefix script:

      treefix.sh .

  5. If necessary resolve any conflicts caused by the upgrade.  Here you will
     need to find any of the files that patch complained about, and manually
     resolve conflicts.  Because the drop-in tree is linked, these changes will
     also update the drop-in tree.

     If you search the tree for .rej files, these contain the source chunks
     that patch had trouble resolving.

  6. Create a patch that only contains changes made to the drop-in tree.  The
     generated patch is suitable for replacing the original patch for those
     tools:

      cd .. ; difftree.sh gcc-psp gcc     # gcc now contains GCC 4.1

     Note that if this patch is empty, then no files in the drop-in tree were
     modified by the upgrade.  All you need to do then is rename the official
     PSP toolchain patch:

      cd psptoolchain ; cp gcc-4.0.0.patch gcc-4.1.diff
      cvs rm -f gcc-4.0.0.patch ; cvs add gcc-4.1.diff

     However, if a patch was generated, then it's suitable for inclusion into
     the offical PSP patches.  Rename the patch to the name of the new
     toolchain + ".diff", remove the older toolchain patch from CVS, and add
     the new patch to CVS:

      cd psptoolchain ; cp ../patch-gcc-psp-gcc-<timestamp>.diff gcc-4.1.diff
      cvs rm -f gcc-4.0.0.patch ; cvs add gcc-4.1.diff

  Finally, commit any changes made to the drop-in tree to CVS.

 =============
  The Scripts
 =============

  treelink.sh <drop-in tree> <full source tree>

   Symlink a drop-in tree on top of a full source tree.  You can then build and
   edit the full source tree as if it were patched, and commit changes made to
   files contained in the drop-in tree.

  treeunlink.sh <full source tree>

   Undo treelink.sh.

  treefix.sh <full source tree>

   Remove any .orig files or other cruft created by patch.

  difftree.sh <drop-in tree> <full source tree>

   Generate a patch containing only the differences of files that exist in the
   drop-in tree.  The resulting patch is named
   patch-<drop-in name>-<full source name>-<timestamp>.diff.

 ============
  The Author
 ============

  This document was written by Marcus R. Brown.  If you have questions or
  suggestions for maintaining or contributing to the pspdev toolchain please
  use the forums at http://forums.ps2dev.org or stop by #ps2dev on
  irc.freenode.net to chat with the developers there.
 
  The drop-in tree method of development has been used with success on both the
  LinuxDC and LinuxSH projects that I have been involved with, and in various
  other Open Source projects.  Suggestions, questions, and criticisms are
  welcome.

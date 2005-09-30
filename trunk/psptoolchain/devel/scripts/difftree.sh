#!/bin/sh
#
# difftree.sh - Tree Diffing Script
#
# Copyright (C) 2001 Paul Mundt <lethal@chaoticdreams.org>
#
# A simple shell script for diffing a drop in tree against a
# stock kernel tree. A patch is generated that covers the
# differences between the files in the drop-in tree and the
# files (whether existant or not) in the stock tree.
#
# Released under the terms of the GNU GPL v2
#
[ "$#" -ne "2" ] && echo "Usage: $0 <old tree> <new tree>" && exit 1

CPWD=`which pwd`
ODIR=`$CPWD`
cd $1 || exit 1
LDIR=`$CPWD`
echo -n "Building file list ... "
LIST=`find * \( -type d -name CVS -o -name .svn -prune \) -o -type f -print | sort`
echo -e "done."
cd ${ODIR}

PATCH=patch-`basename $1`-`basename $2`-`date +%s`.diff
rm -f $PATCH

echo -n "Generating patch ..... "
for file in $LIST; do
	diff -burN $2/$file $1/$file >> $PATCH 2> /dev/null
done
echo -e "done."


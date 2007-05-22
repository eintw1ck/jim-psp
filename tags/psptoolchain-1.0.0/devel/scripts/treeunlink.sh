#!/bin/sh
#
# treeunlink.sh - Tree Unlinking Script
#
# Copyright (c) 2001 M. R. Brown <mrbrown@0xd6.org>
#
# This script attempts to restore a previously tree-linked tree.
# It's the anti-thesis of (and based on) treelink.sh by Paul Mundt.
#
# Released under the terms of the GNU GPL v2

[ "$#" -ne "1" ] && echo "Usage: $0 <kernel tree>" && exit 1

cd $1 || exit 1
echo -n "Building file list ... "
LIST=`find * \( -type d -name CVS -prune \) -o -type l -print`
echo -e "done."

[ -z "$LIST" ] && echo "No linked files to unlink." && exit 1

echo -n "Restoring originals .. "
for file in $LIST; do
	DIR=`dirname $file`
	ofile=`basename $file`
	rm -f $file
	if [ -d ${DIR}/.orig  -a  -e ${DIR}/.orig/$ofile ]; then
		mv ${DIR}/.orig/$ofile $file
		[ -z "`ls ${DIR}/.orig`" ] && rmdir ${DIR}/.orig
	fi
done
echo -e "done."

#!/bin/sh
#
# treefix.sh - Clean up drop-in tree after patch.
#
# Braindead script to cleanup after patch does it's thing in a drop-in tree.

[ "$#" -ne "1" ] && echo "Usage: $0 <tree to fix>" && exit 1

ODIR=${PWD}
cd $1 || exit 1
LDIR=${PWD}
echo -n "Finding .orig files ... "
LIST=`find . -name \*.orig`
echo -e "done."

echo -n "Fixing tree ... "
for file in $LIST; do
	basefile=`dirname $file`/`basename $file .orig`
	rm -f $file
done
echo -e "done."
cd $ODIR

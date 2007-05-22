#!/bin/sh
#
# treefix.sh - Clean up drop-in tree after patch.
#
# Braindead script to cleanup after patch does it's thing in a drop-in tree.

[ "$#" -ne "1" ] && echo "Usage: $0 <tree to fix>" && exit 1

CPWD=`which pwd`
ODIR=`$CPWD`
cd $1 || exit 1
LDIR=`$CPWD`
echo -n "Finding .orig files ... "
LIST=`find . -name \*.orig`
echo -e "done."

echo "Fixing tree ... "
for file in $LIST; do
	if test -f $file ; then
		basefile=`dirname $file`/`basename $file .orig`
		cp $basefile $file
		mv $file $basefile
		echo "Fixed \`$basefile'."
	fi
done
echo "done."
cd $ODIR

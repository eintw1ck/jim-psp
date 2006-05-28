#! /bin/bash
PSPSDK=`psp-config --pspsdk-path`
SAMPLES=$PSPSDK/samples

if test `find  $SAMPLES -name "Makefile" | grep $1 | wc -l` != 1; then
	echo notok
	find  $SAMPLES -name "Makefile" | grep $1
	exit -1
fi

#echo ok
MAKEFILE=`find  $SAMPLES -name "Makefile" | grep $1`
#echo $MAKEFILE
MAKEDIR=`echo $MAKEFILE | sed -e 's/Makefile.*$//'`
#echo $MAKEDIR

make -C $MAKEDIR -f $MAKEFILE

#find  $MAKEDIR -name "*.elf"
#find  $MAKEDIR -name "*.PBP"

if test `find  $MAKEDIR -name "*.elf" | wc -l` != 1; then
	echo notok
	find  $MAKEDIR -name "*.elf"
	exit -1
fi

ELFFILE=`find  $MAKEDIR -name "*.elf"`
#echo $ELFFILE

#xterm -e ./gxemul-psp -v -v -v -E psp -u psp -p 0 -X $ELFFILE
#./gxemul-psp -v -v -v -E psp -u psp -p 0 -X $ELFFILE
#./gxemul-psp -i -v -v -v -E psp -u psp -p 0 -X $ELFFILE
./gxemul-psp -t -v -v -v -E psp -u psp -p 0 -X $ELFFILE

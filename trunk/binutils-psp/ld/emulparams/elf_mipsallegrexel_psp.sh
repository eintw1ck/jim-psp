# Based off of a normal elf32 MIPS target, but we use a seperate script
# because the PSP architecture defines sections that cannot be overriden and
# get absorbed (i.e. .rodata.sceModuleInfo).

EMBEDDED=yes
. ${srcdir}/emulparams/elf32lmip.sh
unset NONPAGED_TEXT_START_ADDR
unset SHLIB_TEXT_START_ADDR
unset COMMONPAGESIZE

SCRIPT_NAME=elf_psp
TEXT_START_ADDR=0x08900000
MAXPAGESIZE=256
ARCH="mips:allegrex"
MACHINE=
TEMPLATE_NAME=elf32
GENERATE_SHLIB_SCRIPT=yes
DYNAMIC_LINK=FALSE

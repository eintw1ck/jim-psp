/*
# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# Copyright 2001-2004, ps2dev - http://www.ps2dev.org
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
#
# $Id$
# The global init/deinit code for our crt0.
*/

void _pspsdk_alloc_init();
void _pspsdk_alloc_deinit();
void _pspsdk_stdio_init();
void _pspsdk_stdio_deinit();
void _pspsdk_stdlib_init();
void _pspsdk_stdlib_deinit();

__attribute__((weak, constructor))
void _pspsdk_libc_init()
{
    _pspsdk_alloc_init();
    _pspsdk_stdio_init();
    _pspsdk_stdlib_init();
}

__attribute__((weak, destructor))
void _pspsdk_libc_deinit()
{
    _pspsdk_stdlib_deinit();
    _pspsdk_stdio_deinit();
    _pspsdk_alloc_deinit();
}

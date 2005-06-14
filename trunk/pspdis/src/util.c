/*                          ____  _     
#         ____  _________  / __ \(_)____
#        / __ \/ ___/ __ \/ / / / / ___/
#       / /_/ (__  ) /_/ / /_/ / (__  ) 
#      / .___/____/ .___/_____/_/____/  
#     /_/        /_/
#     
# Copyright 2005, pspdev - http://www.pspdev.org
# Author:       John Kelley
# Date:         June 1 2005
# File:         util.c
# Description:  Utility functions.
#
*/
#include "util.h"
/*
char makehexchar(int i) 
	return (i<=9) ? '0'+i : 'A'+(i-10);
}
*/

void hexdump(const u8* data, size_t length) {
	const int char_offset=16*3;
	const int line_size=16*3+16+1;
	char line[line_size+1];
	size_t i, line_i;
	
	for (i=0; i<length; ) {
		int bi=0;
		int ci=0;
		for (line_i=0; i<length && line_i<16; i++, line_i++) {
			line[bi++]=makehexchar(*data>>4);
			line[bi++]=makehexchar((*data & 0x0f));
			line[bi++]=' ';
			line[char_offset+(ci++)]=(isprint(*data) ? *data : '.');
			data++;
		}

		while (bi<16*3) {
			line[bi++]=' ';
		}

		line[char_offset+(ci++)]='\n';
		line[char_offset+ci]=0;

		printf("%s\n", line);
	}
}

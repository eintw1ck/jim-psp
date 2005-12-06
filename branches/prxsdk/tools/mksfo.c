/*
# _____     ___ ____     ___ ____ 
#  ____|   |    ____|   |        | |____|    
# |     ___|   |     ___|    ____| |    \    PSPDEV Open Source Project. 
#-----------------------------------------------------------------------
# Review ps2sdk README & LICENSE files for further details. 
# 
# A simple tool to build an SFO file for use in the EBOOT.PBP
# $Id$
*/

#include <stdio.h>
#include <string.h>

#define SIZE_POS 0x48
#define TITLE_POS 0x80
#define TITLE_SIZE 0x80

/* A default, simple SFO file */
unsigned char g_defaultSfo[] = {
	0x00, 0x50, 0x53, 0x46, 0x01, 0x01, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x74, 0x00, 0x00, 0x00, 
	0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x04, 0x02, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 
	0x04, 0x00, 0x00, 0x00, 0x12, 0x00, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 
	0x08, 0x00, 0x00, 0x00, 0x19, 0x00, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
	0x0c, 0x00, 0x00, 0x00, 0x42, 0x4f, 0x4f, 0x54, 0x41, 0x42, 0x4c, 0x45, 0x00, 0x43, 0x41, 0x54, 
	0x45, 0x47, 0x4f, 0x52, 0x59, 0x00, 0x52, 0x45, 0x47, 0x49, 0x4f, 0x4e, 0x00, 0x54, 0x49, 0x54, 
	0x4c, 0x45, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x4d, 0x47, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

int main(int argc, char **argv)
{
	FILE *fp;

	if(argc < 3)
	{
		fprintf(stderr, "Usage: mksfo TITLE output.sfo\n");
		return 1;
	}

	g_defaultSfo[SIZE_POS] = (unsigned char) (strlen(argv[1]) & 0xFF);
	strncpy((char *) &g_defaultSfo[TITLE_POS], argv[1], TITLE_SIZE);
	/* Don't know if the name needs null termination or not */
	g_defaultSfo[TITLE_SIZE-1] = 0;

	fp = fopen(argv[2], "wb");
	if(fp != NULL)
	{
		fwrite(g_defaultSfo, 1, sizeof(g_defaultSfo), fp);
		fclose(fp);
	}
	else
	{
		fprintf(stderr, "Could not open %s\n", argv[2]);
		return 1;
	}

	return 0;
}

// outpatch
// patches elf header and section name
// Original written by nem
// Modded by tyranid
// $Id$

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef HAVE_MALLOC_H 
#include <malloc.h> 
#endif 

#define str_modulename "PSPSDK"
#define str_scemoduleinfo_pre "xodata.sceModuleInfo"
#define str_scemoduleinfo "rodata.sceModuleInfo"

int main(int argc, char* argv[])
{
	FILE *in,*out;
	unsigned int filesize;
	unsigned char *buf=NULL;
	unsigned int i,ofs_modulename,ofs_scemoduleinfo;

	if(argc < 3)
	{
		printf("Usage: outpatch elffile outputfile\n");
		return 1;
	}

	in=fopen(argv[1],"rb");
	if (!in) {
		printf("file '%s' not found\n", argv[1]);
		exit(1);
	}
	fseek(in,0,SEEK_END);
	filesize=ftell(in);
	fseek(in,0,SEEK_SET);
	buf=(unsigned char *)malloc(filesize);
	fread(buf,1,filesize,in);
	fclose(in);

	ofs_modulename=0;
	unsigned long len_modulename=strlen(str_modulename);
	for (i=0; i<filesize; i++) {
		if (memcmp(buf+i,str_modulename,len_modulename)==0) {
			ofs_modulename=i;
			break;
		}
	}
	ofs_scemoduleinfo=0;
	unsigned long len_scemoduleinfo_pre=strlen(str_scemoduleinfo_pre);
	for (i=0; i<filesize; i++) {
		if (memcmp(buf+i,str_scemoduleinfo_pre,len_scemoduleinfo_pre)==0) {
			ofs_scemoduleinfo=i;
			break;
		}
	}
	if (ofs_modulename==0) {
		printf("modulename not found\n");
		if (buf) { free(buf); buf=NULL; }
		exit(1);
	}
	if (ofs_scemoduleinfo==0) {
		printf("scemoduleinfo not found\n");
		if (buf) { free(buf); buf=NULL; }
		exit(1);
	}

	*(unsigned long *)(buf+0x40)=ofs_modulename-4;
	memcpy(buf+ofs_scemoduleinfo,str_scemoduleinfo,strlen(str_scemoduleinfo));

	out=fopen(argv[2],"wb");
	if (!out) {
		printf("file '%s' can not opened\n", argv[2]);
		exit(1);
	}
	fwrite(buf,1,filesize,out);
	fclose(out);

	printf("successed filesize:%08X modulename:%08X scemoduleinfo:%08X\n",filesize,ofs_modulename,ofs_scemoduleinfo);
	if (buf) { free(buf); buf=NULL; }
	return 0;
}


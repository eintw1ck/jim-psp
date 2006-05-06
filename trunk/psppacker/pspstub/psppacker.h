#ifndef __PSPPACKER_H__
#define __PSPPACKER_H__

#define PACKER_MAGIC "PSPK"
#define VER_MAJ 0
#define VER_MIN 2

struct PackHeader
{
	unsigned char magic[4];
	unsigned int  unpacked_size;
	unsigned int  packed_size;
};

#endif

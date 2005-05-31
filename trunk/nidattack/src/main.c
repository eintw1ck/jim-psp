/*
SHA1 dictionary attack program v1.0 (c) 2005 adresd
based on original by djhuevo

hash searchtable and other mods by adresd
performance checked by gorim

No License, public domain, do as you want, no warranties
*/
/*
SHA-1 in C
By Steve Reid <steve@edmweb.com>
100% Public Domain

Test Vectors (from FIPS PUB 180-1)
"abc"
A9993E36 4706816A BA3E2571 7850C26C 9CD0D89D
"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"
84983E44 1C3BD26E BAAE4AA1 F95129E5 E54670F1
A million repetitions of "a"
34AA973C D4C4DAA4 F61EEB2B DBAD2731 6534016F
*/

/* #define LITTLE_ENDIAN * This should be #define'd if true. */
/* #define SHA1HANDSOFF * Copies data before messing with it. */

#define LITTLE_ENDIAN

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

typedef struct {
	unsigned long state[5];
	unsigned long count[2];
	unsigned char buffer[64];
} SHA1_CTX;

void SHA1Transform(unsigned long state[5], unsigned char buffer[64]);
void SHA1Init(SHA1_CTX * context);
void SHA1Update(SHA1_CTX * context, unsigned char *data, unsigned int len);
void SHA1Final(unsigned char digest[20], SHA1_CTX * context);

#define rol(value, bits) (((value) << (bits)) | ((value) >> (32 - (bits))))

/* blk0() and blk() perform the initial expand. */
/* I got the idea of expanding during the round function from SSLeay */
#ifdef LITTLE_ENDIAN
#define blk0(i) (block->l[i] = (rol(block->l[i],24)&0xFF00FF00) \
|(rol(block->l[i],8)&0x00FF00FF))
#else
#define blk0(i) block->l[i]
#endif
#define blk(i) (block->l[i&15] = rol(block->l[(i+13)&15]^block->l[(i+8)&15] \
^block->l[(i+2)&15]^block->l[i&15],1))

/* (R0+R1), R2, R3, R4 are the different operations used in SHA1 */
#define R0(v,w,x,y,z,i) z+=((w&(x^y))^y)+blk0(i)+0x5A827999+rol(v,5);w=rol(w,30);
#define R1(v,w,x,y,z,i) z+=((w&(x^y))^y)+blk(i)+0x5A827999+rol(v,5);w=rol(w,30);
#define R2(v,w,x,y,z,i) z+=(w^x^y)+blk(i)+0x6ED9EBA1+rol(v,5);w=rol(w,30);
#define R3(v,w,x,y,z,i) z+=(((w|x)&y)|(w&x))+blk(i)+0x8F1BBCDC+rol(v,5);w=rol(w,30);
#define R4(v,w,x,y,z,i) z+=(w^x^y)+blk(i)+0xCA62C1D6+rol(v,5);w=rol(w,30);


/* Hash a single 512-bit block. This is the core of the algorithm. */

__inline__ void SHA1Transform(unsigned long state[5], unsigned char buffer[64])
{
	unsigned long a, b, c, d, e;
	typedef union {
		unsigned char c[64];
		unsigned long l[16];
	} CHAR64LONG16;
	CHAR64LONG16 *block;
#ifdef SHA1HANDSOFF
	static unsigned char workspace[64];
	block = (CHAR64LONG16 *) workspace;
	memcpy(block, buffer, 64);
#else
	block = (CHAR64LONG16 *) buffer;
#endif
	/* Copy context->state[] to working vars */
	a = state[0];
	b = state[1];
	c = state[2];
	d = state[3];
	e = state[4];
	/* 4 rounds of 20 operations each. Loop unrolled. */
	R0(a, b, c, d, e, 0);
	R0(e, a, b, c, d, 1);
	R0(d, e, a, b, c, 2);
	R0(c, d, e, a, b, 3);
	R0(b, c, d, e, a, 4);
	R0(a, b, c, d, e, 5);
	R0(e, a, b, c, d, 6);
	R0(d, e, a, b, c, 7);
	R0(c, d, e, a, b, 8);
	R0(b, c, d, e, a, 9);
	R0(a, b, c, d, e, 10);
	R0(e, a, b, c, d, 11);
	R0(d, e, a, b, c, 12);
	R0(c, d, e, a, b, 13);
	R0(b, c, d, e, a, 14);
	R0(a, b, c, d, e, 15);
	R1(e, a, b, c, d, 16);
	R1(d, e, a, b, c, 17);
	R1(c, d, e, a, b, 18);
	R1(b, c, d, e, a, 19);
	R2(a, b, c, d, e, 20);
	R2(e, a, b, c, d, 21);
	R2(d, e, a, b, c, 22);
	R2(c, d, e, a, b, 23);
	R2(b, c, d, e, a, 24);
	R2(a, b, c, d, e, 25);
	R2(e, a, b, c, d, 26);
	R2(d, e, a, b, c, 27);
	R2(c, d, e, a, b, 28);
	R2(b, c, d, e, a, 29);
	R2(a, b, c, d, e, 30);
	R2(e, a, b, c, d, 31);
	R2(d, e, a, b, c, 32);
	R2(c, d, e, a, b, 33);
	R2(b, c, d, e, a, 34);
	R2(a, b, c, d, e, 35);
	R2(e, a, b, c, d, 36);
	R2(d, e, a, b, c, 37);
	R2(c, d, e, a, b, 38);
	R2(b, c, d, e, a, 39);
	R3(a, b, c, d, e, 40);
	R3(e, a, b, c, d, 41);
	R3(d, e, a, b, c, 42);
	R3(c, d, e, a, b, 43);
	R3(b, c, d, e, a, 44);
	R3(a, b, c, d, e, 45);
	R3(e, a, b, c, d, 46);
	R3(d, e, a, b, c, 47);
	R3(c, d, e, a, b, 48);
	R3(b, c, d, e, a, 49);
	R3(a, b, c, d, e, 50);
	R3(e, a, b, c, d, 51);
	R3(d, e, a, b, c, 52);
	R3(c, d, e, a, b, 53);
	R3(b, c, d, e, a, 54);
	R3(a, b, c, d, e, 55);
	R3(e, a, b, c, d, 56);
	R3(d, e, a, b, c, 57);
	R3(c, d, e, a, b, 58);
	R3(b, c, d, e, a, 59);
	R4(a, b, c, d, e, 60);
	R4(e, a, b, c, d, 61);
	R4(d, e, a, b, c, 62);
	R4(c, d, e, a, b, 63);
	R4(b, c, d, e, a, 64);
	R4(a, b, c, d, e, 65);
	R4(e, a, b, c, d, 66);
	R4(d, e, a, b, c, 67);
	R4(c, d, e, a, b, 68);
	R4(b, c, d, e, a, 69);
	R4(a, b, c, d, e, 70);
	R4(e, a, b, c, d, 71);
	R4(d, e, a, b, c, 72);
	R4(c, d, e, a, b, 73);
	R4(b, c, d, e, a, 74);
	R4(a, b, c, d, e, 75);
	R4(e, a, b, c, d, 76);
	R4(d, e, a, b, c, 77);
	R4(c, d, e, a, b, 78);
	R4(b, c, d, e, a, 79);
	/* Add the working vars back into context.state[] */
	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
	state[4] += e;
	/* Wipe variables */
	a = b = c = d = e = 0;
}


/* SHA1Init - Initialize new context */

__inline__ void SHA1Init(SHA1_CTX * context)
{
	/* SHA1 initialization constants */
	context->state[0] = 0x67452301;
	context->state[1] = 0xEFCDAB89;
	context->state[2] = 0x98BADCFE;
	context->state[3] = 0x10325476;
	context->state[4] = 0xC3D2E1F0;
	context->count[0] = context->count[1] = 0;
}


/* Run your data through this. */

__inline__ void SHA1Update(SHA1_CTX * context, unsigned char *data, unsigned int len)
{
	unsigned int i, j;

	j = (context->count[0] >> 3) & 63;
	if ((context->count[0] += len << 3) < (len << 3))
		context->count[1]++;
	context->count[1] += (len >> 29);
	if ((j + len) > 63) {
		memcpy(&context->buffer[j], data, (i = 64 - j));
		SHA1Transform(context->state, context->buffer);
		for (; i + 63 < len; i += 64) {
			SHA1Transform(context->state, &data[i]);
		}
		j = 0;
	} else
		i = 0;
	memcpy(&context->buffer[j], &data[i], len - i);
}


/* Add padding and return the message digest. */

__inline__ void SHA1Final(unsigned char digest[20], SHA1_CTX * context)
{
	unsigned long i, j;
	unsigned char finalcount[8];

	for (i = 0; i < 8; i++) {
		finalcount[i] = (unsigned char) ((context->count[(i >= 4 ? 0 : 1)]
										  >> ((3 - (i & 3)) * 8)) & 255);	/* Endian independent */
	}
	SHA1Update(context, (unsigned char *) "\200", 1);
	while ((context->count[0] & 504) != 448) {
		SHA1Update(context, (unsigned char *) "\0", 1);
	}
	SHA1Update(context, finalcount, 8);	/* Should cause a SHA1Transform() */
	for (i = 0; i < 20; i++) {
		digest[i] = (unsigned char)
			((context->state[i >> 2] >> ((3 - (i & 3)) * 8)) & 255);
	}
	/* Wipe variables */
	i = j = 0;
	memset(context->buffer, 0, 64);
	memset(context->state, 0, 20);
	memset(context->count, 0, 8);
	memset(&finalcount, 0, 8);
#ifdef SHA1HANDSOFF				/* make SHA1Transform overwrite it's own static vars */
	SHA1Transform(context->state, context->buffer);
#endif
}


#define CUARTO_ORDEN

char **dict;
char *dict_member_length;
int dict_count;
unsigned int *hash;
int hash_count;

__inline__ int hashSHA1(char *buffer, SHA1_CTX * context, int size)
{
	unsigned char digest[20];
	SHA1Init(context);
	SHA1Update(context, buffer, size);
	SHA1Final(digest, context);
	return *((unsigned int *) digest);
}

int load_hash_list(char *filename)
{
	int i;
	unsigned int t;
	FILE *fp;
	printf("Reading hash file '%s'\n", filename);
	if ((fp = fopen(filename, "rt")) == NULL)
		return -1;
	hash_count = 0;
	while (fscanf(fp, "0x%x\n", &t) == 1)
		hash_count++;
printf("hash_count = %d\n", hash_count);
	fseek(fp, 0, SEEK_SET);
	hash = malloc(hash_count * sizeof(unsigned int));
	i = 0;
	while (fscanf(fp, "0x%x\n", &hash[i++]) == 1);
	fclose(fp);
	return 0;
}

int load_dictionary(char *filename)
{
	int i;
	char buffer[0x200];
	FILE *fp;
	printf("Reading dictionary file '%s'\n", filename);
	if ((fp = fopen(filename, "rt")) == NULL)
		return -1;
	dict_count = 0;
	while (fscanf(fp, "%s\n", buffer) != EOF)
		dict_count++;
printf("dict_count = %d\n", dict_count);
	fseek(fp, 0, SEEK_SET);
	dict = (char **) malloc(dict_count * sizeof(char *));
	dict_member_length = malloc(dict_count);
	i = 0;
	while (fscanf(fp, "%s\n", buffer) == 1) {
		if ((buffer[0] == '-') || (buffer[0] == '/')) {	// This handles comments in the dic file
		} else {				// Not a comment, so do duplicate check
			int count;
			int found = 0;
			for (count = 0; count < (i - 1); count++)
				if (strcmp(buffer, dict[count]) == 0)
					found = 1;
			if (found == 0) {	// If not already in dictionary, then add
				dict_member_length[i] = strlen(buffer);
				dict[i] = malloc(dict_member_length[i] + 1);
				strcpy(dict[i], buffer);
				i++;
			}
		}
	}
	dict_count = i;
	fclose(fp);
	return 0;
}

FILE *fout;

// Hash seems to be where the program spends most of its time, so we need to speedup the
// search somehow
// 32 bit value, 4 bytes
// what we do, is pre-sort the hashlist, so they are in order AABBCCDD
// Then index each byte into the list, hence cutting down the search space considerably
typedef struct {
	unsigned int number;
	unsigned int next[256];
} search_space_t2;
typedef struct {
	unsigned int number;
	search_space_t2 next[256];
} search_space_t;
search_space_t searchtable[256];

void fillsearchtable()
{
	unsigned int searchval;
	int hashpos, hashpos2, hashpos3;
	int count, count2, count3;
	// Firstly Sort the hashlist, order AABBCCDD
	int found = 1;
	printf("Sorting Hashlist\n");
	while (found == 1) {
		found = 0;
		for (count = 0; count < (hash_count - 1); count++) {
			if (hash[count] > hash[count + 1]) {	// swap entries if wrong way around
				unsigned int temp = hash[count + 1];
				hash[count + 1] = hash[count];
				hash[count] = temp;
				found = 1;
			}
		}
	}
	printf("Building Search Tree\n");
	// Now build the toplevel (first) byte
	for (count = 0; count < 256; count++) {	// Find the first firstbyte in the hashlist that matches this value
		hashpos = 0;
		searchval = (count << 24);
		while ((hash[hashpos++] & 0xff000000) < searchval);
		hashpos--;
		if ((hash[hashpos] & 0xff000000) == searchval) {	// Add this entry
			searchtable[count].number = hashpos;

			// Now Search for a twobyte combo
			for (count2 = 0; count2 < 256; count2++) {	// Find the first secondbyte in the hashlist from this pos
				hashpos2 = hashpos;
				searchval = (count << 24) | (count2 << 16);
				while ((hash[hashpos2++] & 0xffff0000) < searchval);
				hashpos2--;
				if ((hash[hashpos2] & 0xffff0000) == searchval) {	// Add this entry
					searchtable[count].next[count2].number = hashpos2;

					// Now Search for a threebyte combo
					for (count3 = 0; count3 < 256; count3++) {	// Find the first thirdbyte in the hashlist from this pos
						hashpos3 = hashpos2;
						searchval = (count << 24) | (count2 << 16) | (count3 << 8);
						while ((hash[hashpos3++] & 0xffffff00) < searchval);
						hashpos3--;
						if ((hash[hashpos3] & 0xffffff00) == searchval) {
							searchtable[count].next[count2].next[count3] = hashpos3;
						} else {	// Higher number
							searchtable[count].next[count2].next[count3] = 0;
						}
					}
				} else {		// Higher number
					searchtable[count].next[count2].number = 0;
					for (count3 = 0; count3 < 256; count3++)
						searchtable[count].next[count2].next[count3] = 0;
				}
			}
		} else {				// Higher number
			searchtable[count].number = 0;
			for (count2 = 0; count2 < 256; count2++) {
				searchtable[count].next[count2].number = 0;
				for (count3 = 0; count3 < 256; count3++)
					searchtable[count].next[count2].next[count3] = 0;
			}
		}
	}
}

int findhash(char *buffer, SHA1_CTX * context, int size, int prefixlen)
{
	int h;
	unsigned int hashvalue = hashSHA1(buffer, context, size);
	unsigned int index1 = (hashvalue & 0xff000000) >> 24;
	unsigned int index2 = (hashvalue & 0x00ff0000) >> 16;
	unsigned int index3 = (hashvalue & 0x0000ff00) >> 8;
	unsigned int pos;
	// Get threebyte position
	pos = searchtable[index1].next[index2].next[index3];

	if (pos != 0) {				// Found a position, so search from here
		for (h = pos; h < hash_count; h++) {
			if (hashvalue >= hash[h]) {
				if (hashvalue == hash[h]) {	// If equal, found
					printf("Found : %-40s 0x%08x\n", buffer, hashvalue);
					fprintf(fout, "<FUNC><NAME>%s</NAME><NID>0x%08x</NID></FUNC>\n", buffer, hashvalue);
					fflush(stdout);
					fflush(fout);
					return 1;
				} else			// If not, reject as above
					return 0;
			}
		}
	}
	return 0;
}

int main(int argc, char **argv)
{
	int i; // , j, h;
	int x, y, z, zz; // , z2;
	SHA1_CTX context;
	char buffer[0x200];
	time_t start, end;
	int colisiones;

	char *ptr, *ptr0, *ptr1, *ptr2, *ptr3; // , *ptr4;

	char *prefix = "";
	int prefixlen = 0;

	printf("SHA1 hash dictionary attack v1.0 by adresd\n");
	printf("based on the original by djhuevo\n");

	if (argc < 3) {
		printf("usage:\n\t%s <hash_list> <dictionary> [prefix]\n", argv[0]);
		return 1;
	}

	if (load_hash_list(argv[1]) < 0) {
		fprintf(stderr, "can't open the hash file %s\n", argv[1]);
		return 2;
	}

	if (load_dictionary(argv[2]) < 0) {
		fprintf(stderr, "can't open the dictionary file %s\n", argv[2]);
		return 3;
	}

	if (argc > 3) {
		prefix = argv[3];
		strcpy(buffer, prefix);
		prefixlen = strlen(prefix);
	}

	if (hash_count < 1 || dict_count < 1) {
		fprintf(stderr, "error on input data.\n");
		fprintf(stderr, "hash_count = %d, dict_count = %d\n", hash_count, dict_count);
		return 4;
	}

	if ((fout = fopen("results.xml", "wba")) <= 0) {
		printf("Failed to open output file\n");
		exit(1);
	}

	printf("\nprefix : '%s'\n", prefix != "" ? prefix : "<None>");
	printf("hash count : %d\n", hash_count);
	printf("dictionary words: %d\n\n", dict_count);

	fillsearchtable();

	printf("\nsearching...\n\n");
	fflush(stdout);
	time(&start);
	ptr = buffer + prefixlen;
	colisiones = 0;
	// First Word
	for (x = 0; x < dict_count; x++) {
		ptr0 = ptr;
		for (i = 0; i < dict_member_length[x]; i++) {
			*(ptr0++) = dict[x][i];
		}
		*(ptr0) = 0;
		printf("// processing word: %s\n", buffer);
		fflush(stdout);
		// Second word
		for (y = 0; y < dict_count; y++) {
			ptr1 = ptr0;
			for (i = 0; i < dict_member_length[y]; i++) {
				*(ptr1++) = dict[y][i];
			}
			*(ptr1) = 0;
			//printf("// processing word: %s\n",buffer);

			// Only do next loop if first and second dont match
			if (strcmp(dict[x], dict[y]) != 0) {
				// Third Word
				for (z = 0; z < dict_count; z++) {
					ptr2 = ptr1;
					for (i = 0; i < dict_member_length[z]; i++) {
						*(ptr2++) = dict[z][i];
					}
					// Only do next loop if second and third dont match
					if (strcmp(dict[y], dict[z]) != 0) {
						// Fourth Word
						for (zz = 0; zz < dict_count; zz++) {
							ptr3 = ptr2;
							for (i = 0; i < dict_member_length[zz]; i++) {
								*(ptr3++) = dict[zz][i];
							}
#if 0
							// Only do next loop if third and fourth dont match
							if (strcmp(dict[z], dict[zz]) != 0) {
								// Fifth Word
								for (z2 = 0; z2 < dict_count; z2++) {
									ptr4 = ptr3;
									for (i = 0; i < dict_member_length[z2]; i++) {
										*(ptr4++) = dict[z2][i];
									}
									*(ptr4) = 0x00;
									findhash(buffer, &context, ptr4 - buffer, prefixlen);
								}
							}
#endif
							*(ptr3) = 0x00;
							findhash(buffer, &context, ptr3 - buffer, prefixlen);
						}
					}
					*(ptr2) = 0x00;
					findhash(buffer, &context, ptr2 - buffer, prefixlen);
				}
			}
			*(ptr1) = 0x00;
			findhash(buffer, &context, ptr1 - buffer, prefixlen);
		}
		*(ptr0) = 0x00;
		findhash(buffer, &context, ptr0 - buffer, prefixlen);
	}
	time(&end);
	printf("\n\ntime : %f seconds.", difftime(end, start));

	fclose(fout);
	return 0;
}

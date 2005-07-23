#ifndef _GPWRAP_H_
#define _GPWRAP_H_

// #warning GPWRAP.........................

#include <gpdef.h>
#include <gpstdio.h>
#include <gpstdlib.h>
#include <gpmem.h>
#include <gpos_def.h>


#define EOF     (-1)
#define RAND_MAX 0x7fffffff

#define stderr NULL

static inline void *calloc(size_t nmemb, size_t size) {  return gm_zi_malloc(nmemb*size); }
static inline void free(void *ptr){ gm_free(ptr); }
static inline void *malloc(size_t size){ return gm_zi_malloc(size);}
static inline void memset(void *ptr, unsigned char val, unsigned int size){ gm_memset(ptr,val,size); }
static inline void *memcpy(void *s1, const void *s2, unsigned int size){ return gm_memcpy(s1,s2,size); }
static inline char *strcpy(char *s1, const char *s2){ return gm_strcpy(s1,s2); }
static inline char *strncpy(char *s1, const char *s2, unsigned int size){ return gm_strncpy(s1,s2,size); }
static inline char *strcat(char *s1, const char *s2){ return gm_strcat(s1,s2); }
static inline size_t strlen(const char *s) { return ((size_t)gm_lstrlen(s)); };
static inline int strcmp(const char *s1, const char *s2){ return gm_compare(s1,s2); }
static inline int strncmp(const char *s1, const char *s2, size_t n)
{
	int ret;
	char *tmp_s1=(char *)calloc(1,n+16);
	char *tmp_s2=(char *)calloc(1,n+16);
	strncpy(tmp_s1,s1,n);
	strncpy(tmp_s2,s2,n);
	ret=strcmp(tmp_s1,tmp_s2);
	free(tmp_s2);
	free(tmp_s1);
	return ret;
}
static inline int memcmp(const void *s1, const void *s2, size_t n){ return strncmp(s1,s2,n); }


static int __gp32_fat_initialize__=0;

typedef F_HANDLE FILE;

static FILE __gp32_files__[1024];
static int __gp32_files_pointer__=0;

static inline FILE *fopen(const char *path, const char *mode)
{
	int i,j;
	FILE *ret=(FILE *)&__gp32_files__[__gp32_files_pointer__];
	ulong fopen_mode=OPEN_R;
	if (!__gp32_fat_initialize__)
	{
		__gp32_fat_initialize__=-1;
		GpFatInit();
	}
	j=strlen(mode);
	for(i=0;i<j;i++)
		if (mode[i]=='w')
		{
			if (GpFileCreate(path,ALWAYS_CREATE,ret)!=SM_OK)
				return NULL;
			else
			{
				__gp32_files_pointer__++;
				return ret;
			}
		}
	if (GpFileOpen(path,fopen_mode,ret)!=SM_OK)
		return NULL;
	__gp32_files_pointer__++;
	return ret;	
}

static inline int fclose(FILE *stream){ GpFileClose((*stream)); return 0; }

static inline size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	ulong buf_size=size*nmemb;
	ulong p_read_count;
	GpFileRead((*stream),ptr,buf_size,&p_read_count);
	return (p_read_count/size);
}

static inline size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	ulong count=size*nmemb;
	if (GpFileWrite((*stream),ptr,count)!=SM_OK)
		return 0;
	return (count/size);
}

#define SEEK_SET FROM_BEGIN
#define SEEK_CUR FROM_CURRENT
#define SEEK_END FROM_END

static inline int fseek(FILE *stream, long offset, int whence)
{
	if (GpFileSeek((*stream),whence,offset,NULL)!=SM_OK)
		return -1;
	return 0;
}

static inline long ftell(FILE *stream)
{
	long p_old_offset=0;
	
	if (GpFileSeek((*stream),FROM_CURRENT,0,&p_old_offset)!=SM_OK)
		return -1;
	return p_old_offset;
}

static inline char *getenv(const char *name){ return NULL; }

#define sprintf gm_sprintf

static inline char *strchr(const char *s, int c)
{
	char *ret=(char *)s;
	size_t i,l=strlen(s);
	for(i=0;i<l;i++,ret++)
		if ((*ret)==c)
			return (char *)ret;
	return NULL;
}

static inline char *strrchr(const char *s, int c)
{
	size_t i,l=strlen(s);
	char *ret=(char *)s;
	if (l==0)
		return NULL;
	l--;
	ret+=l;
	for(i=l;i>=0;i--,ret--)
		if ((*ret)==c)
			return (char *)ret;
	return NULL;
}

static inline int fgetc(FILE *stream)
{
	int ret=0;
	if (fread((void *)&ret,1,1,stream)!=1)
		return EOF;
	return ret;
}

static inline int feof(FILE *stream)
{
	long end,pos=ftell(stream);
	fseek(stream,0,SEEK_END);
	end=ftell(stream);
	fseek(stream,pos,SEEK_SET);
	if (pos!=end)
		return 0;
	return EOF;
}

static inline char *strdup(const char *s)
{
	char *ret=NULL;
	size_t l=strlen(s);
	if (s>0)
	{
		ret=calloc(l+16,1);
		strcpy(ret,s);
	}
	return ret;
}


static inline void *realloc(void *ptr, size_t size)
{
	void *ret=NULL;
	if (ptr==NULL)
		return malloc(size);
	if (size>0)
	{
		ret=malloc(size);
		if (ret==NULL)
			return NULL;
		memcpy(ret,ptr,size);
	}
	free(ptr);
	return ret;
}

static inline int printf(const char *format, ...){ return strlen(format);}
static inline int fprintf(FILE *stream, const char *format, ...){ return strlen(format);}

static inline void clearerr( FILE *stream){ ;}

static inline int strcasecmp(const char *s1, const char *s2)
{
	int ret=0;
	int ls1=strlen(s1);
	int ls2=strlen(s2);
	if ((ls1>0)&&(ls2>0))
	{
		char *ns1=(char *)calloc(1,ls1+16);
		char *ns2=(char *)calloc(1,ls2+16);
		memcpy(ns1,s1,ls1);
		memcpy(ns2,s2,ls2);
		gm_lowercase(ns1,ls1);
		gm_lowercase(ns2,ls2);
		ret=strcmp(ns1,ns2);
		free(ns2);
		free(ns1);
	}
	return ret;
}

static inline void srand(unsigned int seed){ GpSrand(seed); }

static inline int rand(void){ return GpRand();}

static inline int abs(int j)
{
	if (j<0)
		return -j;
	return j;
}

static inline int fputc(int c, FILE *stream)
{
	unsigned char ret=c;
	if (fwrite((void *)&ret,1,1,stream)!=1)
		return EOF;
	return ret;
}



#endif

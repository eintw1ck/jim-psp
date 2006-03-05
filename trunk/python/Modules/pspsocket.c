// $Id$

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "pspsocket.h"

int gethostname(char *name, size_t len)
{
    FILE *fp;
    size_t a;

    if (len < 0)
    {
       errno = EINVAL;
       return -1;
    }

    fp = fopen("ms0:/python/hostname", "r");
    if (!fp)
    {
       strncpy(name, "psp.net", len);
       return 0;
    }

    a = fread(name, 1, len - 1, fp);
    name[a] = 0;
    fclose(fp);

    return 0;
}

int sethostname(const char *name, size_t len)
{
    FILE *fp = fopen("ms0:/python/hostname", "w");

    if (len < 0)
    {
       errno = EINVAL;
       return -1;
    }

    if (!fp)
    {
       errno = EPERM;
       return -1;
    }

    fwrite(name, 1, len, fp);
    fclose(fp);

    return 0;
}

struct servent* getservbyname(const char *name, const char *proto)
{
    /* TODO */

    return NULL;
}

struct servent* getservbyport(int port, const char *proto)
{
    /* TODO */

    return NULL;
}

struct protoent* getprotobyname(const char *name)
{
    return NULL;
}

#ifdef GNUC
static const char* _rcsid_pspsocket __attribute__((unused)) = "$Id$";
#endif

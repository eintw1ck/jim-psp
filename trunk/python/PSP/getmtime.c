
/* Subroutine to get the last modification time of a file */

/* (A separate file because this may be OS dependent) */

#include "Python.h"
#include "pyconfig.h"

#include <pspiofilemgr.h>

time_t
PyOS_GetLastModificationTime(char *path, FILE *fp)
{
    SceIoStat st;

    if (sceIoGetstat(path, &st) < 0)
       return -1;

    return ((((st.st_mtime.year * 12 + st.st_mtime.month) * 31 + st.st_mtime.day)
             * 24 + st.st_mtime.hour) * 60 + st.st_mtime.minute) * 60 + st.st_mtime.second;
}

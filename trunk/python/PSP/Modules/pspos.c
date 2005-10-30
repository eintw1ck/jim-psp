
/**
 * @file pspos.c
 */

/**********************************************************************

  Created: 04 Oct 2005

**********************************************************************/
// $Id$

#include "Python.h"

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#include <pspiofilemgr.h>

#include "structseq.h"

extern char* formatPSPError(int); // in ../psperror.c

static PyObject* PyPSP_open(PyObject *self,
                            PyObject *args)
{
    char *path;
    int flags, mode;
    int fd;

    if (!PyArg_ParseTuple(args, "sii:open", &path, &flags, &mode))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    fd = open(path, flags,mode);
    if (fd < 0)
    {
       PyErr_SetString(PyExc_OSError, formatPSPError(fd));
       return NULL;
    }

    return Py_BuildValue("i", fd);
}

static int closefile(FILE *fp)
{
    return fclose(fp);
}

static PyObject* PyPSP_fdopen(PyObject *self,
                              PyObject *args)
{
    int fd;
    char *mode = "r";
    FILE *fp;

    if (!PyArg_ParseTuple(args, "i|s:fdopen", &fd, &mode))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    fp = fdopen(fd, mode);
    return PyFile_FromFile(fp, "", mode, closefile); // FIXME: name ?
}

static PyObject* PyPSP_unlink(PyObject *self,
                              PyObject *args)
{
    char *path;

    if (!PyArg_ParseTuple(args, "s:unlink", &path))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    if (unlink(path))
    {
       PyErr_SetFromErrno(PyExc_OSError);
       return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* PyPSP_rename(PyObject *self,
                              PyObject *args)
{
    char *src, *dst;

    if (!PyArg_ParseTuple(args, "ss:rename", &src, &dst))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    if (rename(src, dst))
    {
       PyErr_SetFromErrno(PyExc_OSError);
       return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* PyPSP_system(PyObject *self,
                              PyObject *args)
{
    char *cmd;

    if (!PyArg_ParseTuple(args, "s:system", &cmd))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    return PyInt_FromLong(system(cmd));
}

static PyObject* PyPSP_rmdir(PyObject *self,
                             PyObject *args)
{
    char *path;

    if (!PyArg_ParseTuple(args, "s:rmdir", &path))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    if (rmdir(path))
    {
       PyErr_SetFromErrno(PyExc_OSError);
       return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* PyPSP_chdir(PyObject *self,
                             PyObject *args)
{
    char *path;

    if (!PyArg_ParseTuple(args, "s:chdir", &path))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    if (chdir(path))
    {
       PyErr_SetFromErrno(PyExc_OSError);
       return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* PyPSP_getcwd(PyObject *self,
                              PyObject *args)
{
    char *cwd = NULL;
    int sz = 128;
    PyObject *ret;

    if (PyErr_CheckSignals())
       return NULL;

    for (;;)
    {
       char *n;

       sz *= 2;
       n = (char*)realloc(cwd, sz);

       if (!n)
       {
          if (cwd) free(cwd);
          PyErr_SetString(PyExc_MemoryError, "");
          return NULL;
       }

       cwd = n;

       if (!getcwd(cwd, sz))
       {
          if (errno == ERANGE)
          {
             continue;
          }

          PyErr_SetFromErrno(PyExc_OSError);
          if (cwd) free(cwd);
       }

       break;
    }

    ret = PyString_FromString(cwd);
    free(cwd);
    return ret;
}

static PyObject* PyPSP_mkdir(PyObject *self,
                             PyObject *args)
{
    char *path;
    int mode = 0, err;

    if (!PyArg_ParseTuple(args, "s|i:mkdir", &path, &mode))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    err = sceIoMkdir(path, mode);
    if (err)
    {
       PyErr_SetString(PyExc_OSError, formatPSPError(err));
       return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* PyPSP_listdir(PyObject *self,
                               PyObject *args)
{
    char *path;
    int fd;

    if (!PyArg_ParseTuple(args, "s:listdir", &path))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    fd = sceIoDopen(path);
    if (fd > 0)
    {
       SceIoDirent dr;

       PyObject *ret;
       int r;

       // Without this memset, the PSP reboots...
       memset(&dr, 0, sizeof(dr));

       ret = PyList_New(0);

       for (;;)
       {
          r = sceIoDread(fd, (SceIoDirent*)&dr);

          if (r < 0)
          {
             PyErr_SetString(PyExc_OSError, formatPSPError(r));
             Py_DECREF(ret);
             sceIoDclose(fd);
             return NULL;
          }

          if (r == 0)
             break;

          PyList_Append(ret, PyString_FromString(dr.d_name)); // FIXME: reference count ?
       }

       sceIoDclose(fd);
       return ret;
    }
    else
    {
       PyErr_SetString(PyExc_OSError, formatPSPError(fd));
       return NULL;
    }
}

PyDoc_STRVAR(stat_result__doc__,
"stat_result: Result from stat or lstat.\n\n\
This object may be accessed either as a tuple of\n\
  (mode,ino,dev,nlink,uid,gid,size,atime,mtime,ctime)\n\
or via the attributes st_mode, st_ino, st_dev, st_nlink, st_uid, and so on.\n\
\n\
See os.stat for more information.");

static PyStructSequence_Field stat_result_fields[] = {
   { "st_mode",  "protection bits" },
   { "st_ino",   "inode" },
   { "st_dev",   "device" },
   { "st_nlink", "number of hard links" },
   { "st_uid",   "user ID of owner" },
   { "st_gid",   "group ID of owner" },
   { "st_size",  "total size, in bytes" },
   { "st_atime", "time of last access" },
   { "st_mtime", "time of last modification" },
   { "st_ctime", "time of last change" },

   { 0 }
};

static PyStructSequence_Desc stat_result_desc = {
   "pspos.stat_result",
   stat_result__doc__,
   stat_result_fields,
   10
};

static PyTypeObject StatResultType;

static PyObject* PyPSP_stat(PyObject *self,
                            PyObject *args)
{
    char *path;
    PyObject *ret;
    //SceIoStat st;
    struct stat st;
    int err;

    if (!PyArg_ParseTuple(args, "s:stat", &path))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    //sceIoGetstat(path, &st);
    err = stat(path, &st);
    if (err)
    {
       PyErr_SetString(PyExc_OSError, formatPSPError(err));
       return NULL;
    }

    ret = PyStructSequence_New(&StatResultType);
    PyStructSequence_SET_ITEM(ret,  0, PyInt_FromLong(st.st_mode));
    PyStructSequence_SET_ITEM(ret,  1, PyInt_FromLong(st.st_ino));
    PyStructSequence_SET_ITEM(ret,  2, PyInt_FromLong(st.st_rdev));
    PyStructSequence_SET_ITEM(ret,  3, PyInt_FromLong(st.st_nlink));
    PyStructSequence_SET_ITEM(ret,  4, PyInt_FromLong(st.st_uid));
    PyStructSequence_SET_ITEM(ret,  5, PyInt_FromLong(st.st_gid));
    PyStructSequence_SET_ITEM(ret,  6, PyInt_FromLong(st.st_size));
    PyStructSequence_SET_ITEM(ret,  7, PyInt_FromLong((long)st.st_atime));
    PyStructSequence_SET_ITEM(ret,  8, PyInt_FromLong((long)st.st_mtime));
    PyStructSequence_SET_ITEM(ret,  9, PyInt_FromLong((long)st.st_ctime));

    return ret;
}

static PyObject* PyPSP_chmod(PyObject *self,
                             PyObject *args)
{
    char *path;
    int mode;

    if (!PyArg_ParseTuple(args, "si:chmod", &path, &mode))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    // FIXME

    /*
    if (chmod(path, mode))
    {
       PyErr_SetString(PyExc_OSError, "FIXME");
       return NULL;
    }
    */

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* PyPSP_utime(PyObject *self,
                             PyObject *args)
{
    // TODO

    if (PyErr_CheckSignals())
       return NULL;

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* PyPSP_getenv(PyObject *self,
                              PyObject *args)
{
    char *name;

    if (!PyArg_ParseTuple(args, "s:getenv", &name))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    // No such thing here...

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* PyPSP_putenv(PyObject *self,
                              PyObject *args)
{
    char *name, *val;

    if (!PyArg_ParseTuple(args, "ss:putenv", &name, &val))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    // No such thing here...

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* PyPSP_delenv(PyObject *self,
                              PyObject *args)
{
    char *name;

    if (!PyArg_ParseTuple(args, "s:delenv", &name))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    // No such thing here...

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* PyPSP_getenvdict(PyObject *self,
                                  PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
       return NULL;

    if (PyErr_CheckSignals())
       return NULL;

    return PyDict_New();
}

static PyMethodDef pspos_functions[] = {
   { "open", PyPSP_open, METH_VARARGS, "" },
   { "fdopen", PyPSP_fdopen, METH_VARARGS, "" },
   { "unlink", PyPSP_unlink, METH_VARARGS, "" },
   { "remove", PyPSP_unlink, METH_VARARGS, "" },
   { "rename", PyPSP_rename, METH_VARARGS, "" },
   { "system", PyPSP_system, METH_VARARGS, "" },
   { "rmdir", PyPSP_rmdir, METH_VARARGS, "" },
   { "chdir", PyPSP_chdir, METH_VARARGS, "" },
   { "getcwd", PyPSP_getcwd, METH_VARARGS, "" },
   { "mkdir", PyPSP_mkdir, METH_VARARGS, "" },
   { "listdir", PyPSP_listdir, METH_VARARGS, "" },
   { "stat", PyPSP_stat, METH_VARARGS, "" },
   { "lstat", PyPSP_stat, METH_VARARGS, "" },
   { "chmod", PyPSP_chmod, METH_VARARGS, "" },
   { "utime", PyPSP_utime, METH_VARARGS, "" },
   { "getenv", PyPSP_getenv, METH_VARARGS, "" },
   { "putenv", PyPSP_putenv, METH_VARARGS, "" },
   { "delenv", PyPSP_delenv, METH_VARARGS, "" },
   { "getenvdict", PyPSP_getenvdict, METH_VARARGS, "" },

   { NULL }
};

void initpspos(void)
{
    PyObject *mdl;

    mdl = Py_InitModule3("pspos", pspos_functions, "");
    if (!mdl)
       return;

    PyStructSequence_InitType(&StatResultType, &stat_result_desc);
    Py_INCREF(&StatResultType);
    PyModule_AddObject(mdl, "stat_result", (PyObject*)&StatResultType);

    PyModule_AddIntConstant(mdl, "O_RDONLY", O_RDONLY);
    PyModule_AddIntConstant(mdl, "O_WRONLY", O_WRONLY);
    PyModule_AddIntConstant(mdl, "O_RDWR", O_RDWR);
    PyModule_AddIntConstant(mdl, "O_CREAT", O_CREAT);
    PyModule_AddIntConstant(mdl, "O_EXCL", O_EXCL);
}

#pragma once

#define PY_SSIZE_T_CLEAN // use Py_ssize_t instead of int

#ifdef FOO_PYTHON_DEBUG
#include <Python.h>
#else
#ifdef _DEBUG
#undef _DEBUG // use these steps to avoid linking with python_d.lib
#define __FOO_RESTORE_DEBUG
#endif
#include <Python.h>
#ifdef __FOO_RESTORE_DEBUG
#define _DEBUG
#undef __FOO_RESTORE_DEBUG
#endif
#endif

#define PY_ARRAY_UNIQUE_SYMBOL opencv_ARRAY_API
#include <numpy/ndarrayobject.h>

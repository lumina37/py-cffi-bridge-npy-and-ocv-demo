#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject* myadd(PyObject* self, PyObject* args)
{
    long a, b;
    if (!PyArg_ParseTuple(args, "ll", &a, &b))
        return NULL;

    return PyLong_FromLong(a + b);
}

static PyMethodDef foo_methods[] = {{"myadd", myadd, METH_VARARGS, NULL}, {NULL, NULL, 0, NULL}};

static struct PyModuleDef foo_module = {PyModuleDef_HEAD_INIT, "libfoo", NULL, -1, foo_methods};

PyMODINIT_FUNC PyInit_libfoo(void) { return PyModule_Create(&foo_module); }
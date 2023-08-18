#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

static PyObject* mybgr2gray(PyObject* self, PyObject* args)
{
    long a, b;
    if (!PyArg_ParseTuple(args, "ll", &a, &b))
        return NULL;

    return PyLong_FromLong(a + b);
}

static PyMethodDef methods[] = {{"mybgr2gray", mybgr2gray, METH_VARARGS, NULL}, {NULL, NULL, 0, NULL}};

static struct PyModuleDef module = {PyModuleDef_HEAD_INIT, "_algorithm", NULL, -1, methods};

PyMODINIT_FUNC PyInit__algorithm(void) { return PyModule_Create(&module); }

#ifdef __cplusplus
}
#endif

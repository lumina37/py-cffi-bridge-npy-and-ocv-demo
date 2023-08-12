#include <Python.h>

static PyObject* myadd(PyObject* self, PyObject* args)
{
    long a, b;
    if (!PyArg_ParseTuple(args, "ll", &a, &b))
        return NULL;

    return PyLong_FromLong(a + b);
}

static PyMethodDef methods[] = {{"myadd", myadd, METH_VARARGS, NULL}, {NULL, NULL, 0, NULL}};

static struct PyModuleDef module = {PyModuleDef_HEAD_INIT, "_algorithm", NULL, -1, methods};

PyMODINIT_FUNC PyInit__algorithm(void) { return PyModule_Create(&module); }
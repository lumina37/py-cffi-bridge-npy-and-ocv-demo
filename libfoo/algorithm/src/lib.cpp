#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <opencv2/imgproc.hpp>

#include "libfoo/convert.hpp"

#ifdef __cplusplus
extern "C" {
#endif

static PyObject* mybgr2gray(PyObject* self, PyObject* args)
{
    PyObject* npy_array;
    if (!PyArg_ParseTuple(args, "O", &npy_array))
        return NULL;

    cv::Mat img, img_gray;
    from_npy(npy_array, img);
    cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
    npy_array = to_npy(img_gray);
    return npy_array;
}

static PyMethodDef methods[] = {{"mybgr2gray", mybgr2gray, METH_VARARGS, NULL}, {NULL, NULL, 0, NULL}};

static struct PyModuleDef module = {PyModuleDef_HEAD_INIT, "_algorithm", NULL, -1, methods};

PyMODINIT_FUNC PyInit__algorithm(void) { return PyModule_Create(&module); }

#ifdef __cplusplus
}
#endif

#include "libfoo/convert.hpp"
#include "libfoo/allocator.hpp"

#include <numpy/ndarrayobject.h>

#define CV_MAX_DIM 32

bool from_npy(PyObject* o, cv::Mat& m)
{
    if (!o || o == Py_None) {
        if (!m.data)
            m.allocator = &g_numpyAllocator;
        return true;
    }

    if (!PyArray_Check(o)) {
        PyObject* cls_name = PyType_GetName(Py_TYPE(o));
        PyErr_Format(PyExc_TypeError, "Expect numpy array, got %U", cls_name);
        return false;
    }

    auto* oarr = (PyArrayObject*)o;

    bool needcopy = false;

    int typenum = PyArray_TYPE(oarr);
    int new_typenum = typenum;
    if (typenum != NPY_UBYTE) {
        PyErr_Format(PyExc_ValueError, "Expect NPY_UBYTE, got %i", typenum);
        return false;
    }

    int ndims = PyArray_NDIM(oarr);
    size_t elemsize = 1;
    const npy_intp* _sizes = PyArray_DIMS(oarr);
    const npy_intp* _strides = PyArray_STRIDES(oarr);

    for (int i = ndims - 1; i >= 0 && !needcopy; i--) {
        // these checks handle cases of
        //  a) multi-dimensional (ndims > 2) arrays, as well as simpler 1- and 2-dimensional cases
        //  b) transposed arrays, where _strides[] elements go in non-descending order
        //  c) flipped arrays, where some of _strides[] elements are negative
        // the _sizes[i] > 1 is needed to avoid spurious copies when NPY_RELAXED_STRIDES is set
        if ((i == ndims - 1 && _sizes[i] > 1 && (size_t)_strides[i] != elemsize) ||
            (i < ndims - 1 && _sizes[i] > 1 && _strides[i] < _strides[i + 1]))
            needcopy = true;
    }

    if (needcopy) {

        oarr = PyArray_GETCONTIGUOUS(oarr);
        o = (PyObject*)oarr;

        _strides = PyArray_STRIDES(oarr);
    }

    int size[CV_MAX_DIM + 1] = {};
    size_t step[CV_MAX_DIM + 1] = {};

    // Normalize strides in case NPY_RELAXED_STRIDES is set
    size_t default_step = elemsize;
    for (int i = ndims - 1; i >= 0; --i) {
        size[i] = (int)_sizes[i];
        if (size[i] > 1) {
            step[i] = (size_t)_strides[i];
            default_step = step[i] * size[i];
        } else {
            step[i] = default_step;
            default_step *= size[i];
        }
    }

    m = cv::Mat(ndims, size, CV_8U, PyArray_DATA(oarr), step);
    m.u = g_numpyAllocator.allocate(o, ndims, size, CV_8U, step);
    m.addref();

    if (!needcopy) {
        Py_INCREF(o);
    }
    m.allocator = &g_numpyAllocator;

    return true;
}

PyObject* to_npy(const cv::Mat& m)
{
    if( !m.data )
        Py_RETURN_NONE;
    cv::Mat temp, *p = (cv::Mat*)&m;
    if(!p->u || p->allocator != &g_numpyAllocator)
    {
        temp.allocator = &g_numpyAllocator;
        m.copyTo(temp);
        p = &temp;
    }
    auto* o = (PyObject*)p->u->userdata;
    Py_INCREF(o);
    return o;
}

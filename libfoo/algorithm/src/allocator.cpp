#define NO_IMPORT_ARRAY
#include "libfoo/allocator.h"

NumpyAllocator g_numpyAllocator;

cv::UMatData* NumpyAllocator::allocate(PyObject* o, int dims, const int* sizes, int type, size_t* step) const
{
    auto* u = new cv::UMatData(this);
    u->data = u->origdata = (uchar*)PyArray_DATA((PyArrayObject*)o);
    npy_intp* _strides = PyArray_STRIDES((PyArrayObject*)o);
    for (int i = 0; i < dims - 1; i++)
        step[i] = (size_t)_strides[i];
    step[dims - 1] = CV_ELEM_SIZE(type);
    u->size = sizes[0] * step[0];
    u->userdata = o;
    return u;
}

cv::UMatData* NumpyAllocator::allocate(int dims0, const int* sizes, int type, void* data, size_t* step,
                                       cv::AccessFlag flags, cv::UMatUsageFlags usageFlags) const
{
    if (data != nullptr) {
        // issue #6969: CV_Error(Error::StsAssert, "The data should normally be NULL!");
        // probably this is safe to do in such extreme case
        return stdAllocator->allocate(dims0, sizes, type, data, step, flags, usageFlags);
    }
    PyEnsureGIL gil;

    int cn = CV_MAT_CN(type);
    int typenum = NPY_UBYTE;
    int i, dims = dims0;
    cv::AutoBuffer<npy_intp> _sizes(dims + 1);
    for (i = 0; i < dims; i++)
        _sizes[i] = sizes[i];
    if (cn > 1)
        _sizes[dims++] = cn;
    PyObject* o = PyArray_SimpleNew(dims, _sizes.data(), typenum);
    return allocate(o, dims0, sizes, type, step);
}

bool NumpyAllocator::allocate(cv::UMatData* u, cv::AccessFlag accessFlags, cv::UMatUsageFlags usageFlags) const
{
    return stdAllocator->allocate(u, accessFlags, usageFlags);
}

void NumpyAllocator::deallocate(cv::UMatData* u) const
{
    if (!u)
        return;
    PyEnsureGIL gil;
    if (u->refcount == 0) {
        auto* o = (PyObject*)u->userdata;
        Py_XDECREF(o);
        delete u;
    }
}

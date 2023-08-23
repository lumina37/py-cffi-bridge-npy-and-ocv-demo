#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <opencv2/core.hpp>

class PyEnsureGIL
{
public:
    PyEnsureGIL() : _state(PyGILState_Ensure()) {}
    ~PyEnsureGIL() { PyGILState_Release(_state); }

private:
    PyGILState_STATE _state;
};

class NumpyAllocator : public cv::MatAllocator
{
public:
    NumpyAllocator() { stdAllocator = cv::Mat::getStdAllocator(); }
    ~NumpyAllocator() {}

    cv::UMatData* allocate(PyObject* o, int dims, const int* sizes, int type, size_t* step) const;
    cv::UMatData* allocate(int dims0, const int* sizes, int type, void* data, size_t* step, cv::AccessFlag flags,
                           cv::UMatUsageFlags usageFlags) const CV_OVERRIDE;
    bool allocate(cv::UMatData* u, cv::AccessFlag accessFlags, cv::UMatUsageFlags usageFlags) const CV_OVERRIDE;
    void deallocate(cv::UMatData* u) const CV_OVERRIDE;

    const cv::MatAllocator* stdAllocator;
};

extern NumpyAllocator g_numpyAllocator;

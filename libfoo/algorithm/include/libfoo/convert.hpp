#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <opencv2/core.hpp>

bool from_npy(PyObject* o, cv::Mat& m);

PyObject* to_npy(const cv::Mat& m);

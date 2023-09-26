# Python-cffi: Bridge NumPy and OpenCV Demo

This demo shows the bidirectional conversion between NumPy ndarray (uint8, not more than 3 channels) and cv::Mat (CV_8U). I hope it could be a draft guideline about how to implement high-performance algorithm based OpenCV as extension for NumPy.

The demo also applies lots of next-generation Python-Cpp hybrid project organizing methods.

For the Cpp side, the complex compilation and source seeking are entirely managed by CMake.

For the Python side, the project follows [pep-518](https://peps.python.org/pep-0518/), with a pyproject.toml containing all project metadata.

Then the Python package managing tool [pdm](https://pdm.fming.dev/) and the extension building tool [scikit-build-core](https://github.com/scikit-build/scikit-build-core) work as glue to bridge both sides together.

Yet, I must admit that it is extremely hard to debug the C-Extension for Python due to the intricate linker settings and poor IDE support.

## Before Build

Install [OpenCV](https://github.com/opencv/opencv) first. This demo is only tested against `BUILD_SHARED_LIBS=ON` mode on Windows-x64 platform.

### Note for Windows

If you are using Windows platform, please make sure the OpenCV DLLs can be found through the enviornment varible `PATH`.

### Choose a Picture

Choose a picture, copy and paste it to the working directory, then rename it to `test.jpg`.

## Build and Run

### Using pip

```shell
pip install -e .
python main.py
```

DO NOT miss the dot after `-e`

### Using pdm

```shell
pdm sync
pdm install
pdm run python main.py
```

### Expect Behaviour

GUI window pops out and shows the grayscaled image.

## Reference

The original converter can be found [here](https://github.com/opencv/opencv/blob/4.x/modules/python/src2/cv2_convert.cpp).

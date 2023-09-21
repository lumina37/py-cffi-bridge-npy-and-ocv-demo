# Python-cffi: Bridge NumPy and OpenCV Demo

This demo shows the bidirectional conversion method between NumPy ndarray (uint8, not more than 3 channels) and cv::Mat (CV_8U).

Aiming to implement high-performance algorithm for NumPy with the assistance of OpenCV.

And the demo additionally applies lots of next-generation Python-Cpp hybrid project organizing methods.

For the Cpp side, the complex compilation and source seeking are entirely managed by CMake.

For the Python side, the project is following [pep-518](https://peps.python.org/pep-0518/), with a pyproject.toml containing all metadata.

Then the Python package managing tool [pdm](https://pdm.fming.dev/) and the extension building tool [scikit-build-core](https://github.com/scikit-build/scikit-build-core) work as glue to bridge both sides together.

But, I must admit that, it is extremely hard to debug the C-Extension for Python, especially when building with [scikit-build-core](https://github.com/scikit-build/scikit-build-core).

## Before build

You must install OpenCV first. This demo is only tested over shared-lib mode on Windows-x64 platform.

### Windows

If you are using Windows platform, please make sure the opencv dlls can be found through the enviornment varible `PATH`.

### Choose a picture

Choose a picture, copy and paste it to the working directory, then rename it to `test.jpg`.

### Using pip

```shell
pip install -e .
python main.py
```

### Using pdm

```shell
pdm sync
pdm run python main.py
```

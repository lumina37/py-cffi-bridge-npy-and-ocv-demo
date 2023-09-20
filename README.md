# Python-cffi: Bridge Numpy and OpenCV Demo

I must admit that it is extremely hard to debug the C-Extension for Python, especially when building with [scikit-build-core](https://github.com/scikit-build/scikit-build-core)

## Before build

You must install OpenCV first. Only tested over shared-lib mode.

### Windows

If you are using Windows platform, please make sure the opencv dlls can be found through the enviornment varible `PATH`.

### Choose a picture

Choose a picture, copy and paste it in the working directory and rename it to `test.jpg`.

## Using pip

```shell
pip install -e .
python main.py
```

## Using pdm

```shell
pdm sync
pdm run python main.py
```

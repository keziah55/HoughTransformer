# HoughTransformer

Hough transform for lines, implemented in C++, with Python bindings.

Get the Hough transform of a signal.

## Installation

`HoughTransformer` is built with [cmake](https://cmake.org/) and uses 
[SWIG](https://www.swig.org/) to generate Python bindings. 
It also requires [numpy](https://numpy.org/), as numpy arrays are passed to the 
`HoughTransform` functions in the Python bindings.

Building requires the path to the numpy `include` directory. It is recommended to create
and activate a Python [virtual environment](https://docs.python.org/3/tutorial/venv.html)
before building, so that it picks up the latest numpy version. If you don't want to build
using a virtual environment, you'll need numpy installed on your system.

To build:
```
mkdir build
cd build
python -m venv .venv
source .venv/bin/activate
python -m pip install numpy build wheel
cmake ..
cmake --build .
```

This builds Python wrappers in `build/src/` and can be installed in another virtual
environment with `python -m pip install path/to/HoughTransformer/build/src`.


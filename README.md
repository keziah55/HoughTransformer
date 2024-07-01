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
using a virtual environment, you'll need numpy installed on your system (and you'll need
to make sure that the numpy version you build against is the same as the one you'll use
`HoughTransformer` with).

To build, including wheel:
```bash
mkdir build
cd build
# setup venv
python -m venv .venv
source .venv/bin/activate
python -m pip install numpy build wheel
# bulid
cmake ..
cmake --build .
# build python wheel
cd src
python -m build
```

```
This creates a `hough-0.1-py3-none-any.whl` file (and tarball) in `dist`, which can be
pip installed
```
python -m pip install path/to/HoughTransformer/build/src/dst/hough-0.1-py3-none-any.whl
```


/* File: hough.i */
%module hough

%{
#define SWIG_FILE_WITH_INIT
#include "hough.h"
%}


%include "numpy.i"
//%include "array2d.i"

%init %{
import_array();
%}

%apply (double* IN_ARRAY1, int DIM1) {(const double* inputSignal,
                                       const std::size_t x_size)};

%apply (double* IN_ARRAY2, int DIM1, int DIM2) {(const double* inputSignal,
                                       const std::size_t x_size,
                                       const std::size_t y_size)};


%include "hough.h"

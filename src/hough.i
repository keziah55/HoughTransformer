/* File: hough.i */
%module hough

%{
#define SWIG_FILE_WITH_INIT
#include "hough.h"
%}

%include std_vector.i
%include std_pair.i
%include <std_string.i>
%include "numpy.i"

%include "documentation.i"

%init %{
import_array();
%}

%apply (double* IN_ARRAY1, int DIM1) {(const double* inputSignal,
                                       const std::size_t x_size)};

%include "hough.h"

/* File: hough.i */
%module hough

%{
#define SWIG_FILE_WITH_INIT
#include "hough.h"
%}

%include std_vector.i
%include std_pair.i
%include "numpy.i"

%init %{
import_array();
%}

%apply (double* IN_ARRAY1, int DIM1) {(const double* inputSignal,
                                       const std::size_t x_size)};

// %apply (double* IN_ARRAY2, int DIM1, int DIM2) {(const double* inputSignal,
//                                        const std::size_t x_size,
//                                        const std::size_t y_size)};
//
// %extend HoughTransformer {
// %rename (transform) transform1D;
// %exception transform1D {
//     $action
//     if (PyErr_Occurred()) SWIG_fail;
// }
// void transform1D(const double* inputSignal, const std::size_t x_size,
//                  const double sig_max=1.)
// {
//     $self->transform(inputSignal, x_size, 1, sig_max);
// }
// }
//
// %ignore HoughTransformer::transform;

%include "hough.h"

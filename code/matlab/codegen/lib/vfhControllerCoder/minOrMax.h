//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// minOrMax.h
//
// Code generation for function 'minOrMax'
//

#ifndef MINORMAX_H
#define MINORMAX_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
double maximum(const double x[2]);

void minimum(const ::coder::array<double, 2U> &x, double ex_data[],
             int *ex_size);

double minimum(const double x_data[], const int x_size[2]);

} // namespace internal
} // namespace coder

#endif
// End of code generation (minOrMax.h)

//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// wrapToPi.h
//
// Code generation for function 'wrapToPi'
//

#ifndef WRAPTOPI_H
#define WRAPTOPI_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace robotics {
namespace internal {
void b_wrapToPi(double theta_data[], int theta_size[2]);

void wrapToPi(double theta_data[], int *theta_size);

} // namespace internal
} // namespace robotics
} // namespace coder

#endif
// End of code generation (wrapToPi.h)

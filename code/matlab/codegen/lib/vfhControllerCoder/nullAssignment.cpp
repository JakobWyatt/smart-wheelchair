//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// nullAssignment.cpp
//
// Code generation for function 'nullAssignment'
//

// Include files
#include "nullAssignment.h"
#include "rt_nonfinite.h"

// Function Definitions
namespace coder {
namespace internal {
void nullAssignment(double x_data[], int *x_size, const boolean_T idx_data[])
{
  int k0;
  int n;
  n = 0;
  k0 = -1;
  for (int k{0}; k < 258; k++) {
    n += idx_data[k];
    if (!idx_data[k]) {
      k0++;
      x_data[k0] = x_data[k];
    }
  }
  if (258 - n < 1) {
    n = -1;
  } else {
    n = 257 - n;
  }
  *x_size = n + 1;
}

} // namespace internal
} // namespace coder

// End of code generation (nullAssignment.cpp)

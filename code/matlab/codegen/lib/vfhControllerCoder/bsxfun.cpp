//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// bsxfun.cpp
//
// Code generation for function 'bsxfun'
//

// Include files
#include "bsxfun.h"
#include "rt_nonfinite.h"

// Function Definitions
namespace coder {
void bsxfun(const double a_data[], int a_size, const double b_data[],
            int b_size, double c_data[], int *c_size)
{
  signed char csz_idx_0;
  if (b_size == 1) {
    csz_idx_0 = static_cast<signed char>(a_size);
  } else if (a_size == 1) {
    csz_idx_0 = static_cast<signed char>(b_size);
  } else if (a_size == b_size) {
    csz_idx_0 = static_cast<signed char>(a_size);
  } else if (b_size < a_size) {
    csz_idx_0 = static_cast<signed char>(b_size);
  } else {
    csz_idx_0 = static_cast<signed char>(a_size);
  }
  if (b_size == 1) {
    *c_size = static_cast<signed char>(a_size);
  } else if (a_size == 1) {
    *c_size = static_cast<signed char>(b_size);
  } else if (a_size == b_size) {
    *c_size = static_cast<signed char>(a_size);
  } else if (b_size < a_size) {
    *c_size = static_cast<signed char>(b_size);
  } else {
    *c_size = static_cast<signed char>(a_size);
  }
  if (csz_idx_0 != 0) {
    int acoef;
    int bcoef;
    int i;
    acoef = (a_size != 1);
    bcoef = (b_size != 1);
    i = csz_idx_0 - 1;
    for (int k{0}; k <= i; k++) {
      c_data[k] = a_data[acoef * k] * b_data[bcoef * k];
    }
  }
}

} // namespace coder

// End of code generation (bsxfun.cpp)

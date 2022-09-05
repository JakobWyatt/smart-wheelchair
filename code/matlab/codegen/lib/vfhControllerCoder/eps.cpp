//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// eps.cpp
//
// Code generation for function 'eps'
//

// Include files
#include "eps.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <math.h>

// Function Definitions
namespace coder {
double eps(double x)
{
  double absx;
  double r;
  int exponent;
  absx = std::abs(x);
  if ((!std::isinf(absx)) && (!std::isnan(absx))) {
    if (absx <= 2.2250738585072014E-308) {
      r = 4.94065645841247E-324;
    } else {
      frexp(absx, &exponent);
      r = std::ldexp(1.0, exponent - 53);
    }
  } else {
    r = rtNaN;
  }
  return r;
}

} // namespace coder

// End of code generation (eps.cpp)

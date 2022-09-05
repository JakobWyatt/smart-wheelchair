//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// angdiff.cpp
//
// Code generation for function 'angdiff'
//

// Include files
#include "angdiff.h"
#include "mod.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions
namespace coder {
namespace robotics {
namespace internal {
double angdiff(double x, double y)
{
  double delta;
  delta = y - x;
  if (std::abs(delta) > 3.1415926535897931) {
    double thetaWrap;
    thetaWrap = ::coder::internal::scalar::b_mod(delta + 3.1415926535897931);
    if ((thetaWrap == 0.0) && (delta + 3.1415926535897931 > 0.0)) {
      thetaWrap = 6.2831853071795862;
    }
    delta = thetaWrap - 3.1415926535897931;
  }
  return delta;
}

} // namespace internal
} // namespace robotics
} // namespace coder

// End of code generation (angdiff.cpp)

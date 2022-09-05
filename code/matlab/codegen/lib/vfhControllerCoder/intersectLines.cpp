//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// intersectLines.cpp
//
// Code generation for function 'intersectLines'
//

// Include files
#include "intersectLines.h"
#include "div.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions
namespace coder {
namespace nav {
namespace algs {
namespace internal {
namespace impl {
void intersectLines(const double line1[4], const double line2[8],
                    double point[4])
{
  double denom_data[2];
  double d;
  double denom_idx_0;
  double dx_idx_0;
  double dx_idx_1;
  double dy_idx_0;
  double dy_idx_1;
  int newline_size[2];
  int b_trueCount;
  int c_size;
  int k;
  int trueCount;
  signed char tmp_data[2];
  boolean_T par[2];
  boolean_T b;
  boolean_T exitg1;
  boolean_T y;
  d = line1[2] * line2[6] - line1[3] * line2[4];
  denom_idx_0 = d;
  b = (std::abs(d) < 1.0E-14);
  par[0] = b;
  y = (std::abs((line2[0] - line1[0]) * line1[3] -
                (line2[2] - line1[1]) * line1[2]) < 1.0E-14);
  dx_idx_0 = 0.0;
  dy_idx_0 = 0.0;
  if (y && b) {
    dx_idx_0 = rtInf;
    dy_idx_0 = rtInf;
  }
  if (b && ((!y) || (!b))) {
    dx_idx_0 = rtNaN;
    dy_idx_0 = rtNaN;
  }
  d = line1[2] * line2[7] - line1[3] * line2[5];
  b = (std::abs(d) < 1.0E-14);
  par[1] = b;
  y = (std::abs((line2[1] - line1[0]) * line1[3] -
                (line2[3] - line1[1]) * line1[2]) < 1.0E-14);
  dx_idx_1 = 0.0;
  dy_idx_1 = 0.0;
  if (y && b) {
    dx_idx_1 = rtInf;
    dy_idx_1 = rtInf;
  }
  if (b && ((!y) || (!b))) {
    dx_idx_1 = rtNaN;
    dy_idx_1 = rtNaN;
  }
  y = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 2)) {
    if (!par[k]) {
      y = false;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (y) {
    point[0] = dx_idx_0;
    point[2] = dy_idx_0;
    point[1] = dx_idx_1;
    point[3] = dy_idx_1;
  } else {
    double newline_data[8];
    double c_data[2];
    double dx2_data[2];
    int acoef;
    int i;
    trueCount = 0;
    if (!par[0]) {
      trueCount = 1;
    }
    if (!b) {
      trueCount++;
    }
    k = 0;
    if (!par[0]) {
      tmp_data[0] = 1;
      k = 1;
    }
    if (!b) {
      tmp_data[k] = 2;
    }
    newline_size[0] = trueCount;
    newline_size[1] = 4;
    for (i = 0; i < 4; i++) {
      for (k = 0; k < trueCount; k++) {
        newline_data[k + trueCount * i] = line2[(tmp_data[k] + (i << 1)) - 1];
      }
    }
    for (i = 0; i < trueCount; i++) {
      dx2_data[i] = newline_data[i + trueCount * 2];
    }
    b_trueCount = 0;
    if (!par[0]) {
      b_trueCount = 1;
    }
    if (!b) {
      b_trueCount++;
    }
    k = 0;
    if (!par[0]) {
      denom_data[0] = denom_idx_0;
      k = 1;
    }
    if (!b) {
      denom_data[k] = d;
    }
    c_size = trueCount;
    if (trueCount != 0) {
      acoef = (trueCount != 1);
      i = trueCount - 1;
      for (k = 0; k <= i; k++) {
        c_data[k] = newline_data[acoef * k + trueCount] - line1[1];
      }
    }
    if (trueCount == b_trueCount) {
      denom_idx_0 = line1[0] * line1[3];
      for (i = 0; i < trueCount; i++) {
        c_data[i] =
            ((newline_data[i] * newline_data[i + trueCount * 3] * line1[2] -
              c_data[i] * line1[2] * newline_data[i + trueCount * 2]) -
             denom_idx_0 * dx2_data[i]) /
            denom_data[i];
      }
    } else {
      binary_expand_op(c_data, &c_size, newline_data, newline_size, &trueCount,
                       line1, dx2_data, &trueCount, denom_data, &b_trueCount);
    }
    k = 0;
    if (!par[0]) {
      dx_idx_0 = c_data[0];
      k = 1;
    }
    if (!b) {
      dx_idx_1 = c_data[k];
    }
    c_size = trueCount;
    if (trueCount != 0) {
      acoef = (trueCount != 1);
      i = trueCount - 1;
      for (k = 0; k <= i; k++) {
        c_data[k] = newline_data[acoef * k] - line1[0];
      }
    }
    if (trueCount == b_trueCount) {
      denom_idx_0 = line1[1] * line1[2];
      for (i = 0; i < trueCount; i++) {
        d = newline_data[i + trueCount * 3];
        c_data[i] = ((c_data[i] * line1[3] * d + denom_idx_0 * d) -
                     newline_data[i + trueCount] * dx2_data[i] * line1[3]) /
                    denom_data[i];
      }
    } else {
      binary_expand_op(c_data, &c_size, line1, newline_data, newline_size,
                       &trueCount, dx2_data, &trueCount, denom_data,
                       &b_trueCount);
    }
    k = 0;
    if (!par[0]) {
      dy_idx_0 = c_data[0];
      k = 1;
    }
    point[0] = dx_idx_0;
    point[2] = dy_idx_0;
    if (!b) {
      dy_idx_1 = c_data[k];
    }
    point[1] = dx_idx_1;
    point[3] = dy_idx_1;
  }
}

} // namespace impl
} // namespace internal
} // namespace algs
} // namespace nav
} // namespace coder

// End of code generation (intersectLines.cpp)

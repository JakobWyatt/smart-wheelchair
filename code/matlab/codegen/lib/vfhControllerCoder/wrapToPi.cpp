//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// wrapToPi.cpp
//
// Code generation for function 'wrapToPi'
//

// Include files
#include "wrapToPi.h"
#include "mod.h"
#include "rt_nonfinite.h"
#include "wrapTo2Pi.h"
#include <cmath>

// Function Definitions
namespace coder {
namespace robotics {
namespace internal {
void b_wrapToPi(double theta_data[], int theta_size[2])
{
  double y_data[273];
  int x_size[2];
  int y_size[2];
  int nx;
  boolean_T x_data[273];
  boolean_T exitg1;
  boolean_T varargout_1;
  nx = theta_size[1];
  y_size[1] = theta_size[1];
  for (int k{0}; k < nx; k++) {
    y_data[k] = std::abs(theta_data[k]);
  }
  x_size[0] = 1;
  x_size[1] = y_size[1];
  nx = y_size[1];
  for (int k{0}; k < nx; k++) {
    x_data[k] = (y_data[k] > 3.1415926535897931);
  }
  varargout_1 = false;
  nx = 1;
  exitg1 = false;
  while ((!exitg1) && (nx <= x_size[1])) {
    if (x_data[nx - 1]) {
      varargout_1 = true;
      exitg1 = true;
    } else {
      nx++;
    }
  }
  if (varargout_1) {
    y_size[0] = 1;
    y_size[1] = theta_size[1];
    nx = theta_size[1];
    for (int k{0}; k < nx; k++) {
      y_data[k] = theta_data[k] + 3.1415926535897931;
    }
    theta_size[0] = 1;
    theta_size[1] = y_size[1];
    nx = y_size[1];
    for (int k{0}; k < nx; k++) {
      theta_data[k] = ::coder::internal::scalar::b_mod(y_data[k]);
    }
    if (theta_size[1] == y_size[1]) {
      x_size[1] = theta_size[1];
      nx = theta_size[1];
      for (int k{0}; k < nx; k++) {
        x_data[k] = ((theta_data[k] == 0.0) && (y_data[k] > 0.0));
      }
    } else {
      g_binary_expand_op(x_data, x_size, theta_data, theta_size, y_data,
                         y_size);
    }
    nx = x_size[1];
    for (int k{0}; k < nx; k++) {
      if (x_data[k]) {
        theta_data[k] = 6.2831853071795862;
      }
    }
    theta_size[0] = 1;
    nx = theta_size[1];
    for (int k{0}; k < nx; k++) {
      theta_data[k] -= 3.1415926535897931;
    }
  }
}

void wrapToPi(double theta_data[], int *theta_size)
{
  double y_data[258];
  int k;
  int tmp_size;
  int y_size;
  boolean_T x_data[273];
  boolean_T tmp_data[258];
  boolean_T exitg1;
  boolean_T varargout_1;
  y_size = *theta_size;
  for (k = 0; k < *theta_size; k++) {
    y_data[k] = std::abs(theta_data[k]);
  }
  for (k = 0; k < y_size; k++) {
    x_data[k] = (y_data[k] > 3.1415926535897931);
  }
  varargout_1 = false;
  k = 1;
  exitg1 = false;
  while ((!exitg1) && (k <= y_size)) {
    if (x_data[k - 1]) {
      varargout_1 = true;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (varargout_1) {
    y_size = *theta_size;
    for (k = 0; k < *theta_size; k++) {
      y_data[k] = theta_data[k] + 3.1415926535897931;
    }
    *theta_size = y_size;
    for (k = 0; k < y_size; k++) {
      theta_data[k] = ::coder::internal::scalar::b_mod(y_data[k]);
    }
    if (*theta_size == y_size) {
      tmp_size = *theta_size;
      for (k = 0; k < *theta_size; k++) {
        tmp_data[k] = ((theta_data[k] == 0.0) && (y_data[k] > 0.0));
      }
    } else {
      f_binary_expand_op(tmp_data, &tmp_size, theta_data, theta_size, y_data,
                         &y_size);
    }
    for (k = 0; k < tmp_size; k++) {
      if (tmp_data[k]) {
        theta_data[k] = 6.2831853071795862;
      }
    }
    for (k = 0; k < *theta_size; k++) {
      theta_data[k] -= 3.1415926535897931;
    }
  }
}

} // namespace internal
} // namespace robotics
} // namespace coder

// End of code generation (wrapToPi.cpp)

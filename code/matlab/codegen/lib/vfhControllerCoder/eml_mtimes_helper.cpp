//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// eml_mtimes_helper.cpp
//
// Code generation for function 'eml_mtimes_helper'
//

// Include files
#include "eml_mtimes_helper.h"
#include "rt_nonfinite.h"
#include <algorithm>

// Function Definitions
void binary_expand_op(double in1_data[], int in1_size[2], double in2,
                      double in3, const double in4_data[],
                      const int in4_size[2], double in5,
                      const double in6_data[], const int in6_size[2],
                      double in7)
{
  double in2_data[273];
  int in2_size_idx_1;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  int stride_2_1;
  if (in6_size[1] == 1) {
    if (in4_size[1] == 1) {
      in2_size_idx_1 = in1_size[1];
    } else {
      in2_size_idx_1 = in4_size[1];
    }
  } else {
    in2_size_idx_1 = in6_size[1];
  }
  stride_0_1 = (in1_size[1] != 1);
  stride_1_1 = (in4_size[1] != 1);
  stride_2_1 = (in6_size[1] != 1);
  if (in6_size[1] == 1) {
    if (in4_size[1] == 1) {
      loop_ub = in1_size[1];
    } else {
      loop_ub = in4_size[1];
    }
  } else {
    loop_ub = in6_size[1];
  }
  for (int i{0}; i < loop_ub; i++) {
    in2_data[i] =
        ((in2 * in1_data[i * stride_0_1] + in3 * in4_data[i * stride_1_1]) +
         in5 * in6_data[i * stride_2_1]) /
        3.0 * in7;
  }
  in1_size[0] = 1;
  in1_size[1] = in2_size_idx_1;
  if (in2_size_idx_1 - 1 >= 0) {
    std::copy(&in2_data[0], &in2_data[in2_size_idx_1], &in1_data[0]);
  }
}

// End of code generation (eml_mtimes_helper.cpp)

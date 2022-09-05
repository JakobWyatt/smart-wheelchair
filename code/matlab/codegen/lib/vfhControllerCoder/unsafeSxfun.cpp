//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// unsafeSxfun.cpp
//
// Code generation for function 'unsafeSxfun'
//

// Include files
#include "unsafeSxfun.h"
#include "rt_nonfinite.h"

// Function Definitions
void binary_expand_op(double in1_data[], int in1_size[2],
                      const double in3_data[], const int in3_size[2])
{
  double b_in3_data[4];
  int in3_size_idx_0;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in1_size[0] == 1) {
    in3_size_idx_0 = in3_size[0];
  } else {
    in3_size_idx_0 = in1_size[0];
  }
  stride_0_0 = (in3_size[0] != 1);
  stride_1_0 = (in1_size[0] != 1);
  if (in1_size[0] == 1) {
    loop_ub = in3_size[0];
  } else {
    loop_ub = in1_size[0];
  }
  for (int i{0}; i < 2; i++) {
    for (int i1{0}; i1 < loop_ub; i1++) {
      b_in3_data[i1 + in3_size_idx_0 * i] =
          in3_data[i1 * stride_0_0 + in3_size[0] * i] -
          in1_data[i1 * stride_1_0 + in1_size[0] * i];
    }
  }
  in1_size[0] = in3_size_idx_0;
  in1_size[1] = 2;
  for (int i{0}; i < 2; i++) {
    for (int i1{0}; i1 < in3_size_idx_0; i1++) {
      double varargin_1;
      varargin_1 = b_in3_data[i1 + in3_size_idx_0 * i];
      in1_data[i1 + in1_size[0] * i] = varargin_1 * varargin_1;
    }
  }
}

// End of code generation (unsafeSxfun.cpp)

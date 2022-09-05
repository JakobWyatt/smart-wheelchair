//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// wrapTo2Pi.cpp
//
// Code generation for function 'wrapTo2Pi'
//

// Include files
#include "wrapTo2Pi.h"
#include "rt_nonfinite.h"

// Function Definitions
void f_binary_expand_op(boolean_T in1_data[], int *in1_size,
                        const double in2_data[], const int *in2_size,
                        const double in3_data[], const int *in3_size)
{
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (*in3_size == 1) {
    *in1_size = *in2_size;
  } else {
    *in1_size = *in3_size;
  }
  stride_0_0 = (*in2_size != 1);
  stride_1_0 = (*in3_size != 1);
  if (*in3_size == 1) {
    loop_ub = *in2_size;
  } else {
    loop_ub = *in3_size;
  }
  for (int i{0}; i < loop_ub; i++) {
    in1_data[i] =
        ((in2_data[i * stride_0_0] == 0.0) && (in3_data[i * stride_1_0] > 0.0));
  }
}

void g_binary_expand_op(boolean_T in1_data[], int in1_size[2],
                        const double in2_data[], const int in2_size[2],
                        const double in3_data[], const int in3_size[2])
{
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  in1_size[0] = 1;
  if (in3_size[1] == 1) {
    in1_size[1] = in2_size[1];
  } else {
    in1_size[1] = in3_size[1];
  }
  stride_0_1 = (in2_size[1] != 1);
  stride_1_1 = (in3_size[1] != 1);
  if (in3_size[1] == 1) {
    loop_ub = in2_size[1];
  } else {
    loop_ub = in3_size[1];
  }
  for (int i{0}; i < loop_ub; i++) {
    in1_data[i] =
        ((in2_data[i * stride_0_1] == 0.0) && (in3_data[i * stride_1_1] > 0.0));
  }
}

// End of code generation (wrapTo2Pi.cpp)

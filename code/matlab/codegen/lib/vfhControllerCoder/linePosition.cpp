//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// linePosition.cpp
//
// Code generation for function 'linePosition'
//

// Include files
#include "linePosition.h"
#include "rt_nonfinite.h"
#include <algorithm>

// Function Definitions
void b_binary_expand_op(double in1_data[], int *in1_size,
                        const double in2_data[], const int *in2_size)
{
  double b_in1_data[2];
  int b_in1_size;
  int stride_0_0;
  int stride_1_0;
  if (*in2_size == 1) {
    b_in1_size = *in1_size;
  } else {
    b_in1_size = *in2_size;
  }
  stride_0_0 = (*in1_size != 1);
  stride_1_0 = (*in2_size != 1);
  if (*in2_size != 1) {
    *in1_size = *in2_size;
  }
  for (int i{0}; i < *in1_size; i++) {
    b_in1_data[i] = in1_data[i * stride_0_0] + in2_data[i * stride_1_0];
  }
  *in1_size = b_in1_size;
  if (b_in1_size - 1 >= 0) {
    std::copy(&b_in1_data[0], &b_in1_data[b_in1_size], &in1_data[0]);
  }
}

// End of code generation (linePosition.cpp)
